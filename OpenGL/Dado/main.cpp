#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "ImageLoader.h"
#define M_PI 3.14159265358979323846
using namespace std;

GLfloat xi = 0.0;
GLfloat yi = 0.0;
GLint escala = 1;

GLdouble anguloY = 0;
GLdouble anguloX = 0;
GLdouble anguloZ = 0;
GLuint _frente;
GLuint _atras;
GLuint _izquierda;
GLuint _derecha;
GLuint _superior;
GLuint _inferior;

GLuint loadTexture(Image* image) {
	GLuint idtextura;
	glGenTextures(1, &idtextura);
	glBindTexture(GL_TEXTURE_2D, idtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return idtextura;
}

void initRendering() {
	Image* frente = loadBMP("frente.bmp");
	Image* atras = loadBMP("trasera.bmp");
	Image* inferior = loadBMP("inferior.bmp");
	Image* superior = loadBMP("superior.bmp");
	Image* izquierda = loadBMP("izquierda.bmp");
	Image* derecha = loadBMP("derecha.bmp");
	
	_frente = loadTexture(frente);
	_atras = loadTexture(atras);
	_inferior = loadTexture(inferior);
	_superior = loadTexture(superior);
	_izquierda = loadTexture(izquierda);
	_derecha = loadTexture(derecha);
	
	delete frente, atras, inferior, superior, derecha, izquierda;
	
}	

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void ArrowKey(int key, int x, int y){
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		if (xi < 10)
			xi += 0.5;
		break;

	case GLUT_KEY_LEFT:
		if (xi > -10)
			xi -= 0.5;
		break;

	case GLUT_KEY_UP:
		if (yi < 10)
			yi += 0.5;
		break;

	case GLUT_KEY_DOWN:
		if (yi > -10)
			yi -= 0.5;
		break;
		case GLUT_KEY_HOME:
		if (escala > 5)
			escala = 5;
		cout << "Aumentando Escala" << endl;
		escala = escala + 1;
		break;
	case GLUT_KEY_PAGE_UP:
		if (escala <= 1)
			escala = 1;
		cout << "Reduciendo Escala" << endl;
		escala = escala - 1;
		break;

	case GLUT_KEY_PAGE_DOWN:
		cout << "Rotando positivamente" << endl;
		anguloY += 5;


		break;

	case GLUT_KEY_END:
		cout << "Rotando negativamente" << endl;
		anguloY -= 5;
		break;
	case GLUT_KEY_F2:
		cout << "Rotando positivamente" << endl;
		anguloZ += 5;

	case GLUT_KEY_F3:
		cout << "Rotando negativamente" << endl;
		anguloX -= 5;



	default:
		break;
	}

	glutPostRedisplay();
}

void drawDado(){
	//LADO TRASERO verdefuerte
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _atras);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);  
	glTexCoord2f(0.0f, 0.0f);  
	glVertex3f(0.5, -0.5, -0.5); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);      
	glVertex3f(-0.5, 0.5, -0.5); 
	glTexCoord2f(0.0f, 1.0f);    
	glVertex3f(-0.5, -0.5, -0.5);     
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// LADO FRONTAL: 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _frente);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// LADO Izquierdo: lado morado
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _izquierda);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// LADO derecho: 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _derecha);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);	
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// LADO SUPERIOR: 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _superior);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// LADO INFERIOR:
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _inferior);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	
	glTranslatef(xi, yi, -3);
	glScaled(escala, escala, 1.0);

	glRotated(anguloX, 1.0, 0.0, 0.0);
	glRotated(anguloY,0.0,1.0,0.0);
	glRotated(anguloZ, 0.0, 0.0, 1.0);
	
	drawDado();
	
	glPopMatrix(); // Cierra la matriz
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Inicializa la matriz de proyeccion
	glOrtho(-4.0, 4.0, -4.00, 4.0, 0.1, 4.0); // WorkSpace
	glMatrixMode(GL_MODELVIEW); // cambiamos la matrix :D

}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 300);

	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ejemplo 3D");
	glEnable(GL_DEPTH_TEST);
	init();
	initRendering();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(ArrowKey);
	glutMainLoop();
	return 0;
}

