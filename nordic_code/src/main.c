#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdio.h>
#include <stdlib.h>
#include "privateKey.h"
#include "publicKey.h"
#include "hex_bytes.h"

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
        printk("Hex Public Key: %s\n", public_key_hex);
        free(public_key_hex);
    } else {
        printk("Failed to generate public key\n");
    }

    free(private_key);
    free(wif);

    return 0;
}
