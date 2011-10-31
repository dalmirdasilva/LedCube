/**
 * Creates a wireframe box that shrinks and grows out from the center 
 * of the cube.
 * 
 * @param   Iterations
 * @param   Delay
 */
void effect_box_woop_woop(uint8_t iterations, uint16_t delay) {
    uint8_t it, a, b, half = (CUBE_SIZE / 2);
    int8_t i;
    fill(0x00);
    for (it = 0; it < iterations; it++) {
        
        // Grows
        for (i = 0; i < half; i++) {
            a = half + i;
            b = half - i;
            box_wire_frame(a, a, a, b, b, b);
            delay_ms(delay);
            fill(0x00);
        }
        
        // Shrinks
        for (i = half - 1; i >= 0; i--) {
            a = half + i;
            b = half - i;
            box_wire_frame(a, a, a, b, b, b);
            delay_ms(delay);
            fill(0x00);
        }
    }
}
