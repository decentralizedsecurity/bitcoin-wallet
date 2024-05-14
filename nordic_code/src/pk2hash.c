#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "psa/crypto.h"
#include "hex_bytes.h"
#include "pk2hash.h"
#include "ripemd160.h" // Incluir la cabecera de RIPEMD-160

void publicKeytoHash(char* data, char *output) {
    psa_status_t status;
    unsigned char sha256_digest[PSA_HASH_MAX_SIZE];
    unsigned char ripemd160_digest[20];  // RIPEMD-160 produce un hash de 20 bytes

    // Inicializar el sistema criptográfico de PSA (si aún no está inicializado)
    status = psa_crypto_init();
    if (status != PSA_SUCCESS) {
        printf("Failed to initialize PSA Crypto\n");
        return;
    }

    // Convertir la data hexadecimal a bytes
    size_t data_len = strlen(data) / 2;
    unsigned char *data_bytes = malloc(data_len);
    if (!data_bytes) {
        printf("Failed to allocate memory\n");
        return;
    }
    for (size_t i = 0; i < data_len; i++) {
        sscanf(&data[i * 2], "%2hhx", &data_bytes[i]);
    }

    // Realizar SHA-256
    psa_hash_operation_t hash_op = psa_hash_operation_init();
    status = psa_hash_setup(&hash_op, PSA_ALG_SHA_256);
    if (status != PSA_SUCCESS) {
        printf("Failed to setup SHA-256 hash operation\n");
        free(data_bytes);
        return;
    }
    status = psa_hash_update(&hash_op, data_bytes, data_len);
    if (status != PSA_SUCCESS) {
        printf("Failed to update SHA-256 hash operation\n");
        free(data_bytes);
        psa_hash_abort(&hash_op);
        return;
    }
    size_t output_length;
    status = psa_hash_finish(&hash_op, sha256_digest, sizeof(sha256_digest), &output_length);
    if (status != PSA_SUCCESS) {
        printf("Failed to finalize SHA-256 hash operation\n");
        free(data_bytes);
        return;
    }

    free(data_bytes);

    // Realizar RIPEMD-160
    ripemd160(sha256_digest, sizeof(sha256_digest), ripemd160_digest); 

    // Convertir el digest de RIPEMD-160 a hexadecimal
    for (int i = 0; i < 20; i++) {
        sprintf(&output[i * 2], "%02x", ripemd160_digest[i]);
    }

}
