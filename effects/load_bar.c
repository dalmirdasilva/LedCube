/**
 * Effect load bar
 * 
 * @param   Delay
 * @return  void
 */
void effect_loadbar(uint8_t delay) {
    uint8_t z, y;
    fill(0x00);
    
    // Turn the leds on
    for (z = 0; z < CUBE_SIZE; z++) {
        for (y = 0; y < CUBE_SIZE; y++) {
            cube[z][y] = 0xff;
        }
        delay_ms(delay);
    }

    // Take a nap
    delay_ms(delay * 3);
    
    // Turn the leds off
    for (z = 0; z < CUBE_SIZE; z++) {
        for (y = 0; y < CUBE_SIZE; y++) {
            cube[z][y] = 0x00;
        }
        delay_ms(delay);
    }
}
