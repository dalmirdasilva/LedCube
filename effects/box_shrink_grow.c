/**
 * Effect box shrink grow
 * 
 * @param   Iterations
 * @param   Rotation
 * @param   Flip
 * @param   delay
 * @return  void
 */
void effect_box_shrink_grow(uint8_t iterations, uint8_t rot, uint8_t flip, uint16_t delay) {
    uint8_t it, i;
    int8_t xyz;
    for (it = 0; it < iterations; it++) {
        for (i = 0; i < 16; i++) {
            xyz = 7 - i; // This reverses counter i between 0 and 7.
            if (i > 7) {
                xyz = i - 8; // at i > 7, i 8-15 becomes xyz 0-7.
            }
            fill(0x00);
            delay_ms(1);

            // disable interrupts while the cube is being rotated
            INTCONbits.GIE = 0;

            box_wire_frame(0, 0, 0, xyz, xyz, xyz);

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
