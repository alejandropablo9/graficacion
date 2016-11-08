#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846
using namespace std;

GLfloat xi = 0.0;
GLfloat yi = 0.0;
//GLint numLados = 3;
GLint escala = 1;

GLdouble anguloY = 0;
GLdouble anguloX = 0;
GLdouble anguloZ = 0;



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



void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(xi, yi, -3);
	glScaled(escala, escala, 1.0);
	//gluPerspective(90.0, 1.0, 1.0, 100.0);

	
	glRotated(anguloX, 1.0, 0.0, 0.0);
	glRotated(anguloY,0.0,1.0,0.0);
	glRotated(anguloZ, 0.0, 0.0, 1.0);
	
	//LADO TRASERO verdefuerte
	glBegin(GL_POLYGON);

	glColor3f(0.0, 0.4, 0.3);    
	glVertex3f(0.5, -0.5, -0.5); 
   
	glVertex3f(0.5, 0.5, -0.5);      
     
	glVertex3f(-0.5, 0.5, -0.5);     
    
	glVertex3f(-0.5, -0.5, -0.5);     

	glEnd();

	// LADO FRONTAL: lado amarillo
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// LADO Izquierdo: lado morado
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// LADO derecho: lado verde
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// LADO SUPERIOR: lado azul
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// LADO INFERIOR: lado rojo
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix(); // Cierra la matriz
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Inicializa la matriz de proyeccion
	glOrtho(-10.0, 10.0, -10.00, 10.0, 0.1, 20.0); // WorkSpace
	glMatrixMode(GL_MODELVIEW); // cambiamos la matrix :D

}
void keyboard(unsigned char key, int x, int y){
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 300);

	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ejemplo 3D");
	glEnable(GL_DEPTH_TEST);
	init();
			
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(ArrowKey);
	glutMainLoop();
	return 0;
}

