
#define     VERTICES        5

typedef int vertice;
typedef int tipo_nombre;
typedef int tipo_elemento;

typedef struct _ARISTA{
    vertice u;
    vertice v;
    int costo;
}arista;

typedef struct _RAMA{
    struct _ARISTA a;
    struct _RAMA * sig;
}rama;

typedef struct _ENCABEZADO{
    int cuenta;
    int primer_elemento;
}encabezado;

typedef struct _NOMBRE{
    tipo_nombre nombre_conjunto;
    int siguiente_elemento;
}nombre;

typedef struct _CONJUNTO_CE{
    nombre nombres[VERTICES];
    encabezado encabezamientos_conjunto[VERTICES];
}conjunto_CE;


void inserta(int i,int j,int costo,rama** r);
arista sacar_min(rama ** r);
void imprimir_cola(rama * r);
void kruskal(rama* r, conjunto_CE c);
conjunto_CE conjunto_ini(tipo_nombre n,tipo_elemento e,conjunto_CE c);
conjunto_CE conjunto_comb(tipo_nombre n, tipo_nombre m, conjunto_CE c);
tipo_nombre conjunto_enc(int x, conjunto_CE c);
unsigned int calc_min(rama * t);

