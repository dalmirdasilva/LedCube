/**
 * LedCube Project
 * 
 * effects.c
 */

#ifndef __PIC_LEDCUBE_EFFECTS_C
#define __PIC_LEDCUBE_EFFECTS_C 1 

#include "effects.h"
#include <math.h>
#include <stdlib.h>

#if EFFECT_TEST == 1
void effect_test(void) {
    uint8_t i, j, k;
    fill(0x00);
	for(j = 0; j < 8; j++) {
		cube[0][j] |= 0xff;
		delay_ms(1000);
	}
    for(i = 0; i < 8; i++) {
		cube[i][0] = 0xff;
		delay_ms(1000);
    }
    for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			cube[i][j] |= 0x01;
		}
		delay_ms(1000);
    }
    for(i = 0; i < 8; i++) {
		cube[i][7] = 0xff;
		delay_ms(1000);
    }
    for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			cube[i][j] |= 0x80;
		}
		delay_ms(1000);
    }
	for(j = 0; j < 8; j++) {
		cube[7][j] |= 0xff;
		delay_ms(1000);
	}
}
#endif

// Draw a plane on one axis and send it back and forth once.
#if EFFECT_PLANBOING == 1
void effect_planboing(int plane, int speed) {
    int i;
    for (i = 0; i < 8; i++) {
        fill(0x00);
        setplane(plane, i);
        delay_ms(speed);
    }

    for (i = 7; i >= 0; i--) {
        fill(0x00);
        setplane(plane, i);
        delay_ms(speed);
    }
}
#endif

#if EFFECT_BLINKY == 1
void effect_blinky2() {
    int i, r;
    fill(0x00);
    for (r = 0; r < 4; r++) {
        i = 750;
        while (i > 0) {
            fill(0x00);
            delay_ms(i);
            fill(0xff);
            delay_ms(100);
            i = i - (15 + (1000 / (i / 10)));
        }
        delay_ms(3000);
        i = 750;
        while (i > 0) {
            fill(0x00);
            delay_ms(751 - i);
            fill(0xff);
            delay_ms(100);
            i = i - (15 + (1000 / (i / 10)));
        }
    }
}
#endif

#if EFFECT_BOX_SHRING_GROW == 1
void effect_box_shrink_grow(int iterations, int rot, int flip, uint16_t delay) {
    int x, i, xyz;
    for (x = 0; x < iterations; x++) {
        for (i = 0; i < 16; i++) {
            xyz = 7 - i; // This reverses counter i between 0 and 7.
            if (i > 7) {
                xyz = i - 8; // at i > 7, i 8-15 becomes xyz 0-7.
            }
            fill(0x00);
            delay_ms(1);

            // disable interrupts while the cube is being rotated
            INTCONbits.GIE = 0;

            box_wireframe(0, 0, 0, xyz, xyz, xyz);

            // upside-down
            if (flip > 0) {
                mirror_z();
            }
            if (rot == 1 || rot == 3) {
                mirror_y();
            }
            if (rot == 2 || rot == 3) {
                mirror_x();
            }

            // enable interrupts
            INTCONbits.GIE = 1;
            delay_ms(delay);
            fill(0x00);
        }
    }
}
#endif

// Creates a wireframe box that shrinks or grows out from the center of the cube.
#if EFFECT_BOX_WOOPWOOP == 1
void effect_box_woopwoop(int delay, int grow) {
    int i, ii;
    fill(0x00);
    for (i = 0; i < 4; i++) {
        ii = i;
        if (grow > 0) {
            ii = 3 - i;
        }
        box_wireframe(4 + ii, 4 + ii, 4 + ii, 3 - ii, 3 - ii, 3 - ii);
        delay_ms(delay);
        fill(0x00);
    }
}
#endif

// Send a voxel flying from one side of the cube to the other
// If its at the bottom, send it to the top..
#if EFFECT_SENDPLANE_RZ == 1 || EFFECT_SENDVOXELS_RZ == 1
void sendvoxel_z(unsigned char x, unsigned char y, unsigned char z, int delay) {
    int i, ii;
    for (i = 0; i < 8; i++) {
        if (z == 7) {
            ii = 7 - i;
            clrvoxel(x, y, ii + 1);
        } else {
            ii = i;
            clrvoxel(x, y, ii - 1);
        }
        setvoxel(x, y, ii);
        delay_ms(delay);
    }
}
#endif

// Send all the voxels from one side of the cube to the other
// Start at z and send to the opposite side.
// Sends in random order.
#if EFFECT_SENDPLANE_RZ == 1
void effect_sendplane_rand_z(unsigned char z, int delay, int wait) {
    unsigned char loop = 16;
    unsigned char x, y;
    fill(0x00);
    setplane_z(z);
    
    // Send voxels at random untill all 16 have crossed the cube.
    while (loop) {
        x = rand() % 4;
        y = rand() % 4;
        if (getvoxel(x, y, z)) {
    
            // Send the voxel flying
            sendvoxel_z(x, y, z, delay);
            delay_ms(wait);
            
            // one down, loop-- to go. when this hits 0, the loop exits.
            loop--;
        }
    }
}
#endif

// For each coordinate along X and Y, a voxel is set either at level 0 or at level 7
// for n iterations, a random voxel is sent to the opposite side of where it was.
#if EFFECT_SENDVOXELS_RZ == 1
void effect_sendvoxels_rand_z(int iterations, int delay, int wait) {
    unsigned char x, y, last_x = 0, last_y = 0, i;
    fill(0x00);
    
    // Loop through all the X and Y coordinates
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
    
            // Then set a voxel either at the top or at the bottom
            // rand()%2 returns either 0 or 1. multiplying by 7 gives either 0 or 7.
            setvoxel(x, y, ((rand() % 2)*7));
        }
    }

    for (i = 0; i < iterations; i++) {
        
        // Pick a random x,y position
        x = rand() % 8;
        y = rand() % 8;
        
        // but not the sameone twice in a row
        if (y != last_y && x != last_x) {
        
            // If the voxel at this x,y is at the bottom
            if (getvoxel(x, y, 0)) {
        
                // send it to the top
                sendvoxel_z(x, y, 0, delay);
            } else {
        
                // if its at the top, send it to the bottom
                sendvoxel_z(x, y, 7, delay);
            }
            delay_ms(wait);

            // Remember the last move
            last_y = y;
            last_x = x;
        }
    }

}
#endif

// Big ugly function :p but it looks pretty
#if EFFECT_BOINGBOING == 1
void effect_boingboing(uint16_t iterations, int delay, unsigned char mode, unsigned char drawmode) {
    
    // Current coordinates for the point
    int x, y, z; 
    
    // Direction of movement
    int dx, dy, dz; 
    
    // lol?
    int lol, i; 
    unsigned char crash_x, crash_y, crash_z;

    // Coordinate array for the snake.
    int snake[8][3];

    // Blank the cube
    fill(0x00);
    
    y = rand() % 8;
    x = rand() % 8;
    z = rand() % 8;
    
    for (i = 0; i < 8; i++) {
        snake[i][0] = x;
        snake[i][1] = y;
        snake[i][2] = z;
    }
    dx = 1;
    dy = 1;
    dz = 1;
    while (iterations) {
        crash_x = 0;
        crash_y = 0;
        crash_z = 0;

        // Let's mix things up a little:
        if (rand() % 3 == 0) {
          
            // Pick a random axis, and set the speed to a random number.
            lol = rand() % 3;
            if (lol == 0) {
                dx = rand() % 3 - 1;
            }
            if (lol == 1) {
                dy = rand() % 3 - 1;
            }
            if (lol == 2) {
                dz = rand() % 3 - 1;
            }
        }

        // The point has reached 0 on the x-axis and is trying to go to -1
        // aka a crash
        if (dx == -1 && x == 0) {
            crash_x = 0x01;
            if (rand() % 3 == 1) {
                dx = 1;
            } else {
                dx = 0;
            }
        }

        // y axis 0 crash
        if (dy == -1 && y == 0) {
            crash_y = 0x01;
            if (rand() % 3 == 1) {
                dy = 1;
            } else {
                dy = 0;
            }
        }

        // z axis 0 crash
        if (dz == -1 && z == 0) {
            crash_z = 0x01;
            if (rand() % 3 == 1) {
                dz = 1;
            } else {
                dz = 0;
            }
        }

        // x axis 7 crash
        if (dx == 1 && x == 7) {
            crash_x = 0x01;
            if (rand() % 3 == 1) {
                dx = -1;
            } else {
                dx = 0;
            }
        }

        // y axis 7 crash
        if (dy == 1 && y == 7) {
            crash_y = 0x01;
            if (rand() % 3 == 1) {
                dy = -1;
            } else {
                dy = 0;
            }
        }

        // z azis 7 crash
        if (dz == 1 && z == 7) {
            crash_z = 0x01;
            if (rand() % 3 == 1) {
                dz = -1;
            } else {
                dz = 0;
            }
        }

        // mode bit 0 sets crash action enable
        if (mode | 0x01) {
            if (crash_x) {
                if (dy == 0) {
                    if (y == 7) {
                        dy = -1;
                    } else if (y == 0) {
                        dy = +1;
                    } else {
                        if (rand() % 2 == 0) {
                            dy = -1;
                        } else {
                            dy = 1;
                        }
                    }
                }
                if (dz == 0) {
                    if (z == 7) {
                        dz = -1;
                    } else if (z == 0) {
                        dz = 1;
                    } else {
                        if (rand() % 2 == 0) {
                            dz = -1;
                        } else {
                            dz = 1;
                        }
                    }
                }
            }

            if (crash_y) {
                if (dx == 0) {
                    if (x == 7) {
                        dx = -1;
                    } else if (x == 0) {
                        dx = 1;
                    } else {
                        if (rand() % 2 == 0) {
                            dx = -1;
                        } else {
                            dx = 1;
                        }
                    }
                }
                if (dz == 0) {
                    if (z == 3) {
                        dz = -1;
                    } else if (z == 0) {
                        dz = 1;
                    } else {
                        if (rand() % 2 == 0) {
                            dz = -1;
                        } else {
                            dz = 1;
                        }
                    }
                }
            }

            if (crash_z) {
                if (dy == 0) {
                    if (y == 7) {
                        dy = -1;
                    } else if (y == 0) {
                        dy = 1;
                    } else {
                        if (rand() % 2 == 0) {
                            dy = -1;
                        } else {
                            dy = 1;
                        }
                    }
                }
                if (dx == 0) {
                    if (x == 7) {
                        dx = -1;
                    } else if (x == 0) {
                        dx = 1;
                    } else {
                        if (rand() % 2 == 0) {
                            dx = -1;
                        } else {
                            dx = 1;
                        }
                    }
                }
            }
        }

        // mode bit 1 sets corner avoid enable
        if (mode | 0x02) {
          
            // We are in one of 8 corner positions
            if (
                    (x == 0 && y == 0 && z == 0) ||
                    (x == 0 && y == 0 && z == 7) ||
                    (x == 0 && y == 7 && z == 0) ||
                    (x == 0 && y == 7 && z == 7) ||
                    (x == 7 && y == 0 && z == 0) ||
                    (x == 7 && y == 0 && z == 7) ||
                    (x == 7 && y == 7 && z == 0) ||
                    (x == 7 && y == 7 && z == 7)
                    ) {
                // At this point, the voxel would bounce
                // back and forth between this corner,
                // and the exact opposite corner
                // We don't want that!

                // So we alter the trajectory a bit,
                // to avoid corner stickyness
                lol = rand() % 3;
                if (lol == 0) {
                    dx = 0;
                }
                if (lol == 1) {
                    dy = 0;
                }
                if (lol == 2) {
                    dz = 0;
                }
            }
        }

        // one last sanity check
        if (x == 0 && dx == -1) {
            dx = 1;
        }

        if (y == 0 && dy == -1) {
            dy = 1;
        }

        if (z == 0 && dz == -1) {
            dz = 1;
        }

        if (x == 7 && dx == 1) {
            dx = -1;
        }

        if (y == 7 && dy == 1) {
            dy = -1;
        }

        if (z == 7 && dz == 1) {
            dz = -1;
        }


        // Finally, move the voxel.
        x = x + dx;
        y = y + dy;
        z = z + dz;

        // show one voxel at time
        if (drawmode == 0x01) {
            setvoxel(x, y, z);
            delay_ms(delay);
            clrvoxel(x, y, z);
            
        // flip the voxel in question
        } else if (drawmode == 0x02) {
            flpvoxel(x, y, z);
            delay_ms(delay);
        }
        
        // draw a snake
        if (drawmode == 0x03) {
            for (i = 7; i >= 0; i--) {
                snake[i][0] = snake[i - 1][0];
                snake[i][1] = snake[i - 1][1];
                snake[i][2] = snake[i - 1][2];
            }
            snake[0][0] = x;
            snake[0][1] = y;
            snake[0][2] = z;
            for (i = 0; i < 8; i++) {
                setvoxel(snake[i][0], snake[i][1], snake[i][2]);
            }
            delay_ms(delay);
            for (i = 0; i < 8; i++) {
                clrvoxel(snake[i][0], snake[i][1], snake[i][2]);
            }
        }
        iterations--;
    }
}
#endif

// Set or clear exactly 512 voxels in a random order.
#if EFFECT_RANDOM_FILTER == 1
void effect_random_filler(int delay, int state) {
    int x, y, z;
    int loop = 0;

    if (state == 1) {
        fill(0x00);
    } else {
        fill(0xff);
    }

    while (loop < 511) {
        x = rand() % 8;
        y = rand() % 8;
        z = rand() % 8;
        if ((state == 0 && getvoxel(x, y, z) == 0x01) || (state == 1 && getvoxel(x, y, z) == 0x00)) {
            altervoxel(x, y, z, state);
            delay_ms(delay);
            loop++;
        }
    }
}
#endif

#if EFFECT_RAIN == 1
void effect_rain(int iterations) {
    int i, ii;
    int rnd_x;
    int rnd_y;
    int rnd_num;
    for (ii = 0; ii < iterations; ii++) {
        rnd_num = rand() % 4;
        for (i = 0; i < rnd_num; i++) {
            rnd_x = rand() % 8;
            rnd_y = rand() % 8;
            setvoxel(rnd_x, rnd_y, 7);
        }
        delay_ms(1000);
        shift(AXIS_Z, -1);
    }
}
#endif

#if EFFECT_Z_UPDOWN == 1
void effect_z_updown(int iterations, int delay) {
    unsigned char positions[64];
    unsigned char destinations[64];
    int i, y, move;
    for (i = 0; i < 64; i++) {
        positions[i] = 4;
        destinations[i] = rand() % 8;
    }
    for (i = 0; i < 8; i++) {
        z_updown_move(positions, destinations, AXIS_Z);
        delay_ms(delay);
    }
    for (i = 0; i < iterations; i++) {
        for (move = 0; move < 8; move++) {
            z_updown_move(positions, destinations, AXIS_Z);
            delay_ms(delay);
        }
        delay_ms(delay * 4);
        for (y = 0; y < 32; y++) {
            destinations[rand() % 64] = rand() % 8;
        }
    }
}
void z_updown_move(unsigned char positions[64], unsigned char destinations[64], char axis) {
    int px;
    for (px = 0; px < 64; px++) {
        if (positions[px] < destinations[px]) {
            positions[px]++;
        }
        if (positions[px] > destinations[px]) {
            positions[px]--;
        }
    }
    draw_positions_axis(axis, positions, 0);
}
#endif

#if EFFECT_AXIS_UPDOWN_RSUSPEND == 1
void effect_axis_updown_randsuspend(char axis, int delay, int sleep, int invert) {
    unsigned char positions[64];
    unsigned char destinations[64];
    int i, px;
    
    // Set 64 random positions
    for (i = 0; i < 64; i++) {
      
        // Set all starting positions to 0
        positions[i] = 0;
        destinations[i] = rand() % 8;
    }

    // Loop 8 times to allow destination 7 to reach all the way
    for (i = 0; i < 8; i++) {
      
        // For every iteration, move all position one step closer to their destination
        for (px = 0; px < 64; px++) {
            if (positions[px] < destinations[px]) {
                positions[px]++;
            }
        }
      
        // Draw the positions and take a nap
        draw_positions_axis(axis, positions, invert);
        delay_ms(delay);
    }

    // Set all destinations to 7(opposite from the side they started out)
    for (i = 0; i < 64; i++) {
        destinations[i] = 7;
    }

    // Suspend the positions in mid-air for a while
    delay_ms(sleep);

    // Then do the same thing one more time
    for (i = 0; i < 8; i++) {
        for (px = 0; px < 64; px++) {
            if (positions[px] < destinations[px]) {
                positions[px]++;
            }
            if (positions[px] > destinations[px]) {
                positions[px]--;
            }
        }
        draw_positions_axis(axis, positions, invert);
        delay_ms(delay);
    }
}
#endif

void draw_positions_axis(char axis, unsigned char positions[64], int invert) {
    int x, y, p;
    fill(0x00);
    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            if (invert) {
                p = (7 - positions[(x * 8) + y]);
            } else {
                p = positions[(x * 8) + y];
            }
            if (axis == AXIS_Z) {
                setvoxel(x, y, p);
            }
            if (axis == AXIS_Y) {
                setvoxel(x, p, y);
            }
            if (axis == AXIS_X) {
                setvoxel(p, y, x);
            }
        }
    }
}

#if EFFECT_BOXSIDE_RAND_SEND == 1
void effect_boxside_randsend_parallel(char axis, int origin, int delay, int mode) {
    int i;
    int done;
    unsigned char cubepos[64];
    unsigned char pos[64];
    int notdone = 1;
    int notdone2 = 1;
    int sent = 0;

    for (i = 0; i < 64; i++) {
        pos[i] = 0;
    }

    while (notdone) {
        if (mode == 1) {
            notdone2 = 1;
            while (notdone2 && sent < 64) {
                i = rand() % 64;
                if (pos[i] == 0) {
                    sent++;
                    pos[i] += 1;
                    notdone2 = 0;
                }
            }
        } else if (mode == 2) {
            if (sent < 64) {
                pos[sent] += 1;
                sent++;
            }
        }
        done = 0;
        for (i = 0; i < 64; i++) {
            if (pos[i] > 0 && pos[i] < 7) {
                pos[i] += 1;
            }

            if (pos[i] == 7) {
                done++;
            }
        }
        if (done == 64) {
            notdone = 0;
        }
        for (i = 0; i < 64; i++) {
            if (origin == 0) {
                cubepos[i] = pos[i];
            } else {
                cubepos[i] = (7 - pos[i]);
            }
        }
        delay_ms(delay);
        draw_positions_axis(axis, cubepos, 0);
    }
}
#endif

// Light all leds layer by layer,
// then unset layer by layer
#if EFFECT_LOADBAR == 1
void effect_loadbar(int delay) {
    int z, y;
    fill(0x00);
    for (z = 0; z < 8; z++) {
        for (y = 0; y < 8; y++) {
            cube[z][y] = 0xff;
        }
        delay_ms(delay);
    }
    delay_ms(delay * 3);
    for (z = 0; z < 8; z++) {
        for (y = 0; y < 8; y++) {
            cube[z][y] = 0x00;
        }
        delay_ms(delay);
    }
}
#endif

// Set n number of voxels at random positions
#if EFFECT_SPARKLE == 1
void effect_random_sparkle_flash(int iterations, int voxels, int delay) {
    int i;
    int v;
    for (i = 0; i < iterations; i++) {
        for (v = 0; v <= voxels; v++) {
            setvoxel(rand() % CUBE_SIZE, rand() % CUBE_SIZE, rand() % CUBE_SIZE);
        }
        delay_ms(delay);
        fill(0x00);
    }
}

// blink 1 random voxel, blink 2 random voxels..... blink 20 random voxels
// and back to 1 again.
void effect_random_sparkle(void) {
    int i;
    for (i = 1; i < 20; i++) {
        effect_random_sparkle_flash(5, i, 200);
    }
    for (i = 20; i >= 1; i--) {
        effect_random_sparkle_flash(5, i, 200);
    }
}
#endif

#if EFFECT_TELKSTAIRS == 1
int effect_telcstairs_do(int x, int val, int delay) {
    int y, z;
    for (y = 0, z = x; y <= z; y++, x--) {
        if (x < CUBE_SIZE && y < CUBE_SIZE) {
            cube[x % CUBE_SIZE][y % CUBE_SIZE] = val;
        }
    }
    delay_ms(delay);
    return z;
}

void effect_telcstairs(int invert, int delay, int val) {
    int x;
    if (invert) {
        for (x = CUBE_SIZE * 2; x >= 0; x--) {
            x = effect_telcstairs_do(x, val, delay);
        }
    } else {
        for (x = 0; x < CUBE_SIZE * 2; x++) {
            x = effect_telcstairs_do(x, val, delay);
        }
    }
}
#endif

#if EFFECT_WORMSQUEEZE == 1
void effect_wormsqueeze(int size, int axis, int direction, int iterations, int delay) {
    int x, y, i, j, k, dx, dy;
    int cube_size;
    int origin = 0;
    if (direction == -1) {
        origin = 7;
    }
    cube_size = 8 - (size - 1);
    x = rand() % cube_size;
    y = rand() % cube_size;
    for (i = 0; i < iterations; i++) {
        dx = ((rand() % 3) - 1);
        dy = ((rand() % 3) - 1);
        if ((x + dx) > 0 && (x + dx) < cube_size) {
            x += dx;
        }
        if ((y + dy) > 0 && (y + dy) < cube_size) {
            y += dy;
        }
        shift(axis, direction);
        for (j = 0; j < size; j++) {
            for (k = 0; k < size; k++) {
                if (axis == AXIS_Z) {
                    setvoxel(x + j, y + k, origin);
                }
                if (axis == AXIS_Y) {
                    setvoxel(x + j, origin, y + k);
                }
                if (axis == AXIS_X) {
                    setvoxel(origin, y + j, x + k);
                }
            } 
        }
        delay_ms(delay);
    }
}
#endif

#if EFFECT_BIT_WALKING == 1
void effect_bit_walking() {
    unsigned char x, y, z;
    for(x = 0; x < 8; x++) {
        for(y = 0; y < 8; y++) {
            for(z = 0; z < 8; z++) {
                fill(0x00);
                setvoxel(x, y, z);
                delay_ms(100);
            }
        }
    }
}
#endif

#if EFFECT_LINES == 1
void effect_lines() {
    unsigned char x;//, y, z;
    
    for(x = 0; x < 8; x++) {
        fill(0x00);
        line(x, 0, 0, 4, 4, 7);
        delay_ms(500);
    }
    /*
        for(y = 0; y < 8; y++) {
            for(z = 0; z < 8; z++) {
                fill(0x00);
                setvoxel(x, y, z);
            }
        }
    }*/
}
#endif

#if EFFECT_RIPPLES == 1
float distance2d(float x1, float y1, float x2, float y2) {
    return sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void effect_ripples(unsigned char iterations, unsigned char delay) {
    float distance, height, ripple_interval;
    int x, y, i;
    fill(0x00);
    for(i = 0; i < 8; i++) {
        for(x = 0; x < 8; x++) {
            for(y = 0; y < 8; y++) {
                distance = distance2d(3.5, 3.5, x, y) / 9.899495 * 8;
                //distance = distance2d(3.5,3.5,x,y);
                ripple_interval = 1.3;
                height = 4 + sinf(distance / ripple_interval + (float) i / 5) * 4;
                setvoxel(x, y, (int) height);
            }
        }
        //delay_ms(delay);
        fill(0x00);
    }
}
#endif

#if EFFECT_STRING_FLY == 1
char str_fly[][] = {
    {0xff,0x9,0x9,0x9,0x1},
    {0x1,0x1,0xff,0x1,0x1},
    {0xff,0x89,0x89,0x89,0x81},
    {0x7e,0x81,0x81,0x81,0x81}
    
};

void send_char(char *char_data) {
    uint8_t l, byte_index;
    for(l = 7; l >= 0; l--) {
        for(byte_index = 4; byte_index >= 0; byte_index--) {
            if(char_data[byte_index] & (1 << (7 - l))) {
                setvoxel(2 + byte_index, 0, l);
            } else {
                clrvoxel(2 + byte_index, 0, l);
            }
        }
    }
}

void shift_cube(uint8_t iterations) {
    uint8_t it, lat, lay;
    for(it = 0; it < iterations; it++) {
        for(lay = 0; lay < 8; lay++) {
            for(lat = 7; lat >= 1; lat--) {
                cube[lay][lat - 1] = cube[lay][lat];
            }
            cube[lay][7] = 0x00;
        }
        delay_ms(2000);
    }
}

void effect_str_fly() {
    uint8_t i;
    for(i = 0; i < 4; i++) {
        send_char(str_fly[i]);
        shift_cube(8);
    }    
}
#endif

#if EFFECT_CLOSING_BOX == 1
void effect_closing_box() {
    int z, x, y, i;
    for(z = 0; z < 8; z++) {
        for(i = 0; i < 100; i++) {
            x = sinf(i / 8) * 2 + 3.5;
            y = cosf(i / 8) * 2 + 3.5;
            setvoxel(x, y, z);
            delay_ms(100);
            fill(0x00);
        }
    }
}
#endif


#endif // __PIC_LEDCUBE_EFFECTS_C
