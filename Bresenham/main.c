/* Jesús Alejandro Pablo Ojeda */
#include <stdio.h>
#include <math.h>

void bresenham(int xi, int yi, int xf, int yf);

int main(int argc, char *argv[]) {
	int xi, xf, yi, yf;
			
	printf("*******************************\n");
	printf("**  Algoritmo de Bresenham  ***\n");
	printf("*******************************\n");
	
	printf("introduce xi: ");
	scanf("%d", &xi );
	printf("introduce yi: ");
	scanf("%d", &yi );
	printf("introduce xf: ");
	scanf("%d", &xf );
	printf("introduce yf: ");
	scanf("%d", &yf );
			
	bresenham(xi, yi, xf, yf);
	return 0;
}

void bresenham(int xi, int yi, int xf, int yf){	
	int dx, dy;
	int temp;
	int p, pAux;	
	int a, b; 
	float m;	
	int k;
	int inc = 1;
		
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

	if (m>1 || m<-1){
		temp = dy;
		dy = dx;
		dx = temp;	
	}

	pAux = p = 2*dy - dx;
	a = 2*dy;
	b = 2*(dy - dx);
	
	printf("k\t| p\t| x\t| y\t \n");
	
	for(k = 0;  k< dx; k++){
		pAux = p;		
		if ( m > 1 ){
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
		} else if (m>-1){
			if( p < 0){
				p += a;
				xi++;
			}else{
				p += b;
				xi++;
				yi--;
			}
		}else if ( m<-1 ){
			if( p < 0){
				p += a;
				yi--;
			}else{
				p += b;
				xi++;
				yi--;
			}
		}		
		printf("%d\t| %d\t| %d\t| %d\t \n", k, pAux, xi, yi);		
	}
	printf("a = %d, b = %d", a, b);
}
