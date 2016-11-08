
package fractalmoore;

import java.awt.Graphics;

/**
 *
 * @author JesúsAlejandro
 */
class FMoore {
    Tortuga tortuga;
    int wAncho, wAlto;
    int orden;
    public FMoore(Tortuga tortuga, int wAncho, int wAlto, int orden) {
        this.tortuga = tortuga;
        this.wAncho = wAncho;
        this.wAlto = wAlto;
        this.orden = orden;
        curvaHilbert();
    }
     
    
    void generaHilbert(int nivel, int direccion, double distancia){
  	if(nivel>0){
            tortuga.gira(-90*direccion);
            generaHilbert(nivel-1, -direccion, distancia);
            tortuga.traza(distancia);
            tortuga.gira(90*direccion);
            generaHilbert(nivel-1, direccion, distancia);
            tortuga.traza(distancia);
            generaHilbert(nivel-1, direccion, distancia);
            tortuga.gira(90*direccion);
            tortuga.traza(distancia);
            generaHilbert(nivel-1, -direccion, distancia);
            tortuga.gira(-90*direccion);
   	}
    }
 void curvaHilbert(){
    double distancia=wAlto-10;
    double x=wAncho/2-wAlto/2;
    double y=495.0;
	tortuga.salta(x, y);
	generaHilbert(orden, -1, distancia/(potencia2(orden)-1));
 }
 private long potencia2(int n){
    long resultado=1;
    for(int i=1; i<=n; i++){
        resultado*=2;
    }
    return resultado;
 }
    
}
