
#include "hashVisitaDia.h"

struct rep_hashvisitadia {
    TVisitaDia *coleccion;
    int max;
};

// interna funcion hash
int funcionHash(TFecha fecha, int cantEstimadas){
    return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

THashVisitaDia crearTHashVisitaDia(int cantEstimadas){
    THashVisitaDia nuevo = new rep_hashvisitadia;
    nuevo->coleccion = new TVisitaDia[cantEstimadas];
    for (int i = 0; i < cantEstimadas; i++){
        nuevo->coleccion[i] = NULL;
    }
    nuevo->max = cantEstimadas;
    return nuevo;
}

void agregarVisitaDiaTHashVisitaDia(THashVisitaDia hash, TVisitaDia visitaDia){
    int posicion = funcionHash(fechaTVisitaDia(visitaDia),hash->max);
    hash->coleccion[posicion] = visitaDia;
}

void imprimirTHashVisitaDia(THashVisitaDia hash){
}

TVisitaDia obtenerVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha){
    return NULL;
}

bool perteneceVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha){
    return false;
}

void liberarTHashVisitaDia(THashVisitaDia &hash){
    for (int i = 0; i < hash->max; i++){
        if (hash->coleccion[i] != NULL){
            liberarTVisitaDia(hash->coleccion[i]);
        }
    }
    delete hash;
    hash = NULL;
}
