#include "base58.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char BASE58_CHARS[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

/**
 * Codifica una cadena hexadecimal a Base58.
 * @param hex Cadena hexadecimal.
 * @param output Buffer para almacenar la cadena Base58.
 */
void encode_base58(const char *hex, char *output) {
    int values[256]; // Mapeo de caracteres hexadecimales a valores enteros.
    for (int i = 0; i < 256; i++) {
        values[i] = -1;
    }
    for (int i = '0'; i <= '9'; i++) {
        values[i] = i - '0';
    }
    for (int i = 'A'; i <= 'F'; i++) {
        values[i] = i - 'A' + 10;
    }
    for (int i = 'a'; i <= 'f'; i++) {
        values[i] = i - 'a' + 10;
    }

    unsigned char *bin = malloc(strlen(hex) / 2);
    size_t bin_size = 0;
    for (size_t i = 0; hex[i] && hex[i+1]; i += 2) {
        bin[bin_size++] = values[hex[i]] * 16 + values[hex[i+1]];
    }

    // Convertir el número binario a Base58.
    int digits[40] = {0}; // Suponer que el número base58 resultante tiene menos de 40 dígitos.
    int num_digits = 0;
    for (size_t i = 0; i < bin_size; i++) {
        int carry = bin[i];
        for (int j = 0; j < num_digits; j++) {
            carry += digits[j] << 8;
            digits[j] = carry % 58;
            carry /= 58;
        }
        while (carry > 0) {
            digits[num_digits++] = carry % 58;
            carry /= 58;
        }
    }

    // Convertir dígitos en caracteres Base58.
    for (int i = 0; i < num_digits; i++) {
        output[num_digits - i - 1] = BASE58_CHARS[digits[i]];
    }
    output[num_digits] = '\0';

    free(bin);
}

/**
 * Decodifica una cadena Base58 a hexadecimal.
 * @param base58 Cadena Base58.
 * @param output Buffer para almacenar la cadena hexadecimal.
 */
void decode_base58(const char* base58, char* output) {
    int values[256]; // Mapeo de caracteres Base58 a valores enteros.
    for (int i = 0; i < 256; i++) {
        values[i] = -1;
    }
    for (int i = 0; BASE58_CHARS[i]; i++) {
        values[(int)BASE58_CHARS[i]] = i;
    }

    unsigned char *bin = calloc(strlen(base58), sizeof(char));
    size_t bin_size = 0;

    for (size_t i = 0; i < strlen(base58); i++) {
        int value = values[(int)base58[i]];
        if (value == -1) {
            fprintf(stderr, "Invalid Base58 character: %c\n", base58[i]);
            free(bin);
            return; // Terminar con error si hay un carácter inválido.
        }
        int carry = value;
        for (size_t j = 0; j < bin_size; j++) {
            carry += bin[j] * 58;
            bin[j] = carry % 256;
            carry /= 256;
        }
        while (carry > 0) {
            bin[bin_size++] = carry % 256;
            carry /= 256;
        }
    }

    // Convertir el número binario a hexadecimal.
    for (int i = 0; i < bin_size; i++) {
        sprintf(output + 2*i, "%02x", bin[bin_size - i - 1]);
    }
    output[2 * bin_size] = '\0'; // Terminar la cadena.

    free(bin);
}