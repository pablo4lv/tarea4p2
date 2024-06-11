#include "../include/conjuntoPiezas.h"

struct rep_conjuntopiezas{
    int* ids;
    int cantidad;
    int max;
};

TConjuntoPiezas crearTConjuntoPiezas(int cantMax){
    TConjuntoPiezas nuevo = new rep_conjuntopiezas;
    nuevo->ids = new int[cantMax];
    for (int i = 0; i < cantMax; i++){
        nuevo->ids[i] = 0;
    }
    nuevo->cantidad = 0;
    nuevo->max = cantMax;
    return nuevo;
}

bool esVacioTConjuntoPiezas(TConjuntoPiezas c){
    return c->cantidad == 0;
}

void insertarTConjuntoPiezas(TConjuntoPiezas &c, int id){
    if (id < c->max){
        if (c->ids[id] != 1){
            c->ids[id] = 1;
            c->cantidad++;
        }
    }
}

void borrarDeTConjuntoPiezas(TConjuntoPiezas &c, int id){
    if (c->ids[id] != 0){
        c->ids[id] = 0;
        c->cantidad--;
    }
}

bool perteneceTConjuntoPiezas(TConjuntoPiezas c, int id){
    if(id < c->max){
        return (c->ids[id] == 1);
    } else {
        return false;
    }
}

int cardinalTConjuntoPiezas(TConjuntoPiezas c){
    return c->cantidad;
}

int cantMaxTConjuntoPiezas(TConjuntoPiezas c){
    return c->max;
}

void imprimirTConjuntoPiezas(TConjuntoPiezas c){
    for (int i = 0; i < c->max; i++){
        if(c->ids[i] == 1){
            printf("%i ",i);
        }
    }
    printf("\n");   
}

void liberarTConjuntoPiezas(TConjuntoPiezas &c){
    delete[] c->ids;
    delete c;
    c = NULL;
}

TConjuntoPiezas unionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){
    TConjuntoPiezas arreglo = crearTConjuntoPiezas(c1->max);
    for (int i = 0; i < c1->max; i++){
        if (c1->ids[i] == 1 || c2->ids[i] == 1){
            insertarTConjuntoPiezas(arreglo, i);
        }
    }
    return arreglo;
}

TConjuntoPiezas interseccionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){
    TConjuntoPiezas arreglo = crearTConjuntoPiezas(c1->max);
    for (int i = 0; i < c1->max; i++){
        if (c1->ids[i] == 1 && c2->ids[i] == 1){
            insertarTConjuntoPiezas(arreglo, i);
        }
    }
    return arreglo;
}

TConjuntoPiezas diferenciaTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){
    TConjuntoPiezas arreglo = crearTConjuntoPiezas(c1->max);
    for (int i = 0; i < c1->max; i++){
        if (c1->ids[i] == 1 && c2->ids[i] != 1){
            insertarTConjuntoPiezas(arreglo, i);
        }
    }
    return arreglo;
}
