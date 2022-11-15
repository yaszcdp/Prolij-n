#include "productos.h"

stProducto cargarProducto(){

    stProducto aux;

    cargarCategoriaProducto(&aux.categoria);
    aux.idProducto = generarIdProducto(aux.categoria) + 1;
    cargarNombreProducto(aux.nombre);
    cargarMarcaProducto(aux.marca);
    cargarProveedorProducto(aux.proveedor);
    cargarDescripcionProducto(aux.descripcion);
    cargarPrecioCostoProducto(&aux.precioCosto);
    cargarPorcentajeGananciaProducto(&aux.porcentajeGanancia);
    calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);

    return aux;
}

void cargarCategoriaProducto(int *categoria){

    do{
        printf("Categoria (1 Bolsas 2 Ladrillos 3 Aridos 4 Hierros 5 Vigas 6 Fletes 7 Otros): ");
        scanf ("%i", categoria);
        if(*categoria < 1 || *categoria > 7){
            printf(ROJO_T "Categoria inv%clida\n" NEUTRA_T, 160);
        }
    }while(*categoria < 1 || *categoria > 7);
}

int generarIdProducto(int categoria){

    stProducto aux;
    int idProducto = categoria * 1000;
    FILE * buf = fopen(archivoProductos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0){
            if(aux.categoria == categoria){
                idProducto++;//se incrementa el id por cada producto de la misma categoría
            }
        }
        fclose(buf);
    }

    return idProducto;
}

void cargarNombreProducto(char nombre[]){

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

void cargarMarcaProducto(char marca[]){

    printf("Marca: ");
    fflush (stdin);
    fgets(marca, dimStr, stdin);
    strtok(marca, "\n");

    for(int i = 0; marca[i]; i++)
        marca[i] = toupper(marca[i]);
}

void cargarProveedorProducto(char proveedor[]){

    printf("Proveedor: ");
    fflush(stdin);
    fgets(proveedor, dimStr, stdin);
    strtok(proveedor, "\n");

    for(int i = 0; proveedor[i]; i++)
        proveedor[i] = toupper(proveedor[i]);
}

void cargarDescripcionProducto(char descripcion[]){

    printf("Descripci%cn: ", 162);
    fflush(stdin);
    fgets(descripcion, dimStr, stdin);
    strtok(descripcion, "\n");

    for(int i = 0; descripcion[i]; i++)
        descripcion[i] = toupper(descripcion[i]);
}

void cargarPrecioCostoProducto(float *precioCosto){

    printf("Precio de costo: $");
    scanf("%f", precioCosto);
}

void cargarPorcentajeGananciaProducto(float *porcentajeGanancia){

    printf("Porcentaje de ganancia: ");
    scanf("%f", porcentajeGanancia);
}

void calcularPrecioVentaProducto(float *precioVenta, float precioCosto, float porcentajeGanancia){

    (*precioVenta) = precioCosto + (precioCosto * (porcentajeGanancia / 100));
}

void menuBuscarProducto(char *opcion){

    printf("Buscar producto por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tNombre");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int buscarProducto(stProducto *aux){

    char opcion;
    int id;
    char nombre[dimStr];
    int reg = -1;

    do{
        system("cls");
        menuBuscarProducto(&opcion);
        switch(opcion){

            case 49://por id
                printf("ID: ");
                scanf("%i", &id);
                reg = buscarProductoId(id);
                break;

            case 50://por nombre
                printf("Nombre: ");
                fflush(stdin);
                fgets(nombre, dimStr, stdin);
                strtok(nombre, "\n");
                for(int i = 0; nombre[i]; i++)
                    nombre[i] = toupper(nombre[i]);
                reg = buscarProductoNombre(nombre);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50);

    if(reg != -1){//se encontró el producto buscado y se guarda en aux para retornarlo y mostrarlo en el main
        FILE * buf = fopen(archivoProductos, "rb");
        if(buf){
            fseek(buf, sizeof(stProducto) * (reg - 1), 0);
            fread(aux, sizeof(stProducto), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

int buscarProductoId(int id){

    int reg = -1;
    stProducto aux;
    FILE * buf = fopen(archivoProductos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0 && reg == -1){
            if(aux.idProducto == id){
                reg = ftell(buf) / sizeof(stProducto);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarProductoNombre(char nombre[]){

    int reg = -1;
    char control;
    stProducto aux;
    FILE * buf = fopen(archivoProductos, "rb");

    for (int i = 0; nombre [i]; i++)
        nombre[i] = toupper (nombre[i]);

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0 && reg == -1){
            if(strstr(aux.nombre, nombre) != NULL){
                printf(RESALTADOR_T "%s %s %s" NEUTRA_T "?", aux.nombre, aux.marca, aux.descripcion);
                printf ("s/n ");//verificación si hay más productos con el mismo nombre
                fflush(stdin);
                control = getche();
                printf("\n");
                if(control == 's' || control == 'S'){
                    reg = ftell(buf) / sizeof(stProducto);
                }
            }
        }
        fclose(buf);
    }

    return reg;
}

void mostrarProducto(stProducto aux){

    gotoxy(1, 1); printf(RESALTADOR_T "ID:" NEUTRA_T ".............................");
    gotoxy(30, 1); printf(RESALTADOR_T "%i", aux.idProducto);

    gotoxy(1, 2); printf("TIPO:" NEUTRA_T "........................." RESALTADOR_T);
    if (aux.categoria == 1){
        gotoxy(30, 2); printf("BOLSA");
    }
    else if(aux.categoria == 2){
        gotoxy(30, 2); printf("LADRILLO");
    }
    else if(aux.categoria == 3){
        gotoxy(30, 2); printf("ARIDO");
    }
    else if(aux.categoria == 4){
        gotoxy(30, 2); printf("HIERRO");
    }
    else if(aux.categoria == 5){
        gotoxy(30, 2); printf("VIGA");
    }
    else if(aux.categoria == 6){
        gotoxy(30, 2); printf("FLETE");
    }
    else{
        gotoxy(30, 2); printf("OTRO");
    }

    gotoxy(1, 3); printf("NOMBRE:" NEUTRA_T "........................" RESALTADOR_T);
    gotoxy(30, 3); printf("%s", aux.nombre);

    gotoxy(1, 4); printf("MARCA:" NEUTRA_T "........................." RESALTADOR_T);
    gotoxy(30, 4); printf("%s", aux.marca);

    gotoxy(1, 5); printf("DESCRIPCION:" NEUTRA_T "..................." RESALTADOR_T);
    gotoxy(30, 5); printf("%s", aux.descripcion);

    gotoxy(1, 6); printf("PROVEEDOR:" NEUTRA_T "....................." RESALTADOR_T);
    gotoxy(30, 6); printf("%s", aux.proveedor);

    gotoxy(1, 7); printf("PRECIO DE COSTO:" NEUTRA_T "................" RESALTADOR_T);
    gotoxy(30, 7); printf("$%.2f", aux.precioCosto);

    gotoxy(1, 8); printf("PORCENTAJE DE GANANCIA:" NEUTRA_T "........." RESALTADOR_T);
    gotoxy(30, 8); printf("%.2f%%", aux.porcentajeGanancia);

    gotoxy(1, 9); printf("PRECIO DE VENTA:" NEUTRA_T "................" RESALTADOR_T);
    gotoxy(30, 9); printf("$%.2f\n" NEUTRA_T, aux.precioVenta);

    printf("\n");
}

void menuModificarProducto(stProducto *aux, char *opcion){

    mostrarProducto(*aux);//muestra el producto a modificar y los campos que van siendo modificados
    printf("\nModificar:");
    printf(RESALTADOR_T "\n 1\tNombre");
    printf("\n 2\tMarca");
    printf("\n 3\tProveedor");
    printf("\n 4\tDescripci%cn", 162);
    printf("\n 5\tPrecio de costo");
    printf("\n 6\tPorcentaje de ganancia");
    printf("\n 0\tFinalizar");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void modificarProducto(int reg){

    stProducto aux;
    char opcion;
    FILE *buf = fopen(archivoProductos, "r+b");

    if(buf){
        fseek(buf, sizeof(stProducto) * (reg - 1), 0);
        fread(&aux, sizeof(stProducto), 1, buf);
        fclose(buf);
        do{
            system("cls");
            menuModificarProducto(&aux, &opcion);
            switch(opcion){

                case 49://nombre
                    cargarNombreProducto(aux.nombre);
                    system("pause");
                    break;

                case 50://marca
                    cargarMarcaProducto(aux.marca);
                    system("pause");
                    break;

                case 51://proveedor
                    cargarProveedorProducto(aux.proveedor);
                    system("pause");
                    break;

                case 52://descripcion
                    cargarDescripcionProducto(aux.descripcion);
                    system("pause");
                    break;

                case 53://precio de costo
                    cargarPrecioCostoProducto(&aux.precioCosto);
                    calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);
                    system("pause");
                    break;

                case 54://porcentaje de ganancia
                    cargarPorcentajeGananciaProducto(&aux.porcentajeGanancia);
                    calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);
                    system("pause");
                    break;

                case 48://finalizar
                    opcionGuardar(&opcion);
                    if(opcion == 's' || opcion == 'S'){
                        guardarModificacion(archivoProductos, sizeof(stProducto), reg, &aux);
                        printf(VERDE_T "\nCambios guardados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    else{
                        printf(ROJO_T "\nCambios descartados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    break;

                default:
                    printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T);
                    system("pause");
            }
        }while(opcion != 48);
    }
}

void aumentarCostoCategoria(int categoria, float aumento){

    stProducto aux;
    FILE *buf = fopen(archivoProductos, "r+b");

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0){
            if(aux.categoria == categoria){
                aux.precioCosto = aux.precioCosto + (aux.precioCosto * (aumento / 100));
                calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);
                fseek(buf, sizeof(stProducto) * (-1), 1);
                fwrite(&aux, sizeof(stProducto), 1, buf);
                fseek(buf, 0, 1);
            }
        }
        fclose(buf);
    }
}

void menuMostrarProductos(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tTodos");
    printf("\n 2\tPor categoria");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int pasarArchivoProductosADL(celdaProductos arreglo[], int validos){

    FILE *buf = fopen("productos.bin", "rb");
    stProducto aux;

    if(buf){
        while(fread(&aux, 1, sizeof(stProducto), buf) > 0 && validos < dimADLProd){
            validos = altaADLProductos(arreglo, validos, aux);
        }
        fclose(buf);
    }

    return validos;
}

int altaADLProductos(celdaProductos arreglo[], int validos, stProducto aux){

    nodoProducto *nuevo = crearNodoProducto(cargarProductoADL(aux));
    int pos = buscarPosADLProductos(arreglo, aux.categoria, validos);

    if(pos == -1){
        validos = agregarCategoriaADL(arreglo, aux.categoria, validos);
        pos = validos -1;
    }

    arreglo[pos].listaProductos = agregarProductosEnOrdenId(arreglo[pos].listaProductos, nuevo);

    return validos;
}

nodoProducto* crearNodoProducto(Producto aux){

    nodoProducto *nuevo = malloc(sizeof(nodoProducto));

    nuevo->dato = aux;
    nuevo->siguiente = NULL;

    return nuevo;
}

Producto cargarProductoADL(stProducto aux){

    Producto nuevo;

    nuevo.idProducto = aux.idProducto;
    strcpy(nuevo.nombre, aux.nombre);
    strcpy(nuevo.marca, aux.marca);
    strcpy(nuevo.proveedor, aux.proveedor);
    strcpy(nuevo.descripcion, aux.descripcion);
    nuevo.precioCosto = aux.precioCosto;
    nuevo.porcentajeGanancia = aux.porcentajeGanancia;
    nuevo.precioVenta = aux.precioVenta;

    return nuevo;
}

int buscarPosADLProductos(celdaProductos arreglo[], int categoria, int validos){

    int i = 0;
    int pos = -1;

    while(i < validos && pos == -1){
        if(arreglo[i].categoria == categoria)
            pos = i;
        i++;
    }

    return pos;
}

int agregarCategoriaADL(celdaProductos arreglo[], int categoria, int validos){

    arreglo[validos].categoria = categoria;
    arreglo[validos].listaProductos = inicListaProductos();
    validos++;

    return validos;
}

nodoProducto* inicListaProductos(){

    return NULL;
}

nodoProducto* agregarProductosEnOrdenId(nodoProducto *listaProductos, nodoProducto *nuevo){

    if(!listaProductos)
        listaProductos = nuevo;
    else if(nuevo->dato.idProducto < listaProductos->dato.idProducto)
        listaProductos = agregarAlPrincipioListaProductos(listaProductos, nuevo);
    else{
        nodoProducto *ante = listaProductos;
        nodoProducto *seg = listaProductos->siguiente;
        while(seg && seg->dato.idProducto < nuevo->dato.idProducto){
            ante = seg;
            seg = seg->siguiente;
        }
        ante->siguiente = nuevo;
        nuevo->siguiente = seg;
    }

    return listaProductos;
}

nodoProducto* agregarAlPrincipioListaProductos(nodoProducto *listaProductos, nodoProducto *nuevo){

    if(listaProductos)
        nuevo->siguiente = listaProductos;

    return nuevo;
}

void encabezadoListadoProducto(int y){

    gotoxy(2,y); printf(RESALTADOR_T "| ID");
    gotoxy(10,y); printf("| TIPO");
    gotoxy(22,y); printf("|   NOMBRE");
    gotoxy(37,y); printf("|   MARCA");
    gotoxy(50,y); printf("| DESCRIPCION");
    gotoxy(67,y); printf("| COSTO");
    gotoxy(82,y); printf("| %% GANANCIA");
    gotoxy(95,y); printf("| VENTA");
    gotoxy(107,y); printf("| PROVEEDOR");
    gotoxy(125,y); printf("|");
    printf ("\n  ----------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
}

void mostrarADLProductos(celdaProductos arreglo[], int validos, int y){

    int i = 0;

    while(i < validos){
        y = mostrarListaProductos(arreglo[i].categoria, arreglo[i].listaProductos, y);
        i++;
    }
}

int mostrarListaProductos(int categoria, nodoProducto *listaProductos, int y){

    if(listaProductos){

        gotoxy(2, y); printf("| %i", listaProductos->dato.idProducto);

        if (categoria == 1){
            gotoxy(10, y); printf("| BOLSA");
        }
        else if(categoria == 2){
            gotoxy(10, y); printf("| LADRILLO");
        }
        else if(categoria == 3){
            gotoxy(10, y); printf("| ARIDO");
        }
        else if(categoria == 4){
            gotoxy(10, y); printf("| HIERRO");
        }
        else if(categoria == 5){
            gotoxy(10, y); printf("| VIGA");
        }
        else if(categoria == 6){
            gotoxy(10, y); printf("| FLETE");
        }
        else{
            gotoxy(10, y); printf("| OTROS");
        }
        mostrarProductoLista(listaProductos, y);
        y = mostrarListaProductos(categoria, listaProductos->siguiente, y+1);
    }

    return y;
}

void mostrarProductoLista(nodoProducto *listaProductos, int y){

    gotoxy(22, y); printf("| %s", listaProductos->dato.nombre);
    gotoxy(37, y); printf("| %s", listaProductos->dato.marca);
    gotoxy(50, y); printf("| %s", listaProductos->dato.descripcion);
    gotoxy(67, y); printf("| $%.2f", listaProductos->dato.precioCosto);
    gotoxy(82, y); printf("| %.2f%%", listaProductos->dato.porcentajeGanancia);
    gotoxy(95, y); printf("| " RESALTADOR_T "$%.2f", listaProductos->dato.precioVenta);
    gotoxy(107, y); printf(NEUTRA_T "| %s", listaProductos->dato.proveedor);
    gotoxy(125,y); printf("|");
    printf("\n");
}
