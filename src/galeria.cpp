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
}

void liberarTGaleria(TGaleria &galeria){
    liberarColeccionPiezas(galeria->coleccion);
    liberarTListaExposiciones(galeria->activas,true);
    liberarTListaExposiciones(galeria->finalizadas,true);
    liberarTListaExposiciones(galeria->futuras,true);
    liberarTFecha(galeria->fecha);
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
