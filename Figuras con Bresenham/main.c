#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAM 50

void polares_cartesianas(int r, int ang, int lados);
void bresenham(int xi, int yi, int xf, int yf);
void grafica();

int med; 
char cuadrante[TAM][TAM];
int coordenadas[TAM][2];

int main(int argc, char *argv[]) {
	int i, j;
	int r;
	int ang;
	int lados;
	med = TAM/2;
	
	printf("\n\tCoordenadas Polares\n");
	printf("\nIngresa el numero de lados:");
	scanf("%d",&lados);
		
	ang = (360/lados);
	
	printf("ingresa el tamanio del radio:");
	scanf("%d",&r);
	printf("angulo: %d\n",ang);
		
	for(i = 0; i<TAM; i++){
		for(j = 0; j<TAM; j++){
			if(j == med ){
				cuadrante[i][j] = '|';
			}
			else if(i==med){
				cuadrante[i][j] = '_';
			}
			else{
				cuadrante[i][j] = ' ';
			}
		}
	}

	polares_cartesianas(r, ang, lados);
		
	for(i = 0; i < lados; i++){	
		if(i == lados-1){
			bresenham(coordenadas[i][0], coordenadas[i][1], coordenadas[0][0], coordenadas[0][1]);
		}else{		
			bresenham(coordenadas[i][0], coordenadas[i][1], coordenadas[i+1][0], coordenadas[i+1][1]);		
		}
	}	
	grafica();
	
	return 0;
}

void bresenham(int xi, int yi, int xf, int yf){

	int dx, dy;
	int temp;
	int p, pAux;	
	int a, b; 
	float m;	
	int k;
		
	dx = abs(xf-xi);
	dy = abs(yf-yi);
	m = (float)(yf-yi)/(xf-xi);
	printf("m = %f \n", m);
	if(xi>xf){
		temp = xf;
		xf = xi;
		xi = temp;
		
		temp = yf;
		yf = yi;
		yi = temp;
	}

	if (m >= 1 || m <= -1){
		temp = dy;
		dy = dx;
		dx = temp;	
	}

	pAux = p = 2*dy - dx;
	a = 2*dy;
	b = 2*(dy - dx);
	printf("k\t| p\t| x\t| y\t \n");
	//printf("%d\t| %d\t| %d\t| %d\t \n", k, pAux, xi, yi);
	cuadrante[yi+med][xi+med]='°';
	for(k = 0;  k< dx; k++){
		pAux = p;		
		if ( m >= 1 ){
			if( p < 0 ){
				p += a;
				yi++;
			} else{
				p += b;
				xi++;
				yi++;
			}
		}else if (m > 0){
			if( p < 0 ){
				p += a;
				xi++;
			} else{
				p += b;
				xi++;
				yi++;			
			}
		} else if (m > -1){
			if( p < 0){
				p += a;
				xi++;
			}else{
				p += b;
				xi++;
				yi--;
			}
		}else if ( m <= -1 ){
			if( p < 0){
				p += a;
				yi--;
			}else{
				p += b;
				xi++;
				yi--;
			}
		}
		cuadrante[yi+med][xi+med]='°';
		printf("%d\t| %d\t| %d\t| %d\t \n", k, pAux, xi, yi);		
	}
	printf("\n");
	printf("a = %d, b = %d \n", a, b);
}

void polares_cartesianas(int r, int ang, int lados){
	int i, j;
	int aux = 0;
	float rad;
	for(i=0 ; i<lados ; i++){
		for(j=0 ; j<2 ;j++){
			rad = (M_PI * aux)/ 180;
			if (j==0){
				coordenadas[i][j] = round( r * cos(rad) );
			}
			else{
				coordenadas[i][j] = round( r * sin(rad) );
			}
		}
		aux = aux + ang;
	}
}

void grafica(){	
	int i, j;
	for(i = 0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			printf("%c", cuadrante[i][j]);
		}
		printf("\n");		
	}
}

			
