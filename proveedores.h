#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#include "pedidos.h"

#define archivoProveedores "proveedores.bin"//nombre archivo proveedores
#define archivoTranProveedores "transaccionesProveedores.bin"//nombre del archivo de transacciones con proveedores
#define dimStr 30//dimensión strings
#define RESALTADOR_T "\x1b[33m"//color menus
#define ROJO_T "\x1b[31m"//color menus
#define VERDE_T "\x1b[32m"//color menus
#define NEUTRA_T "\x1b[37m"//color menus

typedef struct{
    int idProveedor;
    char nombre[dimStr];
    float ctaCorriente;
    int estado;///1 alta 0 baja
}stProveedor;

typedef struct{
    stFecha fecha;
    int id;
    float monto;
    int medioPago;///0 compra, 1 efectivo, 2 transferencia
}stTransaccion;

typedef struct{
    stTransaccion dato;
    int idProveedor;
    int tipo;///1 Pago, 2 Compra
}RegTranProv;

typedef struct{
    stProveedor dato;
    struct nodoDobleProveedor* anterior;
    struct nodoDobleProveedor* siguiente;
}nodoDobleProveedor;

typedef struct{
    RegTranProv dato;
    struct nodoTranProv* anterior;
    struct nodoTranProv* siguiente;
}nodoTranProv;

void cargarNombreProveedor(char nombre[]);
int cargarProveedor(stProveedor *aux);
int bajaProveedor(int reg);
int buscarProveedor(stProveedor *aux);
int buscarProveedorId(int id);
int buscarProveedorNombre(char proveedor[]);
void menuBuscarProveedor(char *opcion);
void mostrarProveedor(stProveedor aux);
void menuMostrarProveedores(char *opcion);
void mostrarProveedorListado(stProveedor aux, int y);
void encabezadoListadoProveedor(int y);
void modificarProveedorNombre(int reg);
void menuOrdenarProveedores(char *opcion);
stTransaccion CargarTranProveedor(int idProveedor, int tipo);
RegTranProv RegistroTransaccionProveedor(stProveedor auxProv);
void modificarCtaCorriente(stProveedor* proveedor, int reg,  RegTranProv aux);
void AnularTransaccion(RegTranProv auxReg);
nodoTranProv* BorrarNodoTranProv(nodoTranProv *lista, RegTranProv dato);
void pasarListaTranProvToArchivo(nodoTranProv* lista);
int buscarTransaccionPorId(RegTranProv *aux);
int BuscarTransaccionId(int idFactura);
int BuscarTransaccionFecha(RegTranProv* auxTran);
int BuscarTransaccionProveedorId(int idProveedor);
int BuscarTransaccionProveedorNombre(char nombre[]);
void MostrarTransaccion(stTransaccion aux);
void MostrarRegistroTranProv(RegTranProv aux);
void MostrarTrasaccionListado(RegTranProv aux, int y);
void menuMostrarTrasaccion(char *opcion);
nodoDobleProveedor* inicListaDobleProveedor();
nodoDobleProveedor* crearNodoDobleProveedor(stProveedor dato);
nodoDobleProveedor* agregarAlPrincipioListaDobleProveedor(nodoDobleProveedor *lista, nodoDobleProveedor *nuevo);
nodoDobleProveedor* agregarAlFinalListaDobleProveedor(nodoDobleProveedor *lista, nodoDobleProveedor *nuevo);
nodoDobleProveedor* buscarUltimoNodoDobleProveedor(nodoDobleProveedor*lista);
nodoDobleProveedor* agregarEnOrdenNombreListaDobleProveedor(nodoDobleProveedor *lista, nodoDobleProveedor *nuevo);
nodoDobleProveedor* pasarArchivoListaDobleProveedorId(nodoDobleProveedor *lista);
nodoDobleProveedor* pasarArchivoListaDobleProveedorNombre(nodoDobleProveedor *lista);
void mostrarListaDobleProveedorTodos(nodoDobleProveedor *lista, int y);
void mostrarListaDobleProveedorAlta(nodoDobleProveedor *lista, int y);
void mostrarListaDobleProveedorBaja(nodoDobleProveedor *lista, int y);
nodoDobleProveedor* borrarListaDobleProveedor(nodoDobleProveedor *lista);
nodoTranProv* inicListaDobleTranProv();
nodoTranProv* crearNodoTranProv(RegTranProv dato);
nodoTranProv* agregarPrincipioTranProv(nodoTranProv *lista, nodoTranProv *nuevo);
nodoTranProv* agregarAlFinalTranProv(nodoTranProv *lista, nodoTranProv *nuevo);
nodoTranProv* buscarUltimoNodoTranProv(nodoTranProv *lista);
nodoTranProv* pasarArchivoListaTranProv(nodoTranProv *lista);
void mostrarListaDobleTranProvTodos(nodoTranProv *lista, int y);
void mostrarListaDobleTranProvFecha(nodoTranProv*lista, stFecha fecha, int y);
void mostrarListaDobleTranIdProv(nodoTranProv*lista, int idProv, int y);
void mostrarListaDobleTranId(nodoTranProv*lista, int idTran, int y);
void encabezadoListadoTranProv(int y);
void menuTransaccionProveedores(char *opcion);
nodoTranProv * borrarListaTransacciones(nodoTranProv * lista);
