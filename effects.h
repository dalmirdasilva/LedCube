/**
 * LedCube Project
 * 
 * effects.h
 */

#ifndef __PIC_LEDCUBE_EFFECTS_H
#define __PIC_LEDCUBE_EFFECTS_H 1 

void effect_test(void);
void effect_planboing(int plane, int speed);
void effect_blinky2();
void effect_box_shrink_grow(uint8_t iterations, uint8_t rot, uint8_t flip, uint16_t delay);
void effect_box_woop_woop(uint8_t delay, uint8_t grow);
void sendvoxel_z(unsigned char x, unsigned char y, unsigned char z, int delay);
void effect_sendplane_rand_z(unsigned char z, int delay, int wait);
void effect_sendvoxels_rand_z(int iterations, int delay, int wait);
void effect_boing_boing(uint16_t iterations, uint16_t delay, uint8_t mode, uint8_t draw_mode);
void effect_random_filler(int delay, int state);
void effect_rain(uint8_t iterations, uint8_t drops);
void effect_z_updown(int iterations, int delay);
void z_updown_move(unsigned char positions[64], unsigned char destinations[64], char axis);
void effect_axis_updown_randsuspend(char axis, int delay, int sleep, int invert);
void draw_positions_axis(char axis, unsigned char positions[64], int invert);
void effect_boxside_randsend_parallel(char axis, int origin, int delay, int mode);
void effect_loadbar(uint8_t delay);
void effect_random_sparkle_flash(int iterations, int voxels, int delay);
void effect_random_sparkle(void);
int effect_telcstairs_do(int x, int val, int delay);
void effect_telcstairs(int invert, int delay, int val);
void effect_worm_squeeze(int size, int axis, int direction, int iterations, int delay);
void effect_filled_box_flowing(unsigned char iterations, unsigned char size);
void effect_lines();
void effect_ripples(unsigned char iterations, unsigned char delay);

#endif // __PIC_LEDCUBE_EFFECTS_H
