#include "generateAddress.h"
#include "base58.h"
#include "hex_bytes.h"
#include <zephyr/kernel.h>
#include <stdlib.h>
#include <string.h>
#include "psa/crypto.h"

char* P2PKH_address(const char* public_key_hash_hex, int network) {
    unsigned char address[25];  // Address buffer
    char* output = malloc(50);  // Output buffer for the final Base58 address
    if (!output) {
        printk("Memory allocation failed\n");
        return NULL;
    }

    unsigned char public_key_hash[20];
    hex_to_bytes(public_key_hash_hex, public_key_hash, sizeof(public_key_hash));
    address[0] = (network == 0) ? 0x00 : 0x6f;  // Prefix: Mainnet or Testnet
    memcpy(address + 1, public_key_hash, 20);   // Public key hash

    // First SHA-256 hash
    psa_status_t status;
    psa_hash_operation_t hash_op = psa_hash_operation_init();
    unsigned char hash[PSA_HASH_MAX_SIZE]; // Temporary buffer for hashes

    status = psa_hash_setup(&hash_op, PSA_ALG_SHA_256);
    if (status != PSA_SUCCESS) {
        printk("Failed to setup hash operation\n");
        free(output);
        return NULL;
    }

    status = psa_hash_update(&hash_op, address, 21);
    if (status != PSA_SUCCESS) {
        printk("Failed to update hash\n");
        psa_hash_abort(&hash_op);
        free(output);
        return NULL;
    }

    size_t hash_length;
    status = psa_hash_finish(&hash_op, hash, sizeof(hash), &hash_length);
    if (status != PSA_SUCCESS) {
        printk("Failed to finish hash\n");
        psa_hash_abort(&hash_op);
        free(output);
        return NULL;
    }

    // Second SHA-256 hash
    status = psa_hash_setup(&hash_op, PSA_ALG_SHA_256);
    if (status != PSA_SUCCESS) {
        printk("Failed to setup hash operation for second hash\n");
        free(output);
        return NULL;
    }

    status = psa_hash_update(&hash_op, hash, hash_length);
    if (status != PSA_SUCCESS) {
        printk("Failed to update second hash\n");
        psa_hash_abort(&hash_op);
        free(output);
        return NULL;
    }

    status = psa_hash_finish(&hash_op, hash, sizeof(hash), &hash_length);
    if (status != PSA_SUCCESS) {
        printk("Failed to finish second hash\n");
        psa_hash_abort(&hash_op);
        free(output);
        return NULL;
    }

    // Append first four bytes of the second hash as checksum
    memcpy(address + 21, hash, 4);

    // Convert binary address to hex string
    char* hex = bytes_to_hex(address, 25);

    // Encode address to Base58
    encode_base58(hex, output);  // Assuming encode_base58 is modified to accept hex string directly
    free(hex);

    return output;
}
