/**
 * Effect boing boing, just make a snake
 * 
 * @param   Iterations
 * @param   Delay
 * 
 */
void effect_boing_boing(uint16_t iterations, uint16_t delay, uint8_t mode, uint8_t draw_mode) {
    
    // Current coordinates for the point
    uint8_t x, y, z; 
    
    // Direction of movement
    int8_t dx, dy, dz; 
    
    // lol?
    int lol, i; 
    
    uint8_t crash_x, crash_y, crash_z;

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
        if (draw_mode == 0x01) {
            set_voxel(x, y, z);
            delay_ms(delay);
            clr_voxel(x, y, z);
            
        // flip the voxel in question
        } else if (draw_mode == 0x02) {
            flp_voxel(x, y, z);
            delay_ms(delay);
        }
        
        // draw a snake
        if (draw_mode == 0x03) {
            for (i = 7; i >= 0; i--) {
                snake[i][0] = snake[i - 1][0];
                snake[i][1] = snake[i - 1][1];
                snake[i][2] = snake[i - 1][2];
            }
            snake[0][0] = x;
            snake[0][1] = y;
            snake[0][2] = z;
            for (i = 0; i < 8; i++) {
                set_voxel(snake[i][0], snake[i][1], snake[i][2]);
            }
            delay_ms(delay);
            for (i = 0; i < 8; i++) {
                clr_voxel(snake[i][0], snake[i][1], snake[i][2]);
            }
        }
        iterations--;
    }
}
