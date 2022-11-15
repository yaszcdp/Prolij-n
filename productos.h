#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#define archivoProductos "productos.bin"//nombre archivo productos
#define dimStr 30//dimensión strings
#define dimADLProd 7//dimensión arreglo de listas de productos
#define RESALTADOR_T "\x1b[33m"//color menus
#define ROJO_T "\x1b[31m"//color menus
#define VERDE_T "\x1b[32m"//color menus
#define NEUTRA_T "\x1b[37m"//color menus

typedef struct{
    int categoria;//1 bolsas 2 ladrillos 3 aridos 4 hierros 5 vigas 6 fletes 7 otros
    int idProducto;
    char nombre[dimStr];
    char marca[dimStr];
    char proveedor[dimStr];
    char descripcion[dimStr];
    float precioCosto;
    float porcentajeGanancia;
    float precioVenta;
}stProducto;

typedef struct{
    int idProducto;
    char nombre[dimStr];
    char marca[dimStr];
    char proveedor[dimStr];
    char descripcion[dimStr];
    float precioCosto;
    float porcentajeGanancia;
    float precioVenta;
}Producto;

typedef struct{
    Producto dato;
    struct nodoProducto *siguiente;
}nodoProducto;

typedef struct{
    int categoria;
    nodoProducto *listaProductos;
}celdaProductos;

stProducto cargarProducto();
void cargarCategoriaProducto(int *categoria);
int generarIdProducto(int categoria);
void cargarNombreProducto(char nombre[]);
void cargarMarcaProducto(char marca[]);
void cargarProveedorProducto(char proveedor[]);
void cargarDescripcionProducto(char descripcion[]);
void cargarPrecioCostoProducto(float *precioCosto);
void cargarPorcentajeGananciaProducto(float *porcentajeGanancia);
void calcularPrecioVentaProducto(float *precioVenta, float precioCosto, float porcentajeGanancia);
void menuBuscarProducto(char *opcion);
int buscarProducto(stProducto *aux);
int buscarProductoId(int id);
int buscarProductoNombre(char nombre[]);
void mostrarProducto(stProducto aux);
void menuModificarProducto(stProducto *aux, char *opcion);
void modificarProducto(int reg);
void aumentarCostoCategoria(int categoria, float aumento);
void menuMostrarProductos(char *opcion);
int pasarArchivoProductosADL(celdaProductos arreglo[], int validos);
int altaADLProductos(celdaProductos arreglo[], int validos, stProducto aux);
nodoProducto* crearNodoProducto(Producto aux);
Producto cargarProductoADL(stProducto aux);
int buscarPosADLProductos(celdaProductos arreglo[], int categoria, int validos);
int agregarCategoriaADL(celdaProductos arreglo[], int categoria, int validos);
nodoProducto* inicListaProductos();
nodoProducto* agregarProductosEnOrdenId(nodoProducto *listaProductos, nodoProducto *nuevo);
nodoProducto* agregarAlPrincipioListaProductos(nodoProducto *listaProductos, nodoProducto *nuevo);
void encabezadoListadoProducto(int y);
void mostrarADLProductos(celdaProductos arreglo[], int validos, int y);
int mostrarListaProductos(int categoria, nodoProducto *listaProductos, int y);
void mostrarProductoLista(nodoProducto *listaProductos, int y);
