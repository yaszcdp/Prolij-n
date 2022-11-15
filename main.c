#include "comunes.h"
#include "caja.h"

void nuevoCliente(stCliente * auxCliente);
void altaBajaCliente(stCliente * auxCliente);
void consultaCliente(stCliente * auxCliente);
void modificaCliente(stCliente * auxCliente);
void listadoClientes();
void nuevoPedido(stPedido * auxPedido);
void altaBajaPedido(stPedido * auxPedido);
void consultaPedido(stPedido * auxPedido);
void modificaPedido(stPedido * auxPedido);
void listadoPedidos(stCliente * auxCliente);
void nuevoProducto(stProducto * auxProducto);
void consultaProducto(stProducto * auxProducto);
void modificaProducto(stProducto * auxProducto);
int aumentoProductos(celdaProductos arregloProductos[], int validosProductos);
int listadoProductos(celdaProductos arregloProductos[], int validosProductos);
void nuevoProveedor(stProveedor * auxProveedor);
void altaBajaProveedor(stProveedor * auxProveedor);
void consultaProveedor(stProveedor * auxProveedor);
void modificarProveedor(stProveedor * auxProveedor);
void listadoProveedores();
void nuevaTransaccion(stProveedor * auxProveedor);
void anulaTransaccion(RegTranProv * auxTransaccion);
void consultaTransaccion(RegTranProv * auxTransaccion);
void listadoTransacciones(stProveedor * auxProveedor, RegTranProv * auxTransaccion);

int main(){

    system("color 07");//fondo blanco (7) letras negro (0)

    char opcion;
    int flag;
    int reg = -1;
    stCliente auxCliente;
    stPedido auxPedido;
    stProducto auxProducto;
    celdaProductos arregloProductos[dimADLProd];
    int validosProductos;
    stProveedor auxProveedor;
    RegTranProv auxTransaccion;
    stCaja auxCaja;
    stFecha fecha;
    celdaCaja arregloCaja[dimADLCaja];
    int validosCaja = 0;
    stAcumulador acumulador;
    int mes;
    int anio;

    do{
        system("cls");
        menuPrincipal(&opcion);
        switch(opcion){

            case 49://clientes
                do{
                    system("cls");
                    menuClientes(&opcion);
                    switch(opcion){

                        case 49://nuevo cliente
                            system ("cls");
                            nuevoCliente(&auxCliente);
                            break;

                        case 50://baja/alta cliente
                            altaBajaCliente(&auxCliente);
                            break;

                        case 51://consulta cliente
                            consultaCliente(&auxCliente);
                            break;

                        case 52://modificacion cliente
                            modificaCliente(&auxCliente);
                            break;

                        case 53://listados clientes
                            listadoClientes();
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                    }

                    if(opcion != 27){
                        system("pause");
                    }

                }while(opcion != 27);
                break;

            case 50://pedidos
                do{
                    system("cls");
                    menuPedidos(&opcion);
                    switch(opcion){

                        case 49://nuevo pedido
                            nuevoPedido(&auxPedido);
                            break;

                        case 50://baja/alta pedido
                            altaBajaPedido(&auxPedido);
                            break;

                        case 51://consulta pedido
                            consultaPedido(&auxPedido);
                            break;

                        case 52://modificacion pedido
                            modificaPedido(&auxPedido);
                            break;

                        case 53://listados pedidos
                            listadoPedidos(&auxCliente);
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                    }

                    if(opcion != 27){
                        system("pause");
                    }

                }while(opcion != 27);
                break;

            case 51://productos
                do{
                    system("cls");
                    menuProductos(&opcion);
                    switch(opcion){

                        case 49://nuevo producto
                            nuevoProducto(&auxProducto);
                            break;

                        case 50://consulta producto
                            consultaProducto(&auxProducto);
                            break;

                        case 51://modificacion producto
                            modificaProducto(&auxProducto);
                            break;

                        case 52://aumentos productos
                            validosProductos = aumentoProductos(arregloProductos, 0);
                            break;

                        case 53://listados productos
                            validosProductos = listadoProductos(arregloProductos, 0);
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                    }

                    if(opcion != 27){
                        system("pause");
                    }

                }while(opcion != 27);
                break;

            case 52://proveedores
                do{
                    system("cls");
                    menuProveedores(&opcion);
                    switch(opcion){

                        case 49://nuevo proveedor
                            system ("cls");
                            nuevoProveedor(&auxProveedor);
                            break;

                        case 50://baja/alta proveedor
                            altaBajaProveedor(&auxProveedor);
                            break;

                        case 51://consulta proveedor
                            consultaProveedor(&auxProveedor);
                            break;

                        case 52://modificación nombre proveedor
                            modificarProveedor(&auxProveedor);
                            break;

                        case 53://listados proveedores
                            listadoProveedores();
                            break;

                        case 54://transacciones proveedores
                            do{
                                system("cls");
                                menuTransaccionProveedores(&opcion);
                                switch(opcion){

                                    case 49://nueva transacción
                                        system("cls");
                                        nuevaTransaccion(&auxProveedor);
                                        break;

                                    case 50://anular transacción
                                        system("cls");
                                        anulaTransaccion(&auxTransaccion);
                                        break;

                                    case 51://consulta transaccion
                                        system("cls");
                                        consultaTransaccion(&auxTransaccion);
                                        break;

                                    case 52://listados transacciones
                                        listadoTransacciones(&auxProveedor, &auxTransaccion);
                                        break;

                                    case 27://menu principal
                                        break;

                                    default:
                                        printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                                }

                                if(opcion != 27){
                                    system("pause");
                                }

                            }while(opcion != 27);
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                    }

                    if(opcion != 27){
                        system("pause");
                    }

                }while(opcion != 27);
                break;

            case 53://caja
                do{
                    system("cls");
                    menuCaja(&opcion);
                    switch(opcion){

                        case 49://iniciar
                            system("cls");
                            iniciarCaja(archivoCaja, &auxCaja);
                            printf("\n");
                            break;

                        case 50://modificar inicio
                            system("cls");
                            modificarInicio(archivoCaja, &auxCaja);
                            printf("\n");
                            break;

                        case 51://ver inicio y cierre
                            system("cls");
                            muestraInicioCierreYDiferencias(archivoCaja, arregloCaja, &auxCaja, validosCaja);
                            printf ("\n");
                            break;

                        case 52://ver caja
                            system("cls");
                            verCaja (arregloCaja, &auxCaja, validosCaja);
                            printf ("\n");
                            break;

                        case 53://acumuladores del día
                            system("cls");
                            acumuladorDia(archivoCaja, arregloCaja, &auxCaja, validosCaja);
                            printf ("\n");
                            break;

                        case 54://acumuladores del mes
                            system ("cls");
                            acumuladorMes(arregloCaja, validosCaja);
                            printf ("\n");
                            break;

                        case 55://cerrar
                            system("cls");
                            cerrarCaja(archivoCaja, arregloCaja, &auxCaja);
                            printf("\n");
                            break;

                        case 56://modificar cierre
                            system("cls");
                            modificarCierre(archivoCaja, &auxCaja);
                            printf("\n");
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opci%cn inv%clida.", 162, 160);
                            printf (NEUTRA_T "\n");
                    }

                    if(opcion != 27){
                        system("pause");
                    }

                }while(opcion != 27);
                break;

            case 48://salir
                printf(ROJO_T "Salir? s/n " NEUTRA_T);
                fflush(stdin);
                char control = getche();
                if(control == 's' || control == 'S')
                    printf(RESALTADOR_T "\nGracias por usar Prolij%cn 2.0\n%c 2022 TiM ToC" NEUTRA_T, 161, 184);
                else
                    opcion = 1;
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 160);
                system("pause");
        }
    }while(opcion != 48);

    return 0;
}

void nuevoCliente(stCliente * auxCliente){

    int flag = cargarCliente(auxCliente);//flag validación dni
    char opcion;

    if(flag == 1){//dni existe
        printf(ROJO_T "Ya existe un cliente registrado con el DNI ingresado"NEUTRA_T);
    }
    else{//dni no existe
        opcionGuardar(&opcion);
        if(opcion == 's' || opcion == 'S'){
            guardarNuevo(archivoClientes, sizeof(stCliente), auxCliente);
            printf(VERDE_T "\nCliente guardado"NEUTRA_T);
        }
        else{
            printf(ROJO_T "\nCliente descartado"NEUTRA_T);
        }
    }
    printf("\n");
}

void altaBajaCliente(stCliente * auxCliente){

    int reg = buscarCliente(auxCliente);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el cliente buscado
        printf(ROJO_T "Cliente no encontrado\n"NEUTRA_T);
    }
    else{//se encontró el cliente buscado y se modifica estado
        system ("cls");
        int flag = bajaCliente(reg);
        mostrarCliente(*auxCliente);
        if(flag == 0){
            printf(ROJO_T "El cliente fue dado de baja\n"NEUTRA_T);
        }
        else{
            printf(VERDE_T "El cliente fue dado de alta\n"NEUTRA_T);
        }
    }
}

void consultaCliente(stCliente * auxCliente){

    int reg = buscarCliente(auxCliente);//reg iniciliazado en -1 en función

    if(reg == -1){//no se encontró el cliente buscado
        printf(ROJO_T "Cliente no encontrado\n" NEUTRA_T);
    }
    else{//se encontró el cliente buscado y se muestra
        system("cls");
        mostrarCliente(*auxCliente);
    }
}

void modificaCliente(stCliente * auxCliente){

    int reg = buscarCliente(auxCliente);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el cliente buscado
        printf(ROJO_T "Cliente no encontrado\n" NEUTRA_T);
    }
    else{
        system("cls");
        modificarCliente(reg);//se encontró el cliente buscado y se modifica
    }
}

void listadoClientes(){

    char opcion;

    nodoDobleCliente * listaCliente = inicListaDobleCliente();

    do{
        system("cls");
        menuOrdenarClientes(&opcion);
        switch(opcion){

            case 49://por id
                listaCliente = pasarArchivoListaDobleClienteId(listaCliente);
                break;

            case 50://por apellido
                listaCliente = pasarArchivoListaDobleClienteApellido(listaCliente);
                break;

            case 51://por cantidad de pedidos
                listaCliente = pasarArchivoListaDobleClientePedidos(listaCliente);
                break;

            case 52://top 10 clientes
                listaCliente = pasarArchivoListaDobleClientePedidos(listaCliente);
                system("cls");
                encabezadoListadoCliente(0);
                top10clientes(listaCliente, 2, 0);
                printf("\n  -------------------------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
                printf("\n");
                break;

            case 53://peor cliente
                listaCliente = pasarArchivoListaDobleClientePedidos(listaCliente);
                system("cls");
                mostrarCliente(buscarUltimoNodoDobleCliente(listaCliente)->dato);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53);

    if(opcion != 52 && opcion != 53){
        do{
            system("cls");
            menuMostrarClientes(&opcion);
            switch(opcion){

                case 49://todos
                    system("cls");
                    encabezadoListadoCliente(0);
                    mostrarListaDobleClienteTodos(listaCliente, 2);
                    printf("\n  -------------------------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
                    printf("\n");
                    break;

                case 50://alta
                    system("cls");
                    encabezadoListadoCliente(0);
                    mostrarListaDobleClienteAlta(listaCliente, 2);
                    printf("\n  -------------------------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
                    printf("\n");
                    break;

                case 51://baja
                    system("cls");
                    encabezadoListadoCliente(0);
                    mostrarListaDobleClienteBaja(listaCliente, 2);
                    printf("\n  -------------------------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
                    printf("\n");
                    break;

                default:
                    printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                    system("pause");
                }
        }while(opcion != 49 && opcion != 50 && opcion != 51);
    }
    listaCliente = borrarListaDobleCliente(listaCliente);
}

void nuevoPedido(stPedido * auxPedido){

    int reg = cargarPedido(auxPedido);
    char opcion;

    if(reg == -1){//cliente no encontrado o no confirmado
        printf(ROJO_T "Cliente no encontrado o no confirmado" NEUTRA_T);
    }
    else{//cliente encontrado, confirmado y pedido cargado
        opcionGuardar(&opcion);
        if(opcion == 's' || opcion == 'S'){
            guardarNuevo(archivoPedidos, sizeof(stPedido), auxPedido);
            sumarPedidoCliente(auxPedido->idCliente);//se suma 1 al campo cantidadPedidos del cliente
            printf(VERDE_T "\nPedido guardado" NEUTRA_T);
        }
        else{
            printf(ROJO_T "\nPedido descartado" NEUTRA_T);
        }
    }
    printf("\n");
}

void altaBajaPedido(stPedido * auxPedido){

    int reg = buscarPedido(auxPedido);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el pedido buscado
        printf(ROJO_T "Pedido no encontrado\n" NEUTRA_T);
    }
    else{//se encontró el pedido buscado y se modifica estado
        int flag = bajaPedido(reg);
        system("cls");
        mostrarPedido(*auxPedido);
        if(flag == 0){
            printf(ROJO_T "El pedido fue dado de baja\n" NEUTRA_T);
            restarPedidoCliente(auxPedido->idCliente);//se resta 1 al campo cantidadPedidos del cliente
        }
        else if(flag == -1){
            printf("\nEl pedido ya ha sido entregado y no puede cancelarse.\n");
        }
        else{
            printf(VERDE_T "El pedido fue dado de alta\n" NEUTRA_T);
            sumarPedidoCliente(auxPedido->idCliente);//se suma 1 al campo cantidadPedidos del cliente
        }
    }
}

void consultaPedido(stPedido * auxPedido){

    int reg = buscarPedido(auxPedido);//reg iniciliazado en -1 en función

    if(reg == -1){//no se encontró el pedido buscado
        printf(ROJO_T "Pedido no encontrado\n" NEUTRA_T);
    }
    else{//se encontró el pedido buscado y se muestra
        system("cls");
        mostrarPedido(*auxPedido);
    }
}

void modificaPedido(stPedido * auxPedido){

    int reg = buscarPedido(auxPedido);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el pedido buscado
        printf(ROJO_T "Pedido no encontrado\n" NEUTRA_T);
    }
    else{
        system("cls");
        modificarPedido(reg);//se encontró el pedido buscado y se modifica
    }
}

void listadoPedidos(stCliente * auxCliente){

    int reg;
    nodoDoblePedido * listaPedido = inicListaDoblePedido();
    char opcion;

    do{
        system("cls");
        menuOrdenarPedidos(&opcion);
        switch(opcion){

            case 49://por id pedido - fecha
                listaPedido = pasarArchivoListaDoblePedidoIdPedido(listaPedido);
                break;

            case 50://por id cliente
                listaPedido = pasarArchivoListaDoblePedidoIdCliente(listaPedido);
                break;

            case 51://pedidos por cliente
                reg = buscarCliente(auxCliente);//reg iniciliazado en -1 en función
                if(reg == -1){//no se encontró el cliente buscado
                    printf(ROJO_T "Cliente no encontrado\n" NEUTRA_T);
                }
                else{//se encontró el cliente buscado y se muestran sus pedidos
                    system("cls");
                    listaPedido = pasarArchivoListaDoblePedidoIdCliente(listaPedido);
                    encabezadoListadoPedido(0);
                    mostrarPedidosPorCliente(listaPedido, auxCliente->idCliente, 2);
                    printf("  --------------------------------------------------------------------------\n");
                }
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
            }
    }while(opcion != 49 && opcion != 50 && opcion != 51);

    if(opcion != 51){
        do{
            system("cls");
            menuMostrarPedidos(&opcion);
            switch(opcion){

            case 49://activos
                system("cls");
                encabezadoListadoPedido(0);
                mostrarListaDoblePedidoActivos(listaPedido, 2);
                printf("  --------------------------------------------------------------------------\n");
                break;

            case 50://activos pagados
                system("cls");
                encabezadoListadoPedido(0);
                mostrarListaDoblePedidoActivosPagados(listaPedido, 2);
                printf("  --------------------------------------------------------------------------\n");
                break;

            case 51://activos pendientes de pago
                system("cls");
                encabezadoListadoPedido(0);
                mostrarListaDoblePedidoActivosPendientesPago(listaPedido, 2);
                printf("  --------------------------------------------------------------------------\n");
                break;

            case 52://activos entregados
                system("cls");
                encabezadoListadoPedido(0);
                mostrarListaDoblePedidoActivosEntregados(listaPedido, 2);
                printf("  --------------------------------------------------------------------------\n");
                break;

            case 53://activos pendientes de entrega
                system("cls");
                encabezadoListadoPedido(0);
                mostrarListaDoblePedidoActivosPendientesEntrega(listaPedido, 2);
                printf("  --------------------------------------------------------------------------\n");
                break;

            case 54://cancelados
                system("cls");
                encabezadoListadoPedido(0);
                mostrarListaDoblePedidoCancelados(listaPedido, 2);
                printf("  --------------------------------------------------------------------------\n");
                break;

            default:
                printf(ROJO_T "Opcion inv%clida\n" NEUTRA_T, 160);
                system("pause");
            }
        }while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 54);
    }
    listaPedido = borrarListaDoblePedido(listaPedido);
}

void nuevoProducto(stProducto * auxProducto){

    *auxProducto = cargarProducto();
    char opcion;

    opcionGuardar(&opcion);
    if(opcion == 's' || opcion == 'S'){
        guardarNuevo(archivoProductos, sizeof(stProducto), auxProducto);
        printf(VERDE_T "\nProducto guardado" NEUTRA_T);
    }
    else{
        printf(ROJO_T "\nProducto descartado" NEUTRA_T);
    }
    printf("\n");
}

void consultaProducto(stProducto * auxProducto){

    int reg = buscarProducto(auxProducto);//reg iniciliazado en -1 en función

    if(reg == -1){//no se encontró el producto buscado
        printf(ROJO_T "Producto no encontrado\n" NEUTRA_T);
    }
    else{//se encontró el producto buscado y se muestra
        system("cls");
        mostrarProducto(*auxProducto);
    }
}

void modificaProducto(stProducto * auxProducto){

    int reg = buscarProducto(auxProducto);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el producto buscado
        printf(ROJO_T "Producto no encontrado\n" NEUTRA_T);
    }
    else{
        system("cls");
        modificarProducto(reg);//se encontró el producto buscado y se modifica
    }
}

int aumentoProductos(celdaProductos arregloProductos[], int validosProductos){

    int categoria;
    float aumento;

    cargarCategoriaProducto(&categoria);
    printf("Ingrese el porcentaje de aumento: ");
    scanf("%f", &aumento);
    aumentarCostoCategoria(categoria, aumento);
    printf(VERDE_T "Aumento guardado\n" NEUTRA_T, aumento);
    system("pause");
    system("cls");

    validosProductos = pasarArchivoProductosADL(arregloProductos, validosProductos);
    encabezadoListadoProducto(0);
    int y = mostrarListaProductos(arregloProductos[categoria-1].categoria, arregloProductos[categoria-1].listaProductos, 2);

    return validosProductos;
}

int listadoProductos(celdaProductos arregloProductos[], int validosProductos){

    int categoria;
    char opcion;

    do{
        system("cls");
        validosProductos = pasarArchivoProductosADL(arregloProductos, validosProductos);
        menuMostrarProductos(&opcion);
        switch(opcion){

            case 49://todos
                system("cls");
                encabezadoListadoProducto(0);
                mostrarADLProductos(arregloProductos, validosProductos, 2);
                printf ("  ----------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
                break;

            case 50://categoria
                cargarCategoriaProducto(&categoria);
                system("cls");
                encabezadoListadoProducto(0);
                int y = mostrarListaProductos(arregloProductos[categoria-1].categoria, arregloProductos[categoria-1].listaProductos, 2);
                printf ("  ----------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50);

    return validosProductos;
}

void nuevoProveedor(stProveedor * auxProveedor){

    char opcion;
    int reg = cargarProveedor(auxProveedor);

    if(reg==-1){ // no hay un provedor con el mismo nombre en el sistema
        opcionGuardar(&opcion);
        if(opcion == 's' || opcion == 'S'){
            guardarNuevo(archivoProveedores, sizeof(stProveedor), auxProveedor);
            printf(VERDE_T "\nProvedor guardado" NEUTRA_T);
        }
        else{
            printf(ROJO_T "\nProvedor descartado" NEUTRA_T);
        }
    }
    printf("\n");
}

void altaBajaProveedor(stProveedor * auxProveedor){

    int reg = buscarProveedor(auxProveedor);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el proveedor buscado
        printf(ROJO_T "Proveedor no encontrado\n"NEUTRA_T);
    }
    else{//se encontró el proveedor buscado y se modifica estado
        system ("cls");
        int flag = bajaProveedor(reg);
        mostrarProveedor(*auxProveedor);
        if(flag == 0){
            printf(ROJO_T "El proveedor fue dado de baja\n"NEUTRA_T);
        }
        else{
            printf(VERDE_T "El proveedor fue dado de alta\n"NEUTRA_T);
        }
    }
}

void consultaProveedor(stProveedor * auxProveedor){

    int reg = buscarProveedor(auxProveedor);//reg iniciliazado en -1 en función

    if(reg == -1){//no se encontró el proveedor buscado
        printf(ROJO_T "Proveedor no encontrado\n" NEUTRA_T);
    }
    else{//se encontró el proveedor buscado y se muestra
        system("cls");
        mostrarProveedor(*auxProveedor);
    }
}

void modificarProveedor(stProveedor * auxProveedor){

    int reg = buscarProveedor(auxProveedor);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el proveedor buscado
        printf(ROJO_T "Proveedor no encontrado\n" NEUTRA_T);
    }
    else{
        system("cls");
        modificarProveedorNombre(reg);//se encontró el proveedor buscado y se modifica
    }
}

void listadoProveedores(){

    char opcion;
    nodoDobleProveedor * listaProveedor = inicListaDobleProveedor();

    do{
        system("cls");
        menuOrdenarProveedores(&opcion);
        switch(opcion){

            case 49://por id
                listaProveedor= pasarArchivoListaDobleProveedorId(listaProveedor);
                break;

            case 50://por nombre
                listaProveedor = pasarArchivoListaDobleProveedorNombre(listaProveedor);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50);

    do{
        system("cls");
        menuMostrarProveedores(&opcion);
        switch(opcion){

            case 49://todos
                system("cls");
                encabezadoListadoProveedor(0);
                mostrarListaDobleProveedorTodos(listaProveedor, 2);
                printf ("\n  ----------------------------------------------------\n" NEUTRA_T);
                break;

            case 50://alta
                system("cls");
                encabezadoListadoProveedor(0);
                mostrarListaDobleProveedorAlta(listaProveedor, 2);
                printf ("\n  ----------------------------------------------------\n" NEUTRA_T);
                break;

            case 51://baja
                system("cls");
                encabezadoListadoProveedor(0);
                mostrarListaDobleProveedorBaja(listaProveedor, 2);
                printf ("\n  ----------------------------------------------------\n" NEUTRA_T);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50 && opcion != 51);
    listaProveedor = borrarListaDobleProveedor(listaProveedor);
}

void nuevaTransaccion(stProveedor * auxProveedor){

    RegTranProv auxTransaccion;
    char opcion;
    int reg = buscarProveedor(auxProveedor);//reg incializado en -1 en función

    if(reg == -1){//no se encontró el proveedor buscado
        printf(ROJO_T "\nProveedor no encontrado." NEUTRA_T);
    }
    else{
        system ("cls");
        auxTransaccion = RegistroTransaccionProveedor(*auxProveedor);
        opcionGuardar(&opcion);
        if(opcion == 's' || opcion == 'S'){
            guardarNuevo(archivoTranProveedores, sizeof(RegTranProv), &auxTransaccion);
            modificarCtaCorriente(auxProveedor, reg, auxTransaccion);
            printf(VERDE_T "\nTransacci%cn guardada", 162);
            printf (NEUTRA_T "\n");
            opcion = '0';///--------------------------------------------------------------------> OPCION '0' ???
        }
        else{
            printf(ROJO_T "\nTrasacci%cn descartada", 162);
            printf (NEUTRA_T "\n");
            opcion = '0';
        }
    }
}

void anulaTransaccion(RegTranProv * auxTransaccion){

    int reg = buscarTransaccionPorId(auxTransaccion);
    char opcion;

    if(reg == -1){//no se encontró el proveedor buscado
        printf(ROJO_T "Transacci%cn no encontrada\n" NEUTRA_T, 162);
    }
    else{
        system("cls");
        MostrarRegistroTranProv(*auxTransaccion);
        printf ("  ------------------------------------------\n" NEUTRA_T);
        printf(ROJO_T "\n\nAnular?" NEUTRA_T " s/n ");
        fflush(stdin);
        opcion = getche();
        if(opcion == 's'||opcion=='S'){
            AnularTransaccion(*auxTransaccion);//se encontró la transacción y se anula
            printf(ROJO_T "\nTransacci%cn anulada\n" NEUTRA_T, 162);
        }
        else{
            printf(VERDE_T "\nTransacci%cn mantenida\n" NEUTRA_T, 162);
        }
    }
}

void consultaTransaccion(RegTranProv * auxTransaccion){

    int reg = buscarTransaccionPorId(auxTransaccion);//reg iniciliazado en -1 en función

    if(reg == -1){//no se encontró la transacción buscada
        printf(ROJO_T "Transacci%cn no encontrada\n" NEUTRA_T, 162);
    }
    else{//se encontró la transaccion buscado y se muestra
        system("cls");
        MostrarRegistroTranProv(*auxTransaccion);
        printf ("  ------------------------------------------\n" NEUTRA_T);
    }
}

void listadoTransacciones(stProveedor * auxProveedor, RegTranProv * auxTransaccion){

    int reg;
    char opcion;
    nodoTranProv * listaTranProv;

    do{
        system("cls");
        menuMostrarTrasaccion(&opcion);
        listaTranProv = inicListaDobleTranProv();
        listaTranProv = pasarArchivoListaTranProv(listaTranProv);
        switch(opcion){

            case 49://todas
                system("cls");
                encabezadoListadoTranProv(0);
                mostrarListaDobleTranProvTodos(listaTranProv, 2);
                printf ("  ---------------------------------------------------------------------------------\n" NEUTRA_T);
                break;

            case 50://por proveedor
                reg = buscarProveedor(auxProveedor);
                if(reg == -1){//no se encontraron las transacciones buscadas
                    printf(ROJO_T "Transacci%cn no encontrada\n" NEUTRA_T, 162);
                }
                else{//se encontron las transacciones buscadas y se muestran
                    system("cls");
                    encabezadoListadoTranProv(0);
                    mostrarListaDobleTranIdProv(listaTranProv, auxProveedor->idProveedor, 2);
                    printf ("  ---------------------------------------------------------------------------------\n" NEUTRA_T);
                }
                break;

            case 51://por fecha
                reg = BuscarTransaccionFecha(auxTransaccion);
                if(reg == -1){//no se encontraron las transacciones buscadas
                    printf(ROJO_T "Transacci%cn no encontrada\n" NEUTRA_T, 162);
                }
                else{//se encontron las transacciones buscadas y se muestran
                    system("cls");
                    encabezadoListadoTranProv(0);
                    mostrarListaDobleTranProvFecha(listaTranProv, auxTransaccion->dato.fecha, 2);
                    printf ("  ---------------------------------------------------------------------------------\n" NEUTRA_T);
                }
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
        listaTranProv = borrarListaTransacciones(listaTranProv);
    }while(opcion != 49 && opcion != 50 && opcion != 51);
}
