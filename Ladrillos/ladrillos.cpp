#include <math.h>
#include "miniwin.h"
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;
using namespace miniwin;

const int CUADRO   = 25;
const int vistaX   = 441;
const int vistaY   = 469;
const int COLUMNAS = 11;
const int FILAS    = 18;
const int ancho = (CUADRO * COLUMNAS) + COLUMNAS;
const int alto  = (CUADRO * FILAS) + FILAS;
const int xf = ancho/2;
const int yf = alto;
const int  mita = xf - 25;
 
double vec_x, vec_y;
int juego = 0;
int tablero[FILAS][COLUMNAS];
struct Coord { int x, y; };
struct Bola {double x, y;} bola; 
int ladrillos = 0;

Coord calcular_rotacion(int xi, int yi, int angulo);
void llena_tablero();
void pintar(int xi, int yi, int xf2, int yf2, int angulo);
int maximo(int angulo, int x);
void reflejo(int angulo, int x, int y);
Coord bresenham(int xi, int yi, int xf, int yf);
void mover_pelota();
void colision();
string a_string(int angulo);
int main(){
	Coord c;
	int angulo = -90;	
	int xi, yi;
	int y;
	xi = xf+40;
	yi = yf;
	bola.x = xf;
	bola.y = yf;
	
	llena_tablero();
	vredimensiona(vistaX, vistaY);
	c = calcular_rotacion(xi, yi, angulo);
	pintar(xi, yi, xf, 1, angulo);
	
	int t = tecla();
	while( t != ESCAPE && ladrillos != 0){
		colision();
		if(t == ESPACIO && !juego){
			vec_y = sin((M_PI * angulo)/ 180) * 5;
			vec_x = cos((M_PI * -angulo)/ 180) * 5;
			juego = 1;
		}		
		if (t == IZQUIERDA){
			if(angulo > -160){		
				angulo--;
				c = calcular_rotacion(xi, yi, angulo);
			}
		} else if (t == DERECHA){			
			if(angulo < -20){
				angulo++;	
				c = calcular_rotacion(xi, yi, angulo);			
			}
		}
		if(angulo == -90){					 
			pintar(c.x, c.y, xf, 1, angulo);
		}
		else if(angulo >= -89){ 
			y = maximo(angulo, mita) + c.y;
			pintar(c.x, c.y, ancho, y, angulo);
		}
		else{
			 y = maximo(-angulo, mita) + c.y;
			pintar(c.x, c.y, 1, y, angulo);
		}
		t = tecla();
		espera(10);
		
	}  
	mensaje("Juego terminado");
	vcierra();
	return 0;
}

void reflejo(int angulo, int x, int y){
	int xc, yc;
	double rad = (M_PI * angulo)/ 180;
	color(ROJO);
	if(angulo > -90){
		yc = maximo (angulo, mita);
		linea(x, y, 1, yc);
	}
	else if(angulo < -90){
		yc = maximo (-angulo, mita);
		linea(x, y, ancho, yc);
	}	
}

void pintar(int xi, int yi, int xf2, int yf2, int angulo){
	int i, j;
	int x; 
	int y=1;	
    
    borra();
    color_rgb(112, 150, 150);
    rectangulo_lleno(0, 0, vistaX, vistaY);

	for(i = 0; i < FILAS; i++){
		x = 0;
		for(j = 0; j < COLUMNAS; j++){
			if(tablero[i][j] == 1){
				color(BLANCO);
				rectangulo_lleno(x, y, x + CUADRO, y + CUADRO);
			}/*else{
				color_rgb(100, 100, 100);
				rectangulo_lleno(x, y, x + CUADRO, y + CUADRO);
			}*/
			x += CUADRO + 1;		
		}
		y += CUADRO + 1;		
	}
	
	texto(ancho + 40, 20, "Angulo ");
	texto(ancho + 40, 40, a_string(angulo));
	texto(ancho + 40, 60, "pos x");
	texto(ancho + 40, 80, a_string(bola.x));
	texto(ancho + 40, 100, "pos y");
	texto(ancho + 40, 120, a_string(bola.y));
	
	/*PISTOLA*/
	//color(ROJO);
	//linea(xf, yf, xf2, yf2);
	//reflejo(angulo, xf2, yf2);
	color(BLANCO); //color_rgb(225, 255, 200);//color(CYAN);
	circulo(xf, yf, 10);
	color(BLANCO); //color_rgb(225, 255, 200);//color(CYAN);
	linea(xi, yi, xf, yf);
	if(!juego){
		circulo_lleno(xf, yf, 5);
	}
	else{
		mover_pelota();
	}	
	/*MARCO*/
	color(NEGRO);
	rectangulo(0, 0, ancho, alto);
	refresca();			
}

void mover_pelota(){
	if((bola.x + vec_x) > ancho - 5){
		vec_x = -vec_x;
		bola.x = ancho - 5;
	}
	if((bola.x + vec_x) < 6){
		vec_x = -vec_x;
		bola.x = 6;
	} 
	if((bola.y + vec_y) < 5){
		vec_y = -vec_y; 
		bola.y = 5;
	}if((bola.y + vec_y > alto)){
		juego = 0;
		bola.x = xf;
		bola.y = yf;
	}
	bola.x += vec_x;
	bola.y += vec_y;
	color(NEGRO);
	circulo_lleno(bola.x, bola.y, 5);
}

int maximo(int angulo, int x){
	return x * tan((M_PI * angulo)/ 180);	
}

void colision(){
	int x, y;
	x = bola.x / 26;
	y = bola.y / 26;
	
	if(tablero[y][x] == 1){
		tablero[y][x] = 0;
		juego = 0;
		bola.x = xf;
		bola.y = yf;
		ladrillos--; 
	}		
}

void llena_tablero(){
	int i, j;
	int aux = 0;
	
	for(i = 0; i < FILAS; i++){
		for(j = 0; j < COLUMNAS; j++)
			tablero[i][j] = 0;
		for(j = aux; j < COLUMNAS - aux; j++){
			tablero[i][j] = 1;
			ladrillos++;
		}
		aux++;
	}	
}

Coord calcular_rotacion(int xi, int yi, int angulo){
	Coord cd;
	float rad = (M_PI * angulo)/ 180;
	
	cd.x = round(xf + ((xi-xf)*cos(rad)) - ((yi - yf)*sin(rad))); 
	cd.y = round(yf + ((xi-xf)*sin(rad)) + ((yi - yf)*cos(rad)));
	
	return cd;
}

string a_string(int puntos) {
   stringstream sout;
   sout << puntos;
   return sout.str();
}

