#include "hex_bytes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Funcion auxiliar para convertir un carácter hexadecimal a un entero
 * @param c Carácter hexadecimal
 * @return Entero correspondiente al carácter hexadecimal o -1 si es inválido
 */
static int hex_char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1; // Indicador de error
}

/** Función para convertir una cadena hexadecimal a bytes
 * @param hex Cadena hexadecimal
 * @param bytes Arreglo de bytes para almacenar el resultado
 * @param bytes_len Longitud del arreglo de bytes
 * @return 1 si la conversión fue exitosa, 0 si falló
*/
int hex_to_bytes(const char *hex, unsigned char *bytes, size_t bytes_len) {
    size_t hex_len = strlen(hex);
    if (hex_len % 2 != 0) {
        // La longitud de la cadena hexadecimal debe ser par
        return 0;
    }

    size_t expected_bytes_len = hex_len / 2;
    if (bytes_len < expected_bytes_len) {
        // El arreglo de bytes proporcionado no es lo suficientemente grande
        return 0;
    }

    for (size_t i = 0, j = 0; i < hex_len; i += 2, j++) {
        int high = hex_char_to_int(hex[i]);
        int low = hex_char_to_int(hex[i + 1]);
        if (high == -1 || low == -1) {
            // Carácter no válido encontrado
            return 0;
        }
        bytes[j] = (unsigned char)((high << 4) | low);
    }

    return 1; // Éxito
}

/** Función para convertir bytes a una cadena hexadecimal
 * @param bytes Bytes a convertir
 * @param len Longitud del array de bytes
 * @return Cadena de caracteres con la representación hexadecimal
*/
char* bytes_to_hex(const unsigned char* bytes, size_t len) {
    char* hex_str = (char*)malloc(len * 2 + 1); // Cada byte se convierte en 2 caracteres hexadecimales
    if (!hex_str) return NULL;
    for (size_t i = 0; i < len; i++) {
        sprintf(hex_str + i * 2, "%02x", bytes[i]);
    }
    hex_str[len * 2] = '\0'; // Asegurarse de terminar la cadena
    return hex_str;
}
