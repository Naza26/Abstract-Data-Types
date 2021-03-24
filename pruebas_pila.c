#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void prueba_pila_vacia(void) {
    printf("\nINICIO DE PRUEBAS CON PILA VACIA\n");

    /*Creo una Pila*/
    pila_t* pila = pila_crear();

    /*Reviso si la Pila esta vacía*/
    print_test("Esta vacia la pila?", pila_esta_vacia(pila) == true);

    /*Reviso si la Pila tiene elementos*/
    print_test("Con una Pila vacia obtengo NULL", pila_ver_tope(pila) == NULL);

    /* Destruyo la Pila*/
    pila_destruir(pila);
    print_test("La Pila fue destruida", true);

}

static void prueba_funcionamiento_pila(void){
    printf("\nINICIO DE PRUEBAS PARA EL FUNCIONAMIENTO DE LA PILA\n");

    /*Creo una Pila*/
    pila_t* pila = pila_crear();

    /*Apilo algunos elementos*/
    int numero1 = 5;
    int* puntNum1 = &numero1;
    print_test("Apilo un 5", pila_apilar(pila, puntNum1));
    int numero2 = 8;
    int* puntNum2 = &numero2;
    print_test("Apilo un 8", pila_apilar(pila, puntNum2));
    int numero3 = 1;
    int* puntNum3 = &numero3;
    print_test("Apilo un 1", pila_apilar(pila, puntNum3));
    
    /*Reviso que el tope coincida con el último elemento ingresado (LIFO)*/
    print_test("Veo el ultimo elemento ingresado, 1", pila_ver_tope(pila) == &numero3);

    /*Desapilo algunos elementos*/
    print_test("Desapilo y obtengo 1", pila_desapilar(pila) == &numero3);
    print_test("Desapilo y obtengo 8", pila_desapilar(pila) == &numero2);
    print_test("Desapilo y obtengo 5", pila_desapilar(pila) == &numero1);

    printf("INICIO DE PRUEBAS VOLUMEN SOBRE LA PILA\n");

    bool ok = true;
    
    int *vector_numeros = malloc(1000 * sizeof(int));

    /*Apilo 1000 elementos para la prueba de volumen*/
    for (int i = 0; i <= 1000; i++){

		ok &= pila_apilar(pila, &vector_numeros[i]);
	}

    print_test("1000 Elementos correctamente apilados", ok);

    /*Reviso el tope*/
	print_test("Reviso que el tope sea 1000", pila_ver_tope(pila) == &vector_numeros[1000]);

    /*Desapilo 800 elementos*/
    for (int i = 0; i <= 800; i++){
        pila_desapilar(pila);
        ok &= pila_ver_tope(pila) == &vector_numeros[1000-i-1];
    }

    print_test("Reviso que los topes sean correctos", ok);

    print_test("Reviso que el tope sea 200", pila_ver_tope(pila) == &vector_numeros[199]);
    free(vector_numeros);

	/* Destruyo la Pila*/
    pila_destruir(pila);
    print_test("La Pila fue destruida", true);
}

static void pruebas_casos_bordes(void){
	printf("\nINICIO DE PRUEBAS PARA CASOS BORDE\n");
	
	int numero1 = 5;
    int* puntNum1 = &numero1;
    
	/*Creo una Pila*/
    pila_t* pila = pila_crear();
    
    /*Pruebo desapilar una Pila vacía*/

    print_test("Desapilo Pila vacia y obtengo NULL", pila_desapilar(pila) == NULL);

    /*Pruebo ver el tope de una Pila vacia*/

    print_test("El tope es NULL", pila_ver_tope(pila) == NULL);

    /*Pruebo que la Pila esté vacia*/

    print_test("La pila esta vacia", pila_esta_vacia(pila) == true);
    
    /*Apilo 3 elementos*/
    print_test("Apilo un 5", pila_apilar(pila, puntNum1));
    print_test("Apilo nuevamente un 5", pila_apilar(pila, puntNum1));
    print_test("Apilo NULL", pila_apilar(pila, NULL));
    
    /*Reviso el tope de la pila siendo NULL*/
    print_test("El tope es NULL", pila_ver_tope(pila) == NULL);
    
    /*Desapilo 1 elemento*/
    print_test("Desapilo y obtengo NULL", pila_desapilar(pila) == NULL);
    
    /*Reviso el tope de la pila luego de desapilar NULL*/
    print_test("El tope es 5", pila_ver_tope(pila) == &numero1);
    
    /* Destruyo la Pila*/
    pila_destruir(pila);
    print_test("Destruyo Pila no vacia", true);
	
	}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_funcionamiento_pila();
    pruebas_casos_bordes();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
