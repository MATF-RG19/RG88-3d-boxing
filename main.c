#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "objekti.h"
#include "image.h"

#define TIMER_INTERVAL 20
#define TIMER_ID1 0
#define TIMER_ID2 1

#define LEN 100
#define BOXES_NUMBER 10
#define OBJECT_NUMBER 10

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void onTimer(int id);
static void draw_end_screen();
static void draw_start_screen();

static float animationParameter = 0;
static float animationOngoing = 0;
float endAnimation = 0;
static float ballParameter = 0;
static float LeftRightMovement = 0;
static bool shouldGoUp = true;
static bool shouldJump = false;
static bool canJump = true;
static bool goRight = false;
static bool goLeft = false;
float shrinkParameter = 0.08;
int window_width, window_height;

/*Struktura koja ce predstavljati svaku kutiju*/
struct BOX {
    float x;
    float z;
    int color;
};
/*Struktura za druge objekte u igrici*/
struct OBJECT {
float x;
float z;
};
/*Pokazivac na prvu kutiju u redu*/
int firstBox = 0;
/*Pokazivac na prvi objekat u redu*/
int firstObject=0;
/*Niz pokazivaca na pozicije kutija*/
struct BOX boxes[BOXES_NUMBER];

/*Niz pokazivaca na pozicije objekata*/
struct OBJECT objects[OBJECT_NUMBER];

static void inicijalizacijaTekstura(void);
static void inicijalizacijaPozicijaKutija(void);

#define FILENAME0 "Teksture/plocicenebo.bmp"
#define FILENAME1 "Teksture/plocicepod.bmp"
#define FILENAME2 "Teksture/endofgame.bmp"
#define FILENAME3 "Teksture/start.bmp"

static GLuint textures[4];

int main(int argc, char **argv){
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(650, 650);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    glutFullScreen();
  
    inicijalizacijaPozicijaKutija();
    inicijalizacijaTekstura();
    
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    
	/*pozivanje funkcije za start ekran*/
	glutDisplayFunc(draw_start_screen);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.15, 0.1, 0.19, 0);
    glutMainLoop();

    return 0;
}

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'r':
          animationParameter = 0;
		  animationOngoing=0;
          ballParameter=0;
          shouldGoUp = true;
          shouldJump = false;
          firstBox = 0;
          shrinkParameter = 0.08;
          endAnimation = 0;
          inicijalizacijaPozicijaKutija();
		  glutDisplayFunc(on_display);
          break;
        case 's':
        case 'S':
          animationOngoing = 0;
          break;
        case 'g':
        case 'G':
          if(!animationOngoing){
			glutDisplayFunc(on_display);
            animationOngoing = 1;
            glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID1);
          }
          break;
        case 32:
            if(canJump)
            {
                shouldJump=true;
                shouldGoUp=true;
            }
            break; 
        case 'a':
            goLeft=true;
            goRight=false;
            break;
        case 'd':
            goRight=true;
            goLeft=false;
            break;            
        case 27:
          exit(0);
          break;
    }
}

void on_reshape(int width, int height) {
	/*Podesavanje sirine i visine za end_screen i start screen*/
	window_width=width;
	window_height=height;
	/*Podesavanje viewporta*/
    glViewport(0, 0, width, height);
	/*Projekcija*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30, (float) width/height, 1, 50);
}

void onTimer(int id){
    if(id == TIMER_ID1){
        animationParameter+=0.2;

        if(shouldJump)
        {
            if(ballParameter>=0.72)
                shouldGoUp=false;
            
            if(shouldGoUp)
                ballParameter+=0.02;
            else
                ballParameter-=0.02;

            if(ballParameter<=0)
                shouldJump=false;

        }

        if(LeftRightMovement >= -0.6 && goLeft)
        {
            LeftRightMovement-=0.02;
        }

        if(LeftRightMovement <= 0.6 && goRight)
        {
            LeftRightMovement+=0.02;
        }
   
        for(int i = 0 ; i < BOXES_NUMBER ; i++)
        {
            boxes[i].x -= 0.125;
			objects[i].x-=0.125;
        }

        if(boxes[firstBox].x == -5)
        {
            boxes[firstBox].x = 85;
            firstBox++;
			

            if(firstBox == BOXES_NUMBER)
            {
                firstBox = 0;
            }
        }
		 if(objects[firstObject].x == -5)
        {
            objects[firstObject].x = 85;
            firstObject++;
			

            if(firstObject == OBJECT_NUMBER)
            {
                firstObject = 0;
            }
        }
/*Ako su ispunjena sva 3 ova uslova za koliziju onda se zavrsava animacija kretanja i krece animacija 
zavrsetka igre*/
        
        if(boxes[firstBox].x == 0.25 
         && (LeftRightMovement > boxes[firstBox].z-0.21 && LeftRightMovement < boxes[firstBox].z+0.21) && ballParameter < 0.3){
            animationOngoing = 0;
            endAnimation = 1;
         
        }
        

    }else if(id == TIMER_ID2)
    {
 
        if(shrinkParameter > 0){
             shrinkParameter -= 0.002;
			}
  		else{
			glutDisplayFunc(draw_end_screen);
			}

    }
	
    glutPostRedisplay();

    if (animationOngoing)
      glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID1);
    else if(endAnimation)
       glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID2);
	    
}


void on_display() {

	/*Podesavanje osvetljenja*/
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


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

  /*Postavljanje pozadine, namestanje koordinata*/
  glBindTexture(GL_TEXTURE_2D, textures[0]);

  glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);

    glTexCoord2f(0, 0);
    glVertex3f(20, 0, -11);

    glTexCoord2f(0, 1);
    glVertex3f(20, 6, -11);

    glTexCoord2f(1, 1);
    glVertex3f(20, 6, 11);

    glTexCoord2f(1, 0);
    glVertex3f(20, 0, 11);
   glEnd();

   /*Postavljanje poda, namestanje koordinata*/
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBegin(GL_QUADS);

        glNormal3f(0, 1, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(-2, 0, -11);
        
        glTexCoord2f(0, 1);
        glVertex3f(20, 0, -11);
        
        glTexCoord2f(1, 1);
        glVertex3f(20,0, 11);
        
        glTexCoord2f(1, 0);
        glVertex3f(-2, 0,11);
  glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    /*Iscrtavanje okoline*/
    glPushMatrix();
        draw_scene();
        glTranslatef(0,ballParameter,LeftRightMovement);
        draw_ball();
    glPopMatrix();

    /*Iscrtavanje kutija*/
    for(int i = 0 ; i < BOXES_NUMBER ; i++){

        glPushMatrix();
            draw_box(boxes[i].x,boxes[i].z,boxes[i].color);
        glPopMatrix();
    }
	/*Iscrtavanje drugih objekata*/
    for(int i = 0 ; i < OBJECT_NUMBER ; i++){

        glPushMatrix();
            draw_objects(objects[i].x,objects[i].z);
        glPopMatrix();
    }
	

        
    glutSwapBuffers();

}

static void inicijalizacijaTekstura(void){
    /*funkcija sa sedmog casa vezbi koja koristi biblioteku image.c*/

    Image * image;
    glEnable(GL_DEPTH_TEST);

    /*ukljucivanje odredjenih flegova za lepljenje tekstura*/
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    /*inicijalizacija*/
    image = image_init(0, 0);
    glGenTextures(4, textures);

    /*Tekstura neba*/
    image_read(image, FILENAME0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    /*Tekstura poda*/
    image_read(image, FILENAME1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	/*Tekstura zavresetka igre(end game)*/
    image_read(image, FILENAME2);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);


    image_read(image, FILENAME3);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    /*Iskljucujemo aktivnu teksturu*/
    glBindTexture(GL_TEXTURE_2D, 0);
    image_done(image);
}

void inicijalizacijaPozicijaKutija(void){
    /*Inicijalizacija pozicija svih kutija,koriscena srand funkcija 
    kako bi pri svakom novom pokretanju raspored kutija bio drugaciji*/
    srand(time(NULL));
    for(int i = 0 , j = 9; i < BOXES_NUMBER; i++ , j+=9) {
        boxes[i].x = j;
		objects[i].x=j;
        if(rand()%3 == 0){
            boxes[i].z = 0;
			objects[i].z=0;
		}
        else if(rand()% 3 == 1){
            boxes[i].z = 0.6;
			objects[i].z=0.6;
		}
        else{
            boxes[i].z = -0.6;
			objects[i].z=-0.6;
		}
        boxes[i].color = rand()%3;
    }

}
/*Funkcija za postavljanje teksture za zavrsetak igre
//Moralo je da se prebaci na ortografsku projekciju*/
static void draw_end_screen(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);

    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
  
		gluOrtho2D(0, window_width,0, window_height);
		
		glMatrixMode(GL_MODELVIEW);
  		glLoadIdentity();

		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(0,0);

			glTexCoord2f(0, 1);
			glVertex2f(0, window_height);

			glTexCoord2f(1, 1);
			glVertex2f(window_width,window_height);

			glTexCoord2f(1, 0);
			glVertex2f(window_width,0);
		glEnd();
		
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();

}
/*Funkcija za postavljanje teksture za pocetak igre*/
static void draw_start_screen(){
                                                                                                                                         
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);

    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
  
		gluOrtho2D(0, window_width,0, window_height);
		
		glMatrixMode(GL_MODELVIEW);
  		glLoadIdentity();

		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(0,0);

			glTexCoord2f(0, 1);
			glVertex2f(0, window_height);

			glTexCoord2f(1, 1);
			glVertex2f(window_width,window_height);

			glTexCoord2f(1, 0);
			glVertex2f(window_width,0);
		glEnd();
		
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();

}


