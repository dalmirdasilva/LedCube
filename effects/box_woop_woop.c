/**
 * Creates a wireframe box that shrinks and grows out from the center 
 * of the cube.
 * 
 * @param   Iterations
 * @param   Delay
 *
void effect_box_woop_woop_unoptimized(uint8_t iterations, uint16_t delay) {
    int8_t i, j;
    uint8_t midle = (CUBE_SIZE / 2);
    fill(0x00);
    while (iterations--) {
        i = midle - 1;
        j = midle;
        
        // Grows
        for (; j < CUBE_SIZE; i--, j++) {
            box_wire_frame(i, i, i, j, j, j);
            delay_ms(delay);
            fill(0x00);
        }
        
        i++;
        j--;
        
        // Shrinks
        for (; i < midle; i++, j--) {
            box_wire_frame(i, i, i, j, j, j);
            delay_ms(delay);
            fill(0x00);
        }
    }
}
 */
void effect_box_woop_woop(uint8_t iterations, uint16_t delay) {
    int8_t i, j;
    fill(0x00);
    while (iterations--) {
        i = 3;
        j = 4;
        
        // Grows
        for (; j < CUBE_SIZE; i--, j++) {
            box_wire_frame(i, i, i, j, j, j);
            delay_ms(delay);
            fill(0x00);
        }
        
        i++;
        j--;
        
        // Shrinks
        for (; i < 4; i++, j--) {
            box_wire_frame(i, i, i, j, j, j);
            delay_ms(delay);
            fill(0x00);
        }
    }
}
