#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "buttons.h"
#include "menu.h"

int main(void) {
    printk("Hardware Wallet iniciado.\n");
    
    print_menu_options();
    setup_buttons();

    while (1) {
        // Un pequeño retraso para evitar rebotes de botón
        k_sleep(K_MSEC(500));
    }
}
