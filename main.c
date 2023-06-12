#include <stdio.h>
#include <stdlib.h>

#include "kruskal.h"

int main()
{
    int M_Costos[VERTICES][VERTICES];
    rama *arbol;
    arbol = NULL;
    conjunto_CE conjunto;
    int num=0;

    printf("*****************************************************************************************\n");
    printf("**              Implementacion del Algoritmo de Kruskal                                **\n");
    printf("**              Integrantes: Avila,Ivan Ezequiel; Torrazza,Virginia Fernanda           **\n");
    printf("*****************************************************************************************\n");

    do{

    /// Se utilizan bucles anidados para completar la matriz y almacenar los datos de los vértices ingresados por el usuario.
    for (int i=0;i<=VERTICES-1;i++)
        for (int j=i+1;j<=VERTICES-1;j++)
        {
            printf("Ingrese el costo de la arista entre los vertices %d y %d: ", i,j);
            scanf("%d",&M_Costos [i][j]);
        }
    ///bucle anidado donde generamos el grafo que utilizaremos a través de una cola de prioridad.
    for(int i=0;i<=VERTICES-1;i++)
        for(int j=i+1;j<=VERTICES-1;j++)
            if(M_Costos[i][j]!=0)
            inserta(i,j,M_Costos[i][j],&arbol);

    kruskal(arbol, conjunto);///llamada a la función Kruskal para realizar el algoritmo de dicho nombre.

    printf("\n");
    printf("Desea salir? Para salir presione 0 : ");
    scanf("%d",&num);
    printf("*****************************************************************************************\n");

    }while(num!=0);
    return 0;
}





