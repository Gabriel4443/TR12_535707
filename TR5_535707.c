#include "heap.h"

//Cria a struct da heap
HEAP* HEAP_create(int n, COMP* compara) {
	//Pega um tamanho para a heap
	HEAP* heap = malloc(sizeof(HEAP));
	//Pega um tamanho para os elementos da heap
	heap->elems = malloc(n * sizeof(void*));
	//tamanho maximo da heap
	heap->N = n;
	//tamanho atual da heap
	heap->P = 0;
	//Comparador
	heap->comparador = compara;

	return heap;
}
//Função que cria uma heap
void HEAP_add(HEAP* heap, void* newelem) {
//Compara se o tamanho atual é menor q o maximo
  if (heap->P < heap->N) {
    heap->elems[heap->P] = newelem;
	int pos = heap->P;
//Loop que ordena 
	while (heap->comparador(heap->elems[pos], heap->elems[(pos - 1) / 2]) > 0) {
		void* aux = heap->elems[pos];
		heap->elems[pos] = heap->elems[(pos - 1) / 2];
		heap->elems[(pos - 1) / 2] = aux;	
		pos = (pos - 1) / 2;
	}	

	heap->P++;
  }
}
//Função que remove da heap que reordena os elementos
void* HEAP_remove(HEAP* heap) {
	void* min = heap->elems[0];

	heap->elems[0] = heap->elems[heap->P - 1];
	heap->elems[heap->P - 1] = min;
	
	heap->P--;

	int pai = 0;
	int filho = pai * 2 + 1;
	//Loop que reordena
	while (filho < heap->P) {
		if (filho + 1 < heap->P) {
			if (heap->comparador(heap->elems[filho], heap->elems[filho + 1]) < 0) {
				filho += 1;
			}
		}

		if (heap->comparador(heap->elems[pai], heap->elems[filho]) < 0) {
			void* aux = heap->elems[pai];
			heap->elems[pai] = heap->elems[filho];
			heap->elems[filho] = aux;

			pai = filho;
			filho = pai * 2 + 1;
		} else {
			filho = heap->P + 1;
		}
	}
//retorna o elemento excluido
	return min;
}
