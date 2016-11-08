#include <Gl/gl.h>
#include <Gl/glut.h>
#include <math.h>
#define PI 3.1416

float x = -8;
float y = -2;
GLfloat xi = 0;
GLfloat yi = 0;
//GLint numLados = 3;
GLint escala = 1;
GLdouble anguloY = 0;
GLdouble anguloX = 0;
GLdouble anguloZ = 0;


void poligono(){
	
	/*A*/
	glBegin(GL_LINE_LOOP);
		glVertex2f(0 + x, 0 + y);
		glVertex2f(1 + x, 0 + y);
		glVertex2f(1 + x, 2 + y);
		glVertex2f(2 + x, 2 + y);	
		glVertex2f(2 + x, 0 + y);
		glVertex2f(3 + x, 0 + y);
		glVertex2f(3 + x, 5 + y);
		glVertex2f(0 + x, 5 + y);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(1 + x, 3 + y);
		glVertex2f(2 + x, 3 + y);
		glVertex2f(2 + x, 4 + y);
		glVertex2f(1 + x, 4 + y);
	glEnd();
	
	/*L*/
	glBegin(GL_LINE_LOOP);
		glVertex2f(4 + x, 0 + y);
		glVertex2f(7 + x, 0 + y);
		glVertex2f(7 + x, 1 + y);
		glVertex2f(5 + x, 1 + y);
		glVertex2f(5 + x, 5 + y);
		glVertex2f(4 + x, 5 + y); 
	glEnd();
	/*E*/
	glBegin(GL_LINE_LOOP);
		glVertex2f( 8 + x, 0 + y);
		glVertex2f(11 + x, 0 + y);
		glVertex2f(11 + x, 1 + y);
		glVertex2f( 9 + x, 1 + y);
		glVertex2f( 9 + x, 2 + y);
		glVertex2f(11 + x, 2 + y);
		glVertex2f(11 + x, 3 + y);
		glVertex2f( 9 + x, 3 + y);
		glVertex2f( 9 + x, 4 + y);
		glVertex2f(11 + x, 4 + y);
		glVertex2f(11 + x, 5 + y);
		glVertex2f( 8 + x, 5 + y);
	glEnd();
	/*X*/
	glBegin(GL_LINE_LOOP);
		glVertex2f(12 + x, 0 + y);
		glVertex2f(13 + x, 0 + y);
		glVertex2f(13.5 + x, 1.5 + y);
		glVertex2f(14 + x, 0 + y);
		glVertex2f(15 + x, 0 + y);
		glVertex2f(14 + x, 2.5 + y);
		glVertex2f(15 + x, 5 + y);
		glVertex2f(14 + x, 5 + y);
		glVertex2f(13.5 + x, 3.5 + y);
		glVertex2f(13 + x, 5 + y);
		glVertex2f(12 + x, 5 + y);
		glVertex2f(13 + x, 2.5 + y);
	glEnd();
	
	
}

void display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glScaled(escala, escala, 1);
	glRotated(anguloX, 1.0, 0.0, 0.0);	
	poligono();
	glFlush();
}

void arrowkey(int k, int xi, int yi){
		switch (k){
			case(GLUT_KEY_RIGHT): 
				x += 1;
			break;
			case(GLUT_KEY_LEFT): 
				x += -1;
			break;
			case(GLUT_KEY_UP):
				y += 1; 
			break;
			case(GLUT_KEY_DOWN): 
				y += -1;
			break;			
		default:
			break;
	}
	glutPostRedisplay();
	/*switch(k){
		case(GLUT_KEY_RIGHT): 
			x += 1;
		break;
		case(GLUT_KEY_LEFT): 
			x += -1;
		break;
		case(GLUT_KEY_UP):
			y += 1; 
		break;
		case(GLUT_KEY_DOWN): 
			y += -1;
		break;
	}
	glutPostRedisplay();*/
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char k, int x, int y){
	switch(k){	
		case 'r':			
			anguloX += 5;
		break;
		case 'e':						
			escala += 1;
		break;
		case 'w':
			if(escala >= 1)			
			escala -= 1;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	
	glutInit(&argc, argv); 
	//inicia la libreria glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	/*tamaño de ventana*/
	glutInitWindowSize(800, 600);
	/*Posiciona la ventana*/
	glutInitWindowPosition(10, 10);
	/**/
	glutCreateWindow("ALE");
	/*enviar una funcion para que e ejecute de foma independiente
	** */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowkey);
	glutMainLoop();
	return 0;
}
