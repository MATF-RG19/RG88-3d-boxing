#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "objekti.h"

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);

/*Osvetljenje sam gledala sa casova vezbi, ali sam pravila
u odnosu na to kako meni odgovaraju boje i razumela postavljanje
koeficijenata, difuzne, spekularne i ambijentalne svetlosti..*/ 

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
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.15, 0.1, 0.19, 0);
    glutMainLoop();

    return 0;
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

    GLfloat light_position[] = { 0, 1, 1, 0};

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };

    GLfloat light_diffuse[] = { 0.8,0.8,0.8};

    GLfloat light_specular[] = { 0.3, 0.3, 0.3, 0 };

    GLfloat ambient_coeffs[] = { 0, 0.9, 0.9, 1 };

    GLfloat diffuse_coeffs[] = { 0.0, 0.2, 0.8, 1 };

    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    GLfloat shininess = 20;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( -2.4, 0.8, 0,
               2, 0.28, 0,
               0, 1, 0);

    //draw_axes(50);         


    
    draw_box();
    draw_path();
    draw_ball();
    draw_sky();
    
    
    glutSwapBuffers();
}
