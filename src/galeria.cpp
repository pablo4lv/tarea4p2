#include "../include/galeria.h"

struct rep_galeria{
    TColeccionPiezas coleccion;
    TFecha fecha;
    TListaExposiciones finalizadas;
    TListaExposiciones activas;
    TListaExposiciones futuras;

    TVisitaDia visitaDia;
    THashVisitaDia hash;
};

void agregarPiezaTGaleria(TGaleria galeria, TPieza pieza){
}

void agregarExposicionTGaleria(TGaleria galeria, TExposicion expo){
}

void agregarPiezaAExposicionTGaleria(TGaleria galeria, int idPieza, int idExpo){
}

void imprimirExposicionesFinalizadasTGaleria(TGaleria galeria){
}

void imprimirExposicionesActivasTGaleria(TGaleria galeria){
}

void imprimirExposicionesFuturasTGaleria(TGaleria galeria){
}

bool esCompatibleExposicionTGaleria(TGaleria galeria, TExposicion expo){
    return false;
}

TGaleria crearTGaleria(TFecha fecha){
    TGaleria nueva = new rep_galeria;
    nueva->coleccion = crearColeccionPiezasVacia();
    nueva->finalizadas = NULL;
    nueva->activas = NULL;
    nueva->futuras = NULL;
    nueva->fecha = fecha;
    nueva->visitaDia = crearTVisitaDia(fecha, MAX_GRUPOS_VISITA_DIA);
    nueva->hash = crearTHashVisitaDia(CANT_ESTIMADA_VISITA_DIA_PASADAS);
    return nueva;
}

void avanzarAFechaTGaleria(TGaleria galeria, TFecha fecha){
    TListaExposiciones unidas1 = unirListaExposiciones(galeria->activas, galeria->finalizadas);
    //Lista con todas las expo
    TListaExposiciones unidas2 = unirListaExposiciones(unidas1, galeria->futuras);
    liberarTListaExposiciones(unidas1, false);

    //liberar las listas de la galeria
    liberarTListaExposiciones(galeria->activas, false);
    liberarTListaExposiciones(galeria->finalizadas, false);
    liberarTListaExposiciones(galeria->futuras, false);

    //agregar las listas modificadas
    galeria->activas = obtenerExposicionesActivas(unidas2, fecha);
    galeria->finalizadas = obtenerExposicionesFinalizadas(unidas2, fecha);
    galeria->futuras = unidas2;

    //liberar la fecha vieja y agregar la nueva
    liberarTFecha(galeria->fecha);
    galeria->fecha = fecha;

    agregarVisitaDiaTHashVisitaDia(galeria->hash, galeria->visitaDia);
    galeria->visitaDia = NULL;
}

void liberarTGaleria(TGaleria &galeria){
    liberarColeccionPiezas(galeria->coleccion);
    liberarTListaExposiciones(galeria->activas,true);
    liberarTListaExposiciones(galeria->finalizadas,true);
    liberarTListaExposiciones(galeria->futuras,true);
    // liberarTFecha(galeria->fecha);
    liberarTHashVisitaDia(galeria->hash);
    liberarTVisitaDia(galeria->visitaDia);
    delete galeria;
    galeria = NULL;
}

// Funciones tarea 4

TConjuntoPiezas piezasEnExposicionTGaleria(TGaleria galeria){
    return NULL;
}

float indiceFelicidadVisitanteTGaleria(TGaleria galeria, TVisitante visitante){
    return 0.0;
}

void llegaGrupoTGaleria(TGaleria galeria, TGrupoABB grupoABB){
}

TConjuntoPiezas piezasEnReservaTGaleria(TGaleria galeria){    
    return NULL;
}

TVisitaDia obtenerVisitaDiaTGaleria(TGaleria galeria, TFecha fecha){
    return NULL;
}
