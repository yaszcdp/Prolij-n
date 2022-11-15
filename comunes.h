#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#define RESALTADOR_T "\x1b[33m"//color menus
#define ROJO_T "\x1b[31m"//color menus
#define VERDE_T "\x1b[32m"//color menus
#define NEUTRA_T "\x1b[37m"//color menus

void menuPrincipal(char *opcion);
void menuClientes(char *opcion);
void menuPedidos(char *opcion);
void menuProductos(char *opcion);
void menuProveedores(char *opcion);
void menuCaja(char *opcion);
int contarRegistrosArchivo(char nombreArchivo[], int tamanio);
void opcionGuardar(char *opcion);
void guardarNuevo(char archivo[], int tamanio, void *aux);
void guardarModificacion(char archivo[], int tamanio, int reg, void *aux);
void gotoxy(int x, int y);
