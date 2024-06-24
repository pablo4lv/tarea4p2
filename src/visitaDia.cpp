#include "../include/visitaDia.h"

struct rep_visitadia{
  TFecha fecha;
  int max;
  int cant;
  TGrupoABB *cola;
  TGrupoABB *ids;
  bool minHeap;
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
  nuevo->minHeap = true;
  return nuevo;
}

void filtradoAscendente(int pos, TVisitaDia &visita){
  while (pos > 1){
    bool condicion;
    if (visita->minHeap){
      condicion = edadPromedioTGrupoABB(visita->cola[pos]) < edadPromedioTGrupoABB(visita->cola[pos/2]);
    } else {
      condicion = edadPromedioTGrupoABB(visita->cola[pos]) > edadPromedioTGrupoABB(visita->cola[pos/2]);
    }

    if (condicion){
      TGrupoABB aux = visita->cola[pos];
      visita->cola[pos] = visita->cola[pos/2];
      visita->cola[pos/2] = aux;

      pos = pos/2;
    } else {
      break;
    }
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
  return visitaDia->cant;
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

void filtradoDescendente(int pos, TVisitaDia &visita){
  int izq = 2*pos;
  int der = 2*pos + 1;
  int objetivo = pos;
 
  if (visita->minHeap){
    if (izq <= visita->cant && edadPromedioTGrupoABB(visita->cola[izq]) < edadPromedioTGrupoABB(visita->cola[objetivo])){
      objetivo = izq;
    }
    if (der <= visita->cant && edadPromedioTGrupoABB(visita->cola[der]) < edadPromedioTGrupoABB(visita->cola[objetivo])){
      objetivo = der;
    }
  } else {
    if (izq <= visita->cant && edadPromedioTGrupoABB(visita->cola[izq]) > edadPromedioTGrupoABB(visita->cola[objetivo])){
      objetivo = izq;
    }
    if (der <= visita->cant && edadPromedioTGrupoABB(visita->cola[der]) > edadPromedioTGrupoABB(visita->cola[objetivo])){
      objetivo = der;
    }
  }

  if (objetivo != pos){
    TGrupoABB aux = visita->cola[pos];
    visita->cola[pos] = visita->cola[objetivo];
    visita->cola[objetivo] = aux;

    filtradoDescendente(objetivo, visita);
  }
}

TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia){
  //Guardo el grupo eliminado
  TGrupoABB res = visitaDia->cola[1];
  //lo elimino del arreglo aux con los ids
  visitaDia->ids[idGrupo(visitaDia->cola[1])] = 0;
  //Muevo el ultimo a la raiz
  visitaDia->cola[1] = visitaDia->cola[visitaDia->cant];
  //Elimino el puntero del ultimo lugar
  visitaDia->cola[visitaDia->cant] = NULL;
  visitaDia->cant--;
  //Filtro - si hay grupos
  if (visitaDia->cant > 0){
    filtradoDescendente(1,visitaDia);
  }
  return res;
}

void liberarTVisitaDia(TVisitaDia &visitaDia){
  if (visitaDia != NULL){
    for(int i = 1; i <= visitaDia->max; i++){
      if (visitaDia->cola[i] != NULL){
        printf("a");
        liberarTGrupoABB(visitaDia->cola[i]);
      }
    }
    delete[] visitaDia->ids;
    delete[] visitaDia->cola;
    liberarTFecha(visitaDia->fecha);
    delete visitaDia;
    visitaDia = NULL;
  }

}

void invertirPrioridadTVisitaDia(TVisitaDia &visita) {
  visita->minHeap = !visita->minHeap;
  //filtrar

  for (int i = visita->cant / 2; i > 0; i--){
    filtradoDescendente(i,visita);
  }
  
  // filtradoDescendente(1,visita);
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


