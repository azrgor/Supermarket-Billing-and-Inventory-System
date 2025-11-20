#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLIENTES 100
#define MAX_PRODUCTOS_FACTURA 20
#define MAX_PRODUCTOS_INVENTARIO 200
#define IVA 0.19f

//declaramos 3 estructuras que utilizará eel código
typedef struct{
	char nombre[50], codigo[10];
	float precio;
	int cantidad;
}producto;

typedef struct{
	char nombre[50], cedula[12], telefono[12];
}cliente;

typedef struct{
	int num_fact;
	char cedula[12];
	char codigoProducto[MAX_PRODUCTOS_FACTURA][10];
	int cantidadProducto[MAX_PRODUCTOS_FACTURA];
	int matrizVentas[MAX_PRODUCTOS_FACTURA][2]; 
	float subtotal, iva, total;
}factura;


//prototipos de los subpocesos
int buscarClientePorCedula(cliente c[], int totalClientes, char cedula[]);
int buscarProducto(producto p[], int totalProductos, char codigo[]);
void crearProducto(producto *p);
void eliminarProducto(producto p[], int *totalProductos);
void registrarCliente(cliente *c);
void imprimirCliente(cliente c[], int totalClientes);
void mostrarDisponibilidad(producto p[], int totalProductos);
void modificarCliente(cliente c[], int totalClientes);
void crearFactura(factura *f, cliente c[], int *totalClientes, producto p[], int totalProductos);
void inicializar(cliente c[], producto p[]);

//subproceso para inicializar 3 clientes y 5 productos de manera predeterminada
void inicializar(cliente c[], producto p[]){
	for (int i=0; i<MAX_CLIENTES;i++) strcpy(c[i].cedula, "0");
	for (int i=0; i<MAX_PRODUCTOS_INVENTARIO;i++) strcpy(p[i].codigo, "0");
	//for (int i=0; i<MAX_FACTURAS;i++) f[i].num_fact=0;
	
	//creamos tres clientes iniciales
	strcpy(c[0].cedula,"123"); strcpy(c[0].nombre,"Pedro Perez"); strcpy(c[0].telefono,"3151234567");
	strcpy(c[1].cedula,"223"); strcpy(c[1].nombre,"Marco Nava"); strcpy(c[1].telefono,"3107654321");
	strcpy(c[2].cedula,"323"); strcpy(c[2].nombre,"Pablo Suarez"); strcpy(c[2].telefono,"3111113344");
	//creamos 5 productos iniciales
	strcpy(p[0].nombre, "Manzana"); strcpy(p[0].codigo, "MANZ01"); p[0].precio = 1500; p[0].cantidad = 100;
	strcpy(p[1].nombre, "Leche"); strcpy(p[1].codigo, "LECH02"); p[1].precio = 2800; p[1].cantidad = 50;
	strcpy(p[2].nombre, "Pan"); strcpy(p[2].codigo, "PAN_03"); p[2].precio = 1000; p[2].cantidad = 200;
	strcpy(p[3].nombre, "Azúcar"); strcpy(p[3].codigo, "AZUC04"); p[3].precio = 1200; p[3].cantidad = 75;
	strcpy(p[4].nombre, "Arroz"); strcpy(p[4].codigo, "ARRO05"); p[4].precio = 1800; p[4].cantidad = 120;
}

//subproceso que retorna el índice del cliente (en la estructura cliente) que usaremos más adelante, esto es muy útil para buscar un cliente.
int buscarClientePorCedula(cliente c[], int totalClientes, char cedula[]){
	for(int i = 0; i<totalClientes; i++){
		if(strcmp(c[i].cedula, cedula) == 0){
			return i;
		}
	}
	return -1;
}

	//lo mismo quee el anterior, pero esta vez para buscar un producto haciendo uso de su código, si el código es igual al que se leyó retornará el índice del mismo.
int buscarProducto(producto p[], int totalProductos, char codigo[]){
	for(int i=0; i<totalProductos; i++){
		if(strcmp(p[i].codigo, codigo) == 0){
			return i;
		}
	}
	return -1;	
}

void crearProducto(producto *p){
	system ("cls");
	printf("\nCrear Nuevo Producto\n");
	printf("Nombre: ");
	while (getchar() != '\n');
	fgets(p->nombre, 50, stdin); //eliminamos el salto de línea
	p->nombre[strcspn(p->nombre, "\n")] = '\0'; //usamos strcspn para que lea los espacios de un char
	printf("Código: ");
	scanf("%9s", p-> codigo);
	printf("precio :");
	scanf("%f", &p->precio);
	printf("cantidad en inventario del producto: ");
	scanf("%d", &p->cantidad);
	printf("Producto agregado: %s (%s) precio: %.0f\n", p->nombre, p->codigo, p->precio);
}	

void eliminarProducto(producto p[], int *totalProductos){
	if(*totalProductos == 0){
		printf("\nNo hay productos en el inventario para eliminar.\n");
		return;
	}
	char codeP[10];
	printf("Productos disponibles:\n");
	mostrarDisponibilidad(p, *totalProductos);
	printf("\nEscriba el código del producto que desea eliminar: ");
	scanf("%9s", codeP);
	
	int indiceProd = buscarProducto(p, *totalProductos, codeP);
	if (indiceProd == -1){
		printf("El producto no existe");
		return;
	}
	
	printf("\nProducto encontrado:\n");
	printf("Nombre: %s\n", p[indiceProd].nombre);
	printf("Código: %s\n", p[indiceProd].codigo);
	printf("Precio: %.2f\n", p[indiceProd].precio);
	printf("Cantidad: %d\n\n", p[indiceProd].cantidad);
	//eliminamos el producto del array 
	for(int i = indiceProd; i < *totalProductos - 1; i++){
		p[i] = p[i + 1];
	}
	
	(*totalProductos)--;
}

void registrarCliente(cliente *c){
	system ("cls");
	printf("\nRegistrar Cliente\n");
	printf("Nombre: ");
	while (getchar() != '\n');
	fgets(c->nombre, 50, stdin);
	c->nombre[strcspn(c->nombre, "\n")] = '\0';
	printf("Cédula: ");
	scanf("%11s", c->cedula);
	printf("Teléfono: ");
	scanf("%11s", c->telefono);
}

void imprimirCliente(cliente c[], int totalClientes){
	system ("cls");
	if(totalClientes == 0){
		printf("\nNo hay clientes para mostrar.\n");
		return;
	}
	printf("\n+-------------------------------------------------------+\n");
	printf("|                   LISTA DE CLIENTES                   |\n");
	printf("+-------------------------------------------------------+\n");
	
	if(totalClientes == 0){
		printf("| No hay clientes registrados                   |\n");
		printf("+-----------------------------------------------+\n");
		return;
	}
	
	printf("| Nº | Nombre                 | Cédula     | Teléfono   |\n");
	printf("+----+------------------------+------------+------------+\n");
	
	for(int i = 0; i < totalClientes; i++){
		printf("| %-2d | %-22s | %-10s | %-10s |\n", i+1, c[i].nombre, c[i].cedula, c[i].telefono);
	}
	
	printf("+----+------------------------+------------+------------+\n");
	
}

	//este es el mismo imprimircliente pero sin limpiar la pantalla, el cual usamos en el main
void imprimirClienteSinCLS(cliente c[], int totalClientes){
	if(totalClientes == 0){
		printf("\nNo hay clientes para mostrar.\n");
		return;
	}
	
	printf("\n+-------------------------------------------------------+\n");
	printf("|                   LISTA DE CLIENTES                   |\n");
	printf("+-------------------------------------------------------+\n");
	printf("| Nº | Nombre                 | Cédula     | Teléfono   |\n");
	printf("+----+------------------------+------------+------------+\n");
	
	for(int i = 0; i < totalClientes; i++){
		printf("| %-2d | %-22s | %-10s | %-10s |\n", i+1, c[i].nombre, c[i].cedula, c[i].telefono);
	}
	
	printf("+----+------------------------+------------+------------+\n");
}

void mostrarDisponibilidad(producto p[], int totalProductos){
	system ("cls");
	if(totalProductos == 0){
		printf("\nNo hay productos en el inventario\n");
		return;
	}
	printf("\n+-------------------------------------------------------+\n");
	printf("|			INVENTARIO			|\n");
	printf("+-------------------------------------------------------+\n");
	
	if(totalProductos == 0){
		printf("| No hay productos en el inventario            |\n");
		printf("+-----------------------------------------------+\n");
		return;
	}
	
	printf("| Nº | Nombre                 | Código  | Precio | Cant |\n");
	printf("+----+------------------------+---------+--------+------+\n");
	
	for(int i = 0; i < totalProductos; i++){
		printf("| %-2d | %-22s | %-7s | %-6.2f | %-3d |\n", i+1, p[i].nombre, p[i].codigo, p[i].precio, p[i].cantidad);
	}
	
	printf("+----+------------------------+---------+--------+------+\n");
	
	
}

void mostrarDisponibilidadSinCLS(producto p[], int totalProductos){
	if(totalProductos == 0){
		printf("\nNo hay productos en el inventario\n");
		return;
	}
	printf("\n+-------------------------------------------------------+\n");
	printf("|			INVENTARIO			|\n");
	printf("+-------------------------------------------------------+\n");
	
	if(totalProductos == 0){
		printf("| No hay productos en el inventario            |\n");
		printf("+-----------------------------------------------+\n");
		return;
	}
	
	printf("| Nº | Nombre                 | Código  | Precio | Cant |\n");
	printf("+----+------------------------+---------+--------+------+\n");
	
	for(int i = 0; i < totalProductos; i++){
		printf("| %-2d | %-22s | %-7s | %-6.2f | %-3d |\n", i+1, p[i].nombre, p[i].codigo, p[i].precio, p[i].cantidad);
	}
	
	printf("+----+------------------------+---------+--------+------+\n");
	
	
}
	
	
void modificarCliente(cliente c[], int totalClientes){
	if(totalClientes == 0){
		printf("\nNo hay clientes registrados.\n");
		return;
	}
	char ced[12];
	imprimirClienteSinCLS(c, totalClientes);
	printf("\nIngrese la cédula del cliente a modificar: ");
	scanf("%11s", ced);
	
	int indic = buscarClientePorCedula(c, totalClientes, ced);
	if(indic == -1){
		printf("Cliente no encontrado.\n");
		return;
	}
	
	printf("Cliente encontrado: Nombre actual: %s - Tel actual: %s - Cédula: %s\n", c[indic].nombre, c[indic].telefono, c[indic].cedula);
	
	int opcion;
	printf("¿Qué desea cambiar del cliente: %s?\n1. Modificar nombre\n2. Modificar cédula\n3. Modificar teléfono\n", c[indic].nombre);
	scanf("%d", &opcion);
	
	switch(opcion){
	case 1:
		printf("Nuevo nombre: ");
		while (getchar() != '\n');
		fgets(c[indic].nombre, 50, stdin);
		c[indic].nombre[strcspn(c[indic].nombre, "\n")] = '\0';
		printf("Nombre actualizado corréctamente.\n");
		break;
	case 2:
		printf("Nueva cédula: ");
		scanf("%11s", c[indic].cedula);
		printf("Cédula actualizada exitósamente.\n");
		break;
	case 3:
		printf("Nuevo teléfono: ");
		scanf("%11s", c[indic].telefono);
		printf("Teléfono actualizado exitósamente.\n");
		break;
	default:
		printf("Opción inválida");
		return;
	}
}

void mostrarMatrizVentas(factura *f, int numProductos, producto p[], int totalProductos) {
	system("cls");
	
	printf("+-------------------------------------------------------------+\n");
	printf("|                 MATRIZ DE VENTAS DEL DIA                    |\n");
	printf("+-------------------------------------------------------------+\n");
	printf("| Producto               | Cantidad         | Subtotal        |\n");
	printf("+-------------------------------------------------------------+\n");
	
	for (int i = 0; i < numProductos; i++) {
		
		if (f->cantidadProducto[i] > 0) {
			
			// Buscar el producto REAL por su código
			int idx = buscarProducto(p, totalProductos, f->codigoProducto[i]);
			
			char nombreProd[50];
			if (idx != -1)
				strcpy(nombreProd, p[idx].nombre); // nombre del inventario
			else
				strcpy(nombreProd, "DESCONOCIDO");
			
			printf("| %-22s | %-15d | %-15d |\n",
				   nombreProd,                    // NOMBRE REAL
				   f->matrizVentas[i][0],         // cantidad
					   f->matrizVentas[i][1]);        // subtotal
		}
	}
	
	printf("+-------------------------------------------------------------+\n");
	system("pause");
}



void crearFactura(factura *f, cliente c[], int *totalClientes, producto p[], int totalProductos){
	system ("cls");
	FILE *fptr;
	static int consecutivoFactura = 1;
	f->num_fact = consecutivoFactura++;
	
	char ced[12];
	char code[10];
	int numProductos = 0;
	f->subtotal = 0;
	
	//inicializar la matriz bidimensional
	for (int i = 0; i < MAX_PRODUCTOS_FACTURA; i++) {
		for (int j = 0; j < 2; j++) {
			f->matrizVentas[i][j] = 0;
		}
	}
	
	printf("\n========== CREAR FACTURA ==========\n");
	imprimirClienteSinCLS(c, *totalClientes);
	printf("Ingrese la cédula del cliente: ");
	scanf("%11s", ced);
	
	int indiceCliente = buscarClientePorCedula(c, *totalClientes, ced);
	
	// --- SI EL CLIENTE NO EXISTE ---
	if (indiceCliente == -1){
		int opcion;
		printf("\nEl cliente no existe.\n");
		printf("1. Crear cliente\n");
		printf("2. Continuar como anonimo\n");
		printf("3. Cancelar factura\n");
		printf("Seleccione una opción: ");
		scanf("%d", &opcion);
		
	if (opcion == 1){
		printf("\n--- Registrar nuevo cliente ---\n");
		registrarCliente(&c[*totalClientes]);
		(*totalClientes)++;
		indiceCliente = *totalClientes - 1;
		printf("Cliente creado exitosamente.\n");
	}
	else if (opcion == 2){
		strcpy(f->cedula, "ANONIMO");
		printf("\nFacturando como cliente ANONIMO.\n");
	}
	else{
		printf("\nFactura cancelada.\n");
		return;
	}
}
	
	//si el cliente no es anónimo
	if (indiceCliente != -1){
		strcpy(f->cedula, c[indiceCliente].cedula);
		printf("\nFacturando a: %s\n", c[indiceCliente].nombre);
	}
	
	// --- REGISTRO DE PRODUCTOS ---
	while (numProductos < MAX_PRODUCTOS_FACTURA){
		mostrarDisponibilidadSinCLS(p, totalProductos);
		printf("\nIngrese código del producto comprado (0 para terminar): ");
		scanf("%9s", code);
		
		if (strcmp(code, "0") == 0){
			break;
		}
		
		int idxP = buscarProducto(p, totalProductos, code);
		if (idxP == -1){
			printf("Ese producto no existe.\nPorfavor, ingrese un producto válido.");
			continue;
		}
		
		printf("Producto: %s | Precio %.2f | Stock: %d\n", p[idxP].nombre, p[idxP].precio, p[idxP].cantidad);
		
		int cant;
		printf("Cantidad a comprar: ");
		scanf("%d", &cant);
		
		if (cant <= 0 || cant > p[idxP].cantidad){
			printf("Cantidad inválida o insuficiente.\n");
			continue;
		}
		
		// Guardar en factura
		strcpy(f->codigoProducto[numProductos], code);
		f->cantidadProducto[numProductos] = cant;
		
		//Guardar en la matriz bidimensional de ventas
		f->matrizVentas[numProductos][0] = cant;
		f->matrizVentas[numProductos][1] = p[idxP].precio * cant;
		
		// Actualizar subtotal
		f->subtotal += p[idxP].precio * cant;
		
		// Restar del inventario
		p[idxP].cantidad -= cant;
		
		numProductos++;
		
		printf("Producto agregado correctamente.\n");
	}
	
	// --- CALCULAR TOTALES ---
	f->iva = f->subtotal * IVA;
	f->total = f->subtotal + f->iva;
	
	system ("cls");
	
	//CREACION FACTURA COMO .txt
	
	char nombreArchivo[100];
	sprintf(nombreArchivo, "factura%d_%s.txt", f->num_fact, c[indiceCliente].nombre);
	
	fptr = fopen(nombreArchivo, "w");
	if (fptr == NULL) {
		printf("Error creando la factura\n");
		return;
	}
	
	
	fprintf(fptr, "\n+-----------------------------------------------+\n");
	fprintf(fptr, "|                    FACTURA                    |\n");
	fprintf(fptr, "+-----------------------------------------------+\n");
	
	if(strcmp(f->cedula, "ANONIMO") == 0){
		fprintf(fptr, "| Cliente: ANONIMO                              |\n");
	} else {
		fprintf(fptr, "| Cliente : %-34s  |\n", c[indiceCliente].nombre);
		fprintf(fptr, "| Cédula  : %-34s  |\n", c[indiceCliente].cedula);
		fprintf(fptr, "| Teléfono: %-34s  |\n", c[indiceCliente].telefono);
	}
	
	fprintf(fptr, "+-----------------------------------------------+\n");
	fprintf(fptr, "| Nº | Producto               | Cant | Precio   |\n");
	fprintf(fptr, "+----+------------------------+------+----------+\n");
	
	for (int i = 0; i < numProductos; i++){
		int idx = buscarProducto(p, totalProductos, f->codigoProducto[i]);
		fprintf(fptr, "| %2d | %-21s | %5d | %8.2f |\n", i+1, p[idx].nombre, f->cantidadProducto[i], p[idx].precio);
	}
	
	fprintf(fptr, "+-----------------------------------------------+\n");
	fprintf(fptr, "| Subtotal:  %-34.2f |\n", f->subtotal);
	fprintf(fptr, "| IVA (19%%): %-34.2f |\n", f->iva);
	fprintf(fptr, "| TOTAL:     %-34.2f |\n", f->total);
	fprintf(fptr, "+-----------------------------------------------+\n");
	fclose(fptr);
	
	fptr=fopen(nombreArchivo, "r"); //open for reading
	if (fptr == NULL){
		printf("Error abriendo el archivo para lectura\n");
		return;
	}
	char linea[100];
	printf("Contenido de factura:\n");
	while (fgets(linea, sizeof(linea), fptr)) {
		printf("%s", linea);
	}
	fclose(fptr); // close after reading
	
	printf("\nFactura generada exitosamente.\n Presione ENTER para regresar al menú: ");
	int d;
	while ((d = getchar()) != '\n' && d != EOF) {}
	getchar();
	system("cls");
	
}
int main(){
	cliente c[MAX_CLIENTES];
	producto p[MAX_PRODUCTOS_INVENTARIO];
	factura f;
	inicializar(c,p);
	int totalClientes = 3, totalProductos = 5;
	int opcion;
	
	do {
		printf("\n+========================================+\n");
		printf("|           MENU PRINCIPAL               |\n");
		printf("+========================================+\n");
		printf("| 1. Registrar cliente                   |\n");
		printf("| 2. Mostrar clientes                    |\n");
		printf("| 3. Modificar cliente                   |\n");
		printf("| 4. Crear producto                      |\n");
		printf("| 5. Mostrar inventario                  |\n");
		printf("| 6. Eliminar producto                   |\n");
		printf("| 7. Crear factura                       |\n");
		printf("| 8. Mostrar ventas                      |\n");
		printf("| 0. Salir                               |\n");
		printf("+========================================+\n");
		printf("Seleccione una opción: ");
		scanf("%d", &opcion);
		
		switch(opcion) {
		case 1:
			registrarCliente(&c[totalClientes]);
			totalClientes++;
			break;
		case 2:
			imprimirCliente(c, totalClientes);
			break;
		case 3:
			modificarCliente(c, totalClientes);
			break;
		case 4:
			crearProducto(&p[totalProductos]);
			totalProductos++;
			break;
		case 5:
			mostrarDisponibilidad(p, totalProductos);
			break;
		case 6:
			eliminarProducto(p, &totalProductos);
			break;
		case 7:
			crearFactura(&f, c, &totalClientes, p, totalProductos);
			break;
		case 8:
			mostrarMatrizVentas(&f, MAX_PRODUCTOS_FACTURA, p, totalProductos);			
			break;
		case 0:
			printf("+-------------------------+\n");
			printf("|Saliendo del sistema...  |\n");
			printf("+-------------------------+\n");
			break;
		default:
			printf("Opción inválida.\n");
		}
	} while(opcion != 0);
	
	return 0;
}
