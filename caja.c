#include "caja.h"

void iniciarCaja(char archivo[], stCaja *auxCaja){

    char opcion;

    stFecha fecha = cargarFecha ();
    printf(RESALTADOR_T "Fecha: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
    printf(NEUTRA_T "\n");
    int reg = buscaCaja(archivo, fecha);

    if(reg == -1){//si no se encontró la fecha correspondiente, se crea la caja.
        auxCaja->fecha = fecha;
        auxCaja->inicioEfectivo = cargarEfectivo ();
        auxCaja->inicioBanco = cargarBanco ();
        opcionGuardar (&opcion);
        if (opcion == 's' || opcion == 'S'){
            guardarNuevoCaja(archivo, *auxCaja);//se guarda la nueva caja con su inicio.
            printf(VERDE_T "\nCambios guardados\n" NEUTRA_T);
        }
        else{
            printf(ROJO_T "\nCambios descartados\n" NEUTRA_T);
        }
    }
    else{//si se encontró la fecha quiere decir que su inicio existe así que no hacemos nada...
        printf(VERDE_T "\nLa caja ya est%c iniciada\n" NEUTRA_T, 160);
    }
}

int buscaCaja(char archivo[], stFecha fecha){

    int reg = -1, flag = 0;
    stCaja aux;
    FILE * buf = fopen (archivo, "rb");

    if (buf){
        while((fread (&aux, sizeof (stCaja), 1, buf) > 0) && reg == -1){
            if (validarFecha(aux.fecha, fecha) == 1){
                reg = ftell (buf) / sizeof (stCaja);
            }
        }
        fclose (buf);
    }

    return reg;
}

float cargarEfectivo(){

    float efectivo;

    printf("\nEfectivo: $", 161);
    scanf("%f", &efectivo);

    return efectivo;
}

float cargarBanco(){

    float banco;

    printf("Banco: $");
    scanf("%f", &banco);

    return banco;
}

int validarFecha(stFecha fecha, stFecha fechaBuscada){

    int flag = 0;

    if(fecha.dia == fechaBuscada.dia && fecha.mes == fechaBuscada.mes && fecha.anio == fechaBuscada.anio){
        flag = 1;
    }

    return flag;
}

void cerrarCaja(char archivo[], celdaCaja arregloCaja[], stCaja* auxCaja){

    char opcion;
    float difEfectivo = 0, difBanco = 0;
    stFecha fecha = cargarFecha();

    int validos = actualizarCaja(archivo, arregloCaja, fecha, auxCaja, 0);
    system("cls");
    stAcumulador acumulador = acumuladores(arregloCaja, validos);

    int reg = buscaCaja (archivo, fecha);
    if(reg == -1){//si no encontró la fecha correspondiente...
        printf(ROJO_T "\nLa caja no existe. Primero debe iniciarla.\n" NEUTRA_T);
    }
    else{//caso contrario guardamos el cierre.
        printf(RESALTADOR_T "Fecha: %d/%d/%d\n" NEUTRA_T, fecha.dia, fecha.mes, fecha.anio);
        (*auxCaja) = retornaCajaBuscada (archivo, reg);
        auxCaja->saldoEfectivo = cargarEfectivo ();
        auxCaja->saldoBanco = cargarBanco ();

        calcularCierre(*auxCaja, acumulador, &difEfectivo, &difBanco);
        muestraCierre(difEfectivo, difBanco);

        opcionGuardar(&opcion);
        if (opcion == 's' || opcion == 'S'){
            guardarModificacionCaja(archivoCaja, reg, *auxCaja);
            printf (VERDE_T "\n\nCambios guardados." NEUTRA_T);
        }
        else{
            printf (ROJO_T "\n\nCambios descartados." NEUTRA_T);
        }
    }
}

void calcularCierre(stCaja aux, stAcumulador acumulador, float *difEfectivo, float *difBanco){

    *difEfectivo = aux.saldoEfectivo - (aux.inicioEfectivo + acumulador.ventasEfvo - acumulador.gastosEfvo);
    *difBanco = aux.saldoBanco - (aux.inicioBanco + acumulador.ventasLista - acumulador.gastosEfvo);
}

void muestraCierre(float difEfectivo, float difBanco){

    printf (NEUTRA_T"\nDIFERENCIAS:");

    if (difEfectivo < 0){
        printf("\nEfectivo: $" ROJO_T " %.2f", difEfectivo);
    }
    else{
        printf("\nEfectivo: $" VERDE_T " %.2f", difEfectivo);
    }

    if(difBanco < 0){
        printf(NEUTRA_T "\nBanco: $" ROJO_T " %.2f", difBanco);
    }
    else{
        printf(NEUTRA_T "\nBanco: $" VERDE_T " %.2f", difBanco);
    }
    printf(NEUTRA_T "\n\n");
}

void muestraInicioCierreYDiferencias (char archivo[], celdaCaja arregloCaja[], stCaja * auxCaja, int validosCaja){ ///AGREGUE

    float difEfectivo = 0, difBanco = 0;

    printf("Ingrese fecha:\n");
    stFecha fecha = cargarFechaManual();

    validosCaja = actualizarCaja (archivo, arregloCaja, fecha, auxCaja, validosCaja);
    system ("cls");

    if(validosCaja != 0){
        stAcumulador acumulador = acumuladores(arregloCaja, validosCaja);
        int reg = buscaCaja(archivo, fecha);
        if (reg == -1){
            printf(ROJO_T "Caja no encontrada\n" NEUTRA_T);
        }
        else{
            (*auxCaja) = retornaCajaBuscada (archivo, reg);
            muestraInicioYSaldo(archivo, reg);
            calcularCierre(*auxCaja, acumulador, &difEfectivo, &difBanco);
            muestraCierre(difEfectivo, difBanco);
        }
    }
    else{
        printf(ROJO_T "Caja no encontrada\n" NEUTRA_T);
    }
}

void muestraInicioYSaldo(char archivo[], int reg){

    stCaja aux;
    FILE * buf = fopen (archivo, "rb");

    if (buf){
        fseek (buf, sizeof (stCaja) * (reg -1), 0);
        fread (&aux, sizeof (stCaja), 1, buf);
        mostrarRegistro (aux);
        fclose (buf);
    }
}

void mostrarRegistro(stCaja aux){

    printf(RESALTADOR_T "Fecha: %d/%d/%d.", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);

    printf(NEUTRA_T "\n\nINICIO:");
    printf("\t\nEfectivo: %.2f.", aux.inicioEfectivo);
    printf("\t\nBanco: %.2f.", aux.inicioBanco);

    printf("\n\nCIERRE");
    printf("\t\nEfectivo: %.2f.", aux.saldoEfectivo);
    printf("\t\nBanco: %.2f.", aux.saldoBanco);
    printf("\n");
}

void guardarNuevoCaja(char archivo[], stCaja aux){

    FILE * buf = fopen(archivo, "ab");

    if(buf){
        fwrite(&aux, sizeof(stCaja), 1, buf);
        fclose(buf);
    }
}

void modificarInicio(char archivo[], stCaja *auxCaja){

    char opcion;

    printf ("Ingrese la fecha:\n");
    stFecha fecha = cargarFechaManual();
    system("cls");
    printf(RESALTADOR_T "Fecha: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);

    int reg = buscaCaja(archivo, fecha);

    if(reg != -1){
        printf (NEUTRA_T "\n\nIngrese el nuevo inicio: ");
        auxCaja->fecha = fecha;
        auxCaja->inicioEfectivo = cargarEfectivo();
        auxCaja->inicioBanco = cargarBanco();

        opcionGuardar(&opcion);
        if (opcion == 's' || opcion == 'S'){
            guardarModificacionCaja (archivo, reg, *auxCaja);
            printf (VERDE_T "\n\nCambios guardados." NEUTRA_T);
        }
        else{
            printf (ROJO_T "\n\nCambios descartados." NEUTRA_T);
        }

    }
    else{
        printf (ROJO_T "\n\nNo se encontr%c la caja.", 162);
    }
    printf (NEUTRA_T "\n");
}

void modificarCierre(char archivo[], stCaja *auxCaja){

    char opcion;

    printf ("Ingrese la fecha: \n");
    stFecha fecha = cargarFechaManual();
    system("cls");
    printf(RESALTADOR_T "Fecha: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);

    int reg = buscaCaja (archivo, fecha);

    if(reg != -1){
        printf (NEUTRA_T "\n\nIngrese el nuevo cierre: ");
        auxCaja->fecha = fecha;
        auxCaja->saldoEfectivo = cargarEfectivo ();
        auxCaja->saldoBanco = cargarBanco ();

        opcionGuardar (&opcion);
        if (opcion == 's' || opcion == 'S'){
            guardarModificacionCaja (archivo, reg, *auxCaja);
            printf (VERDE_T "\nCambios guardados." NEUTRA_T);
        }
        else{
            printf (ROJO_T "\nCambios descartados." NEUTRA_T);
        }
    }
}

void guardarModificacionCaja(char archivo[], int reg, stCaja aux){

    FILE * buf = fopen (archivo, "r+b");

    if(buf){
        fseek (buf, sizeof (stCaja) * (reg-1), 0);
        fwrite (&aux, sizeof (stCaja), 1, buf);
        fclose (buf);
    }
}

stCaja retornaCajaBuscada(char archivo[], int reg){

    stCaja aux;
    FILE * buf = fopen (archivo, "rb");

    if(buf){
        fseek (buf, sizeof (stCaja) * (reg-1), 0);
        fread (&aux, sizeof (stCaja), 1, buf);
        fclose (buf);
    }

    return aux;
}

int actualizarCaja (char archivo[], celdaCaja arregloCaja[], stFecha fecha, stCaja * auxCaja, int validos){

    int reg = buscaCaja(archivo, fecha);

    if (reg == -1){
        printf(ROJO_T "Caja no encontrada\n" NEUTRA_T);
    }
    else{
        (*auxCaja) = retornaCajaBuscada(archivoCaja, reg);
        validos = limpiarArrayCaja(arregloCaja, validos);
        validos = pasarArchivoPedidosToADL(archivoPedidos, fecha, arregloCaja, validos, dimADLCaja);
        validos = pasarArchivoProveedoresToADL(archivoTranProveedores, fecha, arregloCaja, validos, dimADLCaja);
    }

    return validos;
}

int pasarArchivoPedidosToADL(char archivo[], stFecha fecha, celdaCaja arrayCaja[], int validos, int dim){

    stPedido aux;
    FILE * buf = fopen (archivo, "rb");

    if(buf){
        while(fread (&aux, sizeof (stPedido), 1, buf) > 0 && validos <= dim){
            if(validarFecha (fecha, aux.fechaPago) == 1 && aux.estadoPago == 1){//si la fecha coincide y si el estado es pagado.
                validos = altaCajaPedido (arrayCaja, validos, aux);
            }
        }
        fclose (buf);
    }

    return validos;
}

int pasarArchivoProveedoresToADL(char archivo[], stFecha fecha, celdaCaja arrayCaja[], int validos, int dim){

    RegTranProv aux;
    FILE * buf = fopen (archivo, "rb");

    if(buf){
        while(fread (&aux, sizeof (RegTranProv), 1, buf) > 0 && validos <= dim){
            if(validarFecha(fecha, aux.dato.fecha) == 1 && aux.tipo == 1){
                validos = altaCajaProveedor(arrayCaja, validos, aux);
            }
        }
        fclose (buf);
    }

    return validos;
}

int altaCajaPedido(celdaCaja arrayCaja[], int validos, stPedido aux){

    nodoCaja * nuevo = crearNodoCaja(cargarCompraVentaPedido(aux));
    int pos = buscaPosMedioDePago(arrayCaja, validos, aux.medioDePago);

    if (pos == -1){
        validos = agregarMedioDePago(arrayCaja, aux.medioDePago, validos);
        pos = validos -1;
    }

    arrayCaja[pos].listaIngresos = agregaAlFinal(arrayCaja[pos].listaIngresos, nuevo);

    return validos;
}

int altaCajaProveedor(celdaCaja arrayCaja[], int validos, RegTranProv aux){

    nodoCaja * nuevo = crearNodoCaja(cargarCompraVentaPagoProveedor (aux));
    int pos = buscaPosMedioDePago(arrayCaja, validos, aux.dato.medioPago);

    if (pos == -1){
        validos = agregarMedioDePago(arrayCaja, aux.dato.medioPago, validos);
        pos = validos -1;
    }

    arrayCaja[pos].listaEgresos = agregaAlFinal(arrayCaja[pos].listaEgresos, nuevo);

    return validos;
}

stCompraVenta cargarCompraVentaPedido(stPedido aux){

    stCompraVenta compraVenta;

    compraVenta.fecha = aux.fechaPago;
    compraVenta.id = aux.idPedido;
    compraVenta.monto = aux.monto;

    return compraVenta;
}

stCompraVenta cargarCompraVentaPagoProveedor(RegTranProv aux){

    stCompraVenta compraVenta;

    compraVenta.fecha = aux.dato.fecha;
    compraVenta.id = aux.idProveedor;
    compraVenta.monto = aux.dato.monto;

    return compraVenta;
}

int buscaPosMedioDePago(celdaCaja arrayCaja[], int val, int medioDePago){

    int flag = -1, i = 0;

    while (flag == -1 && i < val){
        if (arrayCaja[i].medioDePago == medioDePago){
            flag = i;
        }
        i++;
    }

    return flag;
}

int agregarMedioDePago(celdaCaja arrayCaja[], int medioDePago, int val){

    arrayCaja[val].listaIngresos = inicListaCaja();
    arrayCaja[val].listaEgresos = inicListaCaja();
    arrayCaja[val].medioDePago = medioDePago;
    val++;

    return val;
}

void verCaja (celdaCaja arregloCaja[], stCaja *auxCaja, int validos){

    printf("Ingrese fecha: \n");
    stFecha fecha = cargarFechaManual();

    validos = actualizarCaja (archivoCaja, arregloCaja, fecha, auxCaja, validos);
    system ("cls");

    if(validos != 0){
        printf(RESALTADOR_T "  Fecha: %d/%d/%d", fecha.dia, fecha.mes, fecha.anio);
        printf ("\n  ----------------------------------------------------------------------------\n");
        encabezadoCaja(2);
        mostrarCaja(arregloCaja, validos, 4);
    }
    else{
        printf (ROJO_T "\nLa caja no tiene datos.\n" NEUTRA_T);
    }
    printf("\n");

}

void mostrarCaja(celdaCaja arrayCaja[], int validos, int y){

    int i = 0;

    while(i < validos){
        y = mostrarListaIngresos(arrayCaja[i].listaIngresos, arrayCaja[i].medioDePago, y);
        y = mostrarListaEgresos(arrayCaja[i].listaEgresos, arrayCaja[i].medioDePago, y);
        i++;
    }

    printf (RESALTADOR_T "\n  ----------------------------------------------------------------------------\n" );
    y++;
    mostrarMovimientoReal(arrayCaja, validos, y);
}

void encabezadoCaja(int y){

    gotoxy(2, y); printf(RESALTADOR_T "| ID ");
    gotoxy(12, y); printf("| DESCRIPCION ");
    gotoxy(32, y); printf("| EFECTIVO ");
    gotoxy(47, y); printf("| LISTA ");
    gotoxy(62, y); printf("| CREDITO ");
    gotoxy(77, y); printf("|");
    printf("\n  ----------------------------------------------------------------------------\n" NEUTRA_T);
}

int mostrarListaIngresos(nodoCaja *lista, int medioDePago, int y){

    if(lista){
        mostrarIngreso(lista, medioDePago, y);
        y = mostrarListaIngresos (lista->siguiente, medioDePago, y+1);
    }

    return y;
}

int mostrarListaEgresos(nodoCaja *lista, int medioDePago, int y){

    if (lista){
        mostrarEgreso (lista, medioDePago, y);
        y = mostrarListaEgresos (lista->siguiente, medioDePago, y+1);
    }

    return y;
}

void mostrarIngreso(nodoCaja *lista, int medioDePago, int y){

    gotoxy(2, y); printf("| %d", lista->dato.id);
    gotoxy(12, y); printf("| REMITO");
    if(medioDePago == 1){
        gotoxy(32, y); printf("|" VERDE_T " $ %.2f", lista->dato.monto);
        gotoxy(47, y); printf(NEUTRA_T "| ");
        gotoxy(62, y); printf("| ");
    }else if (medioDePago == 2){
        gotoxy(32, y); printf("| ");
        gotoxy(47, y); printf("|" VERDE_T " $ %.2f ", lista->dato.monto);
        gotoxy(62, y); printf(NEUTRA_T "| ");
    }else if (medioDePago == 3){
        gotoxy(32, y); printf("| ");
        gotoxy(47, y); printf("| ");
        gotoxy(62, y); printf("|" VERDE_T " $ %.2f ", lista->dato.monto);
    }
    gotoxy(77, y); printf(NEUTRA_T "|");
}

void mostrarEgreso(nodoCaja *lista, int medioDePago, int y){

    char nombre[20];
    buscarProveedorIdRetornaNombre(lista->dato.id, nombre);

    for(int i = 0; nombre[i]; i++){
        nombre[i] = toupper(nombre[i]);
    }

    gotoxy(2, y); printf("| %d", lista->dato.id);
    gotoxy(12, y); printf("| %s", nombre);

    if(medioDePago == 1){
        gotoxy(32, y); printf("|" ROJO_T " - $ %.2f ", lista->dato.monto);
        gotoxy(47, y); printf(NEUTRA_T "| ");
        gotoxy(62, y); printf("| ");
    }else if (medioDePago == 2){
        gotoxy(32, y); printf("| ");
        gotoxy(47, y); printf("|" ROJO_T " - $ %.2f ", lista->dato.monto);
        gotoxy(62, y); printf(NEUTRA_T "| ");
    }

    gotoxy(77, y); printf("|");
}

void buscarProveedorIdRetornaNombre(int id, char nombre[]){

    stProveedor aux;
    FILE * buf = fopen(archivoProveedores, "rb");

    if(buf){
        while(fread(&aux, sizeof(stProveedor), 1, buf) > 0){
            if(aux.idProveedor == id){
                strcpy(nombre, aux.nombre);
            }
        }
        fclose(buf);
    }
}

void mostrarMovimientoReal(celdaCaja arrayCaja[], int validos, int y){

    stAcumulador acumulador = acumuladores(arrayCaja, validos);
    float gananciaEfvo = acumulador.ventasEfvo - acumulador.gastosEfvo;
    float gananciaLista = acumulador.ventasLista - acumulador.gastosLista;

    gotoxy(2, y); printf("|");
    gotoxy(12, y); printf("  MOVIMIENTO REAL");
    gotoxy(32, y); printf("| $ %.2f", gananciaEfvo); //efectivo
    gotoxy(47, y); printf("| $ %.2f", gananciaLista); //lista
    gotoxy(62, y); printf("| $ %.2f", acumulador.ventasCredito); //credito
    gotoxy(77, y); printf("|");
    y++;
    printf(RESALTADOR_T "\n  ----------------------------------------------------------------------------\n");
    y++;
    gotoxy(2, y); printf("| VENTAS TOTALES: $ %.2f ", acumulador.ventasTot);
    gotoxy(37, y); printf("|        GASTOS TOTALES: $ %.2f ", acumulador.gastosTot);
    gotoxy(77, y); printf("|");
    y++;
    printf(RESALTADOR_T "\n  ----------------------------------------------------------------------------\n" NEUTRA_T);
}

void acumuladorDia (char archivo[], celdaCaja arregloCaja [], stCaja * auxCaja, int validos){

    printf("Ingrese fecha: \n");
    stFecha fecha = cargarFechaManual();

    validos = actualizarCaja(archivo, arregloCaja, fecha, auxCaja, validos);
    system("cls");

    if(validos != 0){//verifica que el array esté cargado.
        printf(RESALTADOR_T "Fecha: %d/%d/%d.", fecha.dia, fecha.mes, fecha.anio);
        stAcumulador acumulador = acumuladores (arregloCaja, validos);
        mostrarAcumuladores(acumulador);
    }
    else{
        printf(ROJO_T "Actualizar caja\n" NEUTRA_T);
    }
    printf ("\n");
}

stAcumulador acumuladores(celdaCaja arrayCaja[], int val){

    stAcumulador acumulador;

    acumulador.ventasEfvo = calculaVentasPorMedioDePago(arrayCaja, val, 1);
    acumulador.ventasLista = calculaVentasPorMedioDePago(arrayCaja, val, 2);
    acumulador.ventasCredito = calculaVentasPorMedioDePago(arrayCaja, val, 3);
    acumulador.ventasTot = acumulador.ventasEfvo + acumulador.ventasLista + acumulador.ventasCredito;
    acumulador.gastosEfvo = calculaGastosPorMedioDePago(arrayCaja, val, 1);
    acumulador.gastosLista = calculaGastosPorMedioDePago(arrayCaja, val, 2);
    acumulador.gastosTot = acumulador.gastosEfvo + acumulador.gastosLista;

    return acumulador;
}

void mostrarAcumuladores(stAcumulador acumulador){

    printf(VERDE_T "\n\nVENTAS:" NEUTRA_T);
    printf("\nEfectivo: $ %.2f.", acumulador.ventasEfvo);
    printf("\nLista:   $ %.2f.", acumulador.ventasLista);
    printf("\nCr%cdito: $ %.2f.", 130, acumulador.ventasCredito);
    printf("\nTotales: $ %.2f.", acumulador.ventasTot);

    printf(ROJO_T "\n\nGASTOS:" NEUTRA_T);
    printf("\nEfectivo: $ %.2f.", acumulador.gastosEfvo);
    printf("\nLista:   $ %.2f.", acumulador.gastosLista);
    printf("\nTotales: $ %.2f.", acumulador.gastosTot);
    printf("\n");
}

float calculaVentasPorMedioDePago(celdaCaja arrayCaja[], int val, int medioDePago){

    int i = 0;
    float totalV = 0;

    while(i < val){
        if (arrayCaja[i].medioDePago == medioDePago){
            totalV = sumaLista(arrayCaja[i].listaIngresos);
        }
        i++;
    }

    return totalV;
}

float calculaGastosPorMedioDePago(celdaCaja arrayCaja[], int val, int medioDePago){

    int i = 0;
    float totalG = 0;

    while(i < val){
        if (arrayCaja[i].medioDePago == medioDePago){
            totalG = sumaLista(arrayCaja[i].listaEgresos);
        }
        i++;
    }

    return totalG;
}

float sumaLista(nodoCaja *lista){

    float suma = 0;

    while(lista != NULL){
        suma += lista->dato.monto;
        lista = lista->siguiente;
    }

    return suma;
}

void acumuladorMes(celdaCaja arregloCaja[], int validos){

    int mes, anio;

    do{
        printf("\nIngrese el mes: ");
        scanf("%d", &mes);
        if(mes < 1 || mes > 12){
            printf(ROJO_T "Mes inv%clido\n", 160);
        }
    }while(mes < 1 || mes > 12);

    do{
        printf("Ingrese a%co: ", 164);
        scanf("%d", &anio);
        if(anio < 2022){
            printf(ROJO_T "A%co invalido\n", 164);
        }
    }while(anio < 2022);

    validos = limpiarArrayCaja(arregloCaja, validos);
    validos = pasarArchivoPedidosToADLMensual(archivoPedidos, mes, anio, arregloCaja, validos, dimADLCaja);
    validos = pasarArchivoProveedoresToADLMensual(archivoTranProveedores, mes, anio, arregloCaja, validos, dimADLCaja);

    if(validos != 0){
        system("cls");
        mostrarMesYAnio(mes, anio);
        stAcumulador acumulador = acumuladores(arregloCaja, validos);
        mostrarAcumuladores(acumulador);
    }
    printf("\n");
}

int pasarArchivoPedidosToADLMensual(char archivo[], int mes, int anio, celdaCaja arrayCaja[], int validos, int dim){

    stPedido aux;
    FILE * buf = fopen (archivo, "rb");

    if(buf){
        while(fread (&aux, sizeof (stPedido), 1, buf) > 0 && validos <= dim){
            if(aux.fechaPago.mes == mes && aux.fechaPago.anio == anio && aux.estadoPago == 1){//si la fecha coincide y si el estado es pagado.
                validos = altaCajaPedido(arrayCaja, validos, aux);
            }
        }
        fclose(buf);
    }

    return validos;
}

int pasarArchivoProveedoresToADLMensual(char archivo[], int mes, int anio, celdaCaja arrayCaja[], int validos, int dim){

    RegTranProv aux;
    FILE * buf = fopen (archivo, "rb");

    if(buf){
        while(fread (&aux, sizeof (RegTranProv), 1, buf) > 0 && validos <= dim){
            if(aux.dato.fecha.mes == mes && aux.dato.fecha.anio == anio && aux.tipo == 1){
                validos = altaCajaProveedor (arrayCaja, validos, aux);
            }
        }
        fclose (buf);
    }

    return validos;
}

void mostrarMesYAnio(int mes, int anio){

    if(mes == 1){
        gotoxy(2, 1); printf(RESALTADOR_T "ENERO %d", anio);
    }
    else if(mes == 2){
        gotoxy(2, 1); printf(RESALTADOR_T "FEBRERO %d", anio);
    }else if(mes == 3){
        gotoxy(2, 1); printf(RESALTADOR_T "MARZO %d", anio);
    }else if(mes == 4){
        gotoxy(2, 1); printf(RESALTADOR_T "ABRIL %d", anio);
    }else if(mes == 5){
        gotoxy(2, 1); printf(RESALTADOR_T "MAYO %d", anio);
    }else if(mes == 6){
        gotoxy(2, 1); printf(RESALTADOR_T "JUNIO %d", anio);
    }else if(mes == 7){
        gotoxy(2, 1); printf(RESALTADOR_T "JULIO %d", anio);
    }else if(mes == 8){
        gotoxy(2, 1); printf(RESALTADOR_T "AGOSTO %d", anio);
    }else if(mes == 9){
        gotoxy(2, 1); printf(RESALTADOR_T "SEPTIEMBRE %d", anio);
    }else if(mes == 10){
        gotoxy(2, 1); printf(RESALTADOR_T "OCTUBRE %d", anio);
    }else if(mes == 11){
        gotoxy(2, 1); printf(RESALTADOR_T "NOVIEMBRE %d", anio);
    }else if(mes == 12){
        gotoxy(2, 1); printf(RESALTADOR_T "DICIEMBRE %d", anio);
    }
}

nodoCaja* inicListaCaja (){

    return NULL;
}

nodoCaja* crearNodoCaja(stCompraVenta dato){

    nodoCaja * nuevo = (nodoCaja*) malloc (sizeof (nodoCaja));

    nuevo->dato = dato;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoCaja* agregaAlFinal (nodoCaja * lista, nodoCaja * nuevo){

    if (lista == NULL){
        lista = nuevo;
    }
    else{
        nodoCaja * ultimo = buscaUltimo (lista);
        ultimo->siguiente = nuevo;
    }

    return lista;
}

nodoCaja* buscaUltimo (nodoCaja * lista){

    nodoCaja * seg = lista;

    if(seg){
        while(seg->siguiente){
            seg = seg->siguiente;
        }
    }

    return seg;
}

nodoCaja* borrarListaCaja (nodoCaja *lista){

    nodoCaja * proximo;

    while(lista){
        proximo = lista->siguiente;
        free(lista);
        lista = proximo;
    }

    return lista;
}

int limpiarArrayCaja(celdaCaja arrayCaja[], int val){

    int i;

    for (i = 0; i < val; i++){
        arrayCaja[i].listaIngresos = borrarListaCaja(arrayCaja[i].listaIngresos);
    }

    for(i = 0; i < val; i++){
        arrayCaja[i].listaEgresos = borrarListaCaja(arrayCaja[i].listaEgresos);
    }
    val = 0;

    return val;
}

stFecha cargarFechaManual(){

    stFecha aux;
    printf("\nIngrese el d%ca: ", 161);
    scanf("%i", &aux.dia);

    do{
        printf("Ingrese el mes: ");
        scanf("%d", &aux.mes);
        if(aux.mes < 1 || aux.mes > 12){
            printf(ROJO_T "Mes inv%clido\n", 160);
        }
    }while(aux.mes < 1 || aux.mes > 12);

    printf ("Ingrese el a%co: ", 164);
    scanf ("%i", &aux.anio);

    return aux;
}
