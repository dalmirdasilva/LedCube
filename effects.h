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
void effect_box_shrink_grow(int iterations, int rot, int flip, uint16_t delay);
void effect_box_woopwoop(int delay, int grow);
void sendvoxel_z(unsigned char x, unsigned char y, unsigned char z, int delay);
void effect_sendplane_rand_z(unsigned char z, int delay, int wait);
void effect_sendvoxels_rand_z(int iterations, int delay, int wait);
void effect_boingboing(uint16_t iterations, int delay, unsigned char mode, unsigned char drawmode);
void effect_random_filler(int delay, int state);
void effect_rain(int iterations);
void effect_z_updown(int iterations, int delay);
void z_updown_move(unsigned char positions[64], unsigned char destinations[64], char axis);
void effect_axis_updown_randsuspend(char axis, int delay, int sleep, int invert);
void draw_positions_axis(char axis, unsigned char positions[64], int invert);
void effect_boxside_randsend_parallel(char axis, int origin, int delay, int mode);
void effect_loadbar(int delay);
void effect_random_sparkle_flash(int iterations, int voxels, int delay);
void effect_random_sparkle(void);
int effect_telcstairs_do(int x, int val, int delay);
void effect_telcstairs(int invert, int delay, int val);
void effect_wormsqueeze(int size, int axis, int direction, int iterations, int delay);
void effect_filled_box_flowing(unsigned char iterations, unsigned char size);
void effect_lines();
void effect_ripples(unsigned char iterations, unsigned char delay);

#endif // __PIC_LEDCUBE_EFFECTS_H
