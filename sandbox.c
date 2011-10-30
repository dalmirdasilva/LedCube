#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sandbox.h"

void main() {
    send_char2(str_fly[0]);
    
    print_cube(8, 8, 8);
    shift_cube(8);
}

void send_char2(char *char_data) {
    int8_t l, byte_index;
    for(l = 7; l >= 0; l--) {
        for(byte_index = 4; byte_index >= 0; byte_index--) {
            if(char_data[byte_index] & (1 << (7 - l))) {
                set_voxel(2 + byte_index, 0, l);
            } else {
                clr_voxel(2 + byte_index, 0, l);
            }
        }
    }
}

void shift_cube(uint8_t iterations) {
    int8_t it, lat, lay;
    for(it = 0; it < iterations; it++) {
        for(lay = 0; lay < 8; lay++) {
            for(lat = 0; lat < 7; lat++) {
                cube[lay][lat + 1] = cube[lay][lat];
            }
            cube[lay][0] = 0x00;
        }
        printf("\n=================\n");
        print_cube(8, 8, 8);
    }
}

void effect_str_fly() {
    uint8_t i;
    for(i = 0; i < 4; i++) {
        send_char2(str_fly[i]);
        shift_cube(8);
    }    
}

void print_cube(int layers, int latchs, int bits) {
    int x, y, z;
    for(x = 0; x < layers; x++) {
        printf("\n");
        for(y = 0; y < latchs; y++) {
            printf("\n");
            for(z = 0; z < bits; z++) {
                printf("%c ", (cube[x][y] & (1 << z)) ? '*' : '-');
            }
        }
    }
}
