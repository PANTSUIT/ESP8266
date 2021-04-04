
#include <stdio.h>
#include "xgpio.h"

void gpio_init( uint8_t pin_num, 
                gpio_mode_t mode,
                gpio_pullup_t pull_up_en,
                gpio_pulldown_t pull_down_en,
                gpio_int_type_t intr_type)
{
    gpio_config_t io_conf;

    printf("Init Pin: %#x\n", pin_num);

    io_conf.pin_bit_mask = (0x01 << pin_num);
    io_conf.mode = mode;
    io_conf.pull_up_en = pull_up_en;
    io_conf.pull_down_en = pull_down_en;
    io_conf.intr_type = intr_type;
    if(gpio_config(&io_conf) == ESP_FAIL)
    {
        printf("GPIO Init Failed\n");
    }
    printf("GPIO Init Succeed\n");
}
