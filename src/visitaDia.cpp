#include "../include/visitaDia.h"

struct rep_visitadia{
  TFecha fecha;
  int max;
  int cant;
  TGrupoABB *cola;
  int *ids;
};

TVisitaDia crearTVisitaDia(TFecha fecha, int N){
  TVisitaDia nuevo = new rep_visitadia;
  nuevo->max = N;
  nuevo->cant = 0;
  nuevo->cola = new TGrupoABB[N+1];
  nuevo->ids = new int[N+1];
  for (int i = 0; i <= N; i++){
    nuevo->ids[i] = 0;
  }
  nuevo->fecha = fecha;
  return nuevo;
}

void filtradoAscendente(int pos, TVisitaDia &visita){
  while (pos > 1 && edadPromedioTGrupoABB(visita->cola[pos]) < edadPromedioTGrupoABB(visita->cola[pos/2])){
    TGrupoABB aux = visita->cola[pos];
    visita->cola[pos] = visita->cola[pos/2];
    visita->cola[pos/2] = aux;

    pos = pos/2;
  }
}

void encolarGrupoTVisitaDia(TVisitaDia &visita, TGrupoABB grupo){
  if (visita->cant < visita->max){
    visita->cola[visita->cant + 1] = grupo;
    filtradoAscendente(visita->cant + 1, visita);
    visita->cant++;
  }
}

int cantidadGruposTVisitaDia(TVisitaDia visitaDia){
  return 0;
}

void imprimirTVisitaDia(TVisitaDia visitaDia){
}

TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia){
    return NULL;  
}

void liberarTVisitaDia(TVisitaDia &visitaDia){
  for(int i = 0; i < visitaDia->max; i++){
    liberarTGrupoABB(visitaDia->cola[i]);
  }
  delete visitaDia->cola;
  liberarTFecha(visitaDia->fecha);
  delete visitaDia;
  visitaDia = NULL;
}

void invertirPrioridadTVisitaDia(TVisitaDia &visita) {
}

bool estaEnTVisitaDia(TVisitaDia visita, int id) {
  return visita->ids[id] == 1;
} 

float prioridadTVisitaDia(TVisitaDia visita, int id){
  return 0.0;
}

TGrupoABB masPrioritarioTVisitaDia(TVisitaDia visita){
	return NULL;
}


int maxGruposTVisitaDia(TVisitaDia visita){
  return visita->max+1;
}

TFecha fechaTVisitaDia(TVisitaDia visitaDia){
  return visitaDia->fecha;
}


