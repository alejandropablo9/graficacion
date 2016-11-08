package fractalmoore;
import java.awt.*;

public class Tortuga {
    double x;
    double y;
    double angulo;    //radianes
    Color color;
    Graphics g;
    public Tortuga(double x, double y, double angulo, Color color) {
        this.x=x;
        this.y=y;
        this.angulo=angulo*Math.PI/180;
        this.color=color;
    }
    public Tortuga() {
        this.x=0.0;
        this.y=0.0;
        this.angulo=0.0;
        this.color=Color.BLUE;
    }
    public void inicia(Graphics g){
        x=0.0;
        y=0.0;
        angulo=0.0;
        color=Color.RED;
        this.g=g;
    }
    public void colorea(Color color){
        this.color=color;
    }
    public void gira(double angulo){
        this.angulo+=angulo*Math.PI/180;
    }
    public void salta(double x, double y){
        this.x=x;
        this.y=y;
    }
    public void salta(double distancia){
        double xx=x+distancia*Math.cos(angulo);
        double yy=y-distancia*Math.sin(angulo);
        salta(xx, yy);
    }

    public void traza(double distancia){
        double xx=x+distancia*Math.cos(angulo);
        double yy=y-distancia*Math.sin(angulo);
        g.setColor(color);
        g.drawLine((int)xx, (int)yy, (int)x, (int)y);
        salta(xx, yy);
    }
}