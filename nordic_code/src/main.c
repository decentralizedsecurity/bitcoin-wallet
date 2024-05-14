#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdio.h>
#include <stdlib.h>
#include "privateKey.h"
#include "pk2hash.h"
#include "publicKey.h"
#include "hex_bytes.h"
#include "generateAddress.h"
#include "psa/crypto.h"
#include "psa/protected_storage.h"

#define PRIVATE_KEY_ID 0x01  // Identificador único para la clave privada

int main() {
    printk("Iniciando...\n");
    psa_status_t status;
    char private_key[129]; // espacio para 64 bytes en hexadecimal + '\0'
    memset(private_key, 0, sizeof(private_key)); // inicializar a 0 para asegurar que esté terminado en NULL

    status = psa_crypto_init();
    if (status != PSA_SUCCESS) {
        printk("Failed to initialize PSA Crypto\n");
        return 1;
    }

    size_t data_length;
    // Intentar recuperar la clave privada
    size_t private_key_len = sizeof(private_key);
    status = psa_ps_get(PRIVATE_KEY_ID, 0, private_key_len, private_key, &data_length);
    if (status != PSA_SUCCESS) {
        printk("La clave privada no existe\n Iniciando generacion de clave privada...\n");
        // Clave no existe, generar una nueva
        char* generated_key = generate_private_key();
        if (!generated_key) {
            printk("Failed to generate private key\n");
            return 1;
        }

        memcpy(private_key, generated_key, private_key_len);
        free(generated_key); // Libera la clave generada después de copiarla
        // Almacenar la nueva clave privada
        status = psa_ps_set(PRIVATE_KEY_ID, private_key_len, private_key, PSA_STORAGE_FLAG_WRITE_ONCE);
        if (status != PSA_SUCCESS) {
            printk("Failed to store private key\n");
            return 1;
        }
        printk("Clave privada generada y almacenada\n");
    }else{
        printk("Clave privada recuperada\n");
        
        printk("Clave Privada: %s\n", private_key);

        char* wif = convert_private_key_to_wif(private_key, 1);
        if (!wif) {
            printk("Failed to convert private key to WIF\n");
            return 1;
        }

        printk("Clave Privada WIF: %s\n", wif);

        unsigned char public_key[33]; // Tamaño correcto para clave pública comprimida
        size_t public_key_len = sizeof(public_key);
        
        if (generate_public_key_from_hex(private_key, public_key, &public_key_len)) {
            char* public_key_hex = bytes_to_hex(public_key, public_key_len);
            printk("[COMPRESSED] Hex Public Key: %s\n", public_key_hex);

            char* hash160 = malloc(41); // 20 bytes en hexadecimal
            publicKeytoHash(public_key_hex, hash160);
            printk("Public Key Hash: %s\n", hash160);

            char* address = P2PKH_address(hash160, 1);
            if (address) {
                printk("Direccion P2PKH: %s\n", address);
                free(address);
            } else {
                printk("Error al generar la dirección P2PKH.\n");
            }

            free(public_key_hex);
            free(hash160);
        } else {
            printk("Failed to generate public key\n");
        }

        free(wif);
    }
    
    return 0;
}
