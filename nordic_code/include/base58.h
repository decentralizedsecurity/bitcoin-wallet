#ifndef BASE58_H
#define BASE58_H

// Función para codificar una cadena hexadecimal a Base58.
void encode_base58(const char *hex, char *output);
void decode_base58(const char* base58, char* output);


#endif //BASE58_H