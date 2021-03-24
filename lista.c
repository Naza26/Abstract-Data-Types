#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
    void* dato;
    struct nodo* sig;
} nodo_t;

struct lista {
    nodo_t *prim;
    nodo_t *ult;
    size_t largo;
};

nodo_t *nodo_crear(void *dato, nodo_t *sig){

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    
    if(!nuevo_nodo) return NULL;
    nuevo_nodo->dato = dato;
    nuevo_nodo->sig = sig;
    return nuevo_nodo;
}

lista_t *lista_crear(void){

    lista_t *lista = malloc(sizeof(lista_t));

    if(!lista) return NULL;

    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;

    return lista;    
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	
	nodo_t *nuevo_nodo = nodo_crear(dato, lista->prim);
	
	if(!nuevo_nodo) return false;
	
    lista->prim = nuevo_nodo;
    lista->largo++;
    if(lista->largo == 1){
	    lista->ult = nuevo_nodo;
    }
    return true;
}


bool lista_insertar_ultimo(lista_t *lista, void *dato){
    
    nodo_t *nuevo_nodo = nodo_crear(dato, NULL);
    
    if(!nuevo_nodo) return false;
    
    if (lista->ult) {
        lista->ult->sig = nuevo_nodo;
    }
    lista->ult = nuevo_nodo;
    lista->largo++;

    if(lista->largo == 1){
		lista->prim = lista->ult;
    }
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    
	if(lista_esta_vacia(lista)) return NULL;

	nodo_t *nodo_a_eliminar = lista->prim;
    void *dato = lista->prim->dato;
    lista->prim = lista->prim->sig;
    free(nodo_a_eliminar);

    if(lista->largo == 1){
		lista->ult = NULL;
		lista->prim = lista->ult;
    }

    lista->largo--;
    return dato;
}

void *lista_ver_primero(const lista_t *lista){

    if(lista_esta_vacia(lista)) return NULL;
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){

    if(lista_esta_vacia(lista)) return NULL;
    return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}


void lista_destruir(lista_t* lista, void (*destruir_dato)(void*)){

    while (!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if(destruir_dato != NULL){
            destruir_dato(dato);
        }
    }
    free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){

    nodo_t *actual = lista->prim;

    while(actual){
        if(!visitar(actual->dato, extra)){
            return;
        }
        actual = actual->sig;
    }
}
struct lista_iter {
    nodo_t *actual;
    nodo_t *ant;
    lista_t *lista;
};

lista_iter_t *lista_iter_crear(lista_t *lista){

    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
	
	if(!iter) return NULL;
	
    iter->lista = lista;
    iter->actual = lista->prim;
    iter->ant = NULL;

    return iter;  
}

bool lista_iter_avanzar(lista_iter_t *iter){

    if(lista_iter_al_final(iter)) return false;
    iter->ant = iter->actual;
    iter->actual = iter->actual->sig;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){

    if(lista_iter_al_final(iter)) return NULL;
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	
	bool ok = true;
	
    if(iter->actual == iter->lista->prim){
        ok = lista_insertar_primero(iter->lista, dato);
        if(!ok){
			return false;
		}
        iter->ant = NULL;
        iter->actual = iter->lista->prim;
    } else if(lista_iter_al_final(iter)){
        ok = lista_insertar_ultimo(iter->lista, dato);
        if(!ok){
			return false;
		}
        iter->actual = iter->lista->ult;
    } else {
		nodo_t *nuevo_nodo = nodo_crear(dato, iter->actual);
		if(!nuevo_nodo){
			return false;
		}
		if(iter->actual == iter->lista->ult){
			iter->ant->sig = nuevo_nodo;
		} else {
			iter->ant->sig = nuevo_nodo;
			iter->actual = nuevo_nodo;
		}
        iter->lista->largo++;
    }
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	
	if(lista_iter_al_final(iter)) return NULL;

    nodo_t *aux = iter->actual;
    void *eliminar_dato = iter->actual->dato;

    if(iter->actual == iter->lista->prim){
        if(iter->lista->largo == 1){
			iter->actual = iter->actual->sig;
			iter->lista->prim = iter->actual;
            iter->lista->ult = iter->ant;
            iter->lista->largo--;
            free(aux);
			return eliminar_dato;
        } else {
            lista_borrar_primero(iter->lista); 
            iter->actual = iter->lista->prim;
			return eliminar_dato;
        }
    } 
    if(iter->actual == iter->lista->ult){
		iter->actual = NULL;
		iter->ant->sig = iter->actual;
        iter->lista->ult = iter->ant;
        iter->lista->largo--;
        free(aux);
		return eliminar_dato;
    }
	iter->ant->sig = iter->actual->sig;
    iter->actual = iter->actual->sig;
    iter->lista->largo--;
    free(aux);
	return eliminar_dato;
}
