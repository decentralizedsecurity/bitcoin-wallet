#ifndef MENU_H
#define MENU_H

#include <zephyr/types.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

// Estados del menú
typedef enum {
    MENU_MAIN,
    MENU_GENERATE_PRIVATE_KEY,
    MENU_GENERATE_PUBLIC_KEY,
    MENU_SIGN_TRANSACTION,
    MENU_EXIT
} menu_state_t;

void print_menu_options(void);
void button_0_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void button_1_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
void handle_menu_action(void);

#endif // MENU_H
