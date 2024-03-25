#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <psa/crypto.h>
#include <psa/crypto_extra.h>
#include "buttons.h"
#include "menu.h"
#include "crypto.h"

int main(void) {

   int status;

	printk("Starting ECDSA example...");

	status = crypto_init();
	if (status != APP_SUCCESS) {
		printk(APP_ERROR_MESSAGE);
		return APP_ERROR;
	}

	status = generate_ecdsa_keypair();
	if (status != APP_SUCCESS) {
		printk(APP_ERROR_MESSAGE);
		return APP_ERROR;
	}

	status = import_ecdsa_pub_key();
	if (status != APP_SUCCESS) {
		printk(APP_ERROR_MESSAGE);
		return APP_ERROR;
	}

	status = sign_message();
	if (status != APP_SUCCESS) {
		printk(APP_ERROR_MESSAGE);
		return APP_ERROR;
	}

	status = verify_message();
	if (status != APP_SUCCESS) {
		printk(APP_ERROR_MESSAGE);
		return APP_ERROR;
	}

	status = crypto_finish();
	if (status != APP_SUCCESS) {
		printk(APP_ERROR_MESSAGE);
		return APP_ERROR;
	}

	printk(APP_SUCCESS_MESSAGE);

	return APP_SUCCESS;
    
}
