
#include "hashVisitaDia.h"

struct nodo{
    TVisitaDia visita;
    nodo *sig;
};

struct rep_hashvisitadia {
    nodo **coleccion;
    int max;
};

// interna funcion hash
int funcionHash(TFecha fecha, int cantEstimadas){
    return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

THashVisitaDia crearTHashVisitaDia(int cantEstimadas){
    THashVisitaDia nuevo = new rep_hashvisitadia;
    nuevo->coleccion = new nodo*[cantEstimadas];
    for (int i = 0; i < cantEstimadas; i++){
        nuevo->coleccion[i] = NULL;
    }
    nuevo->max = cantEstimadas;
    return nuevo;
}

void agregarVisitaDiaTHashVisitaDia(THashVisitaDia hash, TVisitaDia visitaDia){
    int posicion = funcionHash(fechaTVisitaDia(visitaDia),hash->max);
    nodo* nuevo = new nodo;
    nuevo->visita = visitaDia;
    nuevo->sig = hash->coleccion[posicion];
    hash->coleccion[posicion] = nuevo;
}

void imprimirTHashVisitaDia(THashVisitaDia hash){
    for (int i = 0; i < hash->max; i++){
        if (hash->coleccion[i] == NULL){
            printf("No hay elementos guardados la posicion %d de la tabla.\n", i);
        } else {
            printf("Elementos en la posicion %d de la tabla:\n",i);
            nodo *aux = hash->coleccion[i];
            while (aux != NULL){
                imprimirTVisitaDia(aux->visita);
                aux = aux->sig;
            }
        }
    }
}

TVisitaDia obtenerVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha){
    int pos = funcionHash(fecha, hash->max);
    nodo *aux = hash->coleccion[pos];
    while (aux != NULL){
        if (compararTFechas(fecha,fechaTVisitaDia(aux->visita)) == 0){
            return aux->visita;
        }
        aux = aux->sig;
    }
    return NULL;
}

bool perteneceVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha){
    int pos = funcionHash(fecha, hash->max);
    nodo *aux = hash->coleccion[pos];
    while (aux != NULL){
        if (compararTFechas(fecha,fechaTVisitaDia(aux->visita)) == 0){
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

void liberarTHashVisitaDia(THashVisitaDia &hash){
    for (int i = 0; i < hash->max; i++){
        nodo *actual = hash->coleccion[i];
        while (actual != NULL){
            nodo *aux = actual;
            actual = actual->sig;
            //
            if (aux->visita != NULL){
                liberarTVisitaDia(aux->visita);
            }
            delete aux;
        }
    }
    delete[] hash->coleccion;
    delete hash;
    hash = NULL;
}
