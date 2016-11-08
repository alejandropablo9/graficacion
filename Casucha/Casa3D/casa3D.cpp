#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "ImageLoader.h"
#define M_PI 3.14159265358979323846
using namespace std;
// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera’s direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=-2.0f,z=13.0f;
float y=1.7f;
float aux1=0.0;
float aux2=0.0;
float alto = 2.95;
float grosor = 0.15;
float grosorLoza = 0.30;
//texturas
GLuint _piso;
GLuint _bricks;
GLuint _muro_interior;
GLuint _pasto;
GLuint _cielo;
GLuint _techo;
GLuint _base;
GLuint _puerta1;
GLuint _puerta2;

GLuint loadTexture(Image* image) {
	GLuint idtextura;
	glGenTextures(1, &idtextura);
	glBindTexture(GL_TEXTURE_2D, idtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return idtextura;
}

void initRendering() {
	Image* piso = loadBMP("pisito_madera.bmp");
	Image* brick = loadBMP("murito2.bmp");
	Image* m_interior = loadBMP("murito_interior.bmp");
	Image* pasto = loadBMP("pastito.bmp");
	Image* cielo = loadBMP("cielo.bmp");
	Image* techo = loadBMP("techito.bmp");
	Image* base = loadBMP("basecita.bmp");
	Image* puerta1 = loadBMP("puerta.bmp");	
	Image* puerta2 = loadBMP("puerta2.bmp");
	
	_piso = loadTexture(piso);
	_bricks = loadTexture(brick);
	_muro_interior = loadTexture(m_interior);
	_pasto = loadTexture(pasto);
	_cielo = loadTexture(cielo);
	_techo = loadTexture(techo);
	_base = loadTexture(base);
	_puerta1 = loadTexture(puerta1);
	_puerta2 = loadTexture(puerta2);
	
	delete piso, brick, m_interior, pasto, cielo, techo, base, puerta1, puerta2;
}

void puertaHorizontal(float posix, float posy, float posz, float largo, GLuint _puerta1){
	//LADO TRASERO rojo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz);       
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy + alto, posz + grosor);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy, posz + grosor);    
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO FRONTAL: lado amarillo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix + largo, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz + grosor);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + largo, posy, posz + grosor);
	glEnd();
	glDisable(GL_TEXTURE_2D);	
		
	// LADO Izquierdo: lado azul
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + largo, posy, posz);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO derecho: lado azul
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz + grosor);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz + grosor);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz + grosor);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + largo, posy, posz + grosor); 
	glEnd();
	glDisable(GL_TEXTURE_2D);	
	
	// LADO SUPERIOR: lado rojo
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(posix, posy + alto, posz); 
	glVertex3f(posix + largo, posy + alto, posz);
	glVertex3f(posix + largo, posy + alto, posz + grosor);
	glVertex3f(posix, posy + alto, posz + grosor);
	glEnd();
	
	// LADO INFERIOR: lado rojo
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(posix, posy, posz); 
	glVertex3f(posix + largo, posy, posz);
	glVertex3f(posix + largo, posy, posz + grosor);
	glVertex3f(posix, posy, posz + grosor);
	glEnd();	
}

void puertaVertical(float posix, float posy, float posz, float largo, GLuint _puerta1){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);    
	glVertex3f(posix, posy, posz); 
	glVertex3f(posix, posy + alto, posz);       
	glVertex3f(posix + grosor, posy + alto, posz);     
	glVertex3f(posix + grosor, posy, posz);    
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO FRONTAL: lado amarillo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz + largo); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz + largo);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + grosor, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// LADO Izquierdo:
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	// LADO derecho: lado azul
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _puerta1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix + grosor, posy, posz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + grosor, posy, posz + largo);	 
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO SUPERIOR: lado azul
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(posix, posy + alto, posz); 
	glVertex3f(posix, posy + alto, posz + largo);
	glVertex3f(posix + grosor, posy + alto, posz + largo);
	glVertex3f(posix + grosor, posy + alto, posz);
	glEnd();
	
	// LADO INFERIOR: lado rojo
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(posix, posy, posz); 
	glVertex3f(posix, posy, posz + largo);
	glVertex3f(posix + grosor, posy, posz + largo);
	glVertex3f(posix + grosor, posy, posz);
	glEnd();
}

void draw_wall(float posix, float posy, float posz, float largo, GLuint _muro1, GLuint _muro2){
	
	//LADO TRASERO rojo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz);       
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy + alto, posz + grosor);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy, posz + grosor);    
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO FRONTAL: lado amarillo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix + largo, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz + grosor);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + largo, posy, posz + grosor);
	glEnd();
	glDisable(GL_TEXTURE_2D);	
		
	// LADO Izquierdo: lado azul
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + largo, posy, posz);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO derecho: lado azul
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz + grosor);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz + grosor);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz + grosor);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + largo, posy, posz + grosor); 
	glEnd();
	glDisable(GL_TEXTURE_2D);	
	
	// LADO SUPERIOR: lado rojo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy + alto, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy + alto, posz + grosor);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy + alto, posz + grosor);
	glEnd();
	glDisable(GL_TEXTURE_2D);	
	
	// LADO INFERIOR:
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix + largo, posy, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + largo, posy, posz + grosor);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy, posz + grosor);
	glEnd();
	glDisable(GL_TEXTURE_2D);	
}

void put_loza(float posx, float posy, float posz, float ancho, float largo, GLuint _muro1, GLuint _muro2){
	//LADO TRASERO verdefuerte	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz);       
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx + ancho, posy, posz);    
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO FRONTAL: lado amarillo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy, posz + largo); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz + largo);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz + largo);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx + ancho, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO Izquierdo: lado morado
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO derecho:
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx + ancho, posy, posz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz + largo);     
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx + ancho, posy, posz + largo);      
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO SUPERIOR: 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy + grosorLoza, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx, posy + grosorLoza, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO INFERIOR: 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx + ancho, posy, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx + ancho, posy, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void sky(){	
	//trasera
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _cielo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-20, -5, -20); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-20, 20, -20);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(20, 20 , -20);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(20, -5, -20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	//fronta
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _cielo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-20, -5, 20); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-20, 20, 20);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(20, 20, 20);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(20, -5, 20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	//derecha
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _cielo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(20, -5, -20); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(20, 20, -20);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(20, 20, 20);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(20, -5, 20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	//izquierda
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _cielo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-20, -5, -20); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-20, 20, -20);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-20, 20, 20);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-20, -5, 20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	//arriba
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _cielo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-20, 20, -20); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(20, 20, -20);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(20, 20, 20);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-20, 20, 20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void put_wall(float posix, float posy, float posz, float largo, GLuint _muro1, GLuint _muro2){
	
	//LADO TRASERO
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz);       
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + grosor, posy, posz);    
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO FRONTAL: lado amarillo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz + largo); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz + largo);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + grosor, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// LADO Izquierdo:
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	// LADO derecho: lado azul
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix + grosor, posy, posz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + grosor, posy, posz + largo);	 
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO SUPERIOR: lado azul
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy + alto, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + grosor, posy + alto, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + grosor, posy + alto, posz);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO INFERIOR:
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posix, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posix, posy, posz + largo);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posix + grosor, posy, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posix + grosor, posy, posz);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void put_techo(float posx, float posy, float posz, float ancho, float largo, GLuint _muro1, GLuint _muro2){ 
	
	//LADO TRASERO
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);    
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(posx, posy, posz); 
   	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy + grosorLoza, posz);       
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz);     
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx + ancho, posy, posz);    
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO FRONTAL: lado amarillo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy, posz + largo); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz + largo);     
	glTexCoord2f(0.0f, 1.0f);glVertex3f(posx + ancho, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO Izquierdo: lado morado
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx, posy, posz); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz + largo);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx, posy, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO derecho: lado verde
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx + ancho, posy, posz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz + largo);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx + ancho, posy, posz + largo);      
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO SUPERIOR: 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx + ancho, posy + grosorLoza, posz + largo);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx, posy + grosorLoza, posz + largo);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	// LADO INFERIOR:
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _muro2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(posx, posy, posz);   
	glTexCoord2f(1.0f, 0.0f); glVertex3f(posx + ancho, posy, posz);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(posx + ancho, posy, posz + largo);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(posx, posy, posz + largo);
	glEnd();
}

void planta_alta(){
	float piso1 = 3.25;
	
	put_techo(-5.0, alto*2.1, 4.15, 3.50, 6.65, _piso,_techo);
	
	put_techo(-1.50, alto*2.1, 5.00, 6.65, 4.63, _piso, _techo);
	
	put_techo(-1.50, alto*2.1, 9.63, 4.92, 3.70, _piso, _techo);
	
	put_wall(-1.67, piso1, 4.43, 0.90,_muro_interior, _bricks);
	put_wall(-1.67, piso1, 5.18, 1.70,_muro_interior, _muro_interior);
	put_wall(-5, piso1, 4.43, 5.73,_bricks,_muro_interior);
	put_wall(-1.07, piso1, 9.68, 3.50, _bricks, _muro_interior);
	put_wall(0.43, piso1, 8.68, 0.95, _muro_interior, _muro_interior);
	put_wall(0.78, piso1, 5.18, 2.25, _muro_interior, _muro_interior);
	
	//recamara
	put_wall(2.68, piso1, 8.68, 4.50, _muro_interior, _bricks);
	put_wall(4.85, piso1, 5.18, 4.30, _muro_interior , _bricks);
	
	//paredes horizontales
	//recamara 
	draw_wall(-1.07, piso1, 13.18, 3.90, _bricks, _muro_interior);
	draw_wall(-5, piso1, 10.08, 2.73, _bricks, _muro_interior);
	draw_wall(0.43, piso1, 8.52, 2.40, _muro_interior, _muro_interior);//largo completo: 4.43
	draw_wall(-4.85, piso1, 7.77, 3.18,_muro_interior, _muro_interior);
	draw_wall(0.93, piso1, 7.30, 1.00,_muro_interior, _muro_interior);
	draw_wall(-0.87, piso1, 6.70, 1.70, _muro_interior, _muro_interior);
	draw_wall(-1.67, piso1, 5.03, 6.68,_muro_interior, _bricks);
	draw_wall(-5, piso1, 4.28, 3.48, _muro_interior, _bricks);
	
	draw_wall(-1.07, piso1, 9.63, 0.55, _muro_interior, _muro_interior);
	
	
	
	puertaVertical(-1.82, piso1,6.82, 0.95, _puerta2);
	puertaVertical(0.80, piso1, 7.43, 1.10, _puerta2);
	puertaHorizontal(-0.52, piso1, 9.63, 0.95, _puerta2);
	puertaHorizontal(-1.55, piso1, 6.70, 0.71, _puerta2);	
	
}

void planta_baja(){
	float piso0 = 0;
	float piso1 = .10;
	
	put_loza(-20, (piso0 - grosorLoza) * 2, -20, 40, 40, _pasto, _pasto);
	
	//Piso
	//estudio
	put_techo(-5.0, piso0 - grosorLoza, 4.43, 3.33, 3.65, _piso, _techo);
	//escaleras
	put_techo(-5.0, piso0 - grosorLoza, 8.08, 3.33, 2.15, _piso, _techo);	
	//pasillo 
	put_techo(-1.67, piso0 - grosorLoza, 5.18, 1.20, 3.65, _piso, _techo);
	//baño y comedor
	put_techo(-0.62, piso0 - grosorLoza, 5.18, 5.63, 3.65, _piso, _techo);
	//sala
	put_techo(-1.07, piso0 - grosorLoza, 8.83, 3.90, 4.50, _piso, _techo);
	//cocina
	put_techo(0.78, piso0 - grosorLoza, 2.43, 4.23, 2.75, _piso, _techo);	
	//sobra
	put_techo(-1.67, piso0 - grosorLoza, 8.68, 0.60, 1.55, _piso, _techo);
	//Entrada
	put_techo(-5.0, piso0 - grosorLoza, 10.23, 3.93, 0.95, _piso, _techo);
	//
	put_techo(2.83, piso0 - grosorLoza, 8.68, 2.18, 1.43, _piso, _techo);

	
	
	//verticales
	put_wall(-5, piso0, 4.43, 6.75, _bricks, _muro_interior); //pared uno
	//estudio
	put_wall(-1.82, piso0, 4.58, 2.45, _muro_interior, _muro_interior);
	put_wall(-0.62, piso0, 5.18, 2.80, _muro_interior, _muro_interior);
	put_wall(0.78, piso0, 2.43, 6.40, _muro_interior, _muro_interior);
	put_wall(4.86, piso0, 2.58, 7.05, _muro_interior, _bricks);
	put_wall(2.68, piso0, 8.68, 4.65, _muro_interior, _bricks);	
	put_wall(-1.07, piso0, 10.06, 3.30,  _bricks, _muro_interior);
	
	//Paredes Horizontales
	draw_wall(-4.85, piso0, 4.43, 3.25, _muro_interior, _bricks);
	draw_wall(-4.85, piso0, 7.93, 3.30, _muro_interior, _bricks);
	draw_wall(-4.85, piso0, 10.08, 2.73, _bricks, _muro_interior);
	//cocina
	draw_wall(1.83, piso0, 2.43, 3.18, _muro_interior, _bricks);
	draw_wall(1.83, piso0, 5.09, 3.18, _muro_interior, _muro_interior);
	//baño
	draw_wall(-0.62, piso0, 5.18, 1.50, _muro_interior, _bricks);
	draw_wall(-0.62, piso0, 8.83, 1.50, _muro_interior, _muro_interior);
	//sala
	draw_wall(-0.92, piso0, 13.18, 3.60, _bricks, _muro_interior);
	//ventana comedor
	draw_wall(2.68, piso0, 8.68, 2.33, _bricks, _muro_interior);
	
	//techo
	put_techo(-5.0, alto, 4.43, 3.33, 3.65, _piso, _techo);
	put_techo(-1.67, alto, 5.18, 6.68, 4.45, _piso, _techo);
	put_techo(0.78, alto, 2.43, 4.23, 2.90, _piso, _techo);
	put_techo(-1.04, alto, 9.63, 3.90, 3.70, _piso, _techo);
		//escaleras
	put_techo(-5.0, alto, 8.08, 3.93, 2.15, _piso, _techo);
	
	puertaHorizontal(-2.17, piso0, 10.08, 1.1, _puerta1);	
	puertaHorizontal(-1.66, piso0, 5.10, 1.05, _puerta1);
	puertaHorizontal(0.93, piso0, 2.43, 0.90, _puerta1);
	
	puertaVertical(-1.82, piso0, 7.0, 0.90, _puerta2);
	puertaVertical(-0.62, piso0, 7.98, 0.90, _puerta2);	
}

void drawSnowMan(){
	glColor3f(1.0f, 1.0f, 1.0f);
// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);
// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);
// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();
// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void renderScene(void) {
// Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Reset transformations
		glLoadIdentity();
// Set the camera
gluLookAt( x, y+aux1, z,
          x+lx, y+aux2, z+lz,
          0.0f, y, 0.0f);
          
		glPushMatrix();
		sky();
		planta_baja();
		planta_alta();
		drawSnowMan();
		glPopMatrix();
		glutSwapBuffers();
}

void changeSize(int w, int h) {
// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
// Reset Matrix	
	glLoadIdentity();
// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
// Set the correct perspective.
	gluPerspective(90.0f, ratio, 0.1f, 90.0f);
// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
 switch(key) {
    case 27: // escape
    	    exit(0);
        break;
        
	case 'a':
		aux1=1.0;
		aux2=0.0;
		break;
	case 's':
		aux1=0.0;
		aux2=0.0;
	 	break;
	case 'd':
		 aux2=1.0;
		 aux1=0.0;
		 break;
		
    }
}

void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.1f;
	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.2f;
			lx = sin(angle);
			lz = -cos(angle);
		break;
		case GLUT_KEY_RIGHT :
			angle += 0.2f;
			lx = sin(angle);
			lz = -cos(angle);
		break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
		break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
		break;
		case GLUT_KEY_END:
			y=y+0.2f;
		break;
		case GLUT_KEY_HOME:
			y=y-0.2f;
			break;
			if(y==1.7f)
			y=1.7f;
		break;
	}
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Casucha 3D");
// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(processSpecialKeys);
// OpenGL init
	glEnable(GL_DEPTH_TEST);
	initRendering();
// enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}
