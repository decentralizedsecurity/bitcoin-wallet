#include "buttons.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include "menu.h" // Para usar los callbacks de los botones

static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw0), gpios, {0});
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw1), gpios, {0});
static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;

void setup_buttons(void) {
    if (!device_is_ready(button0.port) || !device_is_ready(button1.port)) {
        printk("Error: botón no está listo.\n");
        return;
    }

    // Configurar el botón 0
    gpio_pin_configure_dt(&button0, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&button0_cb_data, button_0_callback, BIT(button0.pin));
    gpio_add_callback(button0.port, &button0_cb_data);

    // Configurar el botón 1
    gpio_pin_configure_dt(&button1, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&button1_cb_data, button_1_callback, BIT(button1.pin));
    gpio_add_callback(button1.port, &button1_cb_data);
}
