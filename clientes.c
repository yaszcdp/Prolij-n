#include "clientes.h"

int cargarCliente(stCliente *aux){

    int flag;

    aux->idCliente = contarRegistrosArchivo(archivoClientes, sizeof(stCliente)) + 1;//suma 1 a la cantidad de registros del archivo
    aux->dni = cargarDniCliente(&flag);//flag validación dni
    if(flag == 0){//dni no existe
        cargarTelefonoCliente(aux->telefono);
        cargarMailCliente(aux->mail);
        cargarApellidoCliente(aux->apellido);
        cargarNombreCliente(aux->nombre);
        aux->domicilio = cargarDomicilioCliente();
        aux->estado = 1;//alta por defecto
        aux->cantidadPedidos = 0;//como es un cliente nuevo se inicializa en 0
    }

    return flag;
}

long int cargarDniCliente(int *flag){

    long int dni;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");
    (*flag) = 0;

    do{
        printf("DNI: ");
        scanf("%li", &dni);
        if(dni <= 0){
            printf(ROJO_T "DNI inv%clido\n" NEUTRA_T, 160);
        }
    }while(dni <= 0);

    if(buf){
        do{
            fread(&aux, sizeof(stCliente), 1, buf);
            if(aux.dni == dni){
                (*flag) = 1;//dni existe
            }
        }while(!feof(buf) && *flag == 0);
        fclose(buf);
    }

    return dni;
}

void cargarTelefonoCliente(char telefono[]){

    printf("Tel%cfono: ", 130);
    fflush(stdin);
    fgets(telefono, dimStr, stdin);
    strtok(telefono, "\n");
}

void cargarMailCliente(char mail[]){

    do{
        printf("Mail: ");
        fflush(stdin);
        fgets(mail, dimStr, stdin);
        strtok(mail, "\n");
        if(mail[0] != '\n' && (!strstr(mail, "@")  || !strstr(mail, "."))){
            printf(ROJO_T "Mail inv%clido\n" NEUTRA_T, 160);
        }
    }while(mail[0] != '\n' && (!strstr(mail, "@")  || !strstr(mail, ".")));
}

void cargarApellidoCliente(char apellido[]){

    do{
        printf("Apellido: ");
        fflush(stdin);
        fgets(apellido, dimStr, stdin);
        strtok(apellido, "\n");
        if(apellido[0] == '\n'){//validación apellido
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(apellido[0] == '\n');

    for(int i = 0; apellido[i]; i++)
        apellido[i] = toupper(apellido[i]);
}

void cargarNombreCliente(char nombre[]){

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

stDomicilio cargarDomicilioCliente(){

    stDomicilio domicilio;

    printf("Domicilio:\n");
    do{
        printf("Calle: ");
        fflush(stdin);
        fgets(domicilio.calle, dimStr, stdin);
        strtok(domicilio.calle, "\n");
        if(domicilio.calle[0] == '\n'){
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(domicilio.calle[0] == '\n');

    for(int i = 0; domicilio.calle[i]; i++)
        domicilio.calle[i] = toupper(domicilio.calle[i]);

    printf("Altura: ");
    fflush(stdin);
    fgets(domicilio.altura, dimStr, stdin);
    strtok(domicilio.altura, "\n");

    printf("Piso: ");
    fflush(stdin);
    fgets(domicilio.piso, dimStr, stdin);
    strtok(domicilio.piso, "\n");

    printf("Departamento: ");
    fflush(stdin);
    fgets(domicilio.departamento, dimStr, stdin);
    strtok(domicilio.departamento, "\n");

    do{
        printf("Localidad: ");
        fflush(stdin);
        fgets(domicilio.localidad, dimStr, stdin);
        strtok(domicilio.localidad, "\n");
        if(domicilio.localidad[0] == '\n'){
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(domicilio.localidad[0] == '\n');

    for(int i = 0; domicilio.localidad[i]; i++)
        domicilio.localidad[i] = toupper(domicilio.localidad[i]);

    return domicilio;
}

int bajaCliente(int reg){

    stCliente aux;
    int flag;
    FILE * buf = fopen(archivoClientes, "r+b");

    if(buf){
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        if(aux.estado == 1){
            aux.estado = 0;
            flag = 0;
        }
        else{
            aux.estado = 1;
            flag = 1;
        }
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fwrite(&aux, sizeof(stCliente), 1, buf);
        fclose(buf);
    }

    return flag;
}

void menuBuscarCliente(char *opcion){

    printf("Buscar cliente por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tDNI");
    printf("\n 3\tApellido");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int buscarCliente(stCliente *aux){

    char opcion;
    int id;
    long int dni;
    char apellido[dimStr];
    int reg = -1;

    do{
        system("cls");
        menuBuscarCliente(&opcion);
        switch(opcion){

            case 49://por id
                printf("ID: ");
                scanf("%i", &id);
                reg = buscarClienteId(id);
                break;

            case 50://por dni
                printf("DNI: ");
                scanf("%li", &dni);
                reg = buscarClienteDni(dni);
                break;

            case 51://por apellido
                printf("Apellido: ");
                fflush(stdin);
                fgets(apellido, dimStr, stdin);
                strtok(apellido, "\n");
                for(int i = 0; apellido[i]; i++)
                    apellido[i] = toupper(apellido[i]);
                reg = buscarClienteApellido(apellido);
                break;

            default:
                printf(ROJO_T "Opci%cn inv%clida\n" NEUTRA_T, 162, 160);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50 && opcion != 51);

    if(reg != -1){//se encontró el cliente buscado y se guarda en aux para retornarlo y mostrarlo en el main
        FILE * buf = fopen(archivoClientes, "rb");
        if(buf){
            fseek(buf, sizeof(stCliente) * (reg - 1), 0);
            fread(aux, sizeof(stCliente), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

int buscarClienteId(int id){

    int reg = -1;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0 && reg == -1){
            if(aux.idCliente == id){
                reg = ftell(buf) / sizeof(stCliente);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarClienteDni(long int dni){

    int reg = -1;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0 && reg == -1){
            if(aux.dni == dni){
                reg = ftell(buf) / sizeof(stCliente);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarClienteApellido(char apellido[]){

    int reg = -1;
    char control;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0 && reg == -1){
            if(strstr(aux.apellido, apellido) != NULL){
                printf("\"" RESALTADOR_T "%s %s" NEUTRA_T "\"? s/n ", aux.apellido, aux.nombre);//verificación si hay más clientes con el mismo apellido
                fflush(stdin);
                control = getche();
                printf("\n");
                if(control == 's' || control == 'S'){
                    reg = ftell(buf) / sizeof(stCliente);
                }
            }
        }
        fclose(buf);
    }

    return reg;
}

void mostrarCliente(stCliente aux){

    gotoxy(1,1); printf(RESALTADOR_T "ID:" NEUTRA_T ".........................");
    gotoxy(30,1); printf(RESALTADOR_T "%i", aux.idCliente);

    gotoxy(1,2); printf("Apellido:" NEUTRA_T "....................." RESALTADOR_T);
    gotoxy(30,2); printf ("%s", aux.apellido);

    gotoxy(1,3); printf("Nombre:" NEUTRA_T "......................." RESALTADOR_T);
    gotoxy(30,3); printf ("%s", aux.nombre);

    gotoxy(1,4); printf("DNI:" NEUTRA_T "............................" RESALTADOR_T);
    gotoxy(30,4); printf("%li", aux.dni);

    gotoxy(1,5); printf("Tel%cfono:" NEUTRA_T, 130, "......................." RESALTADOR_T);
    if(aux.telefono[0] == '\n'){//si no tiene teléfono
        gotoxy(30,5); printf("-----");
    }
    else{
        gotoxy(30,5); printf("%s", aux.telefono);
    }

    gotoxy(1,6); printf("Mail:" NEUTRA_T ".........................." RESALTADOR_T);
    if(aux.mail[0] == '\n'){//si no tiene mail
        gotoxy(30,6); printf("-----");
    }
    else{
        gotoxy(30,6); printf("%s", aux.mail);
    }

    gotoxy(1,7); printf("Domicilio:");
    gotoxy(3,8); printf ("- Calle:"NEUTRA_T "........................" RESALTADOR_T);
    gotoxy(30,8); printf ("%s", aux.domicilio.calle);
    gotoxy(3,9); printf ("- Altura:" NEUTRA_T "...................." RESALTADOR_T);
    if(aux.domicilio.altura[0] != '\n'){//si tiene altura
        gotoxy(30,9); printf("%s", aux.domicilio.altura);
    }
    else{
        gotoxy(30,9); printf("-----");
    }
    gotoxy(3,10); printf ("- Piso:" NEUTRA_T "....................." RESALTADOR_T);
    if(aux.domicilio.piso[0] != '\n'){//si tiene piso
        gotoxy(30,10); printf("%s", aux.domicilio.piso);
    }
    else{
        gotoxy(30,10); printf("-----");
    }
    gotoxy(3,11); printf ("- Departamento:" NEUTRA_T "............." RESALTADOR_T);
    if(aux.domicilio.departamento[0] != '\n'){//si tiene departamento
        gotoxy(30,11); printf("%s", aux.domicilio.departamento);
    }
    else{
        gotoxy(30,11); printf("-----");
    }
    gotoxy(1,12); printf ("Localidad:" NEUTRA_T "..................." RESALTADOR_T);
    gotoxy(30,12); printf("%s", aux.domicilio.localidad);

    gotoxy(1,13); printf("Estado:" NEUTRA_T "..................." RESALTADOR_T);
    if(aux.estado == 1){
        gotoxy(30,13); printf(VERDE_T "ALTA\n"NEUTRA_T);//alta si el estado es 1
    }
    else{
        gotoxy(30,13); printf(ROJO_T "BAJA\n"NEUTRA_T);//baja si el estado es 0
    }

    gotoxy(1,14); printf(RESALTADOR_T "Cantidad de pedidos:" NEUTRA_T ".........." RESALTADOR_T);
    gotoxy(30,14); printf ("%i\n" NEUTRA_T, aux.cantidadPedidos);

    printf("\n");
}

void menuModificarCliente(stCliente *aux, char *opcion){

    mostrarCliente(*aux);//muestra el cliente a modificar y los campos que van siendo modificados
    printf("\nModificar:");
    printf(RESALTADOR_T "\n 1\tDNI");
    printf("\n 2\tTel%cfono", 130);
    printf("\n 3\tMail");
    printf("\n 4\tApellido");
    printf("\n 5\tNombre");
    printf("\n 6\tDomicilio");
    printf("\n 0\tFinalizar");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void modificarCliente(int reg){

    stCliente aux;
    char opcion;
    long int dni;
    int flag;
    FILE *buf = fopen(archivoClientes, "rb");

    if(buf){
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        fclose(buf);
        do{
            system("cls");
            menuModificarCliente(&aux, &opcion);
            switch(opcion){

                case 49://dni
                    dni = aux.dni;//guarda dni por si el nuevo existe
                    aux.dni = cargarDniCliente(&flag);
                    if(flag == 1){//dni existe
                        printf(ROJO_T "Ya existe un cliente registrado con el DNI ingresado\n" NEUTRA_T);
                        aux.dni = dni;//no cambia dni porque el nuevo existe
                    }
                    system("pause");
                    break;

                case 50://telefono
                    cargarTelefonoCliente(aux.telefono);
                    system("pause");
                    break;

                case 51://mail
                    cargarMailCliente(aux.mail);
                    system("pause");
                    break;

                case 52://apellido
                    cargarApellidoCliente(aux.apellido);
                    system("pause");
                    break;

                case 53://nombre
                    cargarNombreCliente(aux.nombre);
                    system("pause");
                    break;

                case 54://domicilio
                    aux.domicilio = cargarDomicilioCliente();
                    system("pause");
                    break;

                case 48://finalizar
                    opcionGuardar(&opcion);
                    if(opcion == 's' || opcion == 'S'){
                        guardarModificacion(archivoClientes, sizeof(stCliente), reg, &aux);
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

void menuOrdenarClientes(char *opcion){

    printf("Ordenar por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tApellido");
    printf("\n 3\tCantidad de pedidos");
    printf(NEUTRA_T "\nMostrar:");
    printf(VERDE_T "\n 4\tTop 10");
    printf(ROJO_T "\n 5\tPeor cliente");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void menuMostrarClientes(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tTodos");
    printf(VERDE_T "\n 2\tAlta");
    printf(ROJO_T "\n 3\tBaja");
    printf(NEUTRA_T "\nIngrese una opci%cn: ", 162);
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void encabezadoListadoCliente(int y){

    gotoxy(2,y); printf (RESALTADOR_T "|ID");
    gotoxy(6,y); printf ("|APELLIDO");
    gotoxy(20,y); printf ("|NOMBRE");
    gotoxy(32,y); printf ("|DNI");
    gotoxy(42,y); printf ("|TELEFONO");
    gotoxy(54,y); printf ("|CALLE");
    gotoxy(72,y); printf ("|ALTURA");
    gotoxy(93,y); printf ("|PISO");
    gotoxy(100,y); printf ("|DPTO");
    gotoxy(107,y); printf ("|LOCALIDAD");
    gotoxy(124,y); printf ("|ESTADO");
    gotoxy(134,y); printf ("|C.P");//cantidad pedidos.
    gotoxy(140,y); printf ("|");
    printf("\n  -------------------------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
}

void mostrarClienteListado(stCliente aux, int y){

    gotoxy(2,y); printf("|%i", aux.idCliente);
    gotoxy(6,y); printf("|%s", aux.apellido);
    gotoxy(20,y); printf("|%s", aux.nombre);
    gotoxy(32,y); printf("|%li", aux.dni);
    gotoxy(42,y); printf("|%s", aux.telefono);
    gotoxy(54,y); printf("|%s", aux.domicilio.calle);
    gotoxy(72,y); printf("|%s", aux.domicilio.altura);
    gotoxy(93,y); printf("|%s", aux.domicilio.piso);
    gotoxy(100,y); printf("|%s", aux.domicilio.departamento);
    gotoxy(107,y); printf("|%s", aux.domicilio.localidad);
    if(aux.estado == 1){
        gotoxy(124,y); printf("|" VERDE_T "ALTA");
    }
    else{
        gotoxy(124,y); printf("|" ROJO_T "BAJA");
    }
    gotoxy(134,y); printf(NEUTRA_T "|%i", aux.cantidadPedidos);
    gotoxy(140,y); printf("|");
}

nodoDobleCliente* inicListaDobleCliente(){

    return NULL;
}

nodoDobleCliente* crearNodoDobleCliente(stCliente dato){

    nodoDobleCliente *nuevo = malloc(sizeof(nodoDobleCliente));

    nuevo->dato = dato;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoDobleCliente* agregarAlPrincipioListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo){

    if(lista){
        nuevo->siguiente = lista;
        lista->anterior = nuevo;
    }

    return nuevo;
}

nodoDobleCliente* agregarAlFinalListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo){

    if(!lista)
        lista = nuevo;
    else{
        nodoDobleCliente *ultimo = buscarUltimoNodoDobleCliente(lista);
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
    }

    return lista;
}

nodoDobleCliente* buscarUltimoNodoDobleCliente(nodoDobleCliente *lista){

    while(lista->siguiente)
        lista = lista->siguiente;

    return lista;
}

nodoDobleCliente* agregarEnOrdenApellidoListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo){

    if(!lista)
        lista = nuevo;
    else if(strcmpi(nuevo->dato.apellido, lista->dato.apellido) < 0 || (strcmpi(nuevo->dato.apellido, lista->dato.apellido)== 0 && strcmpi(nuevo->dato.nombre, lista->dato.nombre)<0))
        lista = agregarAlPrincipioListaDobleCliente(lista, nuevo);
    else{
        nodoDobleCliente *seg = lista;
        while(seg && (strcmpi(nuevo->dato.apellido, seg->dato.apellido) > 0 || (strcmpi(nuevo->dato.apellido, seg->dato.apellido) == 0 && strcmpi(nuevo->dato.nombre, seg->dato.nombre) > 0)))
            seg = seg->siguiente;
        if(seg){
            nodoDobleCliente *ante = seg->anterior;
            ante->siguiente = nuevo;
            nuevo->anterior = ante;
            nuevo->siguiente = seg;
            seg->anterior = nuevo;
        }
        else
            lista = agregarAlFinalListaDobleCliente(lista, nuevo);
    }
    return lista;
}

nodoDobleCliente* agregarEnOrdenPedidosListaDobleCliente(nodoDobleCliente *lista, nodoDobleCliente *nuevo){

    if(!lista){
        lista = nuevo;
    }
    else if(nuevo->dato.cantidadPedidos >= lista->dato.cantidadPedidos){
        lista = agregarAlPrincipioListaDobleCliente(lista, nuevo);
    }
    else{
        nodoDobleCliente *seg = lista;
        while(seg && nuevo->dato.cantidadPedidos < seg->dato.cantidadPedidos){
            seg = seg->siguiente;
        }
        if(seg){
            nodoDobleCliente *ante = seg->anterior;
            ante->siguiente = nuevo;
            nuevo->anterior = ante;
            nuevo->siguiente = seg;
            seg->anterior = nuevo;
        }
        else{
            lista = agregarAlFinalListaDobleCliente(lista, nuevo);
        }
    }

    return lista;
}

nodoDobleCliente* pasarArchivoListaDobleClienteId(nodoDobleCliente *lista){

    FILE *buf = fopen(archivoClientes, "rb");
    stCliente aux;

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0){
            lista = agregarAlFinalListaDobleCliente(lista, crearNodoDobleCliente(aux));
        }
        fclose(buf);
    }

    return lista;
}

nodoDobleCliente* pasarArchivoListaDobleClienteApellido(nodoDobleCliente *lista){

    FILE *buf = fopen(archivoClientes, "rb");
    stCliente aux;

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0){
            lista = agregarEnOrdenApellidoListaDobleCliente(lista, crearNodoDobleCliente(aux));
        }
        fclose(buf);
    }

    return lista;
}

nodoDobleCliente* pasarArchivoListaDobleClientePedidos(nodoDobleCliente *lista){

    FILE *buf = fopen(archivoClientes, "rb");
    stCliente aux;

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0){
            lista = agregarEnOrdenPedidosListaDobleCliente(lista, crearNodoDobleCliente(aux));
        }
        fclose(buf);
    }

    return lista;
}

void top10clientes(nodoDobleCliente *lista, int y, int i){

    if(lista){
        if(i < 10){
            mostrarClienteListado(lista->dato, y++);
            top10clientes(lista->siguiente, y, i+1);
        }
    }
}

void mostrarListaDobleClienteTodos(nodoDobleCliente *lista, int y){

    if(lista){
        mostrarClienteListado(lista->dato, y++);
        mostrarListaDobleClienteTodos(lista->siguiente, y);
    }
}

void mostrarListaDobleClienteAlta(nodoDobleCliente *lista, int y){

    if(lista){
        if(lista->dato.estado == 1)
            mostrarClienteListado(lista->dato, y++);
        mostrarListaDobleClienteAlta(lista->siguiente, y);
    }
}

void mostrarListaDobleClienteBaja(nodoDobleCliente *lista, int y){

    if(lista){
        if(lista->dato.estado == 0)
            mostrarClienteListado(lista->dato, y++);
        mostrarListaDobleClienteBaja(lista->siguiente, y);
    }
}

nodoDobleCliente* borrarListaDobleCliente(nodoDobleCliente *lista){

    nodoDobleCliente *proximo;

    while(lista){
        proximo = lista->siguiente;
        free(lista);
        lista = proximo;
    }

    return lista;
}
