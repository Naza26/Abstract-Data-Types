#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_cola_vacia(void) {
    printf("\nINICIO DE PRUEBAS CON COLA VACIA\n");

    /*Creo una cola*/
    cola_t* cola = cola_crear();

    /*Reviso si la cola esta vacía*/
    print_test("La cola esta vacia", cola_esta_vacia(cola));

    /*Intento ver el primer elemento en una cola vacia*/
    print_test("Con una cola vacia obtengo NULL", cola_ver_primero(cola) == NULL);

    /*Intento desencolar en una cola vacia*/
    print_test("No puedo desencolar en una cola vacia", cola_desencolar(cola) == NULL);

    /* Destruyo la cola*/
    cola_destruir(cola, free);
    print_test("La cola fue destruida", true);

}

static void prueba_funcionamiento_cola(void){
    printf("\nINICIO DE PRUEBAS VOLUMEN SOBRE LA COLA\n");

    /*Creo una cola*/
    cola_t* cola = cola_crear();

    bool ok = true;
    
    int *vector_numeros = malloc(1000 * sizeof(int));

    /*Encolo 1000 elementos para la prueba de volumen*/
    for (int i = 0; i <= 1000; i++){
		ok &= cola_encolar(cola, &vector_numeros[i]);
	}

    print_test("Encolo 1000 elementos correctamente", ok);

    /*Reviso el frente*/
	print_test("Reviso que el primer elemento sea 0", cola_ver_primero(cola) == &vector_numeros[0]);

    /*Reviso que la cola no este vacia*/
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));

    /*Desencolo 500 elementos para la prueba de volumen*/
    for (int i = 0; i <= 500; i++){
        int *elem = cola_desencolar(cola);
        ok &= &vector_numeros[i] == elem;
        ok &= cola_ver_primero(cola) == &vector_numeros[i+1];
	}
    /*Reviso que se desencolen correctamente los elementos*/
    print_test("Desencolado correcto", ok);

    /*Reviso que se mantenga la invariante*/
    print_test("Reviso que se cumpla la invariante FIFO", ok);

    /*Reviso el frente*/
	print_test("Reviso el frente luego de desencolar 500 elementos", cola_ver_primero(cola) == &vector_numeros[501]);

    /* Destruyo la cola*/
    cola_destruir(cola, NULL);
    print_test("La cola fue destruida", true);

    free(vector_numeros);
}


static void prueba_null_cola(void){
    printf("\nINICIO DE PRUEBAS CON ELEMENTO NULL SOBRE LA COLA\n");

    /*Creo una cola*/
    cola_t* cola = cola_crear();

    /*Encolo un elemento NULL*/
    print_test("Encolo correctamente NULL", cola_encolar(cola, NULL));

    /*Reviso si la cola esta vacía*/
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));

    /*Reviso el frente*/
	print_test("Reviso que el frente sea NULL", cola_ver_primero(cola) == NULL);

    /*Desencolo y obtengo NULL*/
    print_test("Desencolo y obtengo NULL", cola_desencolar(cola) == NULL);

    /*Reviso que la cola este vacía luego de desencolar*/
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    
    /* Destruyo la cola*/
    cola_destruir(cola, free);
    print_test("La cola fue destruida", true);
}

static void prueba_destruccion(void){

    cola_t *cola = cola_crear();

    int *num1 = malloc(sizeof(int));
    *num1 = 1;

    int *num2 = malloc(sizeof(int));
    *num2 = 2;

    int *num3 = malloc(sizeof(int));
    *num3 = 3;

    print_test("Encolo el numero 1", cola_encolar(cola, num1));
    print_test("Encolo el numero 2", cola_encolar(cola, num2));
    print_test("Encolo el numero 3", cola_encolar(cola, num3));
    cola_destruir(cola, free);
    print_test("La cola fue destruida", true);
}


void pruebas_cola_estudiante(){
    prueba_cola_vacia();
    prueba_funcionamiento_cola();
    prueba_null_cola();
    prueba_destruccion();

}

#ifndef CORRECTOR

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif