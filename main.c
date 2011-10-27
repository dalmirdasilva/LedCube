/**
 * LedCube Project
 * 
 * main.c
 */

#ifndef __PIC_LEDCUBE_MAIN_C
#define __PIC_LEDCUBE_MAIN_C 1

#include <pic18f4550.h>
#include "main.h"
#include "cube.h"
#include "interrupt.h"
#include "launch_effects.c"
#include "fuses.h"

void main() {
    _asm bcf _WDTCON, 0 _endasm;
    
    init_cube();
    init_io();
    init_interrupt();
    
    delay_ms(3000);
    
    while(1) {
        launch_effects();
    }
}

/*
 * Cube initialization
 */
void init_cube() {
    unsigned char i, j, dt;
    dt = 0x55;
    for(i = 0; i < CUBE_SIZE; i++) {
        for(j = 0; j < CUBE_SIZE; j++) {
            if(i % 2 == 0) {
                if(j % 2 == 0) {
                    cube[i][j] = dt;
                } else {
                    cube[i][j] = dt << 1;
                }
            } else {
                cube[i][j] = 0x00;
            }
        }
    }
}

/*
 * IO initialization
 */
void init_io() {
    
    // Set data bus and ctrl bus as output
    TRISB = 0x00;
    TRISE = 0x00;
    TRISD = 0x00;
    
    // Clear add latchs
    LATA = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    // Ser led tris as output
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    
    // Layer select
    TRISAbits.TRISA3 = 0;


    // Set data bus off
    DATA_BUS = 0x00;
}

/*
 * Interrupt initialization
 */
void init_interrupt() {
    
    // Prescalar reg 0
    T0CONbits.T0PS0 = 1;
    
    // Prescalar reg 1
    T0CONbits.T0PS1 = 1;
    
    // Prescalar reg 2, sets up the prescaler to 1:256
    T0CONbits.T0PS2 = 0;
    
    // Enables the prescaler
    T0CONbits.PSA = 0;
    
    // Set the clock source for internal oscillator
    T0CONbits.T0CS = 0;
    
    // Clear the interrupt flag
    INTCONbits.T0IF = 0;
    
    // Enable tmr0 interrupt
    INTCONbits.T0IE = 1;
    
    // Enable Global interrupts
    INTCONbits.GIE = 1;
}

/* 
 * Delay loop.
 * This is not calibrated to milliseconds,
 * Since we have interruptions, we need to calibrate
 */
void delay_ms(uint16_t x) {
    uint8_t y, z;
    for(; x > 0 ; x--){
        for( y = 0 ; y < 40 ; y++){
            for( z = 0 ; z < 7 ; z++){
                __asm nop __endasm;
            }
        }
    }
}

#endif // __PIC_LEDCUBE_MAIN_C
