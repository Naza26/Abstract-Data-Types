#include "pila.h"
#include <stdlib.h>
#define CAPACIDAD 10
#define COEF_AUMENTO 2
#define COEF_REDUCCION 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila{
    void **datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad; // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){

    pila_t *pila = malloc(sizeof(pila_t));

    if (!pila){
        free(pila);
        return NULL;
    }

    pila->capacidad = CAPACIDAD;
    pila->cantidad = 0;
    pila->datos = malloc((pila->capacidad) * sizeof(void *));

    if(!pila->datos){
        free(pila);
        return NULL;
    }

    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_redimension(pila_t *pila, size_t tam){
	
	void *nuevos_datos = NULL;
	nuevos_datos = realloc(pila->datos, tam * sizeof(void *));
	
	if(!nuevos_datos) return false;

    pila->capacidad = tam;
    pila->datos = nuevos_datos;
	return true;
}

bool pila_apilar(pila_t *pila, void *valor){

    if (pila->cantidad == pila->capacidad){
        size_t capacidad_aux = pila->capacidad * COEF_AUMENTO;
        if(!pila_redimension(pila, capacidad_aux)){
            return false;
        }
        pila_redimension(pila, pila->capacidad);
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void *pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;
    return pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila){

    if (pila_esta_vacia(pila)) return NULL;

    if (pila->cantidad * COEF_REDUCCION <= pila->capacidad){

        size_t capacidad_aux = pila->capacidad / COEF_AUMENTO;

        if(capacidad_aux < pila->cantidad){
            return pila->datos[pila->cantidad];
        }

        if(!pila_redimension(pila, capacidad_aux)){
            return pila->datos[pila->cantidad];
        }
        pila_redimension(pila, pila->capacidad);   
    }
    pila->cantidad--;
    return pila->datos[pila->cantidad];
}
