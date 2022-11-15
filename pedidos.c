#include "pedidos.h"

int cargarPedido(stPedido *aux){

    int reg = -1;
    char opcion;
    float monto;

    aux->idPedido = contarRegistrosArchivo(archivoPedidos, sizeof(stPedido)) + 1;//suma 1 a la cantidad de registros del archivo

    aux->idCliente = validarClientePedido(&reg);

    if(reg != -1){//se carga el pedido solo si se encontró y confirmó el cliente
        system("cls");
        aux->fecha = cargarFecha();
        aux->validosProductosPedidos = 0;
        aux->validosProductosPedidos = cargarProductosPedidos(aux->productosPedidos, aux->validosProductosPedidos, 100);
        aux->estadoEntrega = 0;//pendiente por defecto
        monto = calcularMonto(aux->productosPedidos, aux->validosProductosPedidos);
        calcularTotal(aux, monto);
        system("cls");
        mostrarPedido(*aux);
        printf("Pedido pagado? s/n ");
        fflush(stdin);
        opcion = getche();
        printf("\n");
        if(opcion == 's' || opcion == 'S'){
            pagarPedido(aux);
        }
        else{
            aux->monto = monto;
            aux->estadoPago = 0;
        }
        aux->estadoPedido = 1;//activo por defecto
    }

    return reg;
}

int validarClientePedido(int *reg){

    int idCliente;
    stCliente aux;
    char opcion;

    (*reg) = buscarCliente(&aux);//reg iniciliazado en -1 en función

    if(*reg != -1){//cliente encontrado
        system("cls");
        mostrarCliente(aux);
        printf("Confirmar cliente? s/n ");
        fflush(stdin);
        opcion = getche();
        printf("\n");
        if(opcion == 's' || opcion == 'S'){
            idCliente = aux.idCliente;
        }
        else{
            (*reg) = -1;
        }
    }

    return idCliente;
}

stFecha cargarFecha(){

    stFecha aux;
    time_t t = time(NULL);
    struct tm fechaActual = *localtime(&t);

    aux.dia = fechaActual.tm_mday;
    aux.mes = fechaActual.tm_mon + 1;
    aux.anio = fechaActual.tm_year + 1900;

    return aux;
}

int cargarProductosPedidos(stProductoPedido arreglo[], int validos, int dimension){

    char control = 's';

    while(validos < dimension && (control == 's' || control == 'S')){
        arreglo[validos] = cargarProductoPedido();
        validos ++;
        printf("Agregar m%cs productos? s/n ", 160);
        fflush(stdin);
        control = getche();
    }

    return validos;
}

stProductoPedido cargarProductoPedido(){

    stProductoPedido aux;
    stProducto auxProducto;
    int reg = -1;

    while(reg == -1){
        reg = buscarProducto(&auxProducto);
        if(reg == -1){//no se encontró el producto buscado
            printf(ROJO_T "Producto no encontrado\n" NEUTRA_T);
            system("pause");
        }
        else{//se encontró el producto buscado y se muestra
            system("cls");
            mostrarProducto(auxProducto);

            strcpy(aux.nombre, auxProducto.nombre);//se concatenan nombre, marca y descripcion del producto como nombre del producto pedido
            strcat(aux.nombre, " ");
            strcat(aux.nombre, auxProducto.marca);
            strcat(aux.nombre, " ");
            strcat(aux.nombre, auxProducto.descripcion);

            do{
                printf("Cantidad: ");
                scanf("%f", &aux.cantidad);
                if(aux.cantidad <= 0){
                    printf(ROJO_T "Cantidad inv%clida\n" NEUTRA_T, 160);
                }
            }while(aux.cantidad <= 0);

            aux.precioVenta = aux.cantidad * auxProducto.precioVenta;
        }
    }

    return aux;
}

void calcularTotal (stPedido * pedido, float monto){

    pedido->medioDePago = ingresarMedioDePago();
    pedido->monto = calcularPorcentaje(pedido->medioDePago, monto);
}

void pagarPedido(stPedido *pedido){

    pedido->estadoPago = 1;
    pedido->fechaPago = cargarFecha();
}

int ingresarMedioDePago(){

    int opcion;

    do{
        printf(RESALTADOR_T "\n\nMedio de pago:\n");
        printf(NEUTRA_T " 1\tEfectivo\n");
        printf(" 2\tD%cbito/Transferencia/Cr%cdito un pago\n", 130, 130);
        printf(" 3\tCr%cdito en cuotas\n", 130);
        printf("Ingrese una opci%cn: ", 162);
        scanf("%i", &opcion);
        if(opcion < 1 || opcion > 3){
            printf(ROJO_T "\nOpci%cn inv%clida\n" NEUTRA_T, 162, 160);
            system("pause");
            system("cls");
        }
    }while(opcion < 1 || opcion > 3);

    return opcion;
}

float calcularPorcentaje(int medioDePago, float monto){

    if(medioDePago == 1){
        monto = monto - monto * 0.1;
    }
    else if(medioDePago == 3){
        monto = calcularPorcentajePorCuotas(monto);
    }
    return monto;
}

float calcularPorcentajePorCuotas(float monto){

    int opcion;

    do{
        printf(RESALTADOR_T "Cantidad de cuotas:\n" NEUTRA_T);
        printf(" 1\t2 a 3 cuotas\n");
        printf(" 2\t6 cuotas\n");
        printf(" 3\t12 cuotas\n");
        printf(" 4\tAhora 3\n");
        printf(" 5\tAhora 6\n");
        printf(" 6\tAhora 12\n");
        printf(" 7\tAhora 18\n");
        printf("Ingrese una opci%cn: ", 162);
        scanf("%i", &opcion);
        switch(opcion){
            case 1:
                monto = monto * 1.12;
                break;
            case 2:
                monto = monto * 1.35;
                break;
            case 3:
                monto = monto * 1.7;
                break;
            case 4:
                monto = monto * 1.1;
                break;
            case 5:
                monto = monto * 1.21;
                break;
            case 6:
                monto = monto * 1.4;
                break;
            case 7:
                monto = monto * 1.75;
                break;
            case 8:
                monto = monto * 2.07;
                break;
            default:
                printf(ROJO_T "\nOpci%cn inv%clida\n" NEUTRA_T, 162, 160);
        }
    }while(opcion < 1 || opcion > 8);///si la opcion no es valida, sigue el bucle, si la opcion es una de las correctas, se corta.

    return monto;
}

float calcularMonto(stProductoPedido arreglo[], int validos){

    int i;
    float monto = 0;

    for(i = 0; i < validos; i ++){
        monto = monto + arreglo[i].precioVenta;//recorre el arreglo y toma el valor total de cada producto (precio * cantidad), y lo suma al monto anterior
    }

    return monto;
}

void sumarPedidoCliente(int idCliente){

    stCliente aux;
    int flag = 0;
    int reg;
    FILE * buf = fopen(archivoClientes, "r+b");

    if(buf){
        reg = buscarClienteId(idCliente);
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        aux.cantidadPedidos = contarPedidosCliente(aux.idCliente);
        aux.estado = 1;
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fwrite(&aux, sizeof(stCliente), 1, buf);
        fclose(buf);
    }
}

int contarPedidosCliente(int idCliente){
    int cant = 0;
    stPedido aux;
    FILE * buf = fopen(archivoPedidos, "rb");
    if(buf){
        while(fread(&aux, sizeof(stPedido), 1, buf) > 0){
            if(aux.idCliente == idCliente && aux.estadoPedido == 1){
                cant ++;
            }
        }
        fclose(buf);
    }
    return cant;
}

int bajaPedido(int reg){

    stPedido aux;
    int flag;
    FILE * buf = fopen(archivoPedidos, "r+b");

    if(buf){
        fseek(buf, sizeof(stPedido) * (reg - 1), 0);
        fread(&aux, sizeof(stPedido), 1, buf);
        if(aux.estadoPedido == 1 && aux.estadoEntrega == 0 && aux.estadoPago == 0){
            aux.estadoPedido = 0;
            flag = 0;
        }
        else if(aux.estadoPedido == 1 && aux.estadoEntrega == 1 && (aux.estadoPago == 1 || aux.estadoPago == 0)){
            ///no se puede dar de baja un pedido entregado.
            flag = -1;
        }
        else if(aux.estadoPedido == 1 && aux.estadoPago == 1){
            aux.estadoPago = 0; ///cancelo el pago
            stFecha auxFecha;
            aux.fechaPago = auxFecha; ///borro la fecha de pago anterior.
            aux.estadoPedido = 0;
            flag = 0;
        }
        else{
            aux.estadoPedido = 1;
            flag = 1;
        }
        fseek(buf, sizeof(stPedido) * (reg - 1), 0);
        fwrite(&aux, sizeof(stPedido), 1, buf);
        fclose(buf);
    }

    return flag;
}

void restarPedidoCliente(int idCliente){

    stCliente aux;
    int flag = 0;
    int reg;
    FILE * buf = fopen(archivoClientes, "r+b");

    if(buf){
        reg = buscarClienteId(idCliente);
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        aux.cantidadPedidos--;
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fwrite(&aux, sizeof(stCliente), 1, buf);
        fclose(buf);
    }
}

void menuBuscarPedido(char *opcion){

    printf("Buscar por:");
    printf(RESALTADOR_T "\n 1\tID Pedido");
    printf("\n 2\tID Cliente");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int buscarPedido(stPedido *aux){

    char opcion;
    int idPedido;
    int idCliente;
    int reg = -1;

    do{
        system("cls");
        menuBuscarPedido(&opcion);
        switch(opcion){

            case 49://por id pedido
                printf("ID Pedido: ");
                scanf("%i", &idPedido);
                reg = buscarPedidoIdPedido(idPedido);
                break;

            case 50://por id cliente
                printf("ID Cliente: ");
                scanf("%i", &idCliente);
                reg = buscarPedidoIdCliente(idCliente);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50);

    if(reg != -1){//se encontró el cliente buscado y se guarda en aux para retornarlo y mostrarlo en el main
        FILE * buf = fopen(archivoPedidos, "rb");
        if(buf){
            fseek(buf, sizeof(stPedido) * (reg - 1), 0);
            fread(aux, sizeof(stPedido), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

int buscarPedidoIdPedido(int idPedido){

    int reg = -1;
    stPedido aux;
    FILE * buf = fopen(archivoPedidos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stPedido), 1, buf) > 0 && reg == -1){
            if(aux.idPedido == idPedido){
                reg = ftell(buf) / sizeof(stPedido);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarPedidoIdCliente(int idCliente){

    int reg = -1;
    stPedido aux;
    char control;
    FILE * buf = fopen(archivoPedidos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stPedido), 1, buf) > 0 && reg == -1){
            if(aux.idCliente == idCliente){
                printf("Fecha %i/%i/%i  ", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
                printf ("ID Pedido: %i  ", aux.idPedido);
                printf("Monto " RESALTADOR_T "%$%.2f" NEUTRA_T "?  s/n ", aux.monto);//verificación si hay más pedidos del cliente
                fflush(stdin);
                control = getche();
                printf("\n");
                if(control == 's' || control == 'S'){
                    reg = ftell(buf) / sizeof(stPedido);
                }
            }
        }
        fclose(buf);
    }

    return reg;
}

void mostrarPedido(stPedido aux){

    gotoxy(2,1); printf("ID Pedido: %i", aux.idPedido);
    gotoxy(40,1); printf("Fecha: %i/%i/%i", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
    gotoxy(2,2); printf("ID Cliente: %i", aux.idCliente);

    if(aux.estadoPedido == 1){
        gotoxy(2,4); printf(VERDE_T "ACTIVO");
    }
    else{
        gotoxy(2,4); printf(ROJO_T "INACTIVO");
    }

    if(aux.estadoEntrega == 0){
        gotoxy(2,5); printf(ROJO_T "PENDIENTE DE ENTREGA");
    }
    else{
        gotoxy(2,5); printf(VERDE_T "ENTREGADO");
    }

    if(aux.estadoPago == 0){
        gotoxy(2,6); printf(ROJO_T "PENDIENTE DE PAGO");
    }
    else{
        gotoxy(2,6);printf(VERDE_T "PAGADO" NEUTRA_T " (%i/%i/%i)", aux.fechaPago.dia, aux.fechaPago.mes, aux.fechaPago.anio);
    }

    gotoxy(2,8); printf(RESALTADOR_T "------------------------------------------------------\n" );
    gotoxy(2,9); printf("| Cant");
    gotoxy(10,9); printf("|          Producto");
    gotoxy(40,9); printf("| Subtotal");
    gotoxy(55,9); printf("|");
    gotoxy(2,10); printf("------------------------------------------------------\n" );

    int y = 11;
    mostrarProductosPedidos(aux.productosPedidos, aux.validosProductosPedidos, &y);

    gotoxy(2,y); printf("------------------------------------------------------\n");
    y++;
    imprimeMedioDePago (aux.medioDePago, y);
    gotoxy(30,y); printf(RESALTADOR_T "| Total:");
    gotoxy(40,y); printf("| $%.2f\n", aux.monto);
    gotoxy(55,y); printf("|");
    y++;
    gotoxy(2,y); printf ("------------------------------------------------------\n"NEUTRA_T);

    printf ("\n");
}

void imprimeMedioDePago (int medioDePago, int y){
    if (medioDePago == 1){
        gotoxy (2, y); printf ("| Medio de pago: | " VERDE_T "Efectivo." );
    }else if (medioDePago == 2){
        gotoxy (2, y); printf ("| Medio de pago: | " VERDE_T "Lista." );
    }else{
        gotoxy (2, y); printf ("| Medio de pago: | " VERDE_T "Cr%cdito.", 130);
    }
}


void mostrarProductosPedidos(stProductoPedido arreglo[], int validos, int *y){

    int i;

    for(i = 0; i < validos; i ++){
        gotoxy(2,*y); printf("| %.2f", arreglo[i].cantidad);
        gotoxy(10,*y); printf("| %s", arreglo[i].nombre);
        gotoxy(40,*y); printf("| $%.2f", arreglo[i].precioVenta);
        gotoxy(55,*y); printf("|");
        *y = *y + 1;
    }
}

void menuModificarPedido(stPedido *aux, char *opcion){

    mostrarPedido(*aux);//muestra el pedido a modificar y los campos que van siendo modificados
    printf("\nModificar:");
    printf(RESALTADOR_T "\n 1\tID Cliente");
    printf("\n 2\tAgregar productos");
    printf("\n 3\tQuitar productos");
    printf("\n 4\tEstado entrega");
    printf("\n 5\tEstado pago");
    printf("\n 0\tFinalizar");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void modificarPedido(int reg){

    stPedido aux;
    int idCliente;
    char opcion;
    int flag = -1;
    FILE *buf = fopen(archivoPedidos, "r+b");

    if(buf){
        fseek(buf, sizeof(stPedido) * (reg - 1), 0);
        fread(&aux, sizeof(stPedido), 1, buf);
        fclose(buf);
        do{
            system("cls");
            menuModificarPedido(&aux, &opcion);
            switch(opcion){

                case 49://id cliente
                    idCliente = aux.idCliente;//guarda id por si el nuevo no se encuentra o confirma
                    aux.idCliente = validarClientePedido(&flag);
                    if(flag == -1){//cliente no encontrado o no confirmado
                        printf(ROJO_T "Cliente no encontrado o no confirmado\n" NEUTRA_T);
                        aux.idCliente = idCliente;//no cambia dni porque el nuevo existe
                    }
                    system("pause");
                    break;

                case 50://agregar productos
                    aux.validosProductosPedidos = cargarProductosPedidos(aux.productosPedidos, aux.validosProductosPedidos, 100);
                    aux.monto = calcularMonto(aux.productosPedidos, aux.validosProductosPedidos);
                    printf("\n");
                    system("pause");
                    break;

                case 51://quitar productos
                    aux.validosProductosPedidos = quitarProductosPedidos(aux.productosPedidos, aux.validosProductosPedidos);
                    aux.monto = calcularMonto(aux.productosPedidos, aux.validosProductosPedidos);
                    system("pause");
                    break;

                case 52://estado entrega
                    if(aux.estadoEntrega == 0){
                        aux.estadoEntrega = 1;
                        printf(VERDE_T "Pedido entregado\n" NEUTRA_T);
                    }
                    else{
                        aux.estadoEntrega = 0;
                        printf(ROJO_T "Pedido pendiente de entrega\n" NEUTRA_T);
                    }
                    system("pause");
                    break;

                case 53://estado pago
                    if(aux.estadoPago == 0){
                        calcularTotal (&aux, calcularMonto(aux.productosPedidos, aux.validosProductosPedidos));
                        pagarPedido(&aux);
                        printf(VERDE_T "Pedido pagado\n" NEUTRA_T);
                    }
                    else{
                        aux.estadoPago = 0;
                        stFecha auxFecha;
                        aux.fechaPago = auxFecha; ///borro la fecha de pago anterior.
                        printf(ROJO_T "Pedido pendiente de pago\n" NEUTRA_T);
                    }
                    system("pause");
                    break;

                case 48://finalizar
                    opcionGuardar(&opcion);
                    if(opcion == 's' || opcion == 'S'){
                        guardarModificacion(archivoPedidos, sizeof(stPedido), reg, &aux);
                        if(flag != -1){//si se cambio el id cliente
                            sumarPedidoCliente(aux.idCliente);//se suma un pedido al nuevo id cliente
                            restarPedidoCliente(idCliente);//se resta un pedido al viejo id cliente
                        }
                        printf(VERDE_T "\nCambios guardados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    else{
                        printf(ROJO_T "\nCambios descartados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    break;

                default:
                    printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                    system("pause");
            }
        }while(opcion != 48);
    }
}

int quitarProductosPedidos(stProductoPedido arreglo[], int validos){

    int i;
    char control;

    for(i = 0; i < validos; i ++){
        printf("Quitar \"%s\"? s/n ", arreglo[i].nombre);
        fflush(stdin);
        control = getche();
        printf("\n");
        if(control == 's' || control == 'S'){
            validos = quitarUnProducto(arreglo, i, validos);
        }
    }
    return validos;
}

int quitarUnProducto(stProductoPedido arreglo[], int pos, int validos){

    stProductoPedido aux;

    while(pos < validos-1){
        aux = arreglo[pos+1];
        arreglo[pos] = aux;
        pos++;
    }
    validos--;

    return validos;
}

void menuOrdenarPedidos(char *opcion){

    printf("Ordenar por:");
    printf(RESALTADOR_T "\n 1\tID Pedido / Fecha");
    printf("\n 2\tID Cliente");
    printf(NEUTRA_T "\nMostrar:");
    printf(RESALTADOR_T "\n 3\tPedidos por cliente");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void menuMostrarPedidos(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tActivos");
    printf("\n 2\tActivos pagados");
    printf("\n 3\tActivos pendientes de pago");
    printf("\n 4\tActivos entregados");
    printf("\n 5\tActivos pendientes de entrega");
    printf("\n 6\tCancelados");
    printf(NEUTRA_T "\nIngrese una opci%cn: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void encabezadoListadoPedido(int y){

    gotoxy(2,y); printf(RESALTADOR_T "| FECHA");
    gotoxy(12,y); printf("| ID P");
    gotoxy(20,y); printf("| ID C");
    gotoxy(28,y); printf("| MONTO");
    gotoxy(40,y); printf("| PAGO");
    gotoxy(52,y); printf("| ENTREGA");
    gotoxy(65,y); printf("| ESTADO");
    gotoxy(75,y); printf("|");
    printf("\n  --------------------------------------------------------------------------\n");
    printf(NEUTRA_T"\n");
}

void mostrarPedidoListado(stPedido aux, int y){

    gotoxy(2,y); printf(NEUTRA_T "| %i/%i/%i", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
    gotoxy(12,y); printf("| %i", aux.idPedido);
    gotoxy(20,y); printf("| %i", aux.idCliente);
    gotoxy(28,y); printf("| %.2f", aux.monto);

    if(aux.estadoPago == 0){
        gotoxy(40,y); printf("|" ROJO_T "PENDIENTE");
    }
    else{
        gotoxy(40,y);printf(NEUTRA_T "|" VERDE_T "PAGADO");
    }

    if(aux.estadoEntrega == 0){
        gotoxy(52,y); printf(NEUTRA_T "|" ROJO_T "PENDIENTE");
    }
    else{
        gotoxy(52,y); printf(NEUTRA_T "|" VERDE_T "ENTREGADO");
    }

    if(aux.estadoPedido == 1){
        gotoxy(65,y); printf(NEUTRA_T "|" VERDE_T "ACTIVO");
    }
    else{
        gotoxy(65,y); printf(NEUTRA_T "|" ROJO_T "CANCELADO");
    }
    gotoxy(75,y); printf (NEUTRA_T "|\n");
}

nodoDoblePedido* inicListaDoblePedido(){

    return NULL;
}

nodoDoblePedido* crearNodoDoblePedido(stPedido dato){

    nodoDoblePedido *nuevo = malloc(sizeof(nodoDoblePedido));

    nuevo->dato = dato;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoDoblePedido* agregarAlPrincipioListaDoblePedido(nodoDoblePedido *lista, nodoDoblePedido *nuevo){

    if(lista){
        nuevo->siguiente = lista;
        lista->anterior = nuevo;
    }

    return nuevo;
}

nodoDoblePedido* agregarAlFinalListaDoblePedido(nodoDoblePedido *lista, nodoDoblePedido *nuevo){

    if(!lista)
        lista = nuevo;
    else{
        nodoDoblePedido *ultimo = buscarUltimoNodoDoblePedido(lista);
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
    }

    return lista;
}

nodoDoblePedido* buscarUltimoNodoDoblePedido(nodoDoblePedido *lista){

    while(lista->siguiente)
        lista = lista->siguiente;

    return lista;
}

nodoDoblePedido* agregarEnOrdenIdClienteListaDoblePedido(nodoDoblePedido *lista, nodoDoblePedido *nuevo){

    if(!lista){
        lista = nuevo;
    }
    else if(nuevo->dato.idCliente <= lista->dato.idCliente){
        lista = agregarAlPrincipioListaDoblePedido(lista, nuevo);
    }
    else{
        nodoDoblePedido *seg = lista;
        while(seg && nuevo->dato.idCliente > seg->dato.idCliente){
            seg = seg->siguiente;
        }
        if(seg){
            nodoDoblePedido *ante = seg->anterior;
            ante->siguiente = nuevo;
            nuevo->anterior = ante;
            nuevo->siguiente = seg;
            seg->anterior = nuevo;
        }
        else{
            lista = agregarAlFinalListaDoblePedido(lista, nuevo);
        }
    }

    return lista;
}

nodoDoblePedido* pasarArchivoListaDoblePedidoIdPedido(nodoDoblePedido *lista){

    FILE *buf = fopen(archivoPedidos, "rb");
    stPedido aux;

    if(buf){
        while(fread(&aux, sizeof(stPedido), 1, buf) > 0){
            lista = agregarAlFinalListaDoblePedido(lista, crearNodoDoblePedido(aux));
        }
        fclose(buf);
    }

    return lista;
}

nodoDoblePedido* pasarArchivoListaDoblePedidoIdCliente(nodoDoblePedido *lista){

    FILE *buf = fopen(archivoPedidos, "rb");
    stPedido aux;

    if(buf){
        while(fread(&aux, sizeof(stPedido), 1, buf) > 0){
            lista = agregarEnOrdenIdClienteListaDoblePedido(lista, crearNodoDoblePedido(aux));
        }
        fclose(buf);
    }

    return lista;
}

void mostrarPedidosPorCliente(nodoDoblePedido *lista, int idCliente, int y){

    if(lista){
        if(lista->dato.idCliente == idCliente)
            mostrarPedidoListado(lista->dato, y++);
        mostrarPedidosPorCliente(lista->siguiente, idCliente, y);
    }
}

void mostrarListaDoblePedidoActivos(nodoDoblePedido *lista, int y){

    if(lista){
        if(lista->dato.estadoPedido == 1)
            mostrarPedidoListado(lista->dato, y++);
        mostrarListaDoblePedidoActivos(lista->siguiente, y);
    }
}

void mostrarListaDoblePedidoActivosPagados(nodoDoblePedido *lista, int y){

    if(lista){
        if(lista->dato.estadoPedido == 1 && lista->dato.estadoPago == 1)
            mostrarPedidoListado(lista->dato, y++);
        mostrarListaDoblePedidoActivosPagados(lista->siguiente, y);
    }
}

void mostrarListaDoblePedidoActivosPendientesPago(nodoDoblePedido *lista, int y){

    if(lista){
        if(lista->dato.estadoPedido == 1 && lista->dato.estadoPago == 0)
            mostrarPedidoListado(lista->dato, y++);
        mostrarListaDoblePedidoActivosPendientesPago(lista->siguiente, y);
    }
}

void mostrarListaDoblePedidoActivosEntregados(nodoDoblePedido *lista, int y){

    if(lista){
        if(lista->dato.estadoPedido == 1 && lista->dato.estadoEntrega == 1)
            mostrarPedidoListado(lista->dato, y++);
        mostrarListaDoblePedidoActivosEntregados(lista->siguiente, y);
    }
}

void mostrarListaDoblePedidoActivosPendientesEntrega(nodoDoblePedido *lista, int y){

    if(lista){
        if(lista->dato.estadoPedido == 1 && lista->dato.estadoEntrega == 0)
            mostrarPedidoListado(lista->dato, y++);
        mostrarListaDoblePedidoActivosPendientesEntrega(lista->siguiente, y);
    }
}

void mostrarListaDoblePedidoCancelados(nodoDoblePedido *lista, int y){

    if(lista){
        if(lista->dato.estadoPedido == 0)
            mostrarPedidoListado(lista->dato, y++);
        mostrarListaDoblePedidoCancelados(lista->siguiente, y);
    }
}

nodoDoblePedido* borrarListaDoblePedido(nodoDoblePedido *lista){

    nodoDoblePedido *proximo;

    while(lista){
        proximo = lista->siguiente;
        free(lista);
        lista = proximo;
    }

    return lista;
}
