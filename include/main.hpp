#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <SPI.h>
#include <Wire.h>

#include <TFT_eSPI.h>

#include <lvgl.h>

#include "driver/uart.h"

#include "uart_processes.hpp"

#include "user_defines.h"


#define BAUD_RATE 115200
#define SERIAL_PORT_NR UART_NUM_0
#define BUF_SIZE (1024*2)
#define RD_BUF_SIZE (1024)


