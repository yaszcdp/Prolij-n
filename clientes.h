#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#define archivoClientes "clientes.bin"//nombre archivo clientes
#define dimStr 30//dimensión strings
#define RESALTADOR_T "\x1b[33m"//color menus
#define ROJO_T "\x1b[31m"//color menus
#define VERDE_T "\x1b[32m"//color menus
#define NEUTRA_T "\x1b[37m"//color menus

typedef struct{
    char calle[dimStr];
    char altura[dimStr];
    char piso[dimStr];
    char departamento[dimStr];
    char localidad[dimStr];
}stDomicilio;

typedef struct{
    int idCliente;
    long int dni;
    char telefono[dimStr];
    char mail[dimStr];
    char apellido[dimStr];
    char nombre[dimStr];
    stDomicilio domicilio;
    int estado;//1 alta 0 baja
    int cantidadPedidos;
}stCliente;

typedef struct{
    stCliente dato;
    struct nodoDobleCliente *anterior;
    struct nodoDobleCliente *siguiente;
}nodoDobleCliente;

int cargarCliente(stCliente *aux);
long int cargarDniCliente(int *flag);
void cargarTelefonoCliente(char telefono[]);
void cargarMailCliente(char mail[]);
void cargarApellidoCliente(char apellido[]);
void cargarNombreCliente(char nombre[]);
stDomicilio cargarDomicilioCliente();
int bajaCliente(int reg);
void menuBuscarCliente(char *opcion);
int buscarCliente(stCliente *aux);
int buscarClienteId(int id);
int buscarClienteDni(long int dni);
int buscarClienteApellido(char apellido[]);
void mostrarCliente(stCliente aux);
void menuModificarCliente(stCliente *aux, char *opcion);
void modificarCliente(int reg);
void menuOrdenarClientes(char *opcion);
void menuMostrarClientes(char *opcion);
void encabezadoListadoCliente(int y);
void mostrarClienteListado(stCliente aux, int y);
nodoDobleCliente* inicListaDobleCliente();
nodoDobleCliente* crearNodoDobleCliente(stCliente dato);
nodoDobleCliente* agregarAlPrincipioListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo);
nodoDobleCliente* agregarAlFinalListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo);
nodoDobleCliente* buscarUltimoNodoDobleCliente(nodoDobleCliente *lista);
nodoDobleCliente* agregarEnOrdenApellidoListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo);
nodoDobleCliente* agregarEnOrdenPedidosListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo);
nodoDobleCliente* pasarArchivoListaDobleClienteId(nodoDobleCliente *lista);
nodoDobleCliente* pasarArchivoListaDobleClienteApellido(nodoDobleCliente *lista);
nodoDobleCliente* pasarArchivoListaDobleClientePedidos(nodoDobleCliente *lista);
void top10clientes(nodoDobleCliente *lista, int y, int i);
void mostrarListaDobleClienteTodos(nodoDobleCliente *lista, int y);
void mostrarListaDobleClienteAlta(nodoDobleCliente *lista, int y);
void mostrarListaDobleClienteBaja(nodoDobleCliente *lista, int y);
nodoDobleCliente* borrarListaDobleCliente(nodoDobleCliente *lista);
