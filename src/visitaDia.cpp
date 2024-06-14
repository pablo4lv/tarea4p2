#include "../include/visitaDia.h"

struct rep_visitadia{
  TFecha fecha;
  int max;
  int cant;
  TGrupoABB *cola;
  TGrupoABB *ids;
};

TVisitaDia crearTVisitaDia(TFecha fecha, int N){
  TVisitaDia nuevo = new rep_visitadia;
  nuevo->max = N;
  nuevo->cant = 0;
  nuevo->cola = new TGrupoABB[N+1];
  nuevo->ids = new TGrupoABB[N+1];
  for (int i = 0; i <= N; i++){
    nuevo->ids[i] = NULL;
    nuevo->cola[i] = NULL;
  }
  nuevo->fecha = fecha;
  return nuevo;
}

void filtradoAscendente(int pos, TVisitaDia &visita){
  while (pos > 1 && edadPromedioTGrupoABB(visita->cola[pos]) <= edadPromedioTGrupoABB(visita->cola[pos/2])){
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
    visita->ids[idGrupo(grupo)] = grupo;

  }
}

int cantidadGruposTVisitaDia(TVisitaDia visitaDia){
  return 0;
}

void imprimirTVisitaDia(TVisitaDia visitaDia){
  printf("Visita para dia: ");
  imprimirTFecha(visitaDia->fecha);
  printf("\n");

  int inicio = 1;
  int nivel = 1;
  while (inicio <= visitaDia->cant){
    printf("\nNivel %d\n", nivel);
    
    int final;
    if (inicio*2 - 1 <= visitaDia->cant){
      final = inicio*2 - 1;
    } else {
      final = visitaDia->cant;
    }

    for (int i = inicio; i<= final; i++){
      printf("%d) Grupo %d con edad promedio %.2f\n", i,idGrupo(visitaDia->cola[i]), edadPromedioTGrupoABB(visitaDia->cola[i]));
      imprimirTGrupoABB(visitaDia->cola[i]);
    }
    inicio = inicio*2;
    nivel++;
  }
}

TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia){
    return NULL;  
}

void liberarTVisitaDia(TVisitaDia &visitaDia){
  for(int i = 0; i <= visitaDia->max; i++){
    if (visitaDia->cola[i] != NULL){
      liberarTGrupoABB(visitaDia->cola[i]);
    }
  }
  delete[] visitaDia->ids;
  delete[] visitaDia->cola;
  liberarTFecha(visitaDia->fecha);
  delete visitaDia;
  visitaDia = NULL;
}

void invertirPrioridadTVisitaDia(TVisitaDia &visita) {
}

bool estaEnTVisitaDia(TVisitaDia visita, int id) {
  return visita->ids[id] != NULL;
} 

float prioridadTVisitaDia(TVisitaDia visita, int id){
  return edadPromedioTGrupoABB(visita->ids[id]);
}

TGrupoABB masPrioritarioTVisitaDia(TVisitaDia visita){
	return visita->cola[1];
}


int maxGruposTVisitaDia(TVisitaDia visita){
  return visita->max;
}

TFecha fechaTVisitaDia(TVisitaDia visitaDia){
  return visitaDia->fecha;
}


