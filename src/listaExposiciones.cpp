#include "../include/listaExposiciones.h"

struct rep_listaexposiciones{
    TExposicion exposicion;
    TListaExposiciones sig;
};

TListaExposiciones crearTListaExposicionesVacia(){
    return NULL;
}

void agregarExposicionTListaExposiciones(TListaExposiciones &listaExposiciones, TExposicion expo){
    TListaExposiciones nuevo = new rep_listaexposiciones;
    nuevo->exposicion = expo;
    nuevo->sig = NULL;

    //Si se inserta al principio, sea vacía o no la lista
    if (listaExposiciones == NULL || compararTFechas(fechaInicioTExposicion(expo), fechaInicioTExposicion(listaExposiciones->exposicion)) <= 0){
        nuevo->sig = listaExposiciones;
        listaExposiciones = nuevo;
    } else {
        TListaExposiciones aux = listaExposiciones;
        while (aux->sig != NULL && compararTFechas(fechaInicioTExposicion(expo), fechaInicioTExposicion(aux->sig->exposicion)) > 0){
            aux = aux->sig;
        }
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
    }
}

bool perteneceExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){
    while (listaExposiciones != NULL){
        if(idTExposicion(listaExposiciones->exposicion) == idExpo){
            return true;
        }
        listaExposiciones = listaExposiciones->sig;
    }
    return false;
}

TExposicion obtenerExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){
    while (idTExposicion(listaExposiciones->exposicion) != idExpo){
        listaExposiciones = listaExposiciones->sig;
    }
    return listaExposiciones->exposicion;
}

bool esVaciaTListaExposiciones(TListaExposiciones listaExposiciones){
    return listaExposiciones == NULL;
}

void imprimirTListaExposiciones(TListaExposiciones listaExposiciones){
    while (listaExposiciones != NULL){
        imprimirTExposicion(listaExposiciones->exposicion);
        listaExposiciones = listaExposiciones->sig;
    }
}

void liberarTListaExposiciones(TListaExposiciones &listaExposiciones, bool liberarExposiciones){
    while (listaExposiciones != NULL){
        TListaExposiciones aux = listaExposiciones;
        listaExposiciones = listaExposiciones->sig;
        if (liberarExposiciones){
            liberarTExposicion(aux->exposicion);
        }
        delete aux;
    }
    listaExposiciones = NULL;
}

TListaExposiciones obtenerExposicionesFinalizadas(TListaExposiciones &listaExposiciones, TFecha fecha){
    TListaExposiciones res = NULL;
    //puntero al ultimo nodo de res
    TListaExposiciones* ultimoPtr = &res; 

    //auxiliares
    TListaExposiciones prev = NULL;
    TListaExposiciones actual = listaExposiciones;

    while (actual != NULL) {
        if (compararTFechas(fecha, fechaFinTExposicion(actual->exposicion)) == 1) {
            TListaExposiciones movido = actual;
            if (prev == NULL) {
                listaExposiciones = actual->sig;
            } else {
                prev->sig = actual->sig;
            }
            actual = actual->sig;

            movido->sig = NULL;
            *ultimoPtr = movido;
            ultimoPtr = &movido->sig;
        } else {
            prev = actual;
            actual = actual->sig;
        }
    }
    return res;
}              

TListaExposiciones obtenerExposicionesActivas(TListaExposiciones &listaExposiciones, TFecha fecha){
    // TListaExposiciones res = NULL;

    // //Si el primero esta activo
    // while (listaExposiciones != NULL && compararTFechas(fecha, fechaInicioTExposicion(listaExposiciones->exposicion)) >= 0 && compararTFechas(fechaFinTExposicion(listaExposiciones->exposicion),fecha) >= 0){
    //     TListaExposiciones movido = listaExposiciones;
    //     listaExposiciones = listaExposiciones->sig;
    //     movido->sig = NULL;
    //     agregarExposicionTListaExposiciones(res, movido->exposicion);
    //     delete movido;
    // }

    // //Luego del primero
    // TListaExposiciones aux = listaExposiciones;
    // while (aux != NULL && aux->sig != NULL){
    //     TListaExposiciones aux2 = aux->sig;
    //     if (compararTFechas(fecha, fechaInicioTExposicion(aux2->exposicion)) >= 0 && compararTFechas(fechaFinTExposicion(aux2->exposicion),fecha) >= 0){
    //         aux->sig = aux2->sig;
    //         aux2->sig = NULL;
    //         agregarExposicionTListaExposiciones(res, aux2->exposicion);
    //         delete aux2;
    //     } else {
    //         aux = aux->sig;
    //     }
    // }
    // return res;


    TListaExposiciones res = NULL;
    //puntero al ultimo nodo de res
    TListaExposiciones* ultimoPtr = &res; 

    //auxiliares
    TListaExposiciones prev = NULL;
    TListaExposiciones actual = listaExposiciones;

    while (actual != NULL) {
        if (compararTFechas(fecha, fechaInicioTExposicion(actual->exposicion)) >= 0 && compararTFechas(fechaFinTExposicion(actual->exposicion),fecha) >= 0) {
            TListaExposiciones movido = actual;
            if (prev == NULL) {
                listaExposiciones = actual->sig;
            } else {
                prev->sig = actual->sig;
            }
            actual = actual->sig;

            movido->sig = NULL;
            *ultimoPtr = movido;
            ultimoPtr = &movido->sig;
        } else {
            prev = actual;
            actual = actual->sig;
        }
    }
    return res;
}

bool esCompatibleTListaExposiciones(TListaExposiciones listaExposiciones, TExposicion expo){
    while (listaExposiciones != NULL && sonExposicionesCompatibles(listaExposiciones->exposicion, expo)){
        listaExposiciones = listaExposiciones->sig;
    }
    return listaExposiciones == NULL;
}

TListaExposiciones unirListaExposiciones(TListaExposiciones listaExpo1, TListaExposiciones listaExpo2){
    TListaExposiciones res = NULL;
    TListaExposiciones* ultimo = &res;

    while (listaExpo1 != NULL && listaExpo2 != NULL) {
        TListaExposiciones nuevo = new rep_listaexposiciones;
        if (compararTFechas(fechaInicioTExposicion(listaExpo1->exposicion), fechaInicioTExposicion(listaExpo2->exposicion)) <= 0) {
            nuevo->exposicion = listaExpo1->exposicion;
            listaExpo1 = listaExpo1->sig;
        } else {
            nuevo->exposicion = listaExpo2->exposicion;
            listaExpo2 = listaExpo2->sig;
        }
        nuevo->sig = NULL;
        *ultimo = nuevo;
        ultimo = &(*ultimo)->sig;
    }

    while (listaExpo1 != NULL) {
        TListaExposiciones nuevo = new rep_listaexposiciones;
        nuevo->exposicion = listaExpo1->exposicion;
        nuevo->sig = NULL;
        *ultimo = nuevo;
        ultimo = &(*ultimo)->sig;
        listaExpo1 = listaExpo1->sig;
    }

    while (listaExpo2 != NULL) {
        TListaExposiciones nuevo = new rep_listaexposiciones;
        nuevo->exposicion = listaExpo2->exposicion;
        nuevo->sig = NULL;
        *ultimo = nuevo;
        ultimo = &(*ultimo)->sig;
        listaExpo2 = listaExpo2->sig;
    }

    return res;
}

// Agregados tarea 4


int cantidadExposicionesTListaExposiciones(TListaExposiciones listaExpo){
    int cant = 0;
    while (listaExpo != NULL){
        listaExpo = listaExpo->sig;
        cant++;
    }
    return cant;
}

TExposicion obtenerNesimaExposicionTListaExposiciones(TListaExposiciones listaExpo, int n){
    int aux = 1;
    while (aux < n){
        listaExpo = listaExpo->sig;
        aux++;
    }
    return listaExpo->exposicion;
}
