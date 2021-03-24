#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
enum estado{
    VACIO,
    OCUPADO,
    BORRADO
};

typedef struct campo{
    char *clave;
    void *valor;
    enum estado estado;
} campo_t;

struct hash{
    size_t capacidad;
    size_t cantidad_claves;
    size_t cant_borrados;
    hash_destruir_dato_t funcion_destruccion;
    campo_t *tabla;
};

struct hash_iter{
    const hash_t *hash;
    size_t posicion;
};

  static unsigned long f_hash(const char *str){
     unsigned long hash = 0;
     int c;

      while ((c = *str++))
         hash = c + (hash << 6) + (hash << 16) - hash;

      return hash;
  }

void inicializar_campos_vacios(hash_t* hash){
    for (size_t i = 0; i < hash->capacidad; i++){
        hash->tabla[i].estado = VACIO;
    }
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t *hash = malloc(sizeof(hash_t));
    if (!hash){
        return NULL;
    }
    hash->cantidad_claves = 0;
    hash->capacidad = 10;
    hash->cant_borrados = 0;
    campo_t *tabla = malloc(sizeof(campo_t) * hash->capacidad);
    if (!tabla){
        free(hash);
        return NULL;
    }
    hash->tabla = tabla;
    inicializar_campos_vacios(hash);
    hash->funcion_destruccion = destruir_dato;
    return hash;
}

bool redimensionar_hash(hash_t *hash, bool aumento_redimension){
    size_t capacidad_anterior = hash->capacidad;
    campo_t *tabla_anterior = hash->tabla;

    if (aumento_redimension == true){
        hash->capacidad = hash->capacidad * 2;
    }
    else{
        if (hash->capacidad / 2 > 10){
            hash->capacidad = hash->capacidad / 2;
        }
        else{
            hash->capacidad = 10;
        }
    }
    campo_t* nueva_tabla = malloc(sizeof(campo_t) * hash->capacidad);
    if (!nueva_tabla){
        return false;
    }
    hash->cant_borrados = 0;
    hash->tabla = nueva_tabla;
    inicializar_campos_vacios(hash);
    hash->cantidad_claves = 0;
    //inicializar_campos_vacios(hash);
    for (size_t i = 0; i < capacidad_anterior; i++){
        if (tabla_anterior[i].estado == OCUPADO){
            char *clave = tabla_anterior[i].clave;
            hash_guardar(hash, tabla_anterior[i].clave, tabla_anterior[i].valor);
            free(clave);
        }
    }
    free(tabla_anterior);
    return true;
}
bool hash_guardar(hash_t *hash, const char *clave, void *dato){

    char *clave_aux = strdup(clave);
    size_t clave_hasheada = f_hash(clave) % hash->capacidad;
    for (size_t i = 0; i < hash->capacidad; i++){
        if (clave_hasheada >= hash->capacidad){
            clave_hasheada = 0;
        }
        if (hash->tabla[clave_hasheada].estado == VACIO){
            hash->tabla[clave_hasheada].clave = clave_aux;
            hash->tabla[clave_hasheada].valor = dato;
            hash->tabla[clave_hasheada].estado = OCUPADO;
            hash->cantidad_claves++;
            if ((((hash->cantidad_claves + hash->cant_borrados) * 100 / (hash->capacidad)) >= 70)){
                bool red = redimensionar_hash(hash, true);
                if (!red){
					return false;
                }
            }
            return true;
        }
        if (hash->tabla[clave_hasheada].estado == OCUPADO){
            if (strcmp(hash->tabla[clave_hasheada].clave, clave) == 0){
                if (hash->funcion_destruccion != NULL){
                    void *dato_aux = hash->tabla[clave_hasheada].valor;
                    hash->funcion_destruccion(dato_aux);
                }
                hash->tabla[clave_hasheada].valor = dato;
                free(clave_aux);
                return true;
            }
        }
        clave_hasheada++;
    }
    return false;
}

void *hash_borrar(hash_t *hash, const char *clave){
    if (hash->cantidad_claves == 0 ){
        return NULL;
    }
    if ((hash->cantidad_claves * 4) <= hash->capacidad){
            bool red = redimensionar_hash(hash, false);
            if (!red){
                return false;
            }
        }
    size_t clave_hasheada = f_hash(clave) % hash->capacidad;
    for (size_t i = 0; i < hash->capacidad; i++)
    {
		
		if(clave_hasheada >= hash->capacidad)
        {
            clave_hasheada = 0;
        }
        if (hash->tabla[clave_hasheada].estado == OCUPADO)
        {
			
            if (strcmp(hash->tabla[clave_hasheada].clave, clave) == 0)
            {
                hash->tabla[clave_hasheada].estado = BORRADO;
                hash->cantidad_claves--;
                hash->cant_borrados++;
                free(hash->tabla[clave_hasheada].clave);
                return hash->tabla[clave_hasheada].valor;
            }
        }
        clave_hasheada++;
    }
    return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave)
{   
    if(hash->cantidad_claves == 0 || !hash_pertenece(hash, clave)){
        return NULL;
    }
    size_t clave_hasheada = f_hash(clave) % hash->capacidad;
    for (size_t i = 0; i < hash->capacidad; i++)
    {
        if(clave_hasheada >= hash->capacidad){
            clave_hasheada = 0;
        }
        if (hash->tabla[clave_hasheada].estado == OCUPADO)
        {
            if(strcmp(clave, hash->tabla[clave_hasheada].clave) == 0)
            {
                return hash->tabla[clave_hasheada].valor;
            }
        }
        clave_hasheada++;
    }
    return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    if (hash->cantidad_claves == 0){
        return false;
    }
    size_t clave_hasheada = f_hash(clave) % hash->capacidad;
    
    for (size_t i = 0; i < hash->capacidad; i++){
        if (clave_hasheada >= hash->capacidad){
            clave_hasheada = 0;
        }
        if (hash->tabla[clave_hasheada].estado == OCUPADO){
            if (strcmp(hash->tabla[clave_hasheada].clave, clave) == 0){
                return true;
            }
            clave_hasheada++;
        }
    }
    return false;
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad_claves;
}

void hash_destruir(hash_t *hash){
    if (hash->cantidad_claves != 0){
        for (size_t i = 0; i < hash->capacidad; i++){
            if (hash->tabla[i].estado == OCUPADO){
                free(hash->tabla[i].clave);
                if (hash->funcion_destruccion != NULL){
                    hash->funcion_destruccion(hash->tabla[i].valor);
                }
            }
        }
    }
    free(hash->tabla);
    free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t *iter = malloc(sizeof(hash_iter_t));

    if (!iter){
        return NULL;
    }
    iter->hash = hash;
    iter->posicion = 0;
    for (size_t i = 0; i < iter->hash->capacidad; i++){
        if (iter->hash->tabla[i].estado == OCUPADO){
            iter->posicion = i;
            break;
        }
    }
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    if (iter->hash->cantidad_claves == 0){
        return false;
    }
    iter->posicion++;
    while (!hash_iter_al_final(iter)){
        if (iter->hash->tabla[iter->posicion].estado == VACIO || iter->hash->tabla[iter->posicion].estado == BORRADO){
            iter->posicion++;
            continue;
        }
        return true;
    }
    return false;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if (iter->hash->cantidad_claves == 0 || hash_iter_al_final(iter)){
        return NULL;
    }
    return iter->hash->tabla[iter->posicion].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    if (iter->posicion >= iter->hash->capacidad || iter->hash->cantidad_claves == 0){
        return true;
    }
    return false;
}

void hash_iter_destruir(hash_iter_t *iter){
    free(iter);
}



