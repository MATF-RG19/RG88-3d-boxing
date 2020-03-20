#include "objekti.h"

void draw_axes(float len) {
    glDisable(GL_LIGHTING);
  
    glBegin(GL_LINES);
        glColor3f(0.8,0,0);
        glVertex3f(0,0,0);
        glVertex3f(len,0,0);

        glColor3f(0,0.8,0);
        glVertex3f(0,0,0);
        glVertex3f(0,len,0);

        glColor3f(0,0,0.8);
        glVertex3f(0,0,0);
        glVertex3f(0,0,len);
    glEnd();
  
    glEnable(GL_LIGHTING);
}
void draw_box(){
glPushMatrix();
  glLineWidth(2);
    glTranslatef(3,2,3);
    glColor3f(0.4,0.2,0.30);
    glutWireCube(0.4);
    glColor3f(0.4,0,0.24);
    glutSolidCube(0.4);
    
glPopMatrix();   

}
void draw_path(){

    glPushMatrix();
        glColor3f(0.8, 0.6, 0.584); 
        glRotatef(45,0,1,0);
        glTranslatef(0,-1.2, 1.5);
        glScalef(2, -5, -9);
        glutSolidCube(1);
    glPopMatrix();
}
void draw_ball(){
       glPushMatrix();
         glTranslatef(4.5,2,4.5);
        glColor3f(0.4, 0.2, 0.30); 
        glutSolidSphere(0.1,100,50);
    glPopMatrix();
}

