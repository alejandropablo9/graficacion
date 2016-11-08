#include <Gl/gl.h>
#include <Gl/glut.h>
#include <math.h>
#define PI 3.1416

float radio = 1;
int lados = 3;
float posX = 0;
float posY = 0;
float grados = 0;

void poligono(){
	glBegin(GL_POLYGON);
    	float t = (float) 360 / lados;
    	float grado = grados;
		glColor3f(0, 0, 10);

    	for(int i = 0; i < lados; i++){
        	glVertex2f(radio * cos(PI * grado / 180) + posX, radio * sin(PI * grado / 180) + posY);
        	grado += t;
        	glVertex2f(radio * cos(PI * grado / 180) + posX, radio * sin(PI * grado / 180) + posY);
    	}
	glEnd();
}
void display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	poligono();
	glFlush();
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void arrowkey(int k, int x, int y){
	switch(k){
		case(GLUT_KEY_RIGHT): 
			posX += 0.2;
		break;
		case(GLUT_KEY_LEFT): 
			posX += -0.2;
		break;
		case(GLUT_KEY_UP):
			posY += 0.2; 
		break;
		case(GLUT_KEY_DOWN): 
			posY += -0.2;
		break;
		case(GLUT_KEY_F2):
			radio += 0.1;
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y){
	switch(k){
		case 27:
			exit(0);
		break;
		case 'w':
			if(radio <= 7)
				radio += 0.1;
		break;
		case 'e':
			if(radio >= .2)
			radio += -0.1;
		break;
		case 'r':
			if(grados < 360)
				grados += 5;
			else 
				grados = 0;
		break;
		case 't':
			grados -= 5;
		break;
		case 'l':
			lados++;
		break;
		case 'k':
			if(lados > 3)
				lados--;
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
	glutCreateWindow("OpenGL");
	/*enviar una funcion para que e ejecute de foma independiente
	** */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowkey);
	glutMainLoop();
	return 0;
}




