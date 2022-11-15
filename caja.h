#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#include "proveedores.h"

#define archivoCaja "caja.bin"
#define dimStr 30//dimensión strings
#define dimADLCaja 3//dimensión arreglo de listas de caja
#define RESALTADOR_T "\x1b[33m"//color menus
#define ROJO_T "\x1b[31m"//color menus
#define VERDE_T "\x1b[32m"//color menus
#define NEUTRA_T "\x1b[37m"//color menus

typedef struct{
    stFecha fecha;
    float inicioEfectivo;
    float inicioBanco;
    float saldoEfectivo;
    float saldoBanco;
}stCaja;

typedef struct{
    stFecha fecha;
    int id;
    float monto;
}stCompraVenta;//ingreso o egreso

typedef struct{
    stCompraVenta dato;
    struct nodoCaja * siguiente;
}nodoCaja;

typedef struct{
    int medioDePago;//1 efectivo 2 lista/debito/transferencia  3 credito
    nodoCaja * listaIngresos;
    nodoCaja * listaEgresos;
}celdaCaja;

typedef struct{
    float ventasEfvo;
    float ventasLista;
    float ventasCredito;
    float ventasTot;
    float gastosEfvo;
    float gastosLista;
    float gastosTot;
}stAcumulador;

void iniciarCaja(char archivo[], stCaja *auxCaja);
int buscaCaja(char archivo[], stFecha fecha);
float cargarEfectivo();
float cargarBanco();
int validarFecha(stFecha fecha, stFecha fechaBuscada);
void cerrarCaja(char archivo[], celdaCaja arregloCaja [], stCaja * auxCaja);
void calcularCierre(stCaja aux, stAcumulador acumulador, float *difEfectivo, float *difBanco);
void muestraCierre(float difEfectivo, float difBanco);
void muestraInicioCierreYDiferencias (char archivo[], celdaCaja arregloCaja[], stCaja * auxCaja, int validosCaja);
void muestraInicioYSaldo(char archivo[], int reg);
void mostrarRegistro(stCaja aux);
void guardarNuevoCaja(char archivo[], stCaja aux);
void modificarInicio(char archivo[], stCaja *auxCaja);
void modificarCierre(char archivo[], stCaja *auxCaja);
void guardarModificacionCaja(char archivo[], int reg, stCaja aux);
stCaja retornaCajaBuscada(char archivo[], int reg);
int actualizarCaja (char archivo[], celdaCaja arregloCaja[], stFecha fecha, stCaja * auxCaja, int validos);
int pasarArchivoPedidosToADL(char archivo[], stFecha fecha, celdaCaja arrayCaja[], int validos, int dim);
int pasarArchivoProveedoresToADL(char archivo[], stFecha fecha, celdaCaja arrayCaja[], int validos, int dim);
int altaCajaPedido(celdaCaja arrayCaja[], int validos, stPedido aux);
int altaCajaProveedor(celdaCaja arrayCaja[], int validos, RegTranProv aux);
stCompraVenta cargarCompraVentaPedido(stPedido aux);
stCompraVenta cargarCompraVentaPagoProveedor(RegTranProv aux);
int buscaPosMedioDePago(celdaCaja arrayCaja[], int val, int medioDePago);
int agregarMedioDePago(celdaCaja arrayCaja[], int medioDePago, int val);
void verCaja (celdaCaja arregloCaja [], stCaja * auxCaja, int validos);
void mostrarCaja(celdaCaja arrayCaja[], int validos, int y);
void encabezadoCaja(int y);
int mostrarListaIngresos(nodoCaja *lista, int medioDePago, int y);
int mostrarListaEgresos(nodoCaja *lista, int medioDePago, int y);
void mostrarIngreso(nodoCaja *lista, int medioDePago, int y);
void mostrarEgreso(nodoCaja *lista, int medioDePago, int y);
void buscarProveedorIdRetornaNombre(int id, char nombre[]);
void mostrarMovimientoReal(celdaCaja arrayCaja[], int validos, int y);
void acumuladorDia (char archivo[], celdaCaja arregloCaja [], stCaja * auxCaja, int validos);
stAcumulador acumuladores(celdaCaja arrayCaja[], int val);
void mostrarAcumuladores(stAcumulador acumulador);
float calculaVentasPorMedioDePago(celdaCaja arrayCaja[], int val, int medioDePago);
float calculaGastosPorMedioDePago(celdaCaja arrayCaja[], int val, int medioDePago);
float sumaLista(nodoCaja *lista);
void acumuladorMes (celdaCaja arregloCaja [], int validos);
int pasarArchivoPedidosToADLMensual(char archivo[], int mes, int anio, celdaCaja arrayCaja[], int validos, int dim);
int pasarArchivoProveedoresToADLMensual(char archivo[], int mes, int anio, celdaCaja arrayCaja[], int validos, int dim);
void mostrarMesYAnio(int mes, int anio);
nodoCaja* inicListaCaja ();
nodoCaja* crearNodoCaja (stCompraVenta dato);
nodoCaja* agregaAlFinal (nodoCaja * lista, nodoCaja * nuevo);
nodoCaja* buscaUltimo (nodoCaja * lista);
nodoCaja* borrarListaCaja (nodoCaja *lista);
int limpiarArrayCaja(celdaCaja arrayCaja[], int val);
stFecha cargarFechaManual();
