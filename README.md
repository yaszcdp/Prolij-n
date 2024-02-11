# Prolijín
Prolijín es un proyecto de sistema para administración de empresas realizado en C que permite a los administrativos gestionar pedidos, clientes, proveedores, productos y la caja diaria. 

## Integrantes del proyecto
- <img src="https://img.shields.io/badge/Yas'z%20Escobar%20Tomé-Developer-blue" alt="Yas'z Escobar Tomé- Developer">
- <img src="https://img.shields.io/badge/Federico%20Gil%20de%20Muro-Developer-blue" alt="Federico Gil de Muro - Developer">
- <img src="https://img.shields.io/badge/Micaela%20Hermida-Developer-blue" alt="Micaela Hermida - Developer">
- <img src="https://img.shields.io/badge/Paula%20Bereilh-Developer-blue" alt="Paula Bereilh - Developer">

## Características principales

- Manejo de la Interfaz de Usuario: El sistema se destaca por su amigable experiencia de usuario, implementando la función gotoxy para la ubicación precisa en la consola. Esto mejora la estética y legibilidad de la información presentada al usuario durante la ejecución del programa.
  
- Gestión de Datos: El sistema permite agregar, editar, dar de alta/baja, consultar, filtrar y listar pedidos, productos, clientes y proveedores (y sus respectivas cuentas corrientes).

- Gestión de Caja: El sistema permite iniciar la caja, modificar el inicio y cierre, ver la caja de un día determinado permitiendo visualizar número de registro, tipo (si es un pago se mostrará el nombre del proveedor), monto y los acumuladores del día. 
  
- Almacenamiento de datos: Los datos del sistema se guardan y recuperan mediante archivos binarios, asegurando la persistencia de la información entre sesiones.

### Estructuras de Control y Funcionalidades

- Listas Doblemente Enlazadas: Utilizadas para gestionar eficientemente conjuntos de datos como clientes, productos y proveedores.

- Recursividad: Aplicada en diversas funciones para optimizar la manipulación de estructuras de datos complejas.

- Listas de Listas: Empleadas para organizar y relacionar datos de manera estructurada, como en el caso de las transacciones y las cuentas corrientes de los proveedores.


## Estructura del Proyecto
Prolijín está organizado en una estructura modular que facilita la comprensión y mantenimiento del código. A continuación, se presenta una descripción general de las principales estructuras y módulos utilizados en el sistema:

### Estructuras de Datos
- Clientes: Almacena la información de los clientes, como nombre, apellido, dirección, detalles de contacto y cantidades de pedidos realizados.

- Pedido: Contiene detalles sobre los pedidos, incluyendo productos, cantidades, estado del pedido, medio de pago e id del cliente.

- Producto: Describe las características de los productos, como nombre, marca, precio, categoría, proveedor, precio de costo y venta, y margen de ganancia.

- Caja: Registra las transacciones diarias, acumuladores y datos relacionados con la gestión de caja.

- Proveedor: Almacena la información de los proveedores, incluyendo detalles de contacto y transacciones realizadas (compras y pagos).

Otras estructuras como Domicilio, productoPedido, CompraVenta, celdaCaja, Acumulador, Transaccion, RegistroTransaccionProveedor, y Fecha complementan y facilitan la gestión de datos.

## Capturas de pantalla

### Menús
![menues](https://github.com/yaszcdp/Prolij-n/assets/106832395/68e40fdc-2bd9-433f-8e7a-cb380e5826cb)
*En la imagen se muestran distintas capturas de pantalla del menú principal y los secundarios de nuestro sistema de administración. Los usuarios deben ingresar el número correspondiente a la opción que deseen realizar y seguir las indicaciones respectivas.*

### Lista productos
![listaproductos](https://github.com/yaszcdp/Prolij-n/assets/106832395/9f8d158b-bc23-4726-8566-f8caec727d70)
*En la imagen se muestran las capturas de los pasos para listar productos según categoría.*

### Lista clientes
![listaclientes](https://github.com/yaszcdp/Prolij-n/assets/106832395/b51a7bb9-5ace-4657-a6a1-444eedcfe445)
*Esta captura de pantalla muestra el listado de clientes.*

### Pedido
![pedido](https://github.com/yaszcdp/Prolij-n/assets/106832395/9fb40946-394c-465c-a2ce-9fe91c41fcb9)
*En la imagen se muestra como cargar un pedido, primero se busca y confirma el cliente para luego buscar y cargar los productos y las cantidades respectivas. Al final pedirá el medio de pago y la confirmación o no de éste.*

### Edición
![editarcliente](https://github.com/yaszcdp/Prolij-n/assets/106832395/8f2af694-9092-4009-abaf-c5a0aa1804d1)
*En la imagen se muestra como editar un cliente modificando los datos en tiempo real, pudiendo descartar o salvar los cambios al final.*

### Caja
![caja](https://github.com/yaszcdp/Prolij-n/assets/106832395/52d6129c-28df-413f-8cc8-1cc07e09bf92)
*A la izquierda se muestra una captura de la impresión de la caja de un día determinado. A la derecha los acumuladores de dicho día.*

### Transacciones
![transacciones](https://github.com/yaszcdp/Prolij-n/assets/106832395/ee5f7167-b726-4b89-af57-3d5d94f2e52d)
*A la izquierda se muestra el listado de proveedores, su estados y los montos de sus cuentas, seguido del menú de Transacciones y el paso a paso para ingresar un pago al proveedor. A la izquierda el resultado almacenado automáticamente en las lista de proveedores y caja del día.*


## Configuración del proyecto, Compilación y Ejecución
El proyecto está configurado para compilarse y ejecutarse fácilmente utilizando un entorno de desarrollo compatible con C, como Code::Blocks. Sigue las siguientes instrucciones para clonar y ejecutar el sistema en tu entorno local.

1. Clona el repositorio del proyecto: `git clone https://github.com/tu-usuario/Prolij-n.git`
2. Abre el proyecto en tu entorno de desarrollo preferido, como <img src="https://img.shields.io/badge/Code::Blocks-red" alt="Code::Blocks"/>.
3. Ejecuta el compilador, click en el botón "Run and build" para iniciar el sistema.





  
