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
	int contadorIzq = 0;
	int contadorDer = 0;
	
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


Arbol anula(Arbol raiz){
	
	if(raiz == null){
		return -1;
	}
	
	if(raiz->izq != null){
		if(anula(raiz->izq) == null){
			free(raiz->izq);
			raiz->izq = null;
		}
	}
	
	if(raiz->der != null){
		if(anula(raiz->der) == null){
			free(raiz->der);
			raiz->der = null;
		}
	}
	
	if(raiz->izq == null && raiz->der == null){
		return null;
	}
}


//Sustituye, en al arbol dado, los nodos con valor x en el campo de información por y
int sustiuye(Arbol raiz, tipoInfo x, tipoInfo y){
	int sustituido = 0;
	int auxIzq, auxDer;
	
	if(raiz == null){
		return -1;
	}
	
	if(raiz->info == x){
		raiz->info = y;
		sustituido = 1;
	}
	
	if(raiz->izq != null){
		auxIzq = sustituye(raiz->izq, x, y);
	}
	
	if(raiz->der != null){
		auxDer = sustituye(raiz->der, x, y);
	}
	
	if(raiz->izq == null && raiz->der == null){
		return sustituido;
	}else{
		return auxDer + auxIzq + sustituido;
	}
}


int numNodosHoja(Arbol raiz){
	int contadorIzq = 0;
	int contadorDer = 0;
	
	if(raiz == null){
		return -1;		
	}
	
	if(raiz->izq != null){
		contadorIzq = numNodosHoja(raiz->izq);
	}
	
	if(raiz->der != null){
		contadorDer = numNodosHoja(raiz->der);
	}
	
	if(raiz->izq == null && raiz->der == null){
		return 1;
	}
	
	return contadorIzq + contadorDer;
}

int numNodosInternos(Arbol raiz){
	int contadorIzq = 0;
	int contadorDer = 0;
	
	if(raiz == null){
		return -1;		
	}
	
	if(raiz->izq != null){
		contadorIzq = numNodosInternos(raiz->izq);
	}
	
	if(raiz->der != null){
		contadorDer = numNodosInternos(raiz->der);
	}
	
	if(raiz->izq == null && raiz->der == null){
		return 0;
	}
	
	return contadorIzq + contadorDer + 1;
}


int numHijoUnico(Arbol raiz){
	int contadorIzq = 0;
	int contadorDer = 0;
	
	if(raiz == null){
		return -1;		
	}
	
	if(raiz->izq != null){
		contadorIzq = numHijoUnico(raiz->izq);
	}
	
	if(raiz->der != null){
		contadorDer = numHijoUnico(raiz->der);
	}
	
	if(raiz->izq == null && raiz->der == null){
		return 0;
	}else if(raiz->izq == null && raiz->der != null){
		return contadorDer + 1;
	}else if(raiz->izq != null && raiz->der == null){
		return contadorIzq + 1;
	}else{
		return contadorIzq + contadorDer + 0;
	}
}

Arbol buscarMax(Arbol raiz){
	Arbol arbolIzq = 0;
	Arbol arbolDer = 0;
	
	if(raiz == null){
		return -1;
	}
	
	if(raiz->izq != null){
		arbolIzq = buscarMax(raiz->izq);
	}
	
	if(raiz->der != null){
		arbolDer = buscarMax(raiz->der);
	}
	
	if(raiz->izq == null && raiz->der == null){
		return raiz;
	}else if(arbolIzq != null && arbolDer == null){
		if(arbolIzq->info > raiz->info){
			return arbolIzq;
		}else{
			return raiz;
		}
	}else if(arbolIzq == null && arbolDer != null){
		if(arbolDer->info > raiz->info){
			return arbolDer;
		}else{
			return raiz;
	}else{
		if(arbolIzq->info > arbolDer->info){
			if(arbolIzq->info > raiz->info){
				return arbolIzq;
			}else{
				return raiz;
			}
		}else{
			if(arbolDer->info > raiz->info){
				return arbolDer;
			}else{
				return raiz;
			}
		}
	}
}


Arbol buscarMin(Arbol raiz){
	Arbol arbolIzq = null;
	Arbol arbolDer = null;
	
	if(raiz == null){
		return -1;
	}
	
	if(raiz->izq != null){
		arbolIzq = buscarMax(raiz->izq);
	}
	
	if(raiz->der != null){
		arbolDer = buscarMax(raiz->der);
	}
	
	if(raiz->izq == null && raiz->der == null){
		return raiz;
	}else if(arbolIzq != null && arbolDer == null){
		if(arbolIzq->info < raiz->info){
			return arbolIzq;
		}else{
			return raiz;
		}
	}else if(arbolIzq == null && arbolDer != null){
		if(arbolDer->info < raiz->info){
			return arbolDer;
		}else{
			return raiz;
		}
	}else{
		if(arbolIzq->info < arbolDer->info){
			if(arbolIzq->info < raiz->info){
				return arbolIzq;
			}else{
				return raiz;
			}
		}else{
			if(arbolDer->info < raiz->info){
				return arbolDer;
			}else{
				return raiz;
			}
		}
	}
}


int similares(Arbol r1,Arbol r2){
	int equivalenciaIzq = 1;
	int equivalenciaDer = 1;
	
	if(r1 == null || r2 == null){
		return 0;
	}
	
	
	if(r1->izq != null && r2->izq != null){
		equivalenciaIzq = similares(r1->izq, r2->izq);
	}else if(r1->izq == null && r2->izq == null){
		equivalenciaIzq = 1;
	}else{
		equivalenciaIzq = 0;
	}
	
	
	if(r1->der != null && r2->der != null){
		equivalenciaDer = similares(r1->izq, r2->izq);
	}else if(r1->der == null && r2->der == null){
		equivalenciaDer = 1;
	}else{
		equivalenciaDer = 0;
	}
	
	//Si estamos en la hoja de ambos arboles
	/*if(r1->izq == null && r2->izq == null && r1->der == null && r2->der == null){
		return 1;
	}*/
	
	if(equivalenciaDer == 1 && equivalenciaIzq == 1){
		return 1;
	}else{
		return 0; 
	}
	
}



int equivalentes(Arbol r1,Arbol r2){
	int equivalenciaIzq = 1;
	int equivalenciaDer = 1;
	
	if(r1 == null || r2 == null){
		return 0;
	}
	
	
	if(r1->izq != null && r2->izq != null){
		equivalenciaIzq = equivalentes(r1->izq, r2->izq);
	}else if(r1->izq == null && r2->izq == null){
		equivalenciaIzq = 1;
	}else{
		equivalenciaIzq = 0;
	}
	
	
	if(r1->der != null && r2->der != null){
		equivalenciaDer = equivalentes(r1->izq, r2->izq);
	}else if(r1->der == null && r2->der == null){
		equivalenciaDer = 1;
	}else{
		equivalenciaDer = 0;
	}
	
	
	if(equivalenciaDer == 1 && equivalenciaIzq == 1 && r1->info == r2->info){
		return 1;
	}else{
		return 0; 
	}
	
}


Arbol especular(Arbol raiz){
	Arbol esteNodo = crearNodo(raiz->info);
	Arbol subArbolIzq = null;
	Arbol subArbolDer = null;
	
	if(raiz == null){
		return null;
	}
	
	if(raiz->izq != null){
		subArbolIzq = especular(raiz->izq);
		esteNodo->der = subArbolIzq;
	}
	
	if(raiz->der != null){
		subArbolDer = especular(raiz->der);
		esteNodo->izq = subArbolDer;
	}

	if(raiz->izq == null && raiz->der == null){
		return esteNodo;
	}else{
		return esteNodo;
	}
}







