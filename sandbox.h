#include <stdint.h>

char str_fly[][5] = {
    {0xff,0x9,0x9,0x9,0x1},
    {0x1,0x1,0xff,0x1,0x1},
    {0xff,0x89,0x89,0x89,0x81},
    {0x7e,0x81,0x81,0x81,0x81}
};

uint8_t cube[8][8];

void print_cube(int layers, int latchs, int bits);
void send_char2(char *char_data);
void shift_cube(uint8_t iterations);
void effect_str_fly();

char byteline(int start, int end) {
    return ((0xff << start) & ~(0xff << (end + 1)));
}

void setvoxel(int x, int y, int z) {
    cube[z][y] |= (1 << x);
}

void clrvoxel(int x, int y, int z) {
    cube[z][y] &= ~(1 << x);
}
