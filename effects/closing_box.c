/**
 * Effect closing box
 * 
 * @param   void
 * @return  void
 */
void effect_closing_box() {
    uint8_t i, j;
    fill(0x00);
    
    // Closing the bottom of the cube
    for(j = 0; j < CUBE_SIZE; j++) {
		cube[0][j] = 0xff;
		delay_ms(1000);
	}
    
    // Closing the first side of the AXIS_Y
    for(i = 0; i < CUBE_SIZE; i++) {
		cube[i][0] = 0xff;
		delay_ms(1000);
    }
    
    // Closing the last side of the AXIS_X
    for(i = 0; i < CUBE_SIZE; i++) {
		for(j = 0; j < CUBE_SIZE; j++) {
			cube[i][j] |= 0x01;
		}
		delay_ms(1000);
    }
    
    // Closing the last side of the AXIS_Y
    for(i = 0; i < CUBE_SIZE; i++) {
		cube[i][CUBE_SIZE - 1] = 0xff;
		delay_ms(1000);
    }

    // Closing the first side of the AXIS_X
    for(i = 0; i < CUBE_SIZE; i++) {
		for(j = 0; j < CUBE_SIZE; j++) {
			cube[i][j] |= 0x80;
		}
		delay_ms(1000);
    }
    
    // Closing the top of the cube
	for(j = 0; j < CUBE_SIZE; j++) {
		cube[CUBE_SIZE - 1][j] = 0xff;
		delay_ms(1000);
	}
}
