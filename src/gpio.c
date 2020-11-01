// Código adaptado do Livro: Raspberry Pi And The IoT In C
// Autor: Harry Fairhead
// Disponível em: https://www.iot-programmer.com/index.php/books/22-raspberry-pi-and-the-iot-in-c/chapters-raspberry-pi-and-the-iot-in-c/55-raspberry-pi-and-the-iot-in-c-input-and-interrupts?start=1
// 
#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include <sched.h>
#include <sys/mman.h>

#define L1 RPI_V2_GPIO_P1_17
#define L2 RPI_V2_GPIO_P1_18
#define L3 RPI_V2_GPIO_P1_27
#define L4 RPI_V2_GPIO_P1_22
#define A1 RPI_V2_GPIO_P1_23
#define A2 RPI_V2_GPIO_P1_24
#define SP1 RPI_V2_GPIO_P1_25
#define SP2 RPI_V2_GPIO_P1_26
#define SA1 RPI_V2_GPIO_P1_05
#define SA2 RPI_V2_GPIO_P1_06
#define SA3 RPI_V2_GPIO_P1_12
#define SA4 RPI_V2_GPIO_P1_16
#define SA5 RPI_V2_GPIO_P1_20
#define SA6 RPI_V2_GPIO_P1_21


void config_gpio_proj(){
   if (!bcm2835_init())
        exit();	
    gpio_lamp_ar(L1);
    gpio_lamp_ar(L2);
    gpio_lamp_ar(L3);
    gpio_lamp_ar(L4);
    gpio_lamp_ar(A1);
    gpio_lamp_ar(A2);
    gpio_sensores(SP1);
    gpio_sensores(SP2);
    gpio_sensores(SA1);
    gpio_sensores(SA2);
    gpio_sensores(SA3);
    gpio_sensores(SA4);
    gpio_sensores(SA5);
    gpio_sensores(SA6);
}

void gpio_lamp_ar(char porta, int input_user){
    // Set the pin to be an output
            bcm2835_gpio_fsel(porta, BCM2835_GPIO_FSEL_OUTP);

            if(input_user){
                bcm2835_gpio_write(porta, LOW);
                printf("liga porta %c", porta);
                delay(2);
            }
            else{
                bcm2835_gpio_write(porta, HIGH);
                printf("desliga porta %c", porta);
                delay(2);
            }
}

void gpio_sensores(char porta) {

    // Define a prioridade do programa / thread como máxima 
    const struct sched_param priority = {1};
    sched_setscheduler(0, SCHED_FIFO, &priority);
    // Trava o processo na memória para evitar SWAP
    mlockall(MCL_CURRENT | MCL_FUTURE);
    
    bcm2835_gpio_fsel(porta, BCM2835_GPIO_FSEL_INPT);

    volatile int i;
    while (1) {
        while (1 == bcm2835_gpio_lev(porta));
        while (0 == bcm2835_gpio_lev(porta));
        for (i = 0; i < 5000; i++) {
            if (0 == bcm2835_gpio_lev(porta)) break;
        }
        if(i>0){
            printf("Porta %c acionada\n\r", porta);
        }

        fflush(stdout);
    }
}
