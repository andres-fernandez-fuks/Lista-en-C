#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una estructura enlazada de punteros genéricos. */

struct lista;
typedef struct lista lista_t;
struct nodo;
typedef struct nodo nodo_t;
struct lista_iter;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DEL NODO
 * *****************************************************************/

nodo_t* crear_nodo(void* valor);

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, de acuerdo a si la lista está o no vacía.
// Pre: La lista fue creada.
bool lista_esta_vacia(const lista_t*);

// Inserta un elemento en la primera posición de la lista.
// Pre: La lista fue creada.
// Post: La lista tiene un elemento más, ubicado en la primera posición.
bool lista_insertar_primero(lista_t*,void*);

// Inserta un elemento en la última posición de la lista.
// Pre: La lista fue creada.
// Post: La lista tiene un elemento más, ubicado en la última posición.
bool lista_insertar_ultimo(lista_t*,void*);

// Borra y devuelve el primer elemento de la lista. Si la lista estaba vacía, devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el último elemento de la lista. La lista tiene un elemento menos, si no estaba vacía.
// Si tenía sólo un elemento, ahora está vacía. Si no, ahora su primero se modificó.
void* lista_borrar_primero(lista_t*);

// Devuelve el primer elemento de la lista. Si la lista estaba vacía, devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el último elemento de la lista.
void* lista_ver_primero(const lista_t*);

// Devuelve el último elemento de la lista. Si la lista estaba vacía, devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el último elemento de la lista.
void* lista_ver_ultimo(const lista_t*);

// Devuelve el largo de la lista. Si la lista estaba vacía, devuelve 0.
// Pre: La lista fue creada.
size_t lista_largo(const lista_t*);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t*, void destruir_dato(void*));

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t*,bool visitar(void*, void*),void*);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista);
bool lista_iter_avanzar(lista_iter_t *iter);
void *lista_iter_ver_actual(const lista_iter_t *iter);
bool lista_iter_al_final(const lista_iter_t *iter);
void lista_iter_destruir(lista_iter_t *iter);
bool lista_iter_insertar(lista_iter_t *iter, void *dato);
void *lista_iter_borrar(lista_iter_t *iter);

#endif