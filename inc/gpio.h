#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include <sched.h>
#include <sys/mman.h>

void gpio_lamp_ar(uint8_t porta, char input_user);

void config_gpio_proj(char input_user, char equip);

void* gpio_check_status(void* porta);

void gpio_check();



