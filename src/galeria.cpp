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
    insertarPiezaColeccionPiezas(galeria->coleccion,pieza);
}

void agregarExposicionTGaleria(TGaleria galeria, TExposicion expo){
    if (compararTFechas(galeria->fecha,fechaInicioTExposicion(expo)) < 0){
        agregarExposicionTListaExposiciones(galeria->futuras, expo);
    } else {
        if (compararTFechas(galeria->fecha, fechaInicioTExposicion(expo)) >= 0){
            if (compararTFechas(galeria->fecha, fechaFinTExposicion(expo)) > 0){
                agregarExposicionTListaExposiciones(galeria->finalizadas, expo);
            } else {
                agregarExposicionTListaExposiciones(galeria->activas,expo);
            }
        }
    }
}

void agregarPiezaAExposicionTGaleria(TGaleria galeria, int idPieza, int idExpo){
    TPieza pieza = obtenerPiezaColeccionPiezas(galeria->coleccion,idPieza);
    TExposicion destino = NULL;
    if (perteneceExposicionTListaExposiciones(galeria->activas, idExpo)){
        destino = obtenerExposicionTListaExposiciones(galeria->activas,idExpo);
    } else if (perteneceExposicionTListaExposiciones(galeria->futuras, idExpo)){
        destino = obtenerExposicionTListaExposiciones(galeria->futuras,idExpo);
    } else {
        destino = obtenerExposicionTListaExposiciones(galeria->finalizadas,idExpo);
    }
    agregarATExposicion(destino, pieza);
}

void imprimirExposicionesFinalizadasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->finalizadas);
}

void imprimirExposicionesActivasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->activas);
}

void imprimirExposicionesFuturasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->futuras);
}

bool esCompatibleExposicionTGaleria(TGaleria galeria, TExposicion expo){
    return (esCompatibleTListaExposiciones(galeria->activas,expo) &&
    esCompatibleTListaExposiciones(galeria->futuras, expo) &&
    esCompatibleTListaExposiciones(galeria->finalizadas, expo));
}

TGaleria crearTGaleria(TFecha fecha){
    TGaleria nueva = new rep_galeria;
    nueva->coleccion = crearColeccionPiezasVacia();
    nueva->finalizadas = NULL;
    nueva->activas = NULL;
    nueva->futuras = NULL;
    nueva->fecha = fecha;
    nueva->visitaDia = crearTVisitaDia(copiarTFecha(fecha), MAX_GRUPOS_VISITA_DIA);
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

    agregarVisitaDiaTHashVisitaDia(galeria->hash, galeria->visitaDia);
    //
    // liberarTVisitaDia(galeria->visitaDia);

    galeria->visitaDia = crearTVisitaDia(fecha, MAX_GRUPOS_VISITA_DIA);

    delete galeria->fecha;
    galeria->fecha = copiarTFecha(fecha);
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
    encolarGrupoTVisitaDia(galeria->visitaDia, grupoABB);
}

TConjuntoPiezas piezasEnReservaTGaleria(TGaleria galeria){    
    return NULL;
}

TVisitaDia obtenerVisitaDiaTGaleria(TGaleria galeria, TFecha fecha){
    return obtenerVisitaDiaTHashVisitaDia(galeria->hash,fecha);
}
