#include "comunes.h"

void menuPrincipal(char *opcion){

    printf("\tMENU PRINCIPAL\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tClientes\n");
    printf(" 2\tPedidos\n");
    printf(" 3\tProductos\n");
    printf(" 4\tProveedores\n");
    printf(" 5\tCaja\n");
    printf(" 0\tSalir\n");
    printf(NEUTRA_T "Ingrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void menuClientes(char *opcion){

    printf("\tCLIENTES\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNuevo\n");
    printf(" 2\t" VERDE_T "Alta " RESALTADOR_T "/" ROJO_T " Baja\n");
    printf(RESALTADOR_T " 3\tConsulta\n");
    printf(" 4\tModificaci%cn\n", 162);
    printf(" 5\tListados\n");
    printf(" ESC\tMen%c principal\n", 163);
    printf(NEUTRA_T "Ingrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void menuPedidos(char *opcion){

    printf("\tPEDIDOS\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNuevo\n");
    printf(" 2\t" VERDE_T "Alta " RESALTADOR_T "/" ROJO_T " Baja\n");
    printf(RESALTADOR_T " 3\tConsulta\n");
    printf(" 4\tModificaci%cn\n", 162);
    printf(" 5\tListados\n");
    printf(" ESC\tMen%c principal\n", 163);
    printf(NEUTRA_T "Ingrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void menuProductos(char *opcion){

    printf("\tPRODUCTOS\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNuevo\n");
    printf(" 2\tConsulta\n");
    printf(" 3\tModificaci%cn\n", 162);
    printf(" 4\tAumento\n");
    printf(" 5\tListados\n");
    printf(" ESC\tMen%c principal\n", 163);
    printf(NEUTRA_T "Ingrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void menuProveedores(char *opcion){

    printf("\tPROVEEDORES\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNuevo\n");
    printf(" 2\t" VERDE_T "Alta " RESALTADOR_T "/" ROJO_T " Baja\n");
    printf(RESALTADOR_T " 3\tConsulta\n");
    printf(" 4\tModificaci%cn\n", 162);
    printf(" 5\tListados\n");
    printf(" 6\tTransacciones\n");
    printf(" ESC\tMen%c principal\n", 163);
    printf(NEUTRA_T "Ingrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void menuCaja(char *opcion){

    printf("\tCAJA\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tIniciar\n");
    printf(" 2\tModificar inicio\n");
    printf(" 3\tVer inicio y cierre\n");
    printf(" 4\tVer caja\n");
    printf(" 5\tAcumuladores del d%ca\n", 161);
    printf(" 6\tAcumuladores del mes\n");
    printf(" 7\tCerrar\n");
    printf(" 8\tModificar cierre\n");
    printf(" ESC\tMen%c principal\n", 163);
    printf(NEUTRA_T "Ingrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int contarRegistrosArchivo(char nombreArchivo[], int tamanio){

    int reg = 0;
    FILE *buf = fopen(nombreArchivo, "rb");

    if(buf){
        fseek(buf, 0, 2);
        reg = ftell(buf) / tamanio;//calcula la cantidad de registros del archivo
        fclose(buf);
    }

    return reg;
}

void opcionGuardar(char *opcion){

    printf("Guardar? s/n ");
    fflush(stdin);
    (*opcion) = getche();
}

void guardarNuevo(char archivo[], int tamanio, void *aux){

    FILE *buf = fopen(archivo, "ab");

    if(buf){
        fwrite(aux, tamanio, 1, buf);
        fclose(buf);
    }
}

void guardarModificacion(char archivo[], int tamanio, int reg, void *aux){

    FILE *buf = fopen(archivo, "r+b");

    if(buf){
        fseek(buf, tamanio * (reg - 1), 0);
        fwrite(aux, tamanio, 1, buf);
        fclose(buf);
    }
}

void gotoxy(int x, int y){

    HANDLE manipulador;
    COORD coordenadas;
    manipulador = GetStdHandle(STD_OUTPUT_HANDLE);
    coordenadas.X = x;
    coordenadas.Y = y;
    SetConsoleCursorPosition(manipulador, coordenadas);
}
