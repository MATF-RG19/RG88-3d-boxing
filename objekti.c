#include "objekti.h"

//Crtanje osa, trenutno je zakomentarisana funkcija
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
//Crtanje linija po putu, kojim se odvajaju 3 napravljene trake
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
//Crtanje jedne kutije
void draw_box(){
glPushMatrix();
  glLineWidth(2);
    glTranslatef(2,0.28,0);
    glRotatef(45,0,1,0);
    glColor3f(0.9529, 0.011, 0.921);
    glutWireCube(0.3);
    glColor3f(0.4117,0.08235,0.47843);
    glutSolidCube(0.3);
    
glPopMatrix();   

}
//Crtanje puta
void draw_path(){
    glPushMatrix();
      //  glColor3f(0, 0.2, 0.2); 
        glScalef(100, 0.1, 0.7);
        glutSolidCube(1);
    glPopMatrix();
}
//Loptica
void draw_ball(){
    glPushMatrix();
        glTranslatef(0,0.15,0);
        glColor3f(0.9529, 0.011, 0.921); 
        glutSolidSphere(0.08,100,50);
    glPopMatrix();
}
void draw_sky(){
    glPushMatrix();
       glColor3f(0, 0, 0.2); 
       glTranslatef(4,1,0);
       glScalef(3.2, 1, -7);
       glutSolidCube(1);
    glPopMatrix();
      
}
//Crtanje poda, zakomentarisano je, jer se kasnije na ovo postavlja tekstura
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
//Izgled 3 spojena "puta" iliti stazice
void draw_scene() {
	glPushMatrix();
        draw_seperation_lines(20);
       
		glColor3f(0,0.4,0.4);
    	draw_path();

    	glTranslatef(0,0,0.7);
		glColor3f(0,0.2,0.2);
    	draw_path();

    	glTranslatef(0,0,-1.4);
    	draw_path();
  	 glPopMatrix();

   	 glPushMatrix();
    	//draw_ground();
   	 glPopMatrix();

    
}
//Crtanje dolazecih kutija, kroz 3 petlje
void draw_boxes() {
   glPushMatrix();
	draw_box();
	    for(int i = 0 ; i < 100; i++)
	    {
	    	glTranslatef(9,0,0);
	    	draw_box();
	    }
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(3,0,0.6);
    	draw_box(); 
    	for(int i = 0 ; i < 100 ; i++)
	    {
	    	glTranslatef(9,0,0);
	    	draw_box();
	    }
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(3,0,-0.6);
    	draw_box(); 
    	for(int i = 0 ; i < 100; i++)
	    {
	    	glTranslatef(9,0,0);
	    	draw_box();
	    }
    glPopMatrix();
}



