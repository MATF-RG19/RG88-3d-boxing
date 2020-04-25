#ifndef _OBJEKTI_H
#define _OBJEKTI_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void draw_axes(float len);
void draw_box(float x,float z,int color);
void draw_path();
void draw_ball();
void draw_sky();
void draw_scene();
void draw_seperation_lines(float len);
void draw_boxes();
void draw_ground();
void draw_objects(float x,float z);
void draw_score();



#endif
