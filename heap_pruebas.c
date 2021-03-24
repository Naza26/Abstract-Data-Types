
#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_heap_vacio(void) {
    printf("\nINICIO DE PRUEBAS CON HEAP VACIO\n");

    heap_t* heap = heap_crear(NULL);

    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("Con un heap vacio obtengo NULL", heap_ver_max(heap) == NULL);
    print_test("No puedo desencolar en un heap vacio", heap_desencolar(heap) == NULL);
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);

}
/*Funciones de comparacion que se le pueden pasar al heap*/

int compare_max_numbers(const void *n1, const void *n2){
    if(*(int*)n1 > *(int*)n2){
        return 1;
    }
    else if(*(int*)n1 < *(int*)n2){
        return -1;
    }
    return 0;
}

int compare_min_numbers(const void *n1, const void *n2){
    if((int*)n1 < (int*)n2){
        return 1;
    }
    else if((int*)n1 > (int*)n2){
        return -1;
    }
    return 0;
}


static void prueba_pocos_elementos(){
    printf("\nINICIO DE PRUEBAS CON POCOS ELEMENTOS\n");

    heap_t* heap = heap_crear(compare_max_numbers);

    int elemento1 = 50;
    int elemento2 = 30;
    int elemento3 = 20;
    int elemento4 = 15;
    int elemento5 = 10;
    int elemento6 = 8;
    int elemento7 = 16;

    print_test("El heap fue creado", true);
    print_test("Encolar elemento1", heap_encolar(heap, &elemento1));
    print_test("Encolar elemento2", heap_encolar(heap, &elemento2));
    print_test("Encolar elemento3", heap_encolar(heap, &elemento3));
    print_test("Encolar elemento4", heap_encolar(heap, &elemento4));
    print_test("Encolar elemento5", heap_encolar(heap, &elemento5));
    print_test("Encolar elemento6", heap_encolar(heap, &elemento6));
    print_test("Encolar elemento7", heap_encolar(heap, &elemento7));

    //print_heap(heap);

    print_test("La cantidad de elementos es 7", heap_cantidad(heap) == 7);
    print_test("Ver máximo, debe ser el 50", *(int*)heap_ver_max(heap) == elemento1);

    printf("Deberia ver 50 y obtengo %i\n",*(int*)heap_ver_max(heap));
    print_test("Desencolar elemento, debe ser el 50", *(int*)heap_desencolar(heap) == elemento1);
    printf("Deberia ver 30 y obtengo %i\n",*(int*)heap_ver_max(heap));
    print_test("El máximo debería ser el 30", *(int*)heap_ver_max(heap) == elemento2);
    print_test("Desencolar elemento y obtengo 30 como max", *(int*)heap_desencolar(heap) == elemento2);
    printf("Deberia ver 20 y obtengo %i\n", *(int*)heap_ver_max(heap));
    print_test("La cantidad de elementos ahora es 5", heap_cantidad(heap) == 5);
    print_test("Desencolar elemento y obtengo 20 como max", *(int*)heap_desencolar(heap) == elemento3);
    printf("Deberia ver 16 y obtengo %i\n",*(int*)heap_ver_max(heap));
    print_test("Desencolo elemento y obtengo 16 como max", *(int*)heap_desencolar(heap) == elemento7);
    printf("Deberia ver 15 y obtengo %i\n",*(int*)heap_ver_max(heap));
    print_test("Desencolar elemento y obtengo 15 como max", *(int*)heap_desencolar(heap) == elemento4);
    printf("Deberia ver 10 y obtengo %i\n",*(int*)heap_ver_max(heap));
    print_test("Desencolar elemento y obtengo 10 como max", *(int*)heap_desencolar(heap) == elemento5);
    printf("Deberia ver 8 y obtengo %i\n",*(int*)heap_ver_max(heap));
    print_test("Desencolo elemento y obtengo 8 como max", *(int*)heap_desencolar(heap) == elemento6);
    print_test("La cola esta vacia", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);

    /*
        Si pasa las pruebas de arriba ^ el codigo va a andar bien, es un heap de maximos comprobado, cada elemento tiene que salir en ese orden para que se cumpla
        la invariante.
        El bug en nuestro codigo es que downheap no funciona bien por ende, no se mantiene que sea una cola de prioridad (ya sea de maximos o  de minimos)
    */

}

static void prueba_pocos_con_destruir(){
    printf("\nINICIO DE PRUEBAS CON DESTRUIR\n");

    heap_t* heap = heap_crear(compare_max_numbers);
    
    int* elemento1 = malloc(sizeof(int));
    int* elemento2 = malloc(sizeof(int));
    int* elemento3 = malloc(sizeof(int));
    *elemento1 = 100;
    *elemento2 = 400;
    *elemento3 = 500;

    print_test("El heap fue creado", true);
    print_test("Encolar elemento1", heap_encolar(heap, elemento1));
    print_test("Encolar elemento2", heap_encolar(heap, elemento2));
    print_test("Encolar elemento3", heap_encolar(heap, elemento3));
    
    //print_heap(heap);

    heap_destruir(heap, free);
    print_test("El heap fue destruido", true);
}

void pruebas_sobre_arreglo(){
    printf("\nINICIO DE PRUEBAS SOBRE ARREGLO\n");
    void* arreglo[3];
    int primero = 290;
    int segundo = 200;
    int tercero = 550; 
    arreglo[0] = &primero;
    arreglo[1] = &segundo;
    arreglo[2] = &tercero;

    heap_t* heap = heap_crear_arr(arreglo, 3, compare_max_numbers);
    //print_heap(heap);
    print_test("Usar la funcion de conversion", true);
    print_test("Cantidad de elementos del heap es 3", heap_cantidad(heap) == 3);
    print_test("El máximo debería ser 550", heap_ver_max(heap) == arreglo[2]);
    print_test("Se puede desencolar", heap_desencolar(heap));
    //print_heap(heap);
    print_test("El máximo ahora es 290", heap_ver_max(heap) == arreglo[0]);
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
}

void prueba_volumen(){
    printf("\nINICIO DE PRUEBAS VOLUMEN SOBRE HEAP\n");

    heap_t *heap = heap_crear(compare_max_numbers);

    bool ok = true;
    
    int *valores = malloc(5000 * sizeof(int));

    void **numeros_random = malloc(sizeof(void*) * 5000);

    for (int i = 0; i < 5000; i++) {
		valores[i] = i;
        numeros_random[i] = &valores[i];
    }

    heap_sort(numeros_random, 5000, compare_min_numbers);

    for (int i = 0; i < 5000; i++){
		ok &= heap_encolar(heap, numeros_random[i]);
	}
    
    print_test("Encolo 1000 elementos correctamente", ok);

	print_test("Reviso que el primer elemento sea el correcto", heap_ver_max(heap) == numeros_random[0]);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));

    for (int i = 0; i < 5000; i++){
        ok &= *(int*)heap_ver_max(heap) == *(int*)numeros_random[i];
        void *elem = heap_desencolar(heap);
        ok &= *(int*)numeros_random[i] == *(int*)elem;
	}

    print_test("Desencolado correcto", ok);

    heap_destruir(heap, NULL);
    free(valores);
    free(numeros_random);
    print_test("El heap fue destruido", true);

}

void prueba_ordenar(){
    int *valores = malloc(5*sizeof(int));
    void **arreglo = malloc(5*sizeof(void*));
    int j = 0;
    for(int i = 4; i>=0; i--){
        valores[j] = i;
        arreglo[j] = &valores[i];
        j++;
    }
    heap_sort(arreglo, 5, compare_min_numbers);
    bool ok = true;
    j = 0;
    for(int i = 0; i<5; i++){
        ok &= (*(int*)arreglo[i] == j);
        j++;
    }
    print_test("Se ordenaron correctamente de menor a mayor", ok);
    free(valores);
    free(arreglo);

}

void pruebas_heap_estudiante(){
    prueba_heap_vacio();
    prueba_pocos_elementos();
    prueba_pocos_con_destruir();
    pruebas_sobre_arreglo();
    prueba_volumen();
    prueba_ordenar();
}


#ifndef CORRECTOR

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
