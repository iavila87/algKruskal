#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

/** Función inserta: agrega una nueva rama a la cola de prioridad según el valor del costo. Este ordenamiento se realiza de menor a mayor.
    Argumentos:
    int i-> nombre del primer vértice que compone a la arista.
    int j-> nombre del segundo vértice que compone a la arista.
    int costo-> valor del arco
    rama ** r->puntero a la cola.
    Retorna:void.
 */
void inserta(int i,int j,int costo,rama** r){

    int temp_ca = 0;
    rama * temp_sig = NULL;
    rama * temp_ant = NULL;
    rama * temp_ramaf = NULL;

    rama *r_nueva;
    r_nueva = (rama*)malloc(sizeof(rama));

    r_nueva->a.u = i; /// Primer vértice.
    r_nueva->a.v = j; /// Segundo vértice.
    r_nueva->a.costo = costo; /// Costo de la arista formada entre los vértices primero y segundo.

    if((*r) == NULL){
        r_nueva->sig = NULL;
        *r = r_nueva;
    }else{
        r_nueva->sig= *r;
        *r = r_nueva;
    }

    temp_ca = (*r)->a.costo; ///Guardamos el costo de el último nodo agregado para compararlo y ordenarlo de ser necesario.
    temp_sig = (*r)->sig;

    if(temp_sig != NULL){

        do{
            if(temp_sig == NULL){

                temp_ramaf = *r;
                *r = temp_ramaf->sig;
                temp_ramaf->sig = temp_sig;
                temp_ant->sig = temp_ramaf;
                break;

            }else{

                if(temp_ca >= temp_sig->a.costo){
                    if(temp_ant == NULL){
                        break;
                    }else{
                        temp_ramaf = *r;
                        *r = temp_ramaf->sig;
                        temp_ramaf->sig = temp_sig;
                        temp_ant->sig = temp_ramaf;
                        break;
                    }

                }else{
                    temp_ant = temp_sig;
                    temp_sig = temp_sig->sig;
                     }

            }

        }while( temp_ca < temp_ant->a.costo );

    }

}

/** Función sacar_min: elimina de la cola de prioridad la rama de menor peso y retorna la arista propia de esa rama.
    Argumentos:
    rama **r-> puntero doble a la cola de prioridad.
    Retorna:arista.
 */
arista sacar_min(rama ** r){

    rama * aux;
    aux = (*r);
    rama * aux_ant=NULL;

    while(aux->sig!=NULL){
        aux_ant=aux;
        aux=aux->sig;
    }
    aux_ant->sig=NULL;

    arista aris = aux->a;
    free(aux);

    return aris;
}

/** Función imprimir_cola: imprime la cola de prioridad.
    (Utilizada durante el desarrollo del programa para realizar las pruebas).
    Argumentos:
    rama *r-> puntero a la cola de prioridad.
    Retorna:void.
 */
void imprimir_cola(rama *r){
    if(r==NULL){
        printf("La cola esta vacia\n");
    }else{
        do{
            printf("%d\n",r->a.costo);
            r= r->sig;
        } while(r!=NULL);

    }

}

/** Función conjunto_CE conjunto_ini: otorga valores iniciales al conjunto.
    Argumentos.
    int n->nombre del conjunto.
    int e->vértice
    conjunto_CE c-> conjunto de pares ordenados.
    Retorna:conjunto c
 */
conjunto_CE conjunto_ini(tipo_nombre n,tipo_elemento e,conjunto_CE c){

    c.nombres[e].nombre_conjunto=n;
    c.nombres[e].siguiente_elemento=0;
    c.encabezamientos_conjunto[n].cuenta=1;
    c.encabezamientos_conjunto[n].primer_elemento=e;
    return c;
}

/** Función conjunto_CE conjunto_comb: combina los vértices entre conjuntos distintos
    Argumentos.
    int n-> nombre del vértice.
    int m-> nombre del vértice.
    conjunto_CE c-> conjunto de pares ordenados.
    Retorna:conjunto c
 */
conjunto_CE conjunto_comb(tipo_nombre n, tipo_nombre m, conjunto_CE c){
    int i;

    if(c.encabezamientos_conjunto[n].cuenta > c.encabezamientos_conjunto[m].cuenta){
        i = c.encabezamientos_conjunto[m].primer_elemento;

        while(c.nombres[i].siguiente_elemento != 0){
            c.nombres[i].nombre_conjunto = n;
            i = c.nombres[i].siguiente_elemento;
        }

        c.nombres[i].nombre_conjunto = n;
        c.nombres[i].siguiente_elemento = c.encabezamientos_conjunto[n].primer_elemento;
        c.encabezamientos_conjunto[n].primer_elemento = c.encabezamientos_conjunto[m].primer_elemento;
        c.encabezamientos_conjunto[n].cuenta = c.encabezamientos_conjunto[n].cuenta + c.encabezamientos_conjunto[m].cuenta;

    }else{

        i = c.encabezamientos_conjunto[n].primer_elemento;

        while(c.nombres[i].siguiente_elemento != 0){
            c.nombres[i].nombre_conjunto = m;
            i = c.nombres[i].siguiente_elemento;
        }

        c.nombres[i].nombre_conjunto = m;
        c.nombres[i].siguiente_elemento = c.encabezamientos_conjunto[m].primer_elemento;
        c.encabezamientos_conjunto[m].primer_elemento = c.encabezamientos_conjunto[n].primer_elemento;
        c.encabezamientos_conjunto[m].cuenta = c.encabezamientos_conjunto[m].cuenta + c.encabezamientos_conjunto[n].cuenta;

    }
    return c;
}

/** Función tipo_nombre conjunto_enc: devuelve el nombre del conjunto al cual pertenece el vértice.
    Argumentos.
    int x->vértice.
    conjunto_CE c-> conjunto.
    Retorna:int nombre_conjunto.
 */
tipo_nombre conjunto_enc(int x, conjunto_CE c){
    return (c.nombres[x].nombre_conjunto);
}

/** Función calc_min: devuelve la arista de menor peso.
    Argumentos.
    puntero a rama.
    Retorna: unsigned int (costo).
 */
unsigned int calc_min(rama * t){

    unsigned int costo=0;
    while(t->sig!=NULL){
        costo= costo+ t->a.costo;
        t=t->sig;
    }
    costo=costo + t->a.costo;

    return costo;

}


/** Función Kruskal: lleva a cabo el algoritmo de Kruskal para obtener el árbol recubridor mínimo del grafo.
    Argumentos:
    puntero a rama
    conjunto CE c
    Retorna: void
 */

void kruskal(rama * r, conjunto_CE c){
    rama * tree = NULL;
    int comp_sig = 0;
    int comp_n = VERTICES;
    int comp_u = 0;
    int comp_v = 0;

    arista ari;/// estructura tipo arista que permite evaluar si la arista actual se agrega al árbol o se elimina.

    /// bucle empleado para inicializar los conjuntos.
    for(int v = 0; v < VERTICES; v++){
        c = conjunto_ini(comp_sig, v, c);
        comp_sig++;
    }
    ///bucle que cuenta las aristas hasta que se cumpla la propiedad propia de un árbol cuyo número de aristas equivale al número de vértices-1.
    while(comp_n > 1){
        ari = sacar_min(&r);///almacenamos en ari la arista a evaluar.
        comp_u = conjunto_enc(ari.u, c);
        comp_v = conjunto_enc(ari.v, c);


        if(comp_u != comp_v){
            c = conjunto_comb(comp_u, comp_v, c);
            comp_n = comp_n - 1;
            printf("\nAgregue arista conformada por los vertices %d y %d y costo= %d \n", ari.u, ari.v, ari.costo);
            inserta(comp_u, comp_v, ari.costo, &tree);
        }
    }
    printf("\n");
    printf("El costo del arbol recubridor minimo es de : %d\n",calc_min(tree));

}
