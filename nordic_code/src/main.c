#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <psa/crypto.h>
#include <psa/crypto_extra.h>
#include "buttons.h"
#include "menu.h"
#include "crypto.h"

int main(void) {
    printk("INICIANDO HARDWARE WALLET\n");

    // Inicializar el sistema criptográfico
    crypto_init();
    printk("Sistema criptografico inicializado.\n");

    // Generar un nuevo par de claves secp256k1
    if (generate_ecdsa_keypair() == 0) {
        printk("Par de claves generado exitosamente.\n");
    } else {
        printk("Error generando el par de claves.\n");
    }

    // Aquí podrías añadir más lógica, como exportar la clave pública, firmar un mensaje, etc.

    // Limpiar y finalizar el sistema criptográfico
    crypto_finish();
    printk("Sistema criptografico finalizado.\n");
    /*
    print_menu_options();
    setup_buttons();

    while (1) {
        // Un pequeño retraso para evitar rebotes de botón
        k_sleep(K_MSEC(500));
    }

    */
}
