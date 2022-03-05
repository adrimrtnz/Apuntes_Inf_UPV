package tema5;

import java.util.concurrent.*;
import java.util.concurrent.locks.*;

class BufferOk implements Buffer {
    private int elems, cabeza, cola, N;
    private int[] datos;

    ReentrantLock lock;
    Condition noLleno, noVacio;

    public BufferOk(int N) {
        datos = new int[N];
        this.N = N;
        cabeza = cola = elems = 0;

        lock = new ReentrantLock();      // en semáforos esto es el MUTEX
        noLleno = lock.newCondition();
        noVacio = lock.newCondition();
    }

    // Método productor
    public void put(int x) {
        try {
            lock.lock();
            while(elems == N) {
                System.out.println("productor esperando...");
                try { noLleno.await(); }
                catch(InterruptedException e) {}
            }

            datos[cola] = x;
            cola = (cola+1)%N;
            elems++;
            noVacio.signal();
        }
        finally {
            lock.unlock();
        }
    }

    // Método consumidor
    public int get() {
        int x;
        try {
            lock.lock();
            while(elems == 0) {
                System.out.println("consumidor esperando...");
                try { noVacio.await(); }
                catch(InterruptedException e) {}
            }

            x = datos[cabeza];
            cabeza = (cabeza+1)%N;
            elems--;
            noLleno.signal();
        }
        finally {
            lock.unlock();
        }

        return x;
    }
}
