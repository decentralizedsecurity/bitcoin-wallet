#include "privateKey.h"
#include <stdio.h>
#include <string.h>
#include "base58.h"
#include "psa/crypto.h"

/**
 * Convierte un array de bytes en hexadecimal
 * @param hash Array de bytes
 * @param size Tamaño del array
 * @return Cadena de caracteres con la representación hexadecimal
*/
char* to_hexadecimal(unsigned char* hash, size_t size) {
    char* output = (char*)malloc((size * 2) + 1);
    if (!output) return NULL;
    for (size_t i = 0; i < size; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[size * 2] = '\0';
    return output;
}

/**
 * Genera una clave privada aleatoria
 * @return Clave privada en formato hexadecimal
*/
char* generate_private_key() {
    unsigned char bytes[32];
    psa_status_t status;

    // Inicializar el sistema criptográfico de PSA
    psa_crypto_init();

    // Generar bytes aleatorios
    status = psa_generate_random(bytes, sizeof(bytes));
    if (status != PSA_SUCCESS) {
        perror("Failed to generate random bytes");
        return NULL;
    }

    char *private_key = to_hexadecimal(bytes, sizeof(bytes));
    return private_key;
}

/***
 * Convierte una clave privada en hexadecimal a una clave privada en formato WIF
 * @param hex_priv_key Clave privada en hexadecimal
 * @param mainnet 0 para testnet, 1 para mainnet
 * @return Clave privada en formato WIF o NULL si falla la conversión
*/
char* convert_private_key_to_wif(const char* hex_priv_key, int mainnet) {
    char extended_key[69];

    if(mainnet == 0)
        sprintf(extended_key, "80%s01", hex_priv_key); // 80 + clave privada + 01 (para indicar la red mainnet y la compresion activada)
    else
        sprintf(extended_key, "ef%s01", hex_priv_key); // ef + clave privada + 01 (para indicar la red testnet y la compresion activada)
   
    size_t len = (strlen(extended_key) / 2);
    unsigned char* extended_key_bytes = malloc(len);
    if (!extended_key_bytes) return NULL;
    for (size_t i = 0; i < len; i++) {
        sscanf(extended_key + 2 * i, "%2hhx", &extended_key_bytes[i]);
    }

    // Realizar doble SHA-256 sobre la clave extendida
    unsigned char hash[PSA_HASH_MAX_SIZE];  // Usar PSA_HASH_MAX_SIZE para soportar el tamaño máximo de hash.
    size_t hash_length;

    psa_hash_operation_t hash_op = psa_hash_operation_init(); // Inicializar la operación de hash
    psa_hash_setup(&hash_op, PSA_ALG_SHA_256);
    psa_hash_update(&hash_op, extended_key_bytes, len);
    psa_hash_finish(&hash_op, hash, sizeof(hash), &hash_length);

    // Segundo hash
    psa_hash_operation_t hash_op2 = psa_hash_operation_init();
    psa_hash_setup(&hash_op2, PSA_ALG_SHA_256);
    psa_hash_update(&hash_op2, hash, hash_length);
    psa_hash_finish(&hash_op2, hash, sizeof(hash), &hash_length);

    unsigned char checksum[4];
    memcpy(checksum, hash, 4);

    unsigned char* final_key = malloc(len + 4);
    if (!final_key) {
        free(extended_key_bytes);
        return NULL;
    }
    memcpy(final_key, extended_key_bytes, len);
    memcpy(final_key + len, checksum, 4);

    char* wif_private_key = malloc(512);
    if (!wif_private_key) {
        free(extended_key_bytes);
        free(final_key);
        return NULL;
    }
    encode_base58(to_hexadecimal(final_key, len + 4), wif_private_key);

    free(extended_key_bytes);
    free(final_key);
    return wif_private_key;
}
