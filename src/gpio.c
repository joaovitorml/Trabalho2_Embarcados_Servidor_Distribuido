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

#define L1 RPI_V2_GPIO_P1_11
#define L2 RPI_V2_GPIO_P1_12
#define L3 RPI_V2_GPIO_P1_13
#define L4 RPI_V2_GPIO_P1_15
#define A1 RPI_V2_GPIO_P1_16
#define A2 RPI_V2_GPIO_P1_18
#define SP1 RPI_V2_GPIO_P1_22
#define SP2 RPI_V2_GPIO_P1_37
#define SA1 RPI_V2_GPIO_P1_29
#define SA2 RPI_V2_GPIO_P1_31
#define SA3 RPI_V2_GPIO_P1_32
#define SA4 RPI_V2_GPIO_P1_36
#define SA5 RPI_V2_GPIO_P1_38
#define SA6 RPI_V2_GPIO_P1_40

void gpio_lamp_ar(uint8_t porta, char input_user){
    printf("Porta lamp_ar %d\n",porta);
    // Set the pin to be an output
            bcm2835_gpio_fsel(porta, BCM2835_GPIO_FSEL_OUTP);
            if(input_user == '1'){
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

void config_gpio_proj(char input_user, char equip){
   if (!bcm2835_init())
        exit(0);
    switch(equip){
        case '1':
            gpio_lamp_ar(L1,input_user);
            break;
        case '2':
            gpio_lamp_ar(L2,input_user);
            break;
        case '3':
            gpio_lamp_ar(L3,input_user);
            break;
        case '4':
            gpio_lamp_ar(L4,input_user);
            break;
        case '5':
            gpio_lamp_ar(A1,input_user);
            break;
        case '6':
            gpio_lamp_ar(A2,input_user);
            break;
        default:
            break;
    }

}

void* gpio_check_status(void* porta) {
    int porta_escol = (int) porta;
    printf("Porta sensor %d\n", porta_escol);
    // Define a prioridade do programa / thread como máxima 
    const struct sched_param priority = {1};
    sched_setscheduler(0, SCHED_FIFO, &priority);
    // Trava o processo na memória para evitar SWAP
    mlockall(MCL_CURRENT | MCL_FUTURE);
    volatile int i;
    switch(porta_escol){
	    case 1:
   	 	    bcm2835_gpio_fsel(L1, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(L1));
                while (0 == bcm2835_gpio_lev(L1));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(L1)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 2:
   	 	    bcm2835_gpio_fsel(L2, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(L2));
                while (0 == bcm2835_gpio_lev(L2));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(L2)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 3:
   	 	    bcm2835_gpio_fsel(L3, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(L3));
                while (0 == bcm2835_gpio_lev(L3));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(L3)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 4:
   	 	    bcm2835_gpio_fsel(L4, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(L4));
                while (0 == bcm2835_gpio_lev(L4));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(L4)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 5:
   	 	    bcm2835_gpio_fsel(A1, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(A1));
                while (0 == bcm2835_gpio_lev(A1));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(A1)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 6:
   	 	    bcm2835_gpio_fsel(A2, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(A2));
                while (0 == bcm2835_gpio_lev(A2));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(A2)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 7:
   	 	    bcm2835_gpio_fsel(L1, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SP1));
                while (0 == bcm2835_gpio_lev(SP1));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SP1)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 8:
   	 	    bcm2835_gpio_fsel(SP2, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SP2));
                while (0 == bcm2835_gpio_lev(SP2));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SP2)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 9:
   	 	    bcm2835_gpio_fsel(SA1, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SA1));
                while (0 == bcm2835_gpio_lev(SA1));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SA1)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 10:
   	 	    bcm2835_gpio_fsel(SA2, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SA2));
                while (0 == bcm2835_gpio_lev(SA2));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SA2)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 11:
   	 	    bcm2835_gpio_fsel(SA3, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SA3));
                while (0 == bcm2835_gpio_lev(SA3));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SA3)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 12:
   	 	    bcm2835_gpio_fsel(SA4, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SA4));
                while (0 == bcm2835_gpio_lev(SA4));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SA4)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 13:
   	 	    bcm2835_gpio_fsel(SA5, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SA5));
                while (0 == bcm2835_gpio_lev(SA5));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SA5)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        case 14:
   	 	    bcm2835_gpio_fsel(SA6, BCM2835_GPIO_FSEL_INPT);
            while (1) {
                while (1 == bcm2835_gpio_lev(SA6));
                while (0 == bcm2835_gpio_lev(SA6));
                for (i = 0; i < 5000; i++) {
                        if (0 == bcm2835_gpio_lev(SA6)) break;
                }
                if(i>0){
                        printf("Porta %d acionada\n\r", porta_escol);
                }

                fflush(stdout);
            }
        default:
            break;
}
}

void gpio_check(){
    int porta = 1;

    pthread_t thread_id1;
    pthread_create (&thread_id1, NULL, &gpio_check_status, &porta);

    porta = 2;
    pthread_t thread_id2;
    pthread_create (&thread_id2, NULL, &gpio_check_status, &porta);

    porta = 3;
    pthread_t thread_id3;
    pthread_create (&thread_id3, NULL, &gpio_check_status, &porta);

    porta = 4;
    pthread_t thread_id4;
    pthread_create (&thread_id4, NULL, &gpio_check_status, &porta);

    porta = 5;
    pthread_t thread_id5;
    pthread_create (&thread_id5, NULL, &gpio_check_status, &porta);

    porta = 6;
    pthread_t thread_id6;
    pthread_create (&thread_id6, NULL, &gpio_check_status, &porta);

    porta = 7;
    pthread_t thread_id7;
    pthread_create (&thread_id7, NULL, &gpio_check_status, &porta);

    porta = 8;
    pthread_t thread_id8;
    pthread_create (&thread_id8, NULL, &gpio_check_status, &porta);

    porta = 9;
    pthread_t thread_id9;
    pthread_create (&thread_id9, NULL, &gpio_check_status, &porta);

    porta = 10;
    pthread_t thread_id10;
    pthread_create (&thread_id10, NULL, &gpio_check_status, &porta);

    porta = 11;
    pthread_t thread_id11;
    pthread_create (&thread_id11, NULL, &gpio_check_status, &porta);

    porta = 12;
    pthread_t thread_id12;
    pthread_create (&thread_id12, NULL, &gpio_check_status, &porta);

    porta = 13;
    pthread_t thread_id13;
    pthread_create (&thread_id13, NULL, &gpio_check_status, &porta);

    porta = 14;
    pthread_t thread_id14;
    pthread_create (&thread_id14, NULL, &gpio_check_status, &porta);
}
