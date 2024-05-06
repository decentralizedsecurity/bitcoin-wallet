#include <stdio.h>
#include <stdlib.h>
#include "privateKey.h"

int main() {
	char* private_key = generate_private_key();
	if (!private_key) {
		perror("Failed to generate private key");
		return 1;
	}

	printk("Clave Privada: %s\n", private_key);

	char* wif = convert_private_key_to_wif(private_key, 1); // 1 para testnet, 0 para mainnet
	if (!wif) {
		perror("Failed to convert private key to WIF");
		return 1;
	}

	printk("Clave Privada WIF: %s\n", wif);

	free(private_key);
	free(wif);

	return 0;
}