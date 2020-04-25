#include "objekti.h"
#include <string.h>

extern float endAnimation;
extern float shrinkParameter;
extern int rotationParameter;
extern int rotationObject;
extern GLuint textures[5];
extern bool goLeft;
extern int score, window_width, window_height;

GLUquadric* sphere;

/*Crtanje x,y,z osa*/
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
/*Crtanje linija po putu, kojim se odvajaju 3 napravljene trake*/
void draw_seperation_lines(float len) {
	glDisable(GL_LIGHTING);
	
	glTranslatef(-1,0.1,0);
	glLineWidth(2.5);
	glBegin(GL_LINES);
		glColor3f(0.1490,1,0.94);
		
        glVertex3f(0,0,0.33);
        glVertex3f(len,0,0.33);

        glVertex3f(0,0,-0.33);
        glVertex3f(len,0,-0.33);
		
		glVertex3f(0,0,-0.98);
        glVertex3f(len,0,-0.98);
 		
		glVertex3f(0,0,0.98);
        glVertex3f(len,0,0.98);
	
    glEnd();

    glTranslatef(0,-0.1,0);
    
    glEnable(GL_LIGHTING);    
}
/*Iscrtavanje kutija u 3 trake*/
void draw_box(float x,float z,int color){

	glPushMatrix();
	glLineWidth(2);
    switch(color) {
        case 0: 
		/*Crtanje kocke*/
		glPushMatrix();
            glTranslatef(x,0.28,z);
            glRotatef(45,0,1,0);
            glColor3f(0.4237,0.08235,0.47843);
            glutWireCube(0.3);
			glColor3f(0.498039216, 0.2, 1);
            glutSolidCube(0.3);
		glPopMatrix();
		/*Crtanje bodlji na kocki*/
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-45,0,1,0);
			glTranslatef(0,0,0.15);
			glColor3f(0.2,0,0.4);
 			glutSolidCone(0.05,0.16,50,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-90,1,0,0);
			glTranslatef(0,0,0.15);
 			glutSolidCone(0.05,0.16,50,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-135,0,1,0);
			glTranslatef(0,0,0.15);
 			glutSolidCone(0.05,0.16,50,100);
		glPopMatrix();
        break;

        case 1:
		/*Crtanje kocke*/
		glPushMatrix();
            glTranslatef(x,0.28,z);
           	glRotatef(45,0,1,0);
            glColor3f(0.4,0, 0.4);
            glutWireCube(0.3);
            glColor3f(1, 0, 1);
            glutSolidCube(0.3);
		glPopMatrix();
		/*Crtanje bodlji na kocki*/
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-45,0,1,0);
			glTranslatef(0,0,0.15);
			glColor3f(0.4,0, 0.4);
 			glutSolidCone(0.05,0.16,50,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-90,1,0,0);
			glTranslatef(0,0,0.15);
 			glutSolidCone(0.05,0.16,100,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-135,0,1,0);
			glTranslatef(0,0,0.15);
 			glutSolidCone(0.05,0.16,100,100);
		glPopMatrix();
            break;

        case 2:
		/*Crtanje kocke*/
		glPushMatrix();
            glTranslatef(x,0.28,z);
            glRotatef(45,0,1,0);
            glColor3f(0.2,0.1,1);
			glColor3f(0,0,0.38039);
            glutWireCube(0.3);
            glColor3f(0,0,1);
            glutSolidCube(0.3); 
		glPopMatrix();
		/*Crtanje bodlji na kocki*/
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-45,0,1,0);
			glTranslatef(0,0,0.15);
			glColor3f(0.074509,0,0.38039);
 			glutSolidCone(0.05,0.16,100,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-90,1,0,0);
			glTranslatef(0,0,0.15);
 			glutSolidCone(0.05,0.16,100,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-135,0,1,0);
			glTranslatef(0,0,0.15);
 			glutSolidCone(0.05,0.16,100,100);
		glPopMatrix();
            break;   
      
    }   
    
	glPopMatrix();   

}
/*Iscrtavanje drugih objekata(za sakupljanje bodova)*/
void draw_objects(float x,float z){
	glPushMatrix();
		glLineWidth(1);
    	glTranslatef(x,0.28,z);
		glTranslatef(-5,0,0);
		glTranslatef(0,-0.1,0);
	    glScalef(1,1.25,0.75);
		glRotatef(rotationObject,0,-1,0);
		glRotatef(45,1,0,0);
		glScalef(0.4,1,1);
        glColor3f(1, 1, 0);
        glutWireCube(0.133);
        glColor3f(0.788235294,0.788235294,0.0235);
        glutSolidCube(0.113);	
	glPopMatrix();
}
/*Crtanje puta*/
void draw_path(){
    glPushMatrix();
        glScalef(100, 0.1, 0.7);
        glutSolidCube(1);
    glPopMatrix();
}
/*Funkcija za crtanje loptice i 
smanjivanje iste kada dodje do 
sudara sa kockom pomocu shrinkParametra*/

void draw_ball(){
    glPushMatrix();
        glTranslatef(0,0.15,0);
		glRotatef(rotationParameter,0,0,-1);

		/*Postavljanje teksture na loptu
		 Deo ispod kopiran je sa githuba od koleginice*/
   		 sphere=gluNewQuadric();
   		 glEnable(GL_TEXTURE_2D);
    	 gluQuadricDrawStyle(sphere, GLU_FILL);
   		 glBindTexture(GL_TEXTURE_2D, textures[4]);
   		 gluQuadricTexture(sphere, GL_TRUE);
   		 gluQuadricNormals(sphere, GLU_SMOOTH);
   		 gluSphere(sphere, shrinkParameter, 30, 30);

   		 glDisable(GL_TEXTURE_2D);
   		 glBindTexture(GL_TEXTURE_2D,0);
		 
    glPopMatrix();
}
/*Prvobitno nebo*/
void draw_sky(){
    glPushMatrix();
       glColor3f(0, 0, 0.2); 
       glTranslatef(4,1,0);
       glScalef(3.2, 1, -7);
       glutSolidCube(1);
    glPopMatrix();
}

/*Prvobitan pod*/
void draw_ground(){
glPushMatrix();
		glColor3f(0.85, 0.511, 0.9);
		glTranslatef(3,0,8);
		glScalef(100,0.1,20);
		glutSolidCube(0.7);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.85, 0.511, 0.9);
		glTranslatef(3,0,-8);
		glScalef(100,0.1,20);
		glutSolidCube(0.7);
	glPopMatrix();

}
//Izgled 3 spojena "puta" 
void draw_scene() {
	glPushMatrix();
        draw_seperation_lines(30);
       
		glColor3f(0,0.35,0.35);
    	draw_path();

    	glTranslatef(0,0,0.7);
		glColor3f(0,0.135,0.135);
    	draw_path();

    	glTranslatef(0,0,-1.4);
    	draw_path();
  	 glPopMatrix(); 
}
/*Ispisivanje score-a koji predstavlja trenutni rezultat*/
void draw_score(){

    char score_str[50];
	glColor3f(0.788235294,0.788235294,0.0235);

  /*Menjanje projekcije*/
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
   	 glLoadIdentity();
      gluOrtho2D(0, window_width, 0, window_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
      glLoadIdentity();

  /*Ispisivanje scora na ekranu*/
      glPushMatrix();
        glRasterPos2f(window_width-1205, window_height-60);
        sprintf(score_str, "SCORE: %d", score);
        int length = strlen(score_str);
        for (int i = 0; i < length; i++) {
          glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score_str[i]);
        }
      glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
      

}

