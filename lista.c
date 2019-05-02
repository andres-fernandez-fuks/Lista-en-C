#include "lista.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct nodo {
    void* dato;  // Dato del nodo.
    struct nodo* prox;  // Próximo nodo.
}nodo_t;

typedef struct lista {
    nodo_t* primero;  // Primer elemento de la lista.
    nodo_t* ultimo;  // Último elemento de la lista.
    size_t largo;
}lista_t;

/* ******************************************************************
 *                    PRIMITIVAS DEL NODO
 * *****************************************************************/

nodo_t* crear_nodo(void* valor) {
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;
	nodo -> dato = valor;
	nodo -> prox = NULL;
	return nodo;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(void) {
	lista_t* lista = malloc(sizeof(lista_t));
	if (!lista) return NULL;
	lista -> primero = NULL;
	lista -> ultimo = NULL;
	lista -> largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t* lista) {
	return lista->primero == NULL;
}

bool lista_insertar_primero(lista_t* lista, void* dato) {
	nodo_t* nuevo_nodo = crear_nodo(dato);
	if (!nuevo_nodo) return false;
	nodo_t* primero = lista -> primero;
	nuevo_nodo -> prox = primero;
	lista -> primero = nuevo_nodo;
	if (!lista -> ultimo) {
		lista -> ultimo = nuevo_nodo;
	}
	lista -> largo ++;
	return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato) {
	nodo_t* nuevo_nodo = crear_nodo(dato);
	if (!nuevo_nodo) return false;
	if (lista -> ultimo != NULL) {
		lista -> ultimo -> prox = nuevo_nodo;
	}
	else {
		lista -> primero = nuevo_nodo;
	}

		lista -> ultimo = nuevo_nodo;
	lista -> largo ++;
	return true;
}

void* lista_borrar_primero(lista_t* lista) {
	if (!lista -> primero) return NULL;
	nodo_t* primero = lista -> primero;
	void* dato = primero -> dato;
	lista -> primero = primero -> prox;
	if (!lista -> primero) lista -> ultimo = NULL; // si el nodo era el único de la lista, ahora el último es NULL
	free(primero);
	lista -> largo --;
	return dato;
}

void* lista_ver_primero(const lista_t* lista) {
	if (!lista -> primero) return NULL;
	return lista -> primero -> dato;
}

void* lista_ver_ultimo(const lista_t* lista) {
	if (!lista -> ultimo) return NULL;
	return lista -> ultimo -> dato;
}

size_t lista_largo(const lista_t* lista) {
	return lista -> largo;
}

void lista_destruir(lista_t* lista, void destruir_dato(void* dato)) {
	nodo_t* actual = lista -> primero;
	while (actual) {
		if (destruir_dato != NULL) {
			destruir_dato(actual -> dato);
		}
		nodo_t* proximo = actual -> prox;
		free(actual);
		actual = proximo;
	}
	free(lista);
}


/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra) {
	nodo_t* actual = lista -> primero;
	while (actual) {
		void* dato = actual -> dato;
		if (!visitar(dato,extra)) break;
		actual = actual -> prox;
	}
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/


typedef struct lista_iter {
	lista_t* lista;
	nodo_t* actual;
	nodo_t* anterior;
}lista_iter_t;

lista_iter_t* lista_iter_crear(lista_t* lista) {
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (!iter) return NULL;
	iter -> lista = lista;
	iter -> actual = lista -> primero;
	iter -> anterior = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t* iter) {
	if (iter -> actual == NULL) return false;
	iter -> anterior = iter -> actual;
	iter -> actual = iter -> actual -> prox;
	return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter) {
	if (!iter -> actual) return NULL;
	return iter -> actual -> dato;
}

bool lista_iter_al_final(const lista_iter_t* iter) {
	return iter -> actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t* iter, void *dato) {
	nodo_t* nuevo_nodo = crear_nodo(dato);
	nuevo_nodo -> prox = iter -> actual;
	if (!nuevo_nodo) return false;
	if (!iter -> anterior) {
		iter -> lista -> primero = nuevo_nodo;
	}
	else {
		iter -> anterior -> prox = nuevo_nodo;
	}
	if (!iter -> actual) {
		iter -> lista -> ultimo = nuevo_nodo;
	}
	iter -> actual = nuevo_nodo;
	iter -> lista -> largo++;
	return true;
}

void* lista_iter_borrar(lista_iter_t* iter) {
	if (!iter -> actual) return NULL;
	void* dato = iter -> actual -> dato;
	if (!iter -> anterior) {
		iter -> lista -> primero = iter -> actual -> prox;
	}
	else {
		iter -> anterior -> prox = iter -> actual -> prox;
	}
	if ( iter -> actual -> prox == NULL ) {
		iter -> lista -> ultimo = iter -> anterior;
	}
	nodo_t* nodo_a_borrar = iter -> actual;
	iter -> actual = iter -> actual -> prox;
	free(nodo_a_borrar);
	iter -> lista -> largo --;
	return dato;
}
