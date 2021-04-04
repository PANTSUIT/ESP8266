#ifndef _GPIO_H
#define _GPIO_H

#include "driver/gpio.h"

void gpio_init( uint8_t pin_num, 
                gpio_mode_t mode,
                gpio_pullup_t pull_up_en,
                gpio_pulldown_t pull_down_en,
                gpio_int_type_t intr_type);


#endif /* _GPIO_H */

