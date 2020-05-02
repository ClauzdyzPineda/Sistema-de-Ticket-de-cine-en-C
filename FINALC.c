#include <stdio.h>
#include <stdlib.h>

#include <string.h> /* gets, strcmp */

#define USUARIO "c"
#define CLAVE "java"

#define LONGITUD 80

//Definir la estructura a utilizar
typedef struct
{
	char nombreClie[50];
	char email[50];
	char pass[50];
	int codigoPeli;
	char tituloPeliculas[100];
	char generoPelicula[100];
	char fechaProgramada[10];
	char horario[10];
	char duracionPeli[10];
	int nSalas, capacidadSalas;
	struct Nodo *sgte;
} Nodo;

//Crear punteros para el primero y ultimo elemento de la lista
Nodo *primero = NULL;
Nodo *ultimo = NULL;

int inicio()
{
	char usuario[LONGITUD + 1];
	char clave[LONGITUD + 1];
	int intento = 0;
	int ingresa = 0;
	char caracter;
	int i = 0;

	do
	{
		i = 0;
		system("cls");
		printf("\n\t\t\tINICIO DE SESION\n");
		printf("\t\t\t---------------\n");
		printf("\n\tUSUARIO: ");
		gets(usuario);
		printf("\tCLAVE: ");
		while (caracter = getch())
		{
			if (caracter == 13)
			{
				clave[i] = '\0';
				break;
			}
			else if (caracter == 8)
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");
				}
			}
			else
			{
				if (i < LONGITUD)
				{
					printf("*");
					clave[i] = caracter;
					i++;
				}
			}
		}

		if (strcmp(usuario, USUARIO) == 0 && strcmp(clave, CLAVE) == 0)
		{
			ingresa = 1;
		}
		else
		{
			printf("\n\tUsuario y/o clave son incorrectos\n");
			intento++;
			getchar();
		}

	} while (intento < 3 && ingresa == 0);

	if (ingresa == 1)
	{
		printf("\n\tBienvenido al Sistema\n");
	}
	else
	{
		printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
	}

	return 0;
}

void MenuCliente(void)
{

	system("cls");
	printf("\n\n\t<<INICIO DE SISTEMA PARA VENTAS DE TICKETS>>\n");
	printf("\n\t==============================================\n");
	printf("\n\tNo tienes cuenta?\n");
	printf("\n\tcrea una para poder comprar ticket en la opcion 1...\n\n");
	printf("\n\t\t\t   *  *");
	printf("\n\t\t\t   *  *");
	printf("\n\t\t\t   *  *");
	printf("\n\t\t\t   *  *");
	printf("\n\t\t\t****  ****");
	printf("\n\t\t\t *      *");
	printf("\n\t\t\t  *    *");
	printf("\n\t\t\t   *  *");
	printf("\n\t\t\t    *\n");
	printf("\t********************************************\n");
	printf("\t*BIENVENIDOS A COMPRAS DE TICKET PARA CINE *\n");
	printf("\t********************************************\n");
	printf("\t*      [1] Registro de clientes            *\n");
	printf("\t*      [2] INICIAR SESION                  *\n");
	printf("\t*      [3] Iniciar como ADMINISTRADOR      *\n");
	printf("\t*      [4] Salir                           *\n");
	printf("\t*                                          *\n");
	printf("\t********************************************\n");
}

void SubMenuCli(char *nameSubMenus)
{

	system("cls");
	// 43 espacios
	//      0123456789012345678901234567890123456789012
	printf("\t********************************************\n");
	printf("\t*              Menu secundario             *\n");
	printf("\t* %s", nameSubMenus);
	int i;
	for (i = strlen(nameSubMenus); i <= 39; i++)
	{
		printf(" ");
	}
	printf(" *\n");
	printf("\t********************************************\n");
	printf("\t*  [1] Ingresa tus datos personales        *\n");
	printf("\t*  [2] Modificar  datos                    *\n");
	printf("\t*  [3] Guardar informacion                 *\n");
	printf("\t*  [4] Ver datos ingresados                *\n");
	printf("\t*  [5] Regresar                            *\n");
	printf("\t********************************************\n");
}

void Menu(void)
{

	system("cls");

	printf("\t********************************************\n");
	printf("\t*BIENVENIDOS A COMPRAS DE TICKET PARA CINE *\n");
	printf("\t********************************************\n");
	printf("\t*  [1] Registro de Peliculas               *\n");
	printf("\t*  [2] Registro de Tickets                 *\n");
	printf("\t*  [3] Registro de Salas                   *\n");
	printf("\t*  [4] Salir                               *\n");
	printf("\t********************************************\n");
}

void MenuVentas(void)
{

	system("cls");

	printf("\nQuieres comprar tu ticket para disfrutar tu pelicula?\n");

	printf("\t********************************************\n");
	printf("\t*       COMPRAS TU TICKET PARA CINE        *\n");
	printf("\t********************************************\n");
	printf("\t*  [1] Ver peliculas disponible            *\n");
	printf("\t*  [2] Comprar Ticket                      *\n");
	printf("\t*  [4] Salir                               *\n");
	printf("\t********************************************\n");
}

void SubMenuCompra(char *nameSubMenu)
{

	system("cls");
	// 43 espacios
	//      0123456789012345678901234567890123456789012
	printf("\t********************************************\n");
	printf("\t*   Verifica tus datos para comprar tiket  *\n");
	printf("\t* %s", nameSubMenu);
	int i;
	for (i = strlen(nameSubMenu); i <= 39; i++)
	{
		printf(" ");
	}
	printf(" *\n");
	printf("\t********************************************\n");
	printf("\t*  [1] Comprar                             *\n");
	printf("\t*  [2] pagar                               *\n");
	printf("\t********************************************\n");
}

void SubMenu(char *nameSubMenu)
{

	system("cls");
	// 43 espacios
	//      0123456789012345678901234567890123456789012
	printf("\t********************************************\n");
	printf("\t*    Ingresa tus datos para registrarte    *\n");
	printf("\t* %s", nameSubMenu);
	int i;
	for (i = strlen(nameSubMenu); i <= 39; i++)
	{
		printf(" ");
	}
	printf(" *\n");
	printf("\t********************************************\n");
	printf("\t*  [1] Agregar                             *\n");
	printf("\t*  [2] Modificar                           *\n");
	printf("\t*  [3] Buscar                              *\n");
	printf("\t*  [4] Mostrar                             *\n");
	printf("\t*  [5] Guardar informacion                 *\n");
	printf("\t*  [6] Recuperar informacion               *\n");
	printf("\t*  [7] Eliminar                            *\n");
	printf("\t*  [8] Regresar                            *\n");
	printf("\t********************************************\n");
}

int main(int argc, char *argv[])
{
	int sistemExit = 0;
	while (sistemExit == 0)
	{

		int menuCli, subMclie;

		MenuCliente();
		scanf("%d", &menuCli);
		switch (menuCli)
		{
		case 1:
			SubMenuCli("       MENU DE REGISTRO DE CLIENTES");
			scanf("%d", &subMclie);

			switch (subMclie)
			{
			case 1:
				system("cls");
				printf("\nRegistro de clientes\n");
				agregarClientes();
				system("pause");
				break;
			case 2:
				system("cls");
				printf("\nModificar Clientes\n");
				modificarCli();
				system("pause");
				break;
			case 3:
				system("cls");
				printf("\nGuardar informacion de Clientes\n");
				guardarInfoCli();
				system("pause");
				break;
			case 4:
				system("cls");
				printf("\nMostar Clientes\n");
				MostrarCliente();
				system("pause");
				break;

			default:
				system("cls");
				break;
			}
			break;

		case 2:
			system("cls");
			printf("\nInicio de sesion\n");
			inicio();

			int opMenuVentas, opSubMenuCompra;
			MenuVentas();
			scanf("%d", &opMenuVentas);
			switch (opMenuVentas)
			{
			case 2:
				SubMenuCompra("    MENU DE COMPRAS DE TICKETS");
				scanf("%d", &opSubMenuCompra);
				switch (opSubMenuCompra)
				{
				case 1:
					system("cls");
					printf("\n Comprar \n");

					system("pause");
					break;
				case 2:
					system("cls");
					printf("\nPagar\n");

					system("pause");
					break;

				default:
					system("cls");
					break;
				}
				break;

			default:
				system("cls");
				break;
			}
			break;

		case 3:
			system("cls");
			system("\nInicio de administrador");

			int opMenu, opSubMenu;
			Menu();
			scanf("%d", &opMenu);
			switch (opMenu)
			{
			case 1:
				SubMenu("    MENU DE REGISTRO DE PELICULAS");
				scanf("%d", &opSubMenu);
				switch (opSubMenu)
				{
				case 1:
					system("cls");
					printf("\nAgregar pelicula\n");
					agregarPeliculas();
					system("pause");
					break;
				case 2:
					system("cls");
					printf("\nModificar pelicula\n");
					modificarPeliculas();
					system("pause");
					break;

				case 3:
					system("cls");
					printf("\nBuscar pelicula\n");
					buscarPeliculas();
					system("pause");
					break;
				case 4:
					system("cls");
					printf("\nMostrar pelicula\n");
					mostrarPeliculas();
					system("pause");
					break;
				case 5:
					system("cls");
					printf("\nGuardar informacion de peliculas\n");
					guardarInfoPeli();
					system("pause");
					break;
				case 6:
					system("cls");
					printf("\nRecuperar informacion de peliculas\n");
					system("pause");
					break;
				case 7:
					system("cls");
					printf("\nEliminar pelicula\n");
					eliminarPelicula();
					system("pause");
					break;
				case 8:
					system("cls");
					printf("\nVolver a inicio\n");
					Menu();
					system("pause");
					break;

				default:
					system("cls");
					break;
				}
				break;

			case 2:
				SubMenu("MENU DE REGISTRO DE TICKETS");
				scanf("%d", &opSubMenu);
				switch (opSubMenu)
				{
				case 1:
					system("cls");
					printf("\nAgregar Tickets\n");
					system("pause");
					break;
				case 2:
					system("cls");
					printf("\nModificar Tickets\n");
					system("pause");
					break;
				case 3:
					system("cls");
					printf("\nBuscar Tickets\n");
					system("pause");
					break;

				case 4:
					system("cls");
					printf("\nMostrar Tickets\n");

					system("pause");
					break;
				case 5:
					system("cls");
					printf("\nEliminar Tickets\n");
					system("pause");
					break;
				default:
					system("cls");
					break;
				}
				break;
			case 3:
				SubMenu("    MENU DE REGISTRO DE SALAS");
				scanf("%d", &opSubMenu);
				switch (opSubMenu)
				{
				case 1:
					system("cls");
					printf("\nAgregar Salas\n");
					agregarSalas();
					system("pause");
					break;
				case 2:
					system("cls");
					printf("\nModificar Salas\n");
					modificarSalas();
					system("pause");
					break;
				case 3:
					system("cls");
					printf("\nBuscar Salas\n");
					buscarSalas();
					system("pause");
					break;
				case 4:
					system("cls");
					printf("\nMostrar Salas\n");
					mostrarSalas();
					system("pause");
					break;

				case 5:
					system("cls");
					printf("\nGuardar informacion de peliculas\n");
					guardarInfoSalas();
					system("pause");
					break;
				case 6:
					system("cls");
					printf("\nRecuperar informacion de peliculas\n");

					system("pause");
					break;
				case 7:
					system("cls");
					printf("\nEliminar Salas\n");
					eliminarSalas();
					system("pause");
					break;

				case 8:
					system("cls");
					printf("\nVolver a inicio\n");
					Menu();
					system("pause");
					break;
				}
				break;

			default:
				system("cls");
				break;
			}
			break;

		case 4:
			sistemExit = 1;
			break;

		default:
			printf("Opcion incorrecta");
			system("pause");
			break;
		}
	}
	return 0;
}

//Funcion para agregar elementos a CLIENTES
void agregarClientes(void)
{
	//Reservar en memoria el nuevo nodo
	Nodo *nodo = malloc(sizeof(Nodo));
	//Limpiar pantalla
	system("cls");
	//Solicitar los valores del nodo
	printf("\n\n=========================================================\n");
	printf(" \n             REGISTRAR DATOS DE CLIENTES");
	printf("\n\n=========================================================\n");
	printf("Ingrese su nombre completo: ");
	scanf(" %[^\n]", nodo->nombreClie);
	printf("Ingrese su correo: ");
	scanf(" %[^\n]", nodo->email);
	printf("Cree una clave: ");
	scanf(" %s", nodo->pass);
	//Apuntar a NULL el siguiente elemento de la lista
	nodo->sgte = NULL;
	//Preguntar si la lista esta vacia
	if (primero == NULL)
	{
		primero = nodo;
		ultimo = nodo;
	}
	else
	{
		ultimo->sgte = nodo;
		ultimo = nodo;
	}
}

//GUARDAR DATOS DE CLIENTES
void guardarInfoCli(void)
{

	system("cls");

	Nodo *i = primero;

	if (i != NULL)
	{

		printf("\n\tGUARDAR INFORMACION DE CLIENTES\n\n");
		FILE *fichero;
		fichero = fopen("clientes.txt", "wt");
		fprintf(fichero, "%s", "DATOS DE CLIENTES\n");
		while (i != NULL)
		{
			fprintf(fichero, "\nNombre de cliente: %s", i->nombreClie);
			fprintf(fichero, "\nCorreo electronico: %s%s", i->email);
			fprintf(fichero, "%s%s", "\n----------------------------------------------\n");
			i = i->sgte;
		}

		fclose(fichero);

		printf("\n\n\t<<INFORMACION GUARDADA CON EXITO>>\n\n");
		system("pause");
	}
	else
	{
		printf("\n\tREGISTROS NO ENCONTRADOS\n");
		system("pause");
	}
}

void MostrarCliente(void)
{

	system("cls");

	Nodo *i = primero;

	if (i != NULL)
	{

		printf("\n\t\t\tREGISTROS EN EL SISTEMA\n");
		printf("\n");
		printf("*-------------------------------------------------------------------*\n");
		printf("|  Nombre de cliente                 |      Correo electronico      |\n");

		while (i != NULL)
		{

			int nombre_c, correo_c = 0;
			char cadena[10];
			char *cod = sprintf(cadena, "%u", i->nombreClie);

			printf("| %s", i->nombreClie);
			for (nombre_c = strlen(i->nombreClie); nombre_c < 35; nombre_c++)
			{
				printf(" ");
			}
			printf("| %s", i->email);
			for (correo_c = strlen(i->email); correo_c <= 27; correo_c++)
			{
				printf(" ");
			}
			printf(" |\n");
			i = i->sgte;
		}

		printf("*-------------------------------------------------------------------*\n");
		system("pause");
	}
	else
	{
		printf("\nREGISTROS NO ENCONTRADOS\n");
		system("pause");
	}
}

//Funcion para modificar CLIENTES
void modificarCli()
{
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Variable local
	char email[100];
	int encontrado = 0; //Indicar si el nodo fue encontrado

	//Preguntar si la lista esta vacia
	if (i != NULL)
	{
		printf("\n\n=========================================================\n");
		printf(" \n                MODIFICAR DATOS DE CLIENTES");
		printf("\n\n=========================================================\n");

		//PEDIR el valor a buscar en la lista
		printf("\nIngrese el correo de la cuenta a modificar: ");
		scanf(" %[^\n]", &email);

		while (i != NULL)
		{
			//Preguntar si son iguales los valores del nodo con el digitado
			if (strcmp(i->email, email) == 0)
			{	//Si es valor caracter
				//if(i->codigo == descripcion){//Solo si es para valor numerico
				printf("\nIngrese el nombre a modificar: ");
				scanf(" %[^\n]", i->nombreClie);
				printf("\nIngrese el correo a modificar a modificar: ");
				scanf(" %[^\n]", i->email);

				printf("\n\nSu informacion actualizada es:");
				printf("\nNombre: %s", i->email);
				printf("\nDireccion: %s", i->nombreClie);
				printf("\n\n=========================================================\n");
				printf("\n");
				encontrado = 1; //Indicar que el nodo fue encontrado
				break;
			} //Fin de if

			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		} //Fin de while
	}
	else
	{
		printf("\n\n***NO HAY ELEMENTOS PARA MODIFICAR***\n");
	}
}

//Funcion para agregar elementos a PELICULAS
void agregarPeliculas(void)
{
	//Reservar en memoria el nuevo nodo
	Nodo *nodo = malloc(sizeof(Nodo));
	//Limpiar pantalla
	system("cls");
	//Solicitar los valores del nodo
	printf("\n**************************************\n");
	printf("\nREGISTRO DE DATOS DE PELICULAS \n");
	printf("\n**************************************\n");
	printf("Digite codigo: ");
	scanf("%d", &nodo->codigoPeli);
	printf("Digite titulo de pelicula: ");
	scanf(" %[^\n]", nodo->tituloPeliculas);
	printf("Digite genero de pelicula: ");
	scanf(" %[^\n]", nodo->generoPelicula);
	printf("Digite fecha programada: ");
	scanf(" %s", nodo->fechaProgramada);
	printf("Digite hora programada: ");
	scanf(" %[^\n]", nodo->horario);
	printf("Digite duracion de la pelicula: ");
	scanf(" %[^\n]", nodo->duracionPeli);
	//Apuntar a NULL el siguiente elemento de la lista
	nodo->sgte = NULL;
	//Preguntar si la lista esta vacia
	if (primero == NULL)
	{
		primero = nodo;
		ultimo = nodo;
	}
	else
	{
		ultimo->sgte = nodo;
		ultimo = nodo;
	}
}

//Funcion para mostrar PELICULAS
void mostrarPeliculas(void)
{
	system("cls");

	Nodo *i = primero;

	if (i != NULL)
	{

		printf("\nREGISTROS EN EL SISTEMA\n");
		printf("\n");
		printf("*--------------------------------------------------------------------------------------------------------------------------------------*\n");
		printf("|  Codigo    |     Titulo de pelicula          |      Genero      |     Fecha de presentacion    |       Horario      |    Duracion    |\n");

		while (i != NULL)
		{

			int codigo_p, titulo_peli = 0, genero_peli = 0, fecha_peli = 0, horario_peli = 0, duracion_peli = 0;
			char cadena[10];
			char *cod = sprintf(cadena, "%u", i->codigoPeli);

			printf("| %d", i->codigoPeli);

			for (codigo_p = cod; codigo_p < 11; codigo_p++)
			{
				printf(" ");
			}
			printf("| %s", i->tituloPeliculas);
			for (titulo_peli = strlen(i->tituloPeliculas); titulo_peli <= 31; titulo_peli++)
			{
				printf(" ");
			}
			printf("| %s", i->generoPelicula);
			for (genero_peli = strlen(i->generoPelicula); genero_peli <= 16; genero_peli++)
			{
				printf(" ");
			}
			printf("| %s", i->fechaProgramada);
			for (fecha_peli = strlen(i->fechaProgramada); fecha_peli <= 28; fecha_peli++)
			{
				printf(" ");
			}
			printf("| %s", i->horario);
			for (horario_peli = strlen(i->horario); horario_peli <= 18; horario_peli++)
			{
				printf(" ");
			}
			printf("| %s", i->duracionPeli);
			for (duracion_peli = strlen(i->duracionPeli); duracion_peli <= 12; duracion_peli++)
			{
				printf(" ");
			}
			printf("  |\n");
			i = i->sgte;
		}

		printf("*--------------------------------------------------------------------------------------------------------------------------------------*\n");
		system("pause");
	}
	else
	{
		printf("\nREGISTROS NO ENCONTRADOS\n");
		system("pause");
	}
} //Fin de mostrarNodo

void guardarInfoPeli(void)
{

	system("cls");

	Nodo *i = primero;

	if (i != NULL)
	{

		printf("\nGUARDAR INFORMACION DE PELICULAS\n\n");
		FILE *fichero;
		fichero = fopen("peliculas.txt", "wt");
		fprintf(fichero, "%s", "DATOS DE PELICULAS\n");
		while (i != NULL)
		{
			fprintf(fichero, "\nCodigo de sala: %d", i->codigoPeli);
			fprintf(fichero, "\nTitulo de pelicula: %s%s", i->tituloPeliculas);
			fprintf(fichero, "\nGenero de pelicula:  %s%s", i->generoPelicula);
			fprintf(fichero, "\nFecha programada: %s%s", i->fechaProgramada);
			fprintf(fichero, "\nHorario: %s%s", i->horario);
			fprintf(fichero, "\nDuracion de pelicula: %s%s", i->duracionPeli);
			fprintf(fichero, "%s%s", "\n--------------------------------------\n");
			i = i->sgte;
		}

		fclose(fichero);

		printf("\n\n<<INFORMACION GUARDADA CON EXITO>>\n\n");
		system("pause");
	}
	else
	{
		printf("\nREGISTROS NO ENCONTRADOS\n");
		system("pause");
	}
}

//Funcion para modificar PELICULAS
void modificarPeliculas()
{
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Variable local
	char tituloPeliculas[100];
	int encontrado = 0; //Indicar si el nodo fue encontrado

	//Preguntar si la lista esta vacia
	if (i != NULL)
	{
		printf("\n\n=====================================\n");
		printf("MODIFICAR DATOS DE PELICULAS");
		printf("\n\n=====================================\n");

		//PEDIR el valor a buscar en la lista
		printf("\nIngrese el titulo de pelicula a modificar: ");
		scanf(" %[^\n]", &tituloPeliculas);

		while (i != NULL)
		{
			//Preguntar si son iguales los valores del nodo con el digitado
			if (strcmp(i->tituloPeliculas, tituloPeliculas) == 0)
			{	//Si es valor caracter
				//if(i->codigo == descripcion){//Solo si es para valor numerico
				printf("\nIngrese el nuevo codigo: ");
				scanf("%d", &i->codigoPeli);
				printf("\nIngrese un el titulo de la pelicula a modificar: ");
				scanf(" %[^\n]", i->tituloPeliculas);
				printf("\nIngrese el genero de pelicula a modificar: ");
				scanf(" %[^\n]", i->generoPelicula);
				printf("\nIngrese la fecha de presentacion a modificar: ");
				scanf("%s", i->fechaProgramada);
				printf("\nIngrese el horario a modificar: ");
				scanf("%s", i->horario);
				printf("\nIngrese la duracion de pelicula a modificar: ");
				scanf("%s", i->duracionPeli);

				printf("\n\nSu informacion actualizada es");
				printf("\nCodigo: %d", i->codigoPeli);
				printf("\nNombre: %s", i->tituloPeliculas);
				printf("\nDireccion: %s", i->generoPelicula);
				printf("\nFecha de presentacion: %s", i->fechaProgramada);
				printf("\nHorario: %s", i->horario);
				printf("\nDuracion: %s", i->duracionPeli);
				printf("\n\n=====================================\n");
				printf("\n");
				encontrado = 1; //Indicar que el nodo fue encontrado
				break;
			} //Fin de if

			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		} //Fin de while
	}
	else
	{
		printf("\n\n***NO HAY ELEMENTOS PARA MODIFICAR***\n");
	}
}

//Funcion para buscar PELICULAS
void buscarPeliculas(void)
{
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Variable local
	char tituloPeliculas[100];
	int encontrado = 0; //Indicar si el nodo fue encontrado

	//Preguntar si la lista esta vacia
	if (i != NULL)
	{
		printf("\n\n**************************************\n");
		printf("\nBUSQUEDA DE PELICULAS\n");
		printf("\n**************************************\n");

		//PEDIR el valor a buscar en la lista
		printf("\nDigite el titulo de la pelicula a buscar: ");
		scanf(" %[^\n]", &tituloPeliculas);

		//RECORRIENDO LA LISTA
		while (i != NULL)
		{
			//Preguntar si son iguales los valores del nodo con el digitado
			if (strcmp(i->tituloPeliculas, tituloPeliculas) == 0)
			{ //Si es valor caracter
				printf("\nCodigo: %d", i->codigoPeli);
				printf("\nTitulo de peliculas: %s", i->tituloPeliculas);
				printf("\nGenero de peliculas: %s", i->generoPelicula);
				printf("\nFecha persentacion: %s", i->fechaProgramada);
				printf("\nHorario: %s", i->horario);
				printf("\nDuracion: %s", i->duracionPeli);
				printf("\n\n=====================================\n");
				encontrado = 1; //Indicar que el nodo fue encontrado
				break;
			}

			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		} //Fin de while

		//Preguntar si nunca entro por el while
		if (encontrado == 0)
			printf("\n<<REGISTRO DE PELICULAS NO ENCONTRADO>>\n");
	}
	else
	{
		printf("\n\n<<NO HAY ELEMENTOS PARA BUSCAR>>\n");
	}
	system("pause");
} //Fin de buscarNodo

//Funcion eliminar PELICULAS
void eliminarPelicula(void)
{
	system("cls");

	Nodo *actual = (Nodo *)malloc(sizeof(Nodo));
	actual = primero;
	Nodo *anterior = (Nodo *)malloc(sizeof(Nodo));
	anterior = NULL;

	int codigo_Peli, encontrado = 0;
	printf("*       Eliminar Registro          *\n");
	printf("************************************\n");

	printf("\nIngrese el codigo del registro a eliminar: >_");
	scanf("%d", &codigo_Peli);
	if (primero != NULL)
	{
		while (actual != NULL && encontrado != 1)
		{
			if (actual->codigoPeli == codigo_Peli)
			{
				printf("\nEl registro eliminado es: %s", actual->tituloPeliculas);
				if (actual == primero)
				{
					primero = primero->sgte;
				}
				else if (actual == ultimo)
				{
					anterior->sgte = NULL;
					ultimo = anterior;
				}
				else
				{
					anterior->sgte = actual->sgte;
				}
				printf("\n\n<<EL REGISTRO SE HA ELIMINADO CON EXITO>>\n\n");
				encontrado = 1;
			}
			anterior = actual;
			actual = actual->sgte;
		}
		if (encontrado == 0)
		{
			printf("\n\n<<EL REGISTRO NO FUE ENCONTRADO>>\n\n");
		}
		else
		{
			free(anterior);
		}
	}
	else
	{
		printf("\n\n<<NO HAY REGISTROS PARA ELIMINAR>>\n\n");
	}

	system("pause");
} //Fin de eliminar

//Funcion para agregar elementos a la lista de SALAS
void agregarSalas()
{
	Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
	printf("Ingresar el numero de sala: ");
	scanf("%d", &nuevo->nSalas);
	printf("Ingresar la capacidad de la sala: ");
	scanf("%d", &nuevo->capacidadSalas);
	nuevo->sgte = primero;
	primero = nuevo;
}

//Funcion para mostrar SALAS
void mostrarSalas(void)
{

	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Preguntar si la lista esta vacia
	if (i != NULL)
	{
		printf("\n**************************************\n");
		printf("\n MOSTRAR  DATOS GENERALES DE SALA \n");
		printf("\n**************************************\n");

		//RECORRIENDO LA LISTA
		while (i != NULL)
		{
			printf("\nN de sala: %d", i->nSalas);
			printf("\nCapacidad de sala: %d", i->capacidadSalas);
			printf("\n-------------------------------------\n\n");

			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		} //Fin de while
	}
	else
	{
		printf("\n\n***NO HAY ELEMENTOS PARA MOSTRAR***\n");
	}
	system("pause");
} //Fin de mostrarNodo

//Funcion para modificar SALAS
void modificarSalas()
{
	Nodo *actual = (Nodo *)malloc(sizeof(Nodo));
	actual = primero;
	int nodoBuscado = 0, encontrado = 0;
	if (primero != NULL)
	{
		printf(" Ingrese el numero de sala a buscar para modificar: ");
		scanf("%d", &nodoBuscado);
		while (actual != NULL)
		{

			if (actual->nSalas == nodoBuscado)
			{
				printf("\n El numero de sala ( %d ) ha sido encontrado\n\n", nodoBuscado);
				printf("\n Ingrese el nuevo numero de sala: ");
				scanf("%d", &actual->nSalas);
				printf(" Numero de sala modificado\n\n");
				printf("\n La capacidadde la sala ( %d ) ha sido encontrado\n\n", nodoBuscado);
				printf("\n Ingrese la nueva capacidad de la sala: ");
				scanf("%d", &actual->capacidadSalas);
				printf(" La capacidad de sala ha sido modificado\n\n");
				encontrado = 1;
			}

			actual = actual->sgte;
		}
		if (encontrado == 0)
		{
			printf("\n Numero de sala no encontrado\n\n");
		}
	}
	else
	{
		printf("\n La lista de salas se encuentra vacia\n\n");
	}
}

//Funcion para buscar SALAS
void buscarSalas(void)
{
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Variable local
	int nSalas, capacidadSalas;
	int encontrado = 0; //Indicar si el nodo fue encontrado

	//Preguntar si la lista esta vacia
	if (i != NULL)
	{
		printf("\n\n**************************************\n");
		printf("\nBUSQUEDA DE SALAS\n");
		printf("\n**************************************\n");

		//PEDIR el valor a buscar en la lista
		printf("\nDigite el numero de sala a buscar: ");
		scanf(" %d", &nSalas);

		//RECORRIENDO LA LISTA
		while (i != NULL)
		{
			//Preguntar si son iguales los valores del nodo con el digitado
			//	if(strcmp(i->tituloPeliculas,tituloPeliculas)==0){//Si es valor caracter
			if (i->nSalas == nSalas)
			{
				printf("\nNumero de salas: %d", i->nSalas);
				printf("\nCapacidad de sala: %d", i->capacidadSalas);
				printf("\n-------------------------------------\n\n");
				encontrado = 1; //Indicar que el nodo fue encontrado
				break;
			}

			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		} //Fin de while

		//Preguntar si nunca entro por el while
		if (encontrado == 0)
			printf("\n<<REGISTRO DE SALAS NO ENCONTRADO>>\n");
	}
	else
	{
		printf("\n\n<<NO HAY ELEMENTOS PARA BUSCAR>>\n");
	}
	system("pause");
} //Fin de buscarNodo

void guardarInfoSalas(void)
{

	system("cls");

	Nodo *i = primero;

	if (i != NULL)
	{

		printf("\nGUARDAR INFORMACION DE SALAS\n\n");
		FILE *fichero;
		fichero = fopen("salas.txt", "wt");
		fprintf(fichero, "%s", "DATOS DE SALAS\n");
		while (i != NULL)
		{
			fprintf(fichero, "\nNumero de salas: %d ", i->nSalas, " \n");
			fprintf(fichero, "\nCapacidad de salas: %d", i->capacidadSalas);
			fprintf(fichero, "%s%s", "\n--------------------------------------\n");
			i = i->sgte;
		}

		fclose(fichero);

		printf("\n\n<<INFORMACION GUARDADA CON EXITO>>\n\n");
		system("pause");
	}
	else
	{
		printf("\nREGISTROS NO ENCONTRADOS\n");
		system("pause");
	}
}

//Funcion eliminar SALAS
void eliminarSalas()
{
	Nodo *actual = (Nodo *)malloc(sizeof(Nodo));
	actual = primero;
	Nodo *anterior = (Nodo *)malloc(sizeof(Nodo));
	anterior = NULL;
	int nodoBuscado = 0, encontrado = 0;
	printf(" Ingrese el numero de sala a buscar para eliminar: ");
	scanf("%d", &nodoBuscado);
	if (primero != NULL)
	{
		while (actual != NULL && encontrado != 1)
		{

			if (actual->nSalas == nodoBuscado)
			{

				if (actual == primero)
				{
					primero = primero->sgte;
				}
				else
				{
					anterior->sgte = actual->sgte;
				}
				printf("\n El numero de sala ha sido eliminado con exito");
				printf("\n------------------------------------------------\n\n");
				encontrado = 1;
			}
			anterior = actual;
			actual = actual->sgte;
		}
		if (encontrado == 0)
		{
			printf("\n Numero de sala no encontrado\n\n");
		}
		else
		{
			free(anterior);
		}
	}
	else
	{
		printf("\n La lista se encuentra vacia\n\n");
	}
}
