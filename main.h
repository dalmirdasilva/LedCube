/**
 * LedCube Project
 * 
 * main.h
 */

#ifndef __PIC_LEDCUBE_MAIN_H
#define __PIC_LEDCUBE_MAIN_H 1 

#include <stdint.h>

// Address definitions
#define LATA_LOCATION       0xF89
#define LATB_LOCATION       0xF8A
#define LATC_LOCATION       0xF8B
#define LATD_LOCATION       0xF8C

// Bus definitions
#define DATA_BUS            LATB
#define LATCH_SELECT_PORT   LATD
#define LAYER_SELECT_PORT   LATE

#define LAYER_ENABLE_PIN    LATAbits.LATA3

#define TRIS_DATA_BUS       TRISB
#define TRIS_LAYER          TRISE
#define TRIS_LATCH          TRISD

// Led definitions
#define LED0                LATAbits.LATA0
#define LED1                LATAbits.LATA1
#define LED2                LATAbits.LATA2

// Convenient definitions
#define HIGH                1
#define LOW                 0
#define ON                  1
#define OFF                 0
#define LATCH_CP_LOW        0
#define LATCH_CP_HIGH       1
#define LATCH_OE_ENABLE     0
#define LATCH_OE_DISABLE    1
#define LAYER_OE_DISABLE    0
#define LAYER_OE_ENABLE     1

void init_cube();
void init_io();
void init_interrupt();
void delay_ms(uint16_t x);

#endif // __PIC_LEDCUBE_MAIN_H
