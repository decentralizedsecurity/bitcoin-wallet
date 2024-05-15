#include "publicKey.h"
#include <stdio.h>
#include "psa/crypto.h"
#include "hex_bytes.h"
#include <string.h>

/**
 * @brief Comprime una clave pública no comprimida.
 * @param uncompressed_key Clave pública no comprimida debe ser un array de 65 bytes (0x04, x, y).
 * @param compressed_key Buffer para almacenar la clave pública comprimida.
 */
void compress_pubkey(const unsigned char *uncompressed_key, unsigned char *compressed_key) {
    // Asumiendo que uncompressed_key es un array de 65 bytes (0x04, x, y)
    int y_parity = uncompressed_key[64] & 1; // Obtenemos la paridad de y (último byte)
    compressed_key[0] = y_parity ? 0x03 : 0x02; // Prefijo dependiendo de la paridad, 0x03 para y impar y 0x02 para y par 
    memcpy(&compressed_key[1], &uncompressed_key[1], 32); // Copiamos la coordenada x
}

/**
 * @brief Genera una clave pública a partir de una clave privada en formato hexadecimal.
 * @param private_key_hex Clave privada en formato hexadecimal.
 * @param public_key Buffer para almacenar la clave pública.
 * @param public_key_len Longitud de la clave pública.
 * @return 1 si la operación fue exitosa, 0 en caso contrario.
 */
int generate_public_key_from_hex(const char *private_key_hex, unsigned char *public_key, size_t *public_key_len) {
    psa_status_t status;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    unsigned char private_key[32];
    if (!hex_to_bytes(private_key_hex, private_key, sizeof(private_key))) {
        fprintf(stderr, "Error al convertir la clave privada hex a bytes\n");
        return 0;
    }

    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH);
    psa_set_key_algorithm(&attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
    psa_set_key_type(&attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1));

    psa_key_handle_t key_handle;
    status = psa_import_key(&attributes, private_key, sizeof(private_key), &key_handle);
    if (status != PSA_SUCCESS) {
        fprintf(stderr, "Error al importar la clave privada: %d\n", status);
        return 0;
    }

    unsigned char uncompressed_key[65];  // Asume el tamaño máximo para una clave pública sin comprimir
    size_t uncompressed_length = sizeof(uncompressed_key);
    status = psa_export_public_key(key_handle, uncompressed_key, uncompressed_length, &uncompressed_length);
    if (status != PSA_SUCCESS) {
        fprintf(stderr, "Error al exportar la clave pública sin comprimir: %d\n", status);
        psa_destroy_key(key_handle);
        return 0;
    }

    compress_pubkey(uncompressed_key, public_key);
    *public_key_len = 33;  // Tamaño fijo para claves públicas comprimidas secp256k1

    psa_destroy_key(key_handle);
    return 1; // Éxito
}
