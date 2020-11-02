// Código adaptado do Livro: Raspberry Pi And The IoT In C
// Autor: Harry Fairhead
// Disponível em: https://www.iot-programmer.com/index.php/books/22-raspberry-pi-and-the-iot-in-c/chapters-raspberry-pi-and-the-iot-in-c/55-raspberry-pi-and-the-iot-in-c-input-and-interrupts?start=1
// 
#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include <sched.h>
#include <sys/mman.h>
#include <pthread.h>

#define RPI_V2_GPIO_P1_11 L1
#define RPI_V2_GPIO_P1_12 L2
#define RPI_V2_GPIO_P1_13 L3
#define RPI_V2_GPIO_P1_15 L4
#define RPI_V2_GPIO_P1_16 A1
#define RPI_V2_GPIO_P1_18 A2
#define RPI_V2_GPIO_P1_22 SP1
#define RPI_V2_GPIO_P1_37 SP2
#define RPI_V2_GPIO_P1_29 SA1
#define RPI_V2_GPIO_P1_31 SA2
#define RPI_V2_GPIO_P1_32 SA3
#define RPI_V2_GPIO_P1_36 SA4
#define RPI_V2_GPIO_P1_38 SA5
#define RPI_V2_GPIO_P1_40 SA6

void gpio_lamp_ar(int porta, int input_user){
    printf("Porta lamp_ar %d\n",porta);
    // Set the pin to be an output
            bcm2835_gpio_fsel(porta, BCM2835_GPIO_FSEL_OUTP);
            if(input_user){
                bcm2835_gpio_write(porta, LOW);
                printf("liga porta %d", porta);
                delay(2);
            }
            else{
                bcm2835_gpio_write(porta, HIGH);
                printf("desliga porta %d", porta);
                delay(2);
            }
}

void config_gpio_proj(int input_user, int equip){
   if (!bcm2835_init())
        exit(0);
    switch(equip){
        case 1:
            gpio_lamp_ar(L1,input_user);
            break;
        case 2:
            gpio_lamp_ar(L2,input_user);
            break;
        case 3:
            gpio_lamp_ar(L3,input_user);
            break;
        case 4:
            gpio_lamp_ar(L4,input_user);
            break;
        case 5:
            gpio_lamp_ar(A1,input_user);
            break;
        case 6:
            gpio_lamp_ar(A2,input_user);
            break;
        default:
            break;
    }

}

void* gpio_check_status(void* porta) {
    uint8_t * porta_escol = (uint8_t *) porta;
    printf("Porta sensor %d\n", porta_escol);
    // Define a prioridade do programa / thread como máxima 
    const struct sched_param priority = {1};
    sched_setscheduler(0, SCHED_FIFO, &priority);
    // Trava o processo na memória para evitar SWAP
    mlockall(MCL_CURRENT | MCL_FUTURE);
    
    bcm2835_gpio_fsel(porta, BCM2835_GPIO_FSEL_INPT);

    volatile int i;
    while (1) {
        while (1 == bcm2835_gpio_lev(porta_escol));
        while (0 == bcm2835_gpio_lev(porta_escol));
        for (i = 0; i < 5000; i++) {
            if (0 == bcm2835_gpio_lev(porta_escol)) break;
        }
        if(i>0){
            printf("Porta %d acionada\n\r", porta_escol);
        }

        fflush(stdout);
    }
}

void gpio_check(){

    pthread_t thread_id1;
    pthread_create (&thread_id1, NULL, &gpio_check_status, &L1);

    pthread_t thread_id2;
    pthread_create (&thread_id2, NULL, &gpio_check_status, &L2);

    pthread_t thread_id3;
    pthread_create (&thread_id3, NULL, &gpio_check_status, &L3);

    pthread_t thread_id4;
    pthread_create (&thread_id4, NULL, &gpio_check_status, &L4);

    pthread_t thread_id5;
    pthread_create (&thread_id5, NULL, &gpio_check_status, &A1);

    pthread_t thread_id6;
    pthread_create (&thread_id6, NULL, &gpio_check_status, &A2);

    pthread_t thread_id7;
    pthread_create (&thread_id7, NULL, &gpio_check_status, &SP1);

    pthread_t thread_id8;
    pthread_create (&thread_id8, NULL, &gpio_check_status, &SP2);

    pthread_t thread_id9;
    pthread_create (&thread_id9, NULL, &gpio_check_status, &SA1);

    pthread_t thread_id10;
    pthread_create (&thread_id10, NULL, &gpio_check_status, &SA2);

    pthread_t thread_id11;
    pthread_create (&thread_id11, NULL, &gpio_check_status, &SA3);

    pthread_t thread_id12;
    pthread_create (&thread_id12, NULL, &gpio_check_status, &SA4);

    pthread_t thread_id13;
    pthread_create (&thread_id13, NULL, &gpio_check_status, &SA5);

    pthread_t thread_id14;
    pthread_create (&thread_id14, NULL, &gpio_check_status, &SA6);
}
