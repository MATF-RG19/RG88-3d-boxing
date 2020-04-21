#include "objekti.h"

extern float endAnimation;
extern float shrinkParameter;

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

    switch(color) {
        case 0: 
		glPushMatrix();
            glTranslatef(x,0.28,z);
            glRotatef(45,0,1,0);
            glColor3f(0.9529, 0.011, 0.921);
            glutWireCube(0.3);
            glColor3f(0.4117,0.08235,0.47843);
            glutSolidCube(0.3);
		glPopMatrix();
			/*Crtanje bodlji na kocki*/
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-45,0,1,0);
			glTranslatef(0,0,0.15);
			glColor3f(0.67,0.121,0.65);
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

        case 1:
		glPushMatrix();
            glTranslatef(x,0.28,z);
           	glRotatef(45,0,1,0);
            glColor3f(1, 0.2, 0.2);
            glutWireCube(0.3);
            glColor3f(0.48,0,0);
            glutSolidCube(0.3);
		glPopMatrix();
		/*Crtanje bodlji na kocki*/
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-45,0,1,0);
			glTranslatef(0,0,0.15);
			glColor3f(1,0.1,0.1);
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

        case 2:
		glPushMatrix();
            glTranslatef(x,0.28,z);
            glRotatef(45,0,1,0);
            glColor3f(0.2,0.1,1);
            glutWireCube(0.3);
            glColor3f(0.03,0.02,0.62);
            glutSolidCube(0.3); 
		glPopMatrix();
		/*Crtanje bodlji na kocki*/
		glPushMatrix();
			glTranslatef(x,0.28,z);
			glRotatef(-45,0,1,0);
			glTranslatef(0,0,0.15);
			glColor3f(0.2,0.1,1);
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
/*Iscrtavanje drugih objekata*/
void draw_objects(float x,float z){
	glPushMatrix();
    	glTranslatef(x,0.28,z);
		glTranslatef(-5,0,0);
		glRotatef(45,1,0,0);
        glColor3f(0, 0.3, 0.3);
        glutWireCube(0.15);
        glColor3f(0,1,1);
        glutSolidCube(0.15);
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
        glColor3f(0.9529, 0.011, 0.921);
        if(endAnimation)
            glColor3f(1,0,0); 
        glutSolidSphere(shrinkParameter,100,50);
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
        draw_seperation_lines(20);
       
		glColor3f(0,0.35,0.35);
    	draw_path();

    	glTranslatef(0,0,0.7);
		glColor3f(0,0.135,0.135);
    	draw_path();

    	glTranslatef(0,0,-1.4);
    	draw_path();
  	 glPopMatrix(); 
}

