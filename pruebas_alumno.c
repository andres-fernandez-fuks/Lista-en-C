#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>





void pruebas_lista_alumno() {

/* Declaro las variables a utilizar*/
	lista_t* lista_1 = lista_crear();

	/* Inicio de pruebas */
	printf("INICIO DE PRUEBAS DE CREACION Y DESTRUCCION (BÁSICA)\n");

	print_test("crear lista", lista_1 != NULL);
    print_test("la lista creada está vacía", lista_esta_vacia(lista_1));
    print_test("ver el primer elemento de una lista vacía devuelve NULL", lista_ver_primero(lista_1) == NULL);
    print_test("borrar el primer elemento de una lista vacía devuelve NULL", lista_borrar_primero(lista_1) == NULL);
    print_test("ver el último elemento de una lista vacía devuelve NULL", lista_ver_ultimo(lista_1) == NULL);
    print_test("el largo de la lista recién creada es 0", lista_largo(lista_1) == 0);

    lista_destruir(lista_1,NULL);
    print_test("la lista fue destruida",true);

    printf("INICIO DE PRUEBAS DE ENCOLAMIENTO Y DESENCOLAMIENTO DE LA COLA\n");

        /* Declaro las variables a utilizar*/
    lista_t* lista_2 = lista_crear();
    int elem_1 = 5;
    int* punt_1 = &elem_1;

    printf("----PRUEBAS CON UN SOLO ELEMENTO----\n");

    print_test("crear lista", lista_2 != NULL);
    print_test("insertar el elemento 5 en la primera posición es correcto", lista_insertar_primero(lista_2,punt_1));
    print_test("el primer elemento de la lista es el 5", *(int*)lista_ver_primero(lista_2) == 5);
    print_test("el último elemento de la lista es el 5", *(int*)lista_ver_ultimo(lista_2) == 5);
    print_test("el largo de la lista es 1", lista_largo(lista_2) == 1);
    print_test("la lista ya no está vacía", !lista_esta_vacia(lista_2));
    print_test("borrar el primer elemento de la lista devuelve 5", *(int*)lista_borrar_primero(lista_2) == 5);
    print_test("la lista ahora está vacía", lista_esta_vacia(lista_2));
    lista_destruir(lista_2,NULL);

    printf("----PRUEBAS CON VARIOS ELEMENTOS----\n");

    lista_t* lista_3 = lista_crear();
    int elem_2 = 8;
    int* punt_2 = &elem_2;
    int elem_3 = 10;
    int* punt_3 = &elem_3;
    int elem_4 = 20;
    int* punt_4 = &elem_4;

    print_test("crear lista", lista_3 != NULL);
    print_test("insertar el elemento 8 en la primera posición es correcto", lista_insertar_primero(lista_3,punt_2));
    print_test("insertar el elemento 10 en la primera posición es correcto", lista_insertar_primero(lista_3,punt_3));
    print_test("insertar el elemento 20 en la última posición es correcto", lista_insertar_ultimo(lista_3,punt_4));
    print_test("el primer elemento de la lista es el 10", *(int*)lista_ver_primero(lista_3) == 10);
    print_test("el último elemento de la lista es el 20", *(int*)lista_ver_ultimo(lista_3) == 20);
    print_test("el largo de la lista es 3", lista_largo(lista_3) == 3);
    print_test("la lista no está vacía", !lista_esta_vacia(lista_3));
    print_test("borrar el primer elemento de la lista devuelve 10", *(int*)lista_borrar_primero(lista_3) == 10);
    print_test("la lista aún no está vacía", !lista_esta_vacia(lista_3));
    print_test("el largo de la lista es 2", lista_largo(lista_3) == 2);
    print_test("borrar el primer elemento de la lista devuelve 8", *(int*)lista_borrar_primero(lista_3) == 8);
    print_test("la lista aún no está vacía", !lista_esta_vacia(lista_3));
    print_test("el largo de la lista es 1", lista_largo(lista_3) == 1);
    print_test("el primer elemento de la lista es un 20", *(int*)lista_ver_primero(lista_3) == 20);
    print_test("el último elemento de la lista es un 20", *(int*)lista_ver_ultimo(lista_3) == 20);
    print_test("borrar el primer elemento de la lista devuelve 20", *(int*)lista_borrar_primero(lista_3) == 20);
    print_test("la lista ahora está vacía", lista_esta_vacia(lista_3));
    lista_destruir(lista_3,NULL);

    printf("----PRUEBAS DE INSERCIÓN DEL ELEMENTO NULL----\n");

    lista_t* lista_4 = lista_crear();
    int* elem_null = NULL;
    print_test("insertar primero el elemento NULL es correcto", lista_insertar_primero(lista_4,elem_null));
    print_test("el primer elemento de la lista es NULL", lista_ver_primero(lista_4) == elem_null);
    print_test("pero la lista no está vacía", !lista_esta_vacia(lista_4));
    print_test("borrar el primer elemento de la lista devuelve NULL", lista_borrar_primero(lista_4) == elem_null);
    print_test("y la lista queda vacía", lista_esta_vacia(lista_4));
    lista_destruir(lista_4,NULL);

    printf("----PRUEBAS DE ITERACIÓN DE UNA LISTA----\n");

    printf("....PRUEBAS DE ITERADOR INTERNO....\n");
    printf("creo una lista e inserto 50 elementos con insertar_ultimo \n");

    bool imprimir(void* dato, void* extra);
    bool imprimir_con_corte(void* dato, void* extra);

    lista_t* lista_5 = lista_crear();
    int* vector = malloc(sizeof(int)*51);
    for (int i=0; i<=50; i++) {
    	vector[i] = i;
    	lista_insertar_ultimo(lista_5,&vector[i]);
    }

    print_test("el primer elemento de la lista es un 0", *(int*)lista_ver_primero(lista_5) == 0);
    print_test("el último elemento de la lista es un 50", *(int*)lista_ver_ultimo(lista_5) == 50);
    print_test("el largo de la lista es 51", lista_largo(lista_5) == 51);

    printf("utilizo el iterador interno de la Lista para imprimir sus elementos:\n");
    lista_iterar(lista_5,imprimir,NULL);
    printf("\n");

    size_t e = 0;
    size_t* extra = &e;

    printf("utilizo el iterador interno con corte para imprimir sus elementos hasta el 25:\n");
    lista_iterar(lista_5,imprimir_con_corte,extra);
    printf("\n");

    printf("verifico que los elementos de la lista no se hayan modificado: \n");
    print_test("el primer elemento de la lista es un 0", *(int*)lista_ver_primero(lista_5) == 0);
    print_test("el último elemento de la lista es un 50", *(int*)lista_ver_ultimo(lista_5) == 50);
    print_test("el largo de la lista es 51", lista_largo(lista_5) == 51);
    free(vector);
    lista_destruir(lista_5,NULL);

    printf("----PRUEBAS DE ITERADOR EXTERNO----\n");
    lista_t* lista_6 = lista_crear();
    lista_iter_t* iter_externo = lista_iter_crear(lista_6);

    int elem_5 = 3;
    int* punt_5 = &elem_5;
    int elem_6 = 15;
    int* punt_6 = &elem_6;
    int elem_7 = 50;
    int* punt_7 = &elem_7;
    int elem_8 = 75;
    int* punt_8 = &elem_8;
    int elem_9 = 100;
    int* punt_9 = &elem_9;

    printf("....PRUEBAS DE INSERCIÓN DE ELEMENTOS....\n");

    bool avanzar_iterador(lista_iter_t* iter_externo,size_t n);

    print_test("creo el iterador externo para la lista",iter_externo != NULL);
    print_test("inserto el elemento 3 en la posición por defecto del iterador creado..",lista_iter_insertar(iter_externo,punt_5));
    print_test("la lista ahora tiene 1 elemento",lista_largo(lista_6) == 1);
    print_test("el elemento 3 se encuentra primero en la lista",lista_ver_primero(lista_6) == punt_5);
    print_test("por lo tanto esto es equivalente al método lista_insertar_primero",true);
    print_test("inserto el elemento 15 en la posición por defecto del iterador creado..",lista_iter_insertar(iter_externo,punt_6));
    print_test("el elemento 15 se encuentra ahora primero en la lista",lista_ver_primero(lista_6) == punt_6);
    print_test("la lista ahora tiene 2 elementos",lista_largo(lista_6) == 2);
    print_test("avanzo dos posiciones con el iterador externo",avanzar_iterador(iter_externo,2));
    print_test("el iterador está en el final de la lista",lista_iter_al_final(iter_externo));
    print_test("inserto el elemento 50 al final de la lista",lista_iter_insertar(iter_externo,punt_7));
    print_test("la lista ahora tiene 3 elementos",lista_largo(lista_6) == 3);
    print_test("el iterador ya no está en el final de la lista",!lista_iter_al_final(iter_externo));
    print_test("el elemento 15 sigue siendo el primero en la lista",lista_ver_primero(lista_6) == punt_6);
    print_test("el elemento 50 se encuentra último en la lista",lista_ver_ultimo(lista_6) == punt_7);
    print_test("por lo tanto esto es equivalente al método lista_insertar_último",true);
    print_test("inserto el elemento 75 en la posición actual del iterador",lista_iter_insertar(iter_externo,punt_8));
    print_test("inserto el elemento 100 en la posición actual del iterador",lista_iter_insertar(iter_externo,punt_9));
    print_test("los elementos se insertaron en el orden correcto: 15,3,100,75,50",true);
    printf("elementos de la lista: ");
    lista_iterar(lista_6,imprimir,NULL);
    printf("\n");
    print_test("la lista ahora tiene 5 elementos",lista_largo(lista_6) == 5);
    
    lista_iter_destruir(iter_externo);
    lista_destruir(lista_6,NULL);

    print_test("destruyo la lista y el iterador",true);

    printf("....PRUEBAS DE BORRADO DE ELEMENTOS....\n");
    printf("creo una lista y le agrego elementos del 0 al 9\n");

    lista_t* lista_7 = lista_crear();
    int* vector_2 = malloc(sizeof(int)*10);
    for (int i=0; i<10; i++) {
        vector_2[i] = i;
        lista_insertar_ultimo(lista_7,&vector_2[i]);
    }

    lista_iter_t* iter_externo_2 = lista_iter_crear(lista_7);

    print_test("creo el iterador externo para la lista",iter_externo_2 != NULL);
    print_test("la lista tiene 10 elementos",lista_largo(lista_7) == 10);
    int* borrado = lista_iter_borrar(iter_externo_2);
    print_test("borro el elemento que está en la pos. por defecto del iterador creado..",true);
    print_test("el elemento borrado era el primero de la lista (0)",*borrado == 0);
    print_test("la lista ahora tiene 9 elementos",lista_largo(lista_7) == 9);
    borrado = lista_iter_borrar(iter_externo_2);
    print_test("borro el elemento que está en la pos. por defecto del iterador creado..",true);
    print_test("el elemento borrado era el primero de la lista (1)",*borrado == 1);
    print_test("la lista ahora tiene 8 elementos",lista_largo(lista_7) == 8);
    print_test("avanzo tres posiciones con el iterador externo y borro el elemento",avanzar_iterador(iter_externo_2,3));   
    borrado = lista_iter_borrar(iter_externo_2);
    print_test("el elemento borrado es el correcto (5)",*borrado == 5);
    print_test("la lista ahora tiene 7 elementos",lista_largo(lista_7) == 7);
    print_test("avanzo tres posiciones con el iterador externo y borro el elemento",avanzar_iterador(iter_externo_2,3));
    borrado = lista_iter_borrar(iter_externo_2);
    print_test("el elemento borrado es el correcto (9)",*borrado == 9);
    print_test("el iterador se encuentra al final de la lista",lista_iter_al_final(iter_externo_2));
    print_test("el iterador se encuentra sobre el elemento NULL",lista_iter_ver_actual(iter_externo_2) == NULL);
    print_test("borrar un elemento estando al final de la lista devuelve NULL",lista_iter_borrar(iter_externo_2) == NULL);
    print_test("la lista ahora tiene 6 elementos",lista_largo(lista_7) == 6);
    print_test("los elementos borrados (0,1,5,9) ya no se encuentran en la lista",true);
    printf("elementos de la lista: ");
    lista_iterar(lista_7,imprimir,NULL);
    printf("\n");

    lista_iter_destruir(iter_externo_2);
    lista_destruir(lista_7,NULL);
    free(vector_2);

    print_test("destruyo la lista y el iterador",true); 

    printf("----PRUEBAS CON ELEMENTOS GUARDADOS EN EL HEAP----\n");

    lista_t* lista_8 = lista_crear();

    pila_t** vector_3 = malloc(sizeof(pila_t*)*5);

    print_test("creo una lista y le agrego pilas",true);

    for (int i=0; i<5; i++) {
    	pila_t* pila = pila_crear();
    	vector_3[i] = pila;
    	lista_insertar_ultimo(lista_8,vector_3[i]);
    }

    print_test("... y destruyo la lista y sus datos",true);

    void destruir_dato_pila(void* dato);

    lista_destruir(lista_8,*destruir_dato_pila);
    free(vector_3);

    lista_t* lista_9 = lista_crear();

    int** vector_4 = malloc(sizeof(int*)*20);

    print_test("creo una lista y le agrego punteros",true);

    for (int i=0; i<20; i++) {
    	vector_4[i] = malloc(sizeof(int*));
    	lista_insertar_ultimo(lista_9,vector_4[i]);
    }

    void destruir_dato_puntero(void* dato);

    print_test("... y destruyo la lista y sus datos",true);

    lista_destruir(lista_9,*destruir_dato_puntero);
    free(vector_4);

}

bool imprimir(void* dato, void* extra) {
    printf("%d ",*(int*)dato);
    return true;
}


bool imprimir_con_corte(void* dato, void* extra) {
    size_t* corte = extra;
    if (*corte > 25) return false;
    (*corte)++;
    printf("%d ",*(int*)dato);
    return true;
    ;
}

bool avanzar_iterador(lista_iter_t* iter_externo,size_t n) {
    bool avanzar = true;
    for (size_t i = 0; i < n; i++) {
        avanzar = lista_iter_avanzar(iter_externo);
    }
    return avanzar;
}

void destruir_dato_puntero(void* dato) {
    free(dato);
}

void destruir_dato_pila(void* dato) {
    pila_t* pila = dato;
    pila_destruir(pila);
}