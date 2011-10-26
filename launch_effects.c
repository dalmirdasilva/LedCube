/**
 * LedCube Project
 * 
 * launch_effects.c
 */

#ifndef __PIC_LEDCUBE_LAUNCH_C
#define __PIC_LEDCUBE_LAUNCH_C 1 

#include "effect_switch.h"
#include "launch_effects.h"
#include "draw.c"
#include "effects.c"

void clear_and_wait() {
    fill(0x00);
    delay_ms(1000);
    LED2 ^= 1;
}

void launch_effects() {
    unsigned char k;
    k = 0;
    
#if EFFECT_TEST == 1
    clear_and_wait();
    effect_test();
#endif

#if EFFECT_RAIN == 1
    clear_and_wait();
    effect_rain(100);
#endif

#if EFFECT_SENDVOXELS_RZ == 1
    clear_and_wait();
    effect_sendvoxels_rand_z(20,220,2000);
#endif

#if EFFECT_SENDPLANE_RZ == 1
    clear_and_wait();
    effect_sendplane_rand_z(20, 220, 2000);
#endif

#if EFFECT_RANDOM_FILTER == 1
    clear_and_wait();
    effect_random_filler(5, 1);
    effect_random_filler(5, 0);
#endif

#if EFFECT_BLINKY == 1
    clear_and_wait();
    effect_blinky2();
#endif

#if EFFECT_BOX_SHRING_GROW == 1
    clear_and_wait();
    for(k = 0; k < 8; k++) {
        effect_box_shrink_grow(1, k % 4, k & 0x04, 450);
    }
#endif

#if EFFECT_BOX_WOOPWOOP == 1
    clear_and_wait();
    effect_box_woopwoop(800, 0);
    effect_box_woopwoop(800, 1);
    effect_box_woopwoop(800, 0);
    effect_box_woopwoop(800, 1);
#endif

#if EFFECT_PLANBOING == 1
    clear_and_wait();
    effect_planboing(AXIS_Z, 400);
    effect_planboing(AXIS_X, 400);
    effect_planboing(AXIS_Y, 400);
    effect_planboing(AXIS_Z, 400);
    effect_planboing(AXIS_X, 400);
    effect_planboing(AXIS_Y, 400);
#endif
            
#if EFFECT_LOADBAR == 1
    clear_and_wait();
    effect_loadbar(700);
#endif

#if EFFECT_WORMSQUEEZE == 1
    clear_and_wait();
    effect_wormsqueeze(1, AXIS_Z, 1, 100, 1000);
#endif

#if EFFECT_BOXSIDE_RAND_SEND == 1
    clear_and_wait();
    for(k = 0; k < 5; k++) {
        effect_boxside_randsend_parallel(AXIS_Z, 0, 200, 2);
        delay_ms(1500);
    }
#endif

#if EFFECT_Z_UPDOWN == 1
    clear_and_wait();
    effect_z_updown(20, 1000);
#endif

#if EFFECT_TELKSTAIRS == 1
    clear_and_wait();
    effect_telcstairs(0, 800, 0xff);
    effect_telcstairs(0, 800, 0x00);
    effect_telcstairs(1, 800, 0xff);
    effect_telcstairs(1, 800, 0xff);
#endif

#if EFFECT_AXIS_UPDOWN_RSUSPEND == 1
    clear_and_wait();
    effect_axis_updown_randsuspend(AXIS_Z, 550, 5000, 0);
    effect_axis_updown_randsuspend(AXIS_Z, 550, 5000, 1);
    effect_axis_updown_randsuspend(AXIS_Z, 550, 5000, 0);
    effect_axis_updown_randsuspend(AXIS_Z, 550, 5000, 1);
    effect_axis_updown_randsuspend(AXIS_X, 550, 5000, 0);
    effect_axis_updown_randsuspend(AXIS_X, 550, 5000, 1);
    effect_axis_updown_randsuspend(AXIS_Y, 550, 5000, 0);
    effect_axis_updown_randsuspend(AXIS_Y, 550, 5000, 1);
#endif

#if EFFECT_BOINGBOING == 1
    clear_and_wait();
    effect_boingboing(250, 600, 0x01, 0x02);
#endif

#if EFFECT_SPARKLE == 1
    clear_and_wait();
    effect_random_sparkle();
#endif

#if EFFECT_BIT_WALKING == 1
    clear_and_wait();
    effect_bit_walking();
#endif

#if EFFECT_LINES == 1
    clear_and_wait();
    effect_lines();
#endif

#if EFFECT_RIPPLES == 1
    clear_and_wait();
    effect_ripples(100, 10);
#endif

#if EFFECT_STRING_FLY == 1
    clear_and_wait();
    effect_str_fly();
#endif

#if EFFECT_CLOSING_BOX == 1
    clear_and_wait();
    effect_closing_box();
    
#endif
	
}

#endif // __PIC_LEDCUBE_LAUNCH_C

