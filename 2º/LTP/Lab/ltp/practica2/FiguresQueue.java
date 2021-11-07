package practica2;

import practica1.Figure;
import practica2.librerias.implementaciones.QueueAL;

/**
 * class FiguresQueue.
 * 
 * @author LTP 
 * @version 2020-21
 */

public class FiguresQueue<T extends Figure> extends QueueAL<T> { 

    public double area() {
        double sum = 0;
        
        for(int i = 0; i < this.size(); i++) {
            T aux = this.dequeue();
            sum += aux.area();
            this.enqueue(aux);
            
            /* // forma alternativa
             * sum += this.first().area();
             * this.enqueue(this.dequeue());
             */
        }
        
        return sum;
    }
}