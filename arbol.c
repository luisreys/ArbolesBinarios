#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "cola.h"

//
// Reserva de memoria para un nuevo nodo de Arbol binario
//
Arbol creaNodo(tipoInfo info){ 

  tipoNodo * nuevo;

  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL){
	return NULL;
  }else{ 
  	nuevo->info=info;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
   }
}

//
// Recorrido en amplitud o por niveles: necesita una cola de punteros a nodos de Ã¡rbol binario!!!
//

void amplitud(Arbol raiz){ 
  Cola c;
  tipoNodo *nodo;
  colaCreaVacia(&c);
  nodo = raiz;
  if (raiz!=NULL) colaInserta(&c,nodo);
  while (!colaVacia(&c)){ 
  	nodo = (Arbol) colaSuprime(&c);
    printf(" %c ", nodo->info);
    if (nodo->izq!=NULL) colaInserta(&c,nodo->izq);
    if (nodo->der!=NULL) colaInserta(&c,nodo->der);
  }
}
// 
// Recorridos en profundidad "recursivos"
//
void preOrden(Arbol raiz){ 
  if (raiz!=NULL){ 
  	printf("%c ",raiz->info);
    preOrden(raiz->izq);
    preOrden(raiz->der);
  }
}
void enOrden(Arbol raiz){ 
  if (raiz!=NULL){ 
  	enOrden(raiz->izq);
    printf("%c ",raiz->info);
    enOrden(raiz->der);
  }
}
void postOrden(Arbol raiz){ 
  if (raiz!=NULL){ 
  	postOrden(raiz->izq);
    postOrden(raiz->der);
    printf("%c ",raiz->info);
  }
}

/*
int altura(Arbol raiz);   DONE
int numNodos(Arbol raiz);
Arbol anula(Arbol raiz);
int sustiuye(Arbol raiz, tipoInfo x, tipoInfo y);
int numNodosHoja(Arbol raiz);
int numNodosInternos(Arbol raiz);
int numHijoUnico(Arbol raiz);
Arbol buscarMax(Arbol raiz);
Arbol buscarMin(Arbol raiz);
int similares(Arbol r1,Arbol r2);
int equivalentes(Arbol r1,Arbol r2);
Arbol especular(Arbol raiz);
*/

int altura(Arbol raiz){
	int auxIzq, auxDer;
	
	if(raiz==null){
		return -1;
	}
	
	//entramos por la izquierda primero
	if(raiz->izq != null){
		auxIzq = altura(raiz->izq);
	}
	
	//si no hay nada por la izquierda entonces probamos por la derecha
	if(raiz->der != null){
		auxDer = altura(raiz->der);
	}
	
	//hemos llegado a una hoja
	if(raiz->izq == null && raiz->der == null){
		//si estamos en una hoja devolveremos 0 ya que la raiz también va a devolver aux +1,
		//por lo que se contaría una altur de más, de esta manera, si la hoja devuelve 0 se 
		//harán bien los calculos.
		return 0;
	}
	
	if(auxDer > auxIzq){
		return auxDer + 1;
	}else{
		return auxIzq + 1;
	}
}


int numNodos(Arbol raiz){
	int contadorIzq, contadorDer;
	
	if(raiz == null){
		return -1;		
	}
	
	if(raiz->izq != null){
		contadorIzq = numNodos(raiz->izq);
	}
	
	if(raiz->der != null){
		contadorDer = numNodos(raiz->der);
	}
	
	if(raiz->izq == null && raiz->der == null){
		return 1;
	}
	
	return contadorIzq + contadorDer + 1;
}

