/**
 * Rain effect
 * 
 * @param   Iterations
 * @return  void
 */
void effect_rain(uint8_t iterations, uint8_t drops) {
    uint8_t i, it, rnd_x, rnd_y, rnd_num;
    for (it = 0; it < iterations; it++) {
        srand(it);
        rnd_num = rand() % drops;
        for (i = 0; i < rnd_num; i++) {
            rnd_x = rand() % 8;
            rnd_y = rand() % 8;
            set_voxel(rnd_x, rnd_y, 7);
        }
        delay_ms(500);
        shift(AXIS_Z, -1);
    }
}
