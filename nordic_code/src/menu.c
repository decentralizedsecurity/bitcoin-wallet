#include "menu.h"
#include "crypto.h"
#include <zephyr/sys/printk.h>

volatile menu_state_t current_state = MENU_MAIN;

void print_menu_options(void) {
    printk("\nOpciones del Menu:\n");
    printk("1. Generar Clave Privada\n");
    printk("2. Generar Clave Publica\n");
    printk("3. Firmar Transaccion\n");
    printk("4. Salir\n");
    printk("Navega con el boton 0, selecciona con el boton 1.\n\n");
}

void button_0_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    // Cambiar al siguiente estado del menú
    if (current_state == MENU_EXIT - 1) {
        current_state = MENU_EXIT;
    } else if (current_state == MENU_EXIT) {
        current_state = MENU_MAIN;
    } else {
        current_state = (current_state + 1) % MENU_EXIT;
    }

    // Mostrar el estado actual del menú
    switch (current_state) {
        case MENU_MAIN:
            printk("Menu Principal.\n");
            break;
        case MENU_GENERATE_PRIVATE_KEY:
            printk("Generar Clave Privada.\n");
            break;
        case MENU_GENERATE_PUBLIC_KEY:
            printk("Generar Clave Publica.\n");
            break;
        case MENU_SIGN_TRANSACTION:
            printk("Firmar Transaccion.\n");
            break;
        case MENU_EXIT:
            printk("Salir.\n");
            break;
        default:
            printk("Estado desconocido.\n");
            break;
    }
}

void button_1_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    switch (current_state) {
        case MENU_MAIN:
            printk("Menu Principal.\n");
            break;
        case MENU_GENERATE_PRIVATE_KEY:
            printk("Seleccionado: Generar Clave Privada\n");
            // Implementar la funcionalidad aquí
            break;
        case MENU_GENERATE_PUBLIC_KEY:
            printk("Seleccionado: Generar Clave Publica\n");
            // Implementar la funcionalidad aquí
            break;
        case MENU_SIGN_TRANSACTION:
            printk("Seleccionado: Firmar Transaccion\n");
            // Implementar la funcionalidad aquí
            break;
        case MENU_EXIT:
            printk("Seleccionado: Salir\n");
            // Implementar la funcionalidad para salir aquí
            break;
        default:
            break;
    }
}
