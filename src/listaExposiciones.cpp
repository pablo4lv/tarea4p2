#include "../include/listaExposiciones.h"

struct rep_listaexposiciones{
};

TListaExposiciones crearTListaExposicionesVacia(){
    return NULL;
}

void agregarExposicionTListaExposiciones(TListaExposiciones &listaExposiciones, TExposicion expo){
}

bool perteneceExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){
    return false;
}

TExposicion obtenerExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){
    return NULL;
}

bool esVaciaTListaExposiciones(TListaExposiciones listaExposiciones){
    return false;
}

void imprimirTListaExposiciones(TListaExposiciones listaExposiciones){
}

void liberarTListaExposiciones(TListaExposiciones &listaExposiciones, bool liberarExposiciones){
}

TListaExposiciones obtenerExposicionesFinalizadas(TListaExposiciones &listaExposiciones, TFecha fecha){
    return NULL;
}              

TListaExposiciones obtenerExposicionesActivas(TListaExposiciones &listaExposiciones, TFecha fecha){
    return NULL;
}

bool esCompatibleTListaExposiciones(TListaExposiciones listaExposiciones, TExposicion expo){
    return false;
}

TListaExposiciones unirListaExposiciones(TListaExposiciones listaExpo1, TListaExposiciones listaExpo2){
    return NULL;
}


// Agregados tarea 4


int cantidadExposicionesTListaExposiciones(TListaExposiciones listaExpo){
    return 0;
}

TExposicion obtenerNesimaExposicionTListaExposiciones(TListaExposiciones listaExpo, int n){
    return NULL;
}
