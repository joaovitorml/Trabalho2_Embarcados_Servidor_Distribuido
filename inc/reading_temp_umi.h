#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>          //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>

#include "servidor_tcp.h"

float valores[2];

int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev);