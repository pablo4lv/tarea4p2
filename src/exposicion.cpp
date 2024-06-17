#include "../include/exposicion.h"

struct rep_exposicion{
    int id;
    TFecha inicio;
    TFecha fin;
    TConjuntoPiezas conjunto;
};

TExposicion crearTExposicion(int idExp, TFecha ini, TFecha fin, int cantMax){
    TExposicion nuevo = new rep_exposicion;
    nuevo->id = idExp;
    nuevo->inicio = ini;
    nuevo->fin = fin;
    nuevo->conjunto = crearTConjuntoPiezas(cantMax);
    return nuevo;
}

void agregarATExposicion(TExposicion &exp, TPieza p){
    insertarTConjuntoPiezas(exp->conjunto, idTPieza(p));
}

bool perteneceATExposicion(TExposicion exp, TPieza p){
    return perteneceTConjuntoPiezas(exp->conjunto,idTPieza(p));
}

int idTExposicion(TExposicion exp){
    return exp->id;
}

void imprimirTExposicion(TExposicion exp){
    printf("Exposicion #%i del ", exp->id);
    imprimirTFecha(exp->inicio);
    printf(" al ");
    imprimirTFecha(exp->fin);
    printf("\n");
    printf("Piezas: ");
    imprimirTConjuntoPiezas(exp->conjunto);
}

TFecha fechaInicioTExposicion(TExposicion exp){
    return exp->inicio;
}

TFecha fechaFinTExposicion(TExposicion exp){
    return exp->fin;
}

bool sonExposicionesCompatibles(TExposicion exp1, TExposicion exp2){
    //Si se superponen
    if (!(compararTFechas(exp1->fin,exp2->inicio) < 0 || compararTFechas(exp2->fin,exp1->inicio) < 0)){
        //y tienen piezas en comun
        TConjuntoPiezas interseccion = interseccionTConjuntoPiezas(exp1->conjunto,exp2->conjunto);
        if(!esVacioTConjuntoPiezas(interseccion)){
            liberarTConjuntoPiezas(interseccion);
            return false;
        }
        liberarTConjuntoPiezas(interseccion);
    }
    return true;
}

void liberarTExposicion(TExposicion &exp){
    if (exp->inicio != NULL){
        liberarTFecha(exp->inicio);
    }
    if (exp->fin){
        liberarTFecha(exp->fin);
    }
    liberarTConjuntoPiezas(exp->conjunto);
    delete exp;
    exp = NULL;
}


// Agregados tarea 4

TConjuntoPiezas obtenerPiezasTExposicion(TExposicion expo){
    return expo->conjunto;
}
