/**
 * LedCube Project
 * 
 * draw.c
 */
 
#ifndef __PIC_LEDCUBE_DRAW_H
#define __PIC_LEDCUBE_DRAW_H 1 

unsigned char inrange(int x, int y, int z);
char byteline(int start, int end);
void setvoxel(int x, int y, int z);
void tmpsetvoxel(int x, int y, int z);
void clrvoxel(int x, int y, int z);
void tmpclrvoxel(int x, int y, int z);
unsigned char getvoxel(int x, int y, int z);
void altervoxel(int x, int y, int z, int state);
void flpvoxel(int x, int y, int z);
void argorder(int ix1, int ix2, int *ox1, int *ox2);
void setplane_z(int z);
void clrplane_z(int z);
void setplane_x(int x);
void clrplane_x(int x);
void setplane_y(int y);
void clrplane_y(int y);
void setplane(char axis, unsigned char i);
void clrplane(char axis, unsigned char i);
void fill (unsigned char pattern);
void tmpfill (unsigned char pattern);
void box_filled(int x1, int y1, int z1, int x2, int y2, int z2);
void box_walls(int x1, int y1, int z1, int x2, int y2, int z2);
void box_wireframe(int x1, int y1, int z1, int x2, int y2, int z2);
char flipbyte(char byte);
void line(int x1, int y1, int z1, int x2, int y2, int z2);
void tmp2cube();
void shift(char axis, int direction);
void mirror_y();
void mirror_x();
void mirror_z();

#endif // __PIC_LEDCUBE_DRAW_H
