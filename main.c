#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "objekti.h"
#include "image.h"

#define TIMER_INTERVAL 10
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

static int animationParameter = 0;
static float animationOngoing = 0;
float endAnimation = 0;
//Parametri za lopticu
static float ballParameter = 0;
static float LeftRightMovement = 0;
static bool shouldGoUp = true;
static bool shouldJump = false;
static bool canJump = true;
static bool goRight = false;
static bool goLeft = false;
//brzina kretanja
static float speed= 0.06;
//rotacijski parametar za lopticu 
int rotationParameter = 0;
//rotacija zutih objekata
int rotationObject = 0;
//poluprecnik loptice
float shrinkParameter = 0.08;
//sirina i visina prozora
int window_width, window_height;

int score = 0;
int brojac=0;

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
bool obrisi;
};

/*Pokazivac na prvu kutiju u redu*/
int firstBox = 0;
/*Pokazivac na prvi objekat u redu*/
int firstObject=0;
/*Pokazivac na poslednju kutiju u redu*/
int lastBox = 9;
/*Pokazivac na poslednji objekat u redu*/
int lastObject = 9;

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
#define FILENAME4 "Teksture/lopta.bmp"

GLuint textures[5];

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
		  /*resetovanje svih parametara*/
          animationParameter = 0;
		  animationOngoing=0;
          ballParameter=0;
          shouldGoUp = true;
          shouldJump = false;
		  canJump=true;
          firstBox = 0;
		  firstObject = 0;
		  lastBox = 9;
		  lastObject = 9;
		  speed = 0.06;
		  rotationParameter=0;
		  rotationObject=0;
          shrinkParameter = 0.08;
          endAnimation = 0;
		  score=0;
          inicijalizacijaPozicijaKutija();
		  glutDisplayFunc(on_display);
          break;
        case 's':
        case 'S':
		  /*zaustavljanje*/
          animationOngoing = 0;
          break;
        case 'g':
        case 'G':
		  /*pokretanje*/
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
				canJump=false;

            }
            break; 
        case 'a':
		case 'A':
            goLeft=true;
            goRight=false;
            break;
        case 'd':
		case 'D':
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
        animationParameter+=1;
		//uvecavanje skora
		if(animationParameter%20==0)
		score+=1;
		rotationParameter+=6;
		rotationObject+=3;

		if(speed < 0.3)
			speed += 0.00025;

        if(shouldJump)
        {
			
            if(ballParameter>=0.72){
                shouldGoUp=false;
			}
            
            if(shouldGoUp)
                ballParameter+=0.0125;
            else
                ballParameter-=0.019;

            if(ballParameter<=0){
                shouldJump=false;
				canJump=true;
			
}

        }
		

        if(LeftRightMovement >= -0.6 && goLeft)
        {
            LeftRightMovement-=0.013;
        }

        if(LeftRightMovement <= 0.6 && goRight)
        {
            LeftRightMovement+=0.013;
        }
   
        for(int i = 0 ; i < BOXES_NUMBER ; i++)
        {
            boxes[i].x -= speed;
			objects[i].x-= speed;
        }

        if(boxes[firstBox].x <= -5)
        {
            boxes[firstBox].x = boxes[lastBox].x+7;
			lastBox = firstBox;
            firstBox++;
			

            if(firstBox == BOXES_NUMBER)
            {
                firstBox = 0;
            }
        }
		 if(objects[firstObject].x <= -5)
        {
			objects[firstObject].obrisi=false;
            objects[firstObject].x = objects[lastObject].x+10;
			lastObject = firstObject;
            firstObject++;
			

            if(firstObject == OBJECT_NUMBER)
            {
                firstObject = 0;
objects[firstObject].obrisi=false;
            }
        }
		/*Ako su ispunjena sva 3 ova uslova za koliziju onda se zavrsava animacija kretanja i krece animacija 
		zavrsetka igre*/        
        if(boxes[firstBox].x - 0.21 <= 0.08 && boxes[firstBox].x + 0.21 >= -0.08
         && (LeftRightMovement +0.08> boxes[firstBox].z-0.21 && LeftRightMovement -0.08< boxes[firstBox].z+0.21) && ballParameter < 0.46){

            animationOngoing = 0;
            endAnimation = 1;
         
        }

        /*Ako su ispunjena sva 3 ova uslova za koliziju onda se "kupi" iliti nestaje objekat i score se 
		odmah povecava za 10*/	
     	if(objects[firstObject].x<=0.25 && objects[firstObject].x>=0.1
			&& LeftRightMovement-0.15<objects[firstObject].z && LeftRightMovement+0.15>objects[firstObject].z
			&& ballParameter < 0.11*1.25){
     		
            //ako je "pokupljeno" povecavamo score za 20
			objects[firstObject].obrisi=true;
			score+=10;
			
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

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( -2.4, 0.8, 0,
               2, 0.28, 0,
               0, 1, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);	

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


  /*Postavljanje koordinata pozadine*/
  glBindTexture(GL_TEXTURE_2D, textures[0]);

  glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);

    glTexCoord2f(0, 0);
    glVertex3f(30, 0, -16);

    glTexCoord2f(0, 1);
    glVertex3f(30, 6, -16);

    glTexCoord2f(1, 1);
    glVertex3f(30, 6, 16);

    glTexCoord2f(1, 0);
    glVertex3f(30, 0, 16);
   glEnd();

   /*Postavljanje koordinata poda*/
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBegin(GL_QUADS);

        glNormal3f(0, 1, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(-2, 0, -16);
        
        glTexCoord2f(0, 1);
        glVertex3f(30, 0, -16);
        
        glTexCoord2f(1, 1);
        glVertex3f(30,0, 16);
        
        glTexCoord2f(1, 0);
        glVertex3f(-2, 0,16);
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
			glTranslatef(0,-0.05,0);
            draw_box(boxes[i].x,boxes[i].z,boxes[i].color);
        glPopMatrix();
    }
	/*Iscrtavanje drugih objekata*/
    for(int i = 0 ; i < OBJECT_NUMBER ; i++){
		if(!objects[i].obrisi) {
        glPushMatrix();
            draw_objects(objects[i].x,objects[i].z);
        glPopMatrix();
	}
    }

	glDisable(GL_LIGHTING);
  		draw_score();
	glEnable(GL_LIGHTING);

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
    glGenTextures(5, textures);

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

	/*Tekstura pocetka igre(start game)*/
    image_read(image, FILENAME3);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	/*Tekstura lopte*/
    image_read(image, FILENAME4);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
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

    for(int i = 0 , j = 7; i < BOXES_NUMBER; i++ , j+=7) {
        boxes[i].x = j;
        if(rand()%3 == 0)
            boxes[i].z = 0;
        else if(rand()% 3 == 1)
            boxes[i].z = 0.6;
        else
            boxes[i].z = -0.6;

        boxes[i].color = rand()%3;
    } 

	/*Na isti nacin vrsi se i inicijalizacija pozicija objekata
	za prikupljanje poena*/
	  for(int i = 0 , j = 10; i < OBJECT_NUMBER; i++ , j+=10) {
        objects[i].x = j;
		objects[i].obrisi=false;
        
        if(rand()%3 == 0)
            objects[i].z = 0;
        else if(rand()% 3 == 1)
            objects[i].z = 0.6;
        else
            objects[i].z = -0.6;
        
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



