#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_lista_vacia(void) {
    printf("\nINICIO DE PRUEBAS CON LISTA VACIA\n");

    /*Creo una lista*/
    lista_t *lista = lista_crear();

    /*Pruebas para verificar que la lista este vacia*/
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("El primer elemento de una lista vacia es NULL", lista_ver_primero(lista) == NULL);
    print_test("El ultimo elemento de una lista vacia es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("No puedo borrar un elemento en una lista vacia", lista_borrar_primero(lista) == NULL);
    print_test("El largo de una lista recien creada es cero", lista_largo(lista) == 0);

    /* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);

}

static void prueba_funcionamiento_lista(void){
    printf("\nINICIO DE PRUEBAS PARA EL FUNCIONAMIENTO DE LA LISTA\n");

    /*Creo una lista*/
    lista_t *lista = lista_crear();

    int num1 = 1;

    int num2 = 2;

    int num3 = 3;

    /*Pruebas de creacion sobre la lista*/

    print_test("Inserto el numero 1", lista_insertar_primero(lista, &num1));
    print_test("El primer elemento es 1", lista_ver_primero(lista) == &num1);
    print_test("El ultimo elemento tambien es 1", lista_ver_ultimo(lista) == &num1);
    print_test("Inserto el numero 2", lista_insertar_ultimo(lista, &num2));
    print_test("Inserto el numero 3", lista_insertar_ultimo(lista, &num3));
    print_test("El ultimo elemento es 3", lista_ver_ultimo(lista) == &num3);
    print_test("El largo de la lista es 3", lista_largo(lista) == 3);

    /*Pruebas de destruccion sobre la lista*/

    print_test("Elimino el 1 de la lista", lista_borrar_primero(lista) == &num1);
    print_test("El largo de la lista se redujo a 2", lista_largo(lista) == 2);
    print_test("Me aseguro que al lista no este vacia", !lista_esta_vacia(lista));
    print_test("El primer elemento ahora es 2", lista_ver_primero(lista) == &num2);
    print_test("El ultimo elemento sigue siendo 3", lista_ver_ultimo(lista) == &num3);
    print_test("Elimino el segundo elemento", lista_borrar_primero(lista));
    print_test("Elimino el tercer elemento", lista_borrar_primero(lista));
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("Intento eliminar un elemento sobre una lista vacia", lista_borrar_primero(lista) == NULL);
    print_test("El largo de la lista es 0", lista_largo(lista) == 0);
	
    /* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}

static void prueba_null_lista(void){
    printf("\nINICIO DE PRUEBAS CON ELEMENTO NULL SOBRE LA LISTA\n");

    /*Creo una lista*/
    lista_t *lista = lista_crear();

    /*Pruebas para el elemento NULL sobre una lista*/
    print_test("Inserto correctamente NULL", lista_insertar_primero(lista, NULL));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Reviso que el primer elemento sea NULL", lista_ver_primero(lista) == NULL);
    print_test("Reviso que el ultimo elemento sea NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Elimino y obtengo NULL", lista_borrar_primero(lista) == NULL);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
   
    /* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}

static void prueba_volumen_lista(void){
    printf("\nINICIO DE PRUEBAS VOLUMEN SOBRE LA LISTA\n");

    /*Creo una lista*/
    lista_t *lista = lista_crear();

    bool ok = true;
   
    int *vector_numeros = malloc(1000 * sizeof(int));

    /*Inserto 1000 elementos para la prueba de volumen*/
    for (int i = 0; i <= 1000; i++){
    ok &= lista_insertar_ultimo(lista, &vector_numeros[i]);
    }

    print_test("1000 elementos correctamente insertados", ok);

    /*Reviso el primer elemento*/
    print_test("Reviso que el primer elemento sea 0", lista_ver_primero(lista) == &vector_numeros[0]);

    /*Reviso que la lista no este vacia*/
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    /*Elimino 1000 elementos para la prueba de volumen*/
    for (int i = 0; i <= 1000; i++){
        ok &= lista_ver_primero(lista) == &vector_numeros[i];
        int *elem = lista_borrar_primero(lista);
        ok &= &vector_numeros[i] == elem;
   
    }

    /*Reviso que se hayan eleminado correctamente los elementos*/
    print_test("Eliminados correctamente", ok);

    /* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);

    free(vector_numeros);
}

static void prueba_iterador_externo_vacio(void){
    printf("\nINICIO DE PRUEBAS PARA EL ITERADOR EXTERNO CON LISTA VACIA\n");

    /*Creo una lista*/
    lista_t *lista = lista_crear();

    /*Creo un iterador*/
    lista_iter_t *iter = lista_iter_crear(lista);

    /*Verifico que efectivamente el iterador este vacio*/
    print_test("El iterador esta vacio", lista_iter_ver_actual(iter) == NULL);

    /*Verifico no poder avanzar un iterador sobre una lista vacia*/
    print_test("No puedo avanzar un iterador sobre una lista vacia", !lista_iter_avanzar(iter));

    /*Verifico que el iterador este al final en una lista vacia*/
    print_test("El iterador esta al final", lista_iter_al_final(iter));

    /* Destruyo el iterador*/
    lista_iter_destruir(iter);
    print_test("El iterador fue destruido", true);

    /* Destruyo la lista*/
    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}

bool sumar(void *elemento, void *extra){
    int *contador = extra;
    ++(*contador);
    return true;
}

bool vistar_impares(void *elemento, void *extra){
    int *contador = extra;
    if(*( (int *) elemento) % 2 != 0){
        ++(*contador);
        return true;
    } else {
        return false;
    }
}

bool imprimir_un_item(void *elemento, void *extra){
    int *contador = extra;
    printf("%d. %s\n", ++(*contador), (char *) elemento);
    return true;
}

static void pruebas_iterador_interno(){

    printf("INICIO DE PRUEBAS CON ITERADOR INTERNO\n");

    int num1 = 1;
    int num2 = 2;
    int num3 = 3;

    lista_t* lista = lista_crear();
    int extra = 0;
    int cant_suma = 0;
    print_test("Inserto el numero 1 al principio", lista_insertar_primero(lista, &num1) && lista_ver_primero(lista)==&num1);
    print_test("Inserto el numero 2 al final", lista_insertar_ultimo(lista, &num2) && lista_ver_ultimo(lista)==&num2);
    print_test("Inserto el numero 3 al final", lista_insertar_ultimo(lista, &num3) && lista_ver_ultimo(lista)==&num3);
    lista_iterar(lista,vistar_impares,&extra);
    print_test("El extra es igual a la cantidad de impares recorridos",extra==1);
    lista_iterar(lista,sumar,&cant_suma);
    print_test("La cantidad de la suma es igual al largo de la lista",lista_largo(lista)==cant_suma);
    lista_destruir(lista,NULL);
}

static void prueba_iterador_casos_bordes(void){

	printf("\nINICIO DE PRUEBAS CON ITERADOR CASOS BORDES\n");

    int num1 = 1;
    int num2 = 2;
    int num3 = 3;

    lista_t* lista = lista_crear();

    print_test("Inserto el numero 1 al comienzo",lista_insertar_primero(lista,&num1));
    print_test("Inserto el numero 2 al final",lista_insertar_ultimo(lista,&num2));
    print_test("Inserto nuevamente un numero, el 3, al final",lista_insertar_ultimo(lista,&num3));

    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("El actual del iterador esta en el primero de la lista",lista_iter_ver_actual(iter) == &num1);
    print_test("Avanzo el iterador y ahora actual es el numero 2",lista_iter_avanzar(iter) && lista_iter_ver_actual(iter) == &num2);
    print_test("El iterador no esta al final",!lista_iter_al_final(iter));
    print_test("Inserto el numero 3 a la lista",lista_iter_insertar(iter, &num3));
    print_test("El actual ahora es el numero 3",lista_iter_ver_actual(iter) == &num3);
    
    lista_destruir(lista,NULL);
    lista_iter_destruir(iter);

    lista_t* lista2 = lista_crear();

    lista_insertar_primero(lista2, &num1);
    lista_insertar_ultimo(lista2, &num2);
    lista_insertar_ultimo(lista2, &num3);
    print_test("La lista2 no esta vacia y tiene largo 3",!lista_esta_vacia(lista2) && lista_largo(lista2) == 3);

    lista_iter_t* iter2 = lista_iter_crear(lista2);

    print_test("Avanzo el iterador2",lista_iter_avanzar(iter2));
    print_test("Estoy en el numero 2", lista_iter_ver_actual(iter2) == &num2);
    print_test("Borro el numero 2",lista_iter_borrar(iter2) == &num2);
    print_test("El actual ahora es el numero 3", lista_iter_ver_actual(iter2) == &num3);
    print_test("Si avanzo el iterador2, estoy al final",lista_iter_avanzar(iter2) && lista_iter_al_final(iter2));

    lista_destruir(lista2,NULL);
    lista_iter_destruir(iter2);
}
static void pruebas_iterador(void){
	
	printf("\nINICIO DE PRUEBAS CON ITERADOR\n");
	
	int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;

    lista_t* lista = lista_crear();

    print_test("Inserto el numero 1 al comienzo",lista_insertar_primero(lista,&num1));
    print_test("Inserto el numero 2 al final",lista_insertar_ultimo(lista,&num2));
    print_test("Inserto el numero el 3 al final",lista_insertar_ultimo(lista,&num3));
    print_test("Inserto el numero el 4 al final",lista_insertar_ultimo(lista,&num4));
    print_test("Inserto el numero el 5 al final",lista_insertar_ultimo(lista,&num5));

    lista_iter_t* iter = lista_iter_crear(lista);
    
    print_test("La lista tiene 5 elementos", lista_largo(lista) == 5);
    print_test("El actual del iterador esta en el primero de la lista",lista_iter_ver_actual(iter) == &num1);
    print_test("Avanzo el iterador y ahora actual es el numero 2",lista_iter_avanzar(iter) && lista_iter_ver_actual(iter) == &num2);
    print_test("El iterador no esta al final",!lista_iter_al_final(iter));
    print_test("Avanzo el iterador y ahora actual es el numero 3",lista_iter_avanzar(iter) && lista_iter_ver_actual(iter));
    print_test("Avanzo el iterador y ahora actual es el numero 4",lista_iter_avanzar(iter) && lista_iter_ver_actual(iter));
    print_test("Avanzo el iterador y ahora actual es el numero 5",lista_iter_avanzar(iter) && lista_iter_ver_actual(iter));
    print_test("No puedo avanzar mas porque ya estoy al final de la lista", lista_iter_ver_actual(iter) == lista_ver_ultimo(lista));
    print_test("Borro el numero 1", lista_borrar_primero(lista) == &num1);
    print_test("Ahora la lista tiene largo 4", lista_largo(lista) == 4);
    
    lista_destruir(lista,NULL);
    lista_iter_destruir(iter);
}
void pruebas_lista_estudiante(void){
    prueba_lista_vacia();
    prueba_funcionamiento_lista();
    prueba_null_lista();
    prueba_volumen_lista();

    pruebas_iterador_interno();

    prueba_iterador_externo_vacio();
    pruebas_iterador();
    prueba_iterador_casos_bordes();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
