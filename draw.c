/**
 * LedCube Project
 * 
 * draw.c
 */
 
#ifndef __PIC_LEDCUBE_DRAW_C
#define __PIC_LEDCUBE_DRAW_C 1 

#include <string.h>
#include "draw.h"

/**
 * This function validates that we are drawing inside the cube.
 * 
 * @param   The cube coordinates
 * @return  boolean
 */
uint8_t in_range(int8_t x, int8_t y, int8_t z) {
    if (x >= 0 && x < CUBE_SIZE && y >= 0 && y < CUBE_SIZE && z >= 0 && z < CUBE_SIZE) {
        return 1;
    }
    return 0;
}

/**
 * Returns a byte with a row of 1's drawn in it.
 * e.g.: byte_line(2, 5) gives 0b00111100
 * 
 * @param   The start bit
 * @param   The end bit
 * @return  char 
 */
int8_t byte_line(int8_t start, int8_t end) {
    return ((0xff << start) & ~(0xff << (end + 1)));
}

/**
 * Set a single voxel to ON
 *
 * @param   The cube coordenates
 * @reurn   void 
 */
void set_voxel(int8_t x, int8_t y, int8_t z) {
    if (in_range(x, y, z)) {
        cube[z][y] |= (1 << x);
    }
}

/**
 * Set a single voxel in the temporary cube buffer to ON
 * 
 * @param   The cube coordenates
 * @return  void
 */
void tmp_set_voxel(int8_t x, int8_t y, int8_t z) {
    if (in_range(x, y, z)) {
        fb_cube[z][y] |= (1 << x);
    }
}

/**
 * Set a single voxel to OFF
 * 
 * @param   The cube coordenates
 * @return  void
 */
void clr_voxel(int8_t x, int8_t y, int8_t z) {
    if (in_range(x, y, z)) {
        cube[z][y] &= ~(1 << x);
    }
}

/**
 * Set a single voxel to OFF
 * 
 * @param   The cube coordenates
 * @return  void
 */
void tmp_clr_voxel(int8_t x, int8_t y, int8_t z) {
    if (in_range(x, y, z)) {
        fb_cube[z][y] &= ~(1 << x);
    }
}

/**
 * Get the current status of a voxel
 * 
 * @param   The cube coordenates
 * @return  boolean
 */
uint8_t get_voxel(int8_t x, int8_t y, int8_t z) {
    if (in_range(x, y, z)) {
        if (cube[z][y] & (1 << x)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/**
 * In some effect we want to just take bool and write it to a voxel
 *
 * this function calls the apropriate voxel manipulation function.
 * 
 * @param   The cube coordenates
 * @param   The state of voxel
 * @return  void
 */
void alter_voxel(int8_t x, int8_t y, int8_t z, int state) {
    if (state == 1) {
        set_voxel(x, y, z);
    } else {
        clr_voxel(x, y, z);
    }
}

/**
 * Flip the state of a voxel.
 *
 * If the voxel is 1, its turned into a 0, and vice versa.
 * 
 * @param   The cube coordenates
 * @return  void
 */
void flp_voxel(int8_t x, int8_t y, int8_t z) {
    if (in_range(x, y, z)) {
        cube[z][y] ^= (1 << x);
    }
}

/**
 * Makes sure x1 is alwas smaller than x2
 * 
 * This is usefull for functions that uses for loops,
 * to avoid infinite loops
 * 
 * @param   Arguments and its corrsponding poiters
 * @return  void
 */
void arg_order(int8_t i1, int8_t i2, int8_t *p1, int8_t *p2) {
    if (i1 > i2) {
        int tmp;
        tmp = i1;
        i1 = i2;
        i2 = tmp;
    }
    *p1 = i1;
    *p2 = i2;
}

/**
 * Sets all voxels along a X/Y plane at a given point on axis Z
 * 
 * @param   The point on Z axis
 * @return  void
 */
void set_plane_z(int8_t point) {
    uint8_t i;
    if (point >= 0 && point < CUBE_SIZE) {
        for (i = 0; i < CUBE_SIZE; i++) {
            cube[point][i] = 0xff;
        }
    }
}

/**
 * Clear all voxels along a X/Y plane at a given point on axis Z
 * 
 * @param   The point on Z axis
 * @return  void
 */
void clr_plane_z(int8_t point) {
    uint8_t i;
    if (point >= 0 && point < CUBE_SIZE) {
        for (i = 0; i < CUBE_SIZE; i++) {
            cube[point][i] = 0x00;
        }
    }
}

/**
 * Sets all voxels along a Z/Y plane at a given point on axis X
 * 
 * @param   The point on X axis
 * @return  void
 */
void set_plane_x(int8_t point) {
    uint8_t z, y;
    if (point >= 0 && point < CUBE_SIZE) {
        for (z = 0; z < CUBE_SIZE; z++) {
            for (y = 0; y < CUBE_SIZE; y++) {
                cube[z][y] |= (1 << point);
            }
        }
    }
}

/**
 * Clears all voxels along a Z/Y plane at a given point on axis X
 * 
 * @param   The point on X axis
 * @return  void
 */
void clr_plane_x(int8_t point) {
    uint8_t z, y;
    if (point >= 0 && point < CUBE_SIZE) {
        for (z = 0; z < CUBE_SIZE; z++) {
            for (y = 0; y < CUBE_SIZE; y++) {
                cube[z][y] &= ~(1 << point);
            }
        }
    }
}

/**
 * Sets all voxels along a X/Z plane at a given point on axis Y
 * 
 * @param   The point on Y axis
 * @return  void
 */
void set_plane_y(int8_t point) {
    uint8_t z;
    if (point >= 0 && point < CUBE_SIZE) {
        for (z = 0; z < CUBE_SIZE; z++) {
            cube[z][point] = 0xff;
        }
    }
}

/**
 * Clears all voxels along a X/Z plane at a given point on axis Y
 * 
 * @param   The point on Y axis
 * @return  void
 */
void clr_plane_y(int8_t point) {
    uint8_t z;
    if (point >= 0 && point < CUBE_SIZE) {
        for (z = 0; z < CUBE_SIZE; z++) {
            cube[z][point] = 0x00;
        }
    }
}

/**
 * Sets all voxels along a given plane and point
 * 
 * @param   The axis
 * @param   The point on axis
 * @return  void
 */
void set_plane(char axis, int8_t point) {
    switch (axis) {
        case AXIS_X:
            set_plane_x(point);
            break;

        case AXIS_Y:
            set_plane_y(point);
            break;

        case AXIS_Z:
            set_plane_z(point);
            break;
    }
}

/**
 * Clears all voxels along a given plane and point
 * 
 * @param   The axis
 * @param   The point on axis
 * @return  void
 */
void clr_plane(char axis, int8_t point) {
    switch (axis) {
        case AXIS_X:
            clr_plane_x(point);
            break;

        case AXIS_Y:
            clr_plane_y(point);
            break;

        case AXIS_Z:
            clr_plane_z(point);
            break;
    }
}

/**
 * Fill a value into all 64 byts of the cube buffer
 * 
 * Mostly used for clearing. fill(0x00) or setting all on. fill(0xff)
 * 
 * @param   The pattern
 * @return  void
 */
void fill(uint8_t pattern) {
    uint8_t z, y;
    for (z = 0; z < CUBE_SIZE; z++) {
        for (y = 0; y < CUBE_SIZE; y++) {
            cube[z][y] = pattern;
        }
    }
}

/**
 * Fill a value into all 64 byts of the temp cube buffer
 * 
 * Mostly used for clearing. fill(0x00) or setting all on. fill(0xff)
 * 
 * @param   The pattern
 * @return  void
 */
void fb_fill(uint8_t pattern) {
    uint8_t z, y;
    for (z = 0; z < CUBE_SIZE; z++) {
        for (y = 0; y < CUBE_SIZE; y++) {
            fb_cube[z][y] = pattern;
        }
    }
}

/**
 * Draw a box with all walls drawn and all voxels inside set
 * 
 * @param   Two coordenates on the cube
 * @return  void
 */
void box_filled(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2) {
    int8_t iy, iz;
    arg_order(x1, x2, &x1, &x2);
    arg_order(y1, y2, &y1, &y2);
    arg_order(z1, z2, &z1, &z2);
    for (iz = z1; iz <= z2; iz++) {
        for (iy = y1; iy <= y2; iy++) {
            cube[iz % CUBE_SIZE][iy % CUBE_SIZE] |= byte_line(x1, x2);
        }
    }
}

/**
 * Darw a hollow box with side walls.
 * 
 * @param   Two coordenates on the cube
 * @return  void
 */
void box_walls(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2) {
    int8_t iy, iz;
    arg_order(x1, x2, &x1, &x2);
    arg_order(y1, y2, &y1, &y2);
    arg_order(z1, z2, &z1, &z2);
    for (iz = z1; iz <= z2; iz++) {
        for (iy = y1; iy <= y2; iy++) {
            if (iy == y1 || iy == y2 || iz == z1 || iz == z2) {
                cube[iz % CUBE_SIZE][iy % CUBE_SIZE] = byte_line(x1, x2);
            } else {
                cube[iz % CUBE_SIZE][iy % CUBE_SIZE] |= ((0x01 << x1) | (0x01 << x2));
            }
        }
    }
}

/**
 * Draw a wireframe box. This only draws the corners and edges, no walls.
 *
 * @param   Two coordenates on the cube
 * @return  void
 */
void box_wireframe(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2) {
    int8_t iy, iz;
    arg_order(x1, x2, &x1, &x2);
    arg_order(y1, y2, &y1, &y2);
    arg_order(z1, z2, &z1, &z2);

    // Lines along X axis
    cube[z1][y1] = byte_line(x1, x2);
    cube[z1][y2] = byte_line(x1, x2);
    cube[z2][y1] = byte_line(x1, x2);
    cube[z2][y2] = byte_line(x1, x2);

    // Lines along Y axis
    for (iy = y1; iy <= y2; iy++) {
        set_voxel(x1, iy, z1);
        set_voxel(x1, iy, z2);
        set_voxel(x2, iy, z1);
        set_voxel(x2, iy, z2);
    }

    // Lines along Z axis
    for (iz = z1; iz <= z2; iz++) {
        set_voxel(x1, y1, iz);
        set_voxel(x1, y2, iz);
        set_voxel(x2, y1, iz);
        set_voxel(x2, y2, iz);
    }
}

/**
 * Flips a byte 180 degrees.
 * 
 * MSB becomes LSB, LSB becomes MSB.
 * 
 * @param   A byte to be flipped
 * @return  The flipped byte
 */
char flip_byte(char byte) {
    char flop = 0x00;
    flop = (flop & 0b11111110) | (0b00000001 & (byte >> 7));
    flop = (flop & 0b11111101) | (0b00000010 & (byte >> 5));
    flop = (flop & 0b11111011) | (0b00000100 & (byte >> 3));
    flop = (flop & 0b11110111) | (0b00001000 & (byte >> 1));
    flop = (flop & 0b11101111) | (0b00010000 & (byte << 1));
    flop = (flop & 0b11011111) | (0b00100000 & (byte << 3));
    flop = (flop & 0b10111111) | (0b01000000 & (byte << 5));
    flop = (flop & 0b01111111) | (0b10000000 & (byte << 7));
    return flop;
}

/**
 * Draw a line between any coordinates in 3d space.
 * 
 * Uses integer values for input, so dont expect smooth animations.
 * 
 * @param   Two coordenates on the cube
 * @return  void
 */
void line(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2) {

    // how many voxels do we move on the y axis for each step on the x axis
    float xy;
    float xz;

    int8_t x, y, z;
    int8_t lasty, lastz;

    // We always want to draw the line from x=0 to x=7.
    // If x1 is bigget than x2, we need to flip all the values.
    if (x1 > x2) {
        int tmp;
        tmp = x2;
        x2 = x1;
        x1 = tmp;
        tmp = y2;
        y2 = y1;
        y1 = tmp;
        tmp = z2;
        z2 = z1;
        z1 = tmp;
    }

    if (y1 > y2) {
        xy = (float) (y1 - y2) / (float) (x2 - x1);
        lasty = y2;
    } else {
        xy = (float) (y2 - y1) / (float) (x2 - x1);
        lasty = y1;
    }

    if (z1 > z2) {
        xz = (float) (z1 - z2) / (float) (x2 - x1);
        lastz = z2;
    } else {
        xz = (float) (z2 - z1) / (float) (x2 - x1);
        lastz = z1;
    }

    // For each step of x, y increments by:
    for (x = x1; x <= x2; x++) {
        y = (xy * (x - x1)) + y1;
        z = (xz * (x - x1)) + z1;
        set_voxel(x, y, z);
    }
}

/**
 * Copies the contents of fb (temp cube buffer) into the rendering buffer
 * 
 * @param   void
 * @return  void
 */
void fb_to_cube() {
    memcpy(cube, fb_cube, 64); // copy the current cube into a buffer.
}

/**
 * Shift the entire contents of the cube along an axis
 * 
 * This is great for effects where you want to draw something
 * on one side of the cube and have it flow towards the other
 * side. Like rain flowing down the Z axiz.
 * 
 * @param   The axis
 * @param   The direction of the shift
 * @return  void
 */
void shift(char axis, int8_t direction) {
    uint8_t i, x, y;
    uint8_t ii, iii;
    uint8_t state;

    for (i = 0; i < CUBE_SIZE; i++) {
        if (direction == -1) {
            ii = i;
        } else {
            ii = (7 - i);
        }

        for (x = 0; x < CUBE_SIZE; x++) {
            for (y = 0; y < CUBE_SIZE; y++) {
                if (direction == -1) {
                    iii = ii + 1;
                } else {
                    iii = ii - 1;
                }

                if (axis == AXIS_Z) {
                    state = get_voxel(x, y, iii);
                    alter_voxel(x, y, ii, state);
                }

                if (axis == AXIS_Y) {
                    state = get_voxel(x, iii, y);
                    alter_voxel(x, ii, y, state);
                }

                if (axis == AXIS_X) {
                    state = get_voxel(iii, y, x);
                    alter_voxel(ii, y, x, state);
                }
            }
        }
    }

    if (direction == -1) {
        i = 7;
    } else {
        i = 0;
    }

    for (x = 0; x < CUBE_SIZE; x++) {
        for (y = 0; y < CUBE_SIZE; y++) {
            if (axis == AXIS_Z) {
                clr_voxel(x, y, i);
            }
            if (axis == AXIS_Y) {
                clr_voxel(x, i, y);
            }
            if (axis == AXIS_X) {
                clr_voxel(i, y, x);
            }
        }
    }
}

/**
 * Flips the cube 180 degrees along the y axis.
 * 
 * @param   void
 * @return  void
 */
void mirror_y() {
    uint8_t buffer[CUBE_SIZE][CUBE_SIZE];
    uint8_t x, y, z;
    
    // copy the current cube into a buffer.
    memcpy(buffer, cube, CUBE_BYTES);
    fill(0x00);
    for (z = 0; z < CUBE_SIZE; z++) {
        for (y = 0; y < CUBE_SIZE; y++) {
            for (x = 0; x < CUBE_SIZE; x++) {
                if (buffer[z][y] & (0x01 << x)) {
                    set_voxel(x, CUBE_SIZE - 1 - y, z);
                }
            }
        }
    }
}

/**
 * Flips the cube 180 degrees along the x axis
 * 
 * @param   void
 * @return  void
 */
void mirror_x() {
    uint8_t buffer[CUBE_SIZE][CUBE_SIZE];
    uint8_t y, z;
    
    // copy the current cube into a buffer.
    memcpy(buffer, cube, CUBE_BYTES);
    fill(0x00);
    for (z = 0; z < CUBE_SIZE; z++) {
        for (y = 0; y < CUBE_SIZE; y++) {

            // This will break with different buffer sizes..
            cube[z][y] = flip_byte(buffer[z][y]);
        }
    }
}

/**
 * Flips the cube 180 degrees along the z axis
 * 
 * @param   void
 * @return  void
 */
void mirror_z() {
    uint8_t buffer[CUBE_SIZE][CUBE_SIZE];
    uint8_t z, y;
    
    // copy the current cube into a buffer.
    memcpy(buffer, cube, CUBE_BYTES);
    for (y = 0; y < CUBE_SIZE; y++) {
        for (z = 0; z < CUBE_SIZE; z++) {
            cube[CUBE_SIZE - 1 - z][y] = buffer[z][y];
        }
    }
}

#endif // __PIC_LEDCUBE_DRAW_C
