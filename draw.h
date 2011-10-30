/**
 * LedCube Project
 * 
 * draw.c
 */
 
#ifndef __PIC_LEDCUBE_DRAW_H
#define __PIC_LEDCUBE_DRAW_H 1 

/**
 * This function validates that we are drawing inside the cube.
 * 
 * @param   The cube coordinates
 * @return  boolean
 */
uint8_t in_range(int8_t x, int8_t y, int8_t z);

/**
 * Returns a byte with a row of 1's drawn in it.
 * e.g.: byte_line(2, 5) gives 0b00111100
 * 
 * @param   The start bit
 * @param   The end bit
 * @return  char 
 */
int8_t byte_line(int8_t start, int8_t end);

/**
 * Set a single voxel to ON
 *
 * @param   The cube coordenates
 * @reurn   void 
 */
void set_voxel(int8_t x, int8_t y, int8_t z);

/**
 * Set a single voxel in the temporary cube buffer to ON
 * 
 * @param   The cube coordenates
 * @return  void
 */
void tmp_set_voxel(int8_t x, int8_t y, int8_t z);

/**
 * Set a single voxel to OFF
 * 
 * @param   The cube coordenates
 * @return  void
 */
void clr_voxel(int8_t x, int8_t y, int8_t z);

/**
 * Set a single voxel to OFF
 * 
 * @param   The cube coordenates
 * @return  void
 */
void tmp_clr_voxel(int8_t x, int8_t y, int8_t z);

/**
 * Get the current status of a voxel
 * 
 * @param   The cube coordenates
 * @return  boolean
 */
uint8_t get_voxel(int8_t x, int8_t y, int8_t z);

/**
 * In some effect we want to just take bool and write it to a voxel
 *
 * this function calls the apropriate voxel manipulation function.
 * 
 * @param   The cube coordenates
 * @param   The state of voxel
 * @return  void
 */
void alter_voxel(int8_t x, int8_t y, int8_t z, int state);

/**
 * Flip the state of a voxel.
 *
 * If the voxel is 1, its turned into a 0, and vice versa.
 * 
 * @param   The cube coordenates
 * @return  void
 */
void flp_voxel(int8_t x, int8_t y, int8_t z);

/**
 * Makes sure x1 is alwas smaller than x2
 * 
 * This is usefull for functions that uses for loops,
 * to avoid infinite loops
 * 
 * @param   Arguments and its corrsponding poiters
 * @return  void
 */
void arg_order(int8_t i1, int8_t i2, int8_t *p1, int8_t *p2);

/**
 * Sets all voxels along a X/Y plane at a given point on axis Z
 * 
 * @param   The point on Z axis
 * @return  void
 */
void set_plane_z(int8_t point);

/**
 * Clear all voxels along a X/Y plane at a given point on axis Z
 * 
 * @param   The point on Z axis
 * @return  void
 */
void clr_plane_z(int8_t point);

/**
 * Sets all voxels along a Z/Y plane at a given point on axis X
 * 
 * @param   The point on X axis
 * @return  void
 */
void set_plane_x(int8_t point);

/**
 * Clears all voxels along a Z/Y plane at a given point on axis X
 * 
 * @param   The point on X axis
 * @return  void
 */
void clr_plane_x(int8_t point);

/**
 * Sets all voxels along a X/Z plane at a given point on axis Y
 * 
 * @param   The point on Y axis
 * @return  void
 */
void set_plane_y(int8_t point);

/**
 * Clears all voxels along a X/Z plane at a given point on axis Y
 * 
 * @param   The point on Y axis
 * @return  void
 */
void clr_plane_y(int8_t point);

/**
 * Sets all voxels along a given plane and point
 * 
 * @param   The axis
 * @param   The point on axis
 * @return  void
 */
void set_plane(char axis, int8_t point);

/**
 * Clears all voxels along a given plane and point
 * 
 * @param   The axis
 * @param   The point on axis
 * @return  void
 */
void clr_plane(char axis, int8_t point);

/**
 * Fill a value into all 64 byts of the cube buffer
 * 
 * Mostly used for clearing. fill(0x00) or setting all on. fill(0xff)
 * 
 * @param   The pattern
 * @return  void
 */
void fill(uint8_t pattern);

/**
 * Fill a value into all 64 byts of the temp cube buffer
 * 
 * Mostly used for clearing. fill(0x00) or setting all on. fill(0xff)
 * 
 * @param   The pattern
 * @return  void
 */
void fb_fill(uint8_t pattern);

/**
 * Draw a box with all walls drawn and all voxels inside set
 * 
 * @param   Two coordenates on the cube
 * @return  void
 */
void box_filled(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2);

/**
 * Darw a hollow box with side walls.
 * 
 * @param   Two coordenates on the cube
 * @return  void
 */
void box_walls(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2);

/**
 * Draw a wireframe box. This only draws the corners and edges, no walls.
 *
 * @param   Two coordenates on the cube
 * @return  void
 */
void box_wireframe(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2);

/**
 * Flips a byte 180 degrees.
 * 
 * MSB becomes LSB, LSB becomes MSB.
 * 
 * @param   A byte to be flipped
 * @return  The flipped byte
 */
char flip_byte(char byte);

/**
 * Draw a line between any coordinates in 3d space.
 * 
 * Uses integer values for input, so dont expect smooth animations.
 * 
 * @param   Two coordenates on the cube
 * @return  void
 */
void line(int8_t x1, int8_t y1, int8_t z1, int8_t x2, int8_t y2, int8_t z2);

/**
 * Copies the contents of fb (temp cube buffer) into the rendering buffer
 * 
 * @param   void
 * @return  void
 */
void fb_to_cube();

/**
 * Shift the entire contents of the cube along an axis
 * 
 * This is great for effects where you want to draw something
 * on one side of the cube and have it flow towards the other
 * side. Like rain flowing down the Z axiz.
 * 
 * @param   The axis
 * @param   The direction of the shift
 * @return  void
 */
void shift(char axis, int8_t direction);

/**
 * Flips the cube 180 degrees along the y axis.
 * 
 * @param   void
 * @return  void
 */
void mirror_y();

/**
 * Flips the cube 180 degrees along the x axis
 * 
 * @param   void
 * @return  void
 */
void mirror_x();

/**
 * Flips the cube 180 degrees along the z axis
 * 
 * @param   void
 * @return  void
 */
void mirror_z();

#endif // __PIC_LEDCUBE_DRAW_H
