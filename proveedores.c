#include "proveedores.h"

void cargarNombreProveedor(char nombre[]){

    do{
        printf("Nombre: ");
        fflush(stdin);
        fgets(nombre, dimStr, stdin);
        strtok(nombre, "\n");
        if(nombre[0] == '\n'){
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(nombre[0] == '\n');

    for(int i = 0; nombre[i]; i++)
           nombre[i] = toupper(nombre[i]);
}

int cargarProveedor(stProveedor *aux){
    int reg=-1;
    cargarNombreProveedor(aux->nombre);
    reg=buscarProveedorNombre(aux->nombre);
    if(reg == -1){
    aux->idProveedor = contarRegistrosArchivo(archivoProveedores, sizeof(stProveedor)) + 1;//suma 1 a la cantidad de registros del archivo
    aux->ctaCorriente=0;
    aux->estado=1;
    }
    else
        printf("\nEl proveedor ya se encuentra en el sistema.");

    return reg;
}

int bajaProveedor(int reg){

    stProveedor aux;
    int flag;
    FILE * buf = fopen(archivoProveedores, "r+b");

    if(buf){
        fseek(buf, sizeof(stProveedor) * (reg - 1), 0);
        fread(&aux, sizeof(stProveedor), 1, buf);
        if(aux.estado == 1){
            aux.estado = 0;
            flag = 0;
        }
        else{
            aux.estado = 1;
            flag = 1;
        }
        fseek(buf, sizeof(stProveedor) * (reg - 1), 0);
        fwrite(&aux, sizeof(stProveedor), 1, buf);
        fclose(buf);
    }

    return flag;
}

int buscarProveedor(stProveedor *aux){

    char opcion;
    int id;
    long int dni;
    char nombre[dimStr];
    int reg = -1;

    do{
        system("cls");
        menuBuscarProveedor(&opcion);
        switch(opcion){

            case 49://por id
                printf("ID: ");
                scanf("%i", &id);
                reg = buscarProveedorId(id);
                break;

            case 50://por nombre
                printf("Nombre: ");
                fflush(stdin);
                fgets(nombre, dimStr, stdin);
                strtok(nombre, "\n");
                for(int i = 0; nombre[i]; i++)
                    nombre[i] = toupper(nombre[i]);
                reg = buscarProveedorNombre(nombre);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n", 162, 160);
                printf (NEUTRA_T "\n");
                system("pause");
        }
    }while(opcion != 49 && opcion != 50);

    if(reg != -1){//se encontró el proveedor buscado y se guarda en aux para retornarlo y mostrarlo en el main
        FILE * buf = fopen(archivoProveedores, "rb");
        if(buf){
            fseek(buf, sizeof(stProveedor) * (reg - 1), 0);
            fread(aux, sizeof(stProveedor), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

int buscarProveedorId(int id){

    int reg = -1;
    stProveedor aux;
    FILE * buf = fopen(archivoProveedores, "rb");

    if(buf){
        while(fread(&aux, sizeof(stProveedor), 1, buf) > 0 && reg == -1){
            if(aux.idProveedor == id){
                reg = ftell(buf) / sizeof(stProveedor);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarProveedorNombre(char proveedor[]){

    int reg = -1;
    char control;
    stProveedor aux;
    FILE * buf = fopen(archivoProveedores, "rb");

    if(buf){
        while(fread(&aux, sizeof(stProveedor), 1, buf) > 0 && reg == -1){
            if(strstr(aux.nombre, proveedor) != NULL){
                printf("\"" RESALTADOR_T "%s ID: %d" NEUTRA_T "\"? s/n ", aux.nombre, aux.idProveedor);//verificación si hay más proveedores con el mismo apellido
                fflush(stdin);
                control = getche();
                printf("\n");
                if(control == 's' || control == 'S'){
                    reg = ftell(buf) / sizeof(stProveedor);
                }
            }
        }
        fclose(buf);
    }

    return reg;
}

void menuBuscarProveedor(char *opcion){

    printf("Buscar proveedor por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tNombre");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getch();
    printf("\n");
}

void mostrarProveedor(stProveedor aux){

    gotoxy(1,1); printf(RESALTADOR_T "ID:" NEUTRA_T ".........................");
    gotoxy(30,1); printf(RESALTADOR_T "%i", aux.idProveedor);

    gotoxy(1,2); printf("NOMBRE:" NEUTRA_T "....................." RESALTADOR_T);
    gotoxy(30,2); printf ("%s", aux.nombre);

    gotoxy(1,3); printf("CTA CORRIENTE:" NEUTRA_T ".............." RESALTADOR_T);
    gotoxy(30,3); printf ("$%.2f", aux.ctaCorriente);

    gotoxy(1,4); printf("ESTADO:" NEUTRA_T "....................." RESALTADOR_T);
    if(aux.estado == 1){
        gotoxy(30,4); printf(VERDE_T "ALTA\n"NEUTRA_T);//alta si el estado es 1
    }
    else{
        gotoxy(30,4); printf(ROJO_T "BAJA\n"NEUTRA_T);//baja si el estado es 0
    }

    printf("\n");
}

void menuMostrarProveedores(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tTodos");
    printf(VERDE_T "\n 2\tAlta");
    printf(ROJO_T "\n 3\tBaja");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void mostrarProveedorListado(stProveedor aux, int y){

    gotoxy(2,y); printf ("|  %i", aux.idProveedor);
    gotoxy(10,y); printf ("|  %s", aux.nombre);
    gotoxy(27,y); printf ("|  $ %.2f", aux.ctaCorriente);
    if(aux.estado == 1){
        gotoxy(43,y); printf ("|" VERDE_T " ALTA" NEUTRA_T);
    }
    else{
        gotoxy(43,y); printf ("|" ROJO_T " BAJA" NEUTRA_T);
    }
    gotoxy (53, y); printf ("|");

}

void encabezadoListadoProveedor(int y){

    gotoxy(2,y); printf(RESALTADOR_T "| ID");
    gotoxy(10,y); printf("| NOMBRE");
    gotoxy(27,y); printf("|  CTA CTE ");
    gotoxy(43,y); printf ("| ESTADO");
    gotoxy (53, y); printf ("|");

    printf ("\n  ----------------------------------------------------\n" NEUTRA_T);
}

void modificarProveedorNombre(int reg){

    stProveedor aux;
    char opcion;
    FILE *buf = fopen(archivoProveedores, "rb");

    if(buf)
    {
        fseek(buf, sizeof(stProveedor) * (reg - 1), 0);
        fread(&aux, sizeof(stProveedor), 1, buf);
        fclose(buf);

        mostrarProveedor(aux);

        printf("\nModificar ");
        cargarNombreProveedor(aux.nombre);

        opcionGuardar(&opcion);
        if(opcion == 's' || opcion == 'S')
        {
            guardarModificacion(archivoProveedores, sizeof(stProveedor), reg, &aux);
            printf(VERDE_T "\nCambios guardados\n" NEUTRA_T);
            opcion = '0';
        }
        else
        {
            printf(ROJO_T "\nCambios descartados\n" NEUTRA_T);
            opcion = '0';
        }
    }
}

void menuOrdenarProveedores(char *opcion){

    printf("Ordenar por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tNombre");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

stTransaccion CargarTranProveedor(int idProveedor, int tipo){

    stTransaccion aux;
    aux.fecha=cargarFecha();
    aux.id=(idProveedor* 100000)+ contarRegistrosArchivo(archivoTranProveedores, sizeof(RegTranProv))+1;//suma 1 a la cantidad de registros del archivo
    printf("\nIngrese el monto: $");
    scanf("%f", &aux.monto);
    if(tipo == 1){
        printf("\nMedio de pago:" RESALTADOR_T "\n 1\t Efectivo\n 2\t Transferencia\n" NEUTRA_T);
        printf("Ingrese una opci%cn: ", 162);
        scanf("%i", &aux.medioPago);
    }
    else{
        aux.medioPago=0;
    }

    return aux;
}

RegTranProv RegistroTransaccionProveedor(stProveedor auxProv){

    stTransaccion auxTran;
    RegTranProv auxRegistro;
    auxRegistro.idProveedor=auxProv.idProveedor;

    printf("Tipo de transacci%cn:\n", 162);
    printf(RESALTADOR_T " 1\tPago\n 2\tCompra\n" NEUTRA_T);
    printf("Ingrese una opci%cn: ", 162);
    fflush(stdin);
    scanf("%d", &auxRegistro.tipo);

    auxTran= CargarTranProveedor(auxProv.idProveedor, auxRegistro.tipo);
    auxRegistro.dato=auxTran;

    return auxRegistro;
}

void modificarCtaCorriente(stProveedor* proveedor, int reg,  RegTranProv aux){

    if(aux.tipo == 2)
        proveedor->ctaCorriente += aux.dato.monto;
    else
        proveedor->ctaCorriente -= aux.dato.monto;

    guardarModificacion(archivoProveedores, sizeof(stProveedor), reg, proveedor);

}

void AnularTransaccion(RegTranProv auxReg){///pasar archivo a lista de transacciones y eliminar el nodo y luego reescribir el archivo

    int reg = -1;
    stProveedor auxProv;

    nodoTranProv* lista = inicListaDobleTranProv();
    lista = pasarArchivoListaTranProv(lista);

    lista = BorrarNodoTranProv(lista, auxReg);

    pasarListaTranProvToArchivo(lista);

    reg = buscarProveedorId(auxReg.idProveedor);

    FILE *buf = fopen(archivoProveedores, "rb");

    if(buf){
        fseek(buf, sizeof(stProveedor) * (reg - 1), 0);
        fread(&auxProv, sizeof(stProveedor), 1, buf);
        fclose(buf);
    }

    if(auxReg.tipo == 1){
        auxReg.tipo=2;
    }
    else{
        auxReg.tipo=1;
    }

    modificarCtaCorriente(&auxProv, reg, auxReg);
}

nodoTranProv* BorrarNodoTranProv(nodoTranProv *lista, RegTranProv dato){

    if(lista != NULL && lista->dato.dato.id == dato.dato.id)
    {
        nodoTranProv *aux=lista;
        lista=lista->siguiente;
        lista->anterior=NULL;
        free(aux);
    }
    else{
        nodoTranProv *seg=lista;
        while(seg->siguiente != NULL && seg->dato.dato.id != dato.dato.id){
            seg=seg->siguiente;
        }
        if(seg->dato.dato.id == dato.dato.id){
            nodoTranProv *aux=seg;
            nodoTranProv *ante=seg->anterior;
            ante->siguiente=seg->siguiente;
            if(seg->siguiente != NULL){
                seg=seg->siguiente;
                seg->anterior=ante;
            }
            free(aux);
        }
    }

    return lista;
}

void pasarListaTranProvToArchivo(nodoTranProv* lista){//el archivo se reescribe con los datos de la lista

    FILE* buf=fopen(archivoTranProveedores, "wb");
    if(buf){
        while(lista!=NULL){
            fwrite(&lista->dato, sizeof(RegTranProv), 1, buf);
            lista=lista->siguiente;
        }
        fclose(buf);
    }
}

int buscarTransaccionPorId(RegTranProv *aux){

    char nombre[dimStr];
    int reg = -1;
    int id = 0;

    printf("Ingrese n%cmero de factura: ", 163);
    scanf("%i", &id);
    reg = BuscarTransaccionId(id);


    if(reg != -1){ //se encontró la transacción buscada y se guarda en aux para retornarla y mostrarla en el main
        FILE * buf = fopen(archivoTranProveedores, "rb");
        if(buf){
            fseek(buf, sizeof(RegTranProv) * (reg - 1), 0);
            fread(aux, sizeof(RegTranProv), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

int BuscarTransaccionId(int idFactura){

    int reg= -1;
    RegTranProv aux;
    FILE * buf = fopen(archivoTranProveedores, "rb");

    if(buf){
        while(fread(&aux, sizeof(RegTranProv), 1, buf) > 0 && reg == -1){
            if(aux.dato.id == idFactura){
                reg = ftell(buf) / sizeof(RegTranProv);
            }
        }
        fclose(buf);
    }

    return reg;
}

int BuscarTransaccionFecha(RegTranProv* auxTran){

    stFecha fecha;

    printf("Fecha(dd/mm/aaaa):");
    printf("\nD%ca: ", 161);
    scanf("%d", &fecha.dia);
    printf("Mes: ");
    scanf("%d", &fecha.mes);
    printf("Anio: ");
    scanf("%d", &fecha.anio);
    int reg= -1;

    FILE * buf = fopen(archivoTranProveedores, "rb");

    if(buf)
    {
        while(fread(auxTran, sizeof(RegTranProv), 1, buf) > 0 && reg == -1)
        {
            if(auxTran->dato.fecha.anio == fecha.anio && auxTran->dato.fecha.mes == fecha.mes && auxTran->dato.fecha.dia == fecha.dia)
            {
                reg = ftell(buf) / sizeof(RegTranProv);
            }
        }
        fclose(buf);
    }
    return reg;
}

int BuscarTransaccionProveedorId(int idProveedor){

    int reg = -1;
    RegTranProv aux;
    FILE * buf = fopen(archivoTranProveedores, "rb");

    if(buf){
        while(fread(&aux, sizeof(RegTranProv), 1, buf) > 0 && reg == -1){
            if(aux.idProveedor == idProveedor){
                reg = ftell(buf) / sizeof(RegTranProv);
            }
        }
        fclose(buf);
    }
    return reg;
}

int BuscarTransaccionProveedorNombre(char nombre[]){

    int reg = -1;
    reg=buscarProveedorNombre(nombre);
    stProveedor aux;

    if(reg != -1){
        FILE * buf = fopen(archivoProveedores, "rb");
        if(buf){
            fseek(buf, sizeof(stProveedor) * (reg - 1), 0);
            fread(&aux, sizeof(stProveedor), 1, buf);
            fclose(buf);
        }
    }
    reg= BuscarTransaccionProveedorId(aux.idProveedor);

    return reg;
}

void MostrarTransaccion(stTransaccion aux){

    gotoxy(2,1); printf("ID: %i", aux.id);
    gotoxy(40,1); printf("Fecha: %i/%i/%i", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
    gotoxy(2,2); printf("Monto: $ %.2f", aux.monto);
}

void encabezadoListadoTranProv(int y){

    gotoxy(2,y); printf(RESALTADOR_T "|  ID");
    gotoxy(8,y); printf("|  FECHA");
    gotoxy(20,y); printf("|  NRO TRANSACCION");
    gotoxy(40,y); printf ("|  MONTO");
    gotoxy(55,y); printf ("|  TIPO");
    gotoxy(65,y); printf ("|  MEDIO DE PAGO");
    gotoxy (82, y); printf ("|");

    printf ("\n  ---------------------------------------------------------------------------------\n" NEUTRA_T);
}

void MostrarRegistroTranProv(RegTranProv aux){

    printf("  ------------------------------------------\n" NEUTRA_T);
    gotoxy(2,1); printf("| ID: %i", aux.dato.id);
    gotoxy(25,1); printf(RESALTADOR_T "Fecha: %i/%i/%i", aux.dato.fecha.dia, aux.dato.fecha.mes, aux.dato.fecha.anio);
    gotoxy(43, 1); printf (NEUTRA_T "|");
    gotoxy(2,2); printf("| ID Proveedor: %i", aux.idProveedor);
    gotoxy(43, 2); printf ("|");
    gotoxy(2, 3); printf ("|");
    gotoxy(43, 3); printf ("|");
    gotoxy(2, 4); printf ("|");
    gotoxy(43, 4); printf ("|");
    gotoxy(25, 5); printf("Monto: $ %.2f", aux.dato.monto);
    gotoxy(43, 5); printf ("|");
    if(aux.tipo == 1){
        gotoxy(2,5); printf("| Tipo: " VERDE_T "PAGO" NEUTRA_T);
        gotoxy (43, 5); printf ("|");
    }
    else{
        gotoxy(2,5); printf ("| Tipo: " ROJO_T "COMPRA" NEUTRA_T);
        gotoxy (43, 5); printf ("|");
    }
    if(aux.tipo != 2){
        if(aux.dato.medioPago==1){
            gotoxy(2,6); printf("|" VERDE_T "  EFECTIVO" NEUTRA_T);
            gotoxy (43, 6); printf ("|");
        }
        else{
            gotoxy(2,6); printf ("|" NEUTRA_T "  TRANSFERENCIA" NEUTRA_T);
            gotoxy (43, 6); printf ("|");
        }
    }

    printf("\n");
}

void MostrarTrasaccionListado(RegTranProv aux, int y){

    gotoxy(2,y); printf ("|  %i", aux.idProveedor);
    gotoxy(8,y); printf("|%i/%i/%i", aux.dato.fecha.dia, aux.dato.fecha.mes, aux.dato.fecha.anio);
    gotoxy(20,y); printf ("|     %i", aux.dato.id);
    gotoxy(40,y); printf ("|  $ %.2f", aux.dato.monto);

    if(aux.tipo == 1){
        gotoxy(55,y); printf("|" VERDE_T " PAGO" NEUTRA_T);
    }
    else{
        gotoxy(55,y); printf ("|" ROJO_T " COMPRA" NEUTRA_T);
    }

    if(aux.dato.medioPago != 0){
        if(aux.dato.medioPago == 1){
            gotoxy(65,y); printf("|" VERDE_T " EFECTIVO" NEUTRA_T);
        }
        else{
            gotoxy(65,y); printf ("|" RESALTADOR_T " TRANSFERENCIA" NEUTRA_T);
        }
    }
    else{
        gotoxy(65,y); printf ("|" ROJO_T "----------------" NEUTRA_T);
    }
    gotoxy (82, y); printf ("|");
    printf("\n");
}

void menuMostrarTrasaccion(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tTodas");
    printf(VERDE_T "\n 2\tProveedor");
    printf(ROJO_T "\n 3\tFecha");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

nodoDobleProveedor* inicListaDobleProveedor(){

    return NULL;
}

nodoDobleProveedor* crearNodoDobleProveedor(stProveedor dato){

    nodoDobleProveedor *nuevo = malloc(sizeof(nodoDobleProveedor));

    nuevo->dato=dato;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoDobleProveedor* agregarAlPrincipioListaDobleProveedor(nodoDobleProveedor *lista, nodoDobleProveedor *nuevo){

    if(lista){
        nuevo->siguiente = lista;
        lista->anterior = nuevo;
    }

    return nuevo;
}

nodoDobleProveedor* agregarAlFinalListaDobleProveedor(nodoDobleProveedor *lista, nodoDobleProveedor *nuevo){

    if(!lista)
        lista = nuevo;
    else{
        nodoDobleProveedor *ultimo = buscarUltimoNodoDobleProveedor(lista);
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
    }

    return lista;
}

nodoDobleProveedor* buscarUltimoNodoDobleProveedor(nodoDobleProveedor*lista){

    while(lista->siguiente)
        lista = lista->siguiente;

    return lista;
}

nodoDobleProveedor* agregarEnOrdenNombreListaDobleProveedor(nodoDobleProveedor *lista, nodoDobleProveedor *nuevo){

    if(!lista)
        lista = nuevo;
    else if(strcmpi(nuevo->dato.nombre, lista->dato.nombre) < 0)
        lista = agregarAlPrincipioListaDobleProveedor(lista, nuevo);
    else{
        nodoDobleProveedor *seg = lista;
        while(seg && strcmpi(nuevo->dato.nombre, seg->dato.nombre) > 0)
            seg = seg->siguiente;
        if(seg){
            nodoDobleProveedor *ante = seg->anterior;
            ante->siguiente = nuevo;
            nuevo->anterior = ante;
            nuevo->siguiente = seg;
            seg->anterior = nuevo;
        }
        else
            lista = agregarAlFinalListaDobleProveedor(lista, nuevo);
    }
    return lista;
}

nodoDobleProveedor* pasarArchivoListaDobleProveedorId(nodoDobleProveedor *lista){

    FILE *buf = fopen(archivoProveedores, "rb");
    stProveedor aux;

    if(buf){
        while(fread(&aux, sizeof(stProveedor), 1, buf) > 0){
            lista = agregarAlFinalListaDobleProveedor(lista, crearNodoDobleProveedor(aux));
        }
        fclose(buf);
    }

    return lista;
}

nodoDobleProveedor* pasarArchivoListaDobleProveedorNombre(nodoDobleProveedor *lista){

    FILE *buf = fopen(archivoProveedores, "rb");
    stProveedor aux;

    if(buf){
        while(fread(&aux, sizeof(stProveedor), 1, buf) > 0){
            lista = agregarEnOrdenNombreListaDobleProveedor(lista, crearNodoDobleProveedor(aux));
        }
        fclose(buf);
    }
    return lista;
}

void mostrarListaDobleProveedorTodos(nodoDobleProveedor *lista, int y){

    if(lista){
        mostrarProveedorListado(lista->dato, y++);
        mostrarListaDobleProveedorTodos(lista->siguiente, y);
    }
}

void mostrarListaDobleProveedorAlta(nodoDobleProveedor *lista, int y){

    if(lista){
        if(lista->dato.estado == 1)
            mostrarProveedorListado(lista->dato, y++);
        mostrarListaDobleProveedorAlta(lista->siguiente, y);
    }
}

void mostrarListaDobleProveedorBaja(nodoDobleProveedor *lista, int y){

    if(lista){
        if(lista->dato.estado == 0)
            mostrarProveedorListado(lista->dato, y++);
        mostrarListaDobleProveedorBaja(lista->siguiente, y);
    }
}

nodoDobleProveedor* borrarListaDobleProveedor(nodoDobleProveedor *lista){

    nodoDobleProveedor *proximo;
    while(lista){
        proximo = lista->siguiente;
        free(lista);
        lista = proximo;
    }

    return lista;
}

nodoTranProv* inicListaDobleTranProv(){

    return NULL;
}

nodoTranProv* crearNodoTranProv(RegTranProv dato){

    nodoTranProv *nuevo = malloc(sizeof(nodoTranProv));

    nuevo->dato=dato;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoTranProv* agregarPrincipioTranProv(nodoTranProv *lista, nodoTranProv *nuevo){

    if(lista){
        nuevo->siguiente = lista;
        lista->anterior = nuevo;
    }

    return nuevo;
}

nodoTranProv* agregarAlFinalTranProv(nodoTranProv *lista, nodoTranProv *nuevo){

    if(!lista)
        lista = nuevo;
    else{
        nodoTranProv *ultimo = buscarUltimoNodoTranProv(lista);
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
    }

    return lista;
}

nodoTranProv* buscarUltimoNodoTranProv(nodoTranProv *lista){

    while(lista->siguiente)
        lista = lista->siguiente;

    return lista;
}

nodoTranProv* pasarArchivoListaTranProv(nodoTranProv *lista){

    FILE *buf = fopen(archivoTranProveedores, "rb");
    RegTranProv aux;

    if(buf){
        while(fread(&aux, sizeof(RegTranProv), 1, buf) > 0){
            lista = agregarAlFinalTranProv(lista, crearNodoTranProv(aux));
        }
        fclose(buf);
    }

    return lista;
}

void mostrarListaDobleTranProvTodos(nodoTranProv *lista, int y){

    if(lista){
        MostrarTrasaccionListado(lista->dato, y++);
        mostrarListaDobleTranProvTodos(lista->siguiente, y);
    }
}

void mostrarListaDobleTranProvFecha(nodoTranProv*lista, stFecha fecha, int y){

    if(lista){
        if(lista->dato.dato.fecha.anio == fecha.anio && lista->dato.dato.fecha.mes == fecha.mes && lista->dato.dato.fecha.dia == fecha.dia)
            MostrarTrasaccionListado(lista->dato, y++);
        mostrarListaDobleTranProvFecha(lista->siguiente, fecha, y);
    }
}

void mostrarListaDobleTranIdProv(nodoTranProv*lista, int idProv, int y){

    if(lista){
        if(lista->dato.idProveedor == idProv)
            MostrarTrasaccionListado(lista->dato, y++);
        mostrarListaDobleTranIdProv(lista->siguiente, idProv, y);
    }
}

void mostrarListaDobleTranId(nodoTranProv*lista, int idTran, int y){

    if(lista){
        if(lista->dato.dato.id == idTran)
            MostrarTrasaccionListado(lista->dato, y++);
        mostrarListaDobleTranId(lista->siguiente, idTran, y);
    }
}

void menuTransaccionProveedores(char *opcion){

    printf("\tTRANSACCIONES \n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNueva \n");
    printf(" 2\t" ROJO_T "Anular\n");
    printf(RESALTADOR_T " 3\tConsulta\n");
    printf(" 4\tListados\n");
    printf(" ESC\tMen%c principal\n", 163);
    printf(NEUTRA_T "Ingrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

nodoTranProv * borrarListaTransacciones(nodoTranProv * lista){
    nodoTranProv * proximo = inicListaDobleTranProv();
    while(lista){
        proximo = lista->siguiente;
        free(lista);
        lista = proximo;
    }
    return lista;
}
