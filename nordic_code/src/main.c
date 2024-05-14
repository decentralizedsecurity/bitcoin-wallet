#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdio.h>
#include <stdlib.h>
#include "privateKey.h"
#include "publicKey.h"
#include "hex_bytes.h"
#include "generateAddress.h"
#include "pk2hash.h"

int main() {
    char* private_key = generate_private_key();
    if (!private_key) {
        printk("Failed to generate private key\n");
        return 1;
    }

    printk("Clave Privada: %s\n", private_key);

    char* wif = convert_private_key_to_wif(private_key, 1);
    if (!wif) {
        printk("Failed to convert private key to WIF\n");
        free(private_key);
        return 1;
    }

    printk("Clave Privada WIF: %s\n", wif);

    unsigned char public_key[33]; // Tamaño correcto para clave pública comprimida
    size_t public_key_len = sizeof(public_key);
    if (generate_public_key_from_hex(private_key, public_key, &public_key_len)) {
        char* public_key_hex = bytes_to_hex(public_key, public_key_len);
        printk("[COMPRESSED] Hex Public Key: %s\n", public_key_hex);
        char* hash160 = malloc(41); // 20 bytes en hexadecimal
        publicKeytoHash(public_key_hex, hash160); // Hace mal la conversión (devuelve otro valor)
        printk("Public Key Hash: %s\n", hash160); 

        char* address = P2PKH_address(hash160, 1);
        if (address) {
                printk("Direccion P2PKH: %s\n", address);
                free((char*)address); // Asegúrate de liberar la memoria
            } else {
                printk("Error al generar la dirección P2PKH.\n");
            }

        free(public_key_hex);
        free(hash160);
    } else {
        printk("Failed to generate public key\n");
    }

    free(private_key);
    free(wif);

    

    return 0;
}
