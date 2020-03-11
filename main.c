#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);


int main(int argc, char **argv){
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(650, 650);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    glutFullScreen();
 
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.5, 0.3, 0.4, 0.2);
    glutMainLoop();

    return 0;
}

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

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
          exit(0);
          break;
    }
}

void on_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 20);
}


void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 6,
              0, 0, 0,
              0, 1, 0);
 
    draw_axes(50);
    
    glutSwapBuffers();
}
