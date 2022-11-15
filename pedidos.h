#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#include "clientes.h"
#include "productos.h"

#define archivoPedidos "pedidos.bin"//nombre archivo pedidos
#define dimStr 30//dimensión strings
#define RESALTADOR_T "\x1b[33m"//color menus
#define ROJO_T "\x1b[31m"//color menus
#define VERDE_T "\x1b[32m"//color menus
#define NEUTRA_T "\x1b[37m"//color menus

typedef struct{
    char nombre[100];
    float cantidad;
    float precioVenta;
}stProductoPedido;

typedef struct{
    int dia;
    int mes;
    int anio;
}stFecha;

typedef struct{
    int idPedido;
    int idCliente;//id del cliente que realiza el pedido
    int estadoEntrega;//1 entregado 0 pendiente
    int estadoPago;//1 pagado 0 pendiente
    int estadoPedido;//1 activo 0 cancelado
    stProductoPedido productosPedidos[100];
    int validosProductosPedidos;
    float monto;
    int medioDePago; //1 efectivo, 2 lista, 3 credito
    stFecha fecha;
    stFecha fechaPago;
}stPedido;

typedef struct{
    stPedido dato;
    struct nodoDoblePedido *anterior;
    struct nodoDoblePedido *siguiente;
}nodoDoblePedido;

int cargarPedido(stPedido *aux);
int validarClientePedido(int *reg);
stFecha cargarFecha();
int cargarProductosPedidos(stProductoPedido arreglo[], int validos, int dimension);
stProductoPedido cargarProductoPedido();
void calcularTotal (stPedido * pedido, float monto);
void pagarPedido(stPedido *pedido);
int ingresarMedioDePago();
float calcularPorcentaje(int medioDePago, float monto);
float calcularPorcentajePorCuotas(float monto);
float calcularMonto(stProductoPedido arreglo[], int validos);
void sumarPedidoCliente(int idCliente);
int contarPedidosCliente(int idCliente);
int bajaPedido(int reg);
void restarPedidoCliente(int idCliente);
void menuBuscarPedido(char *opcion);
int buscarPedido(stPedido *aux);
int buscarPedidoIdPedido(int idPedido);
int buscarPedidoIdCliente(int idCliente);
void mostrarPedido(stPedido aux);
void imprimeMedioDePago (int medioDePago, int y);
void mostrarProductosPedidos(stProductoPedido arreglo[], int validos, int *y);
void menuModificarPedido(stPedido *aux, char *opcion);
void modificarPedido(int reg);
int quitarProductosPedidos(stProductoPedido arreglo[], int validos);
int quitarUnProducto(stProductoPedido arreglo[], int pos, int validos);
void menuOrdenarPedidos(char *opcion);
void menuMostrarPedidos(char *opcion);
void encabezadoListadoPedido(int y);
void mostrarPedidoListado(stPedido aux, int y);
nodoDoblePedido* inicListaDoblePedido();
nodoDoblePedido* crearNodoDoblePedido(stPedido dato);
nodoDoblePedido* agregarAlPrincipioListaDoblePedido(nodoDoblePedido *lista, nodoDoblePedido *nuevo);
nodoDoblePedido* agregarAlFinalListaDoblePedido(nodoDoblePedido *lista, nodoDoblePedido *nuevo);
nodoDoblePedido* buscarUltimoNodoDoblePedido(nodoDoblePedido *lista);
nodoDoblePedido* agregarEnOrdenIdClienteListaDoblePedido(nodoDoblePedido *lista, nodoDoblePedido *nuevo);
nodoDoblePedido* pasarArchivoListaDoblePedidoIdPedido(nodoDoblePedido *lista);
nodoDoblePedido* pasarArchivoListaDoblePedidoIdCliente(nodoDoblePedido *lista);
void mostrarPedidosPorCliente(nodoDoblePedido *lista, int idCliente, int y);
void mostrarListaDoblePedidoActivos(nodoDoblePedido *lista, int y);
void mostrarListaDoblePedidoActivosPagados(nodoDoblePedido *lista, int y);
void mostrarListaDoblePedidoActivosPendientesPago(nodoDoblePedido *lista, int y);
void mostrarListaDoblePedidoActivosEntregados(nodoDoblePedido *lista, int y);
void mostrarListaDoblePedidoActivosPendientesEntrega(nodoDoblePedido *lista, int y);
void mostrarListaDoblePedidoCancelados(nodoDoblePedido *lista, int y);
nodoDoblePedido* borrarListaDoblePedido(nodoDoblePedido *lista);
