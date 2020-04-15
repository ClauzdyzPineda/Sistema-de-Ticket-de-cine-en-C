#include <stdio.h>
#include <stdlib.h>

#include <string.h> /* gets, strcmp */

#define USUARIO "c"
#define CLAVE "java"

#define LONGITUD 80

//Definir la estructura a utilizar
typedef struct{
	int codigoPeli;
	char tituloPeliculas[100];
	char generoPelicula[100];
	char fechaProgramada[10];
	char horario[10]; 
	char duracionPeli[10];
	int nSalas, capacidadSalas;
	struct Nodo *sgte;
}Nodo;

//Crear punteros para el primero y ultimo elemento de la lista
Nodo *primero = NULL;
Nodo *ultimo = NULL;


int inicio(){
char usuario[LONGITUD + 1];
	char clave[LONGITUD + 1];
	int intento = 0;
	int ingresa = 0;
	char caracter;
	int i = 0;
	
	do {
		i = 0;
		system("cls");
		printf("\n\t\t\tINICIO DE SESION\n");
		printf("\t\t\t---------------\n");
		printf("\n\tUSUARIO: ");
		gets(usuario);
		printf("\tCLAVE: ");
		while (caracter = getch()) {
			if (caracter == 13) {
				clave[i] = '\0';
				break;
				
			} else if (caracter == 8) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
				
			} else {
				if (i < LONGITUD) {
					printf("*");
					clave[i] = caracter;
					i++;
				}
			}
		}
		
		if (strcmp(usuario, USUARIO) == 0 && strcmp(clave, CLAVE) == 0) {
			ingresa = 1;
			
		} else {
			printf("\n\tUsuario y/o clave son incorrectos\n");
			intento++;
			getchar();
		}
		
	} while (intento < 3 && ingresa == 0);
	
	if (ingresa == 1) {
		printf("\n\tBienvenido al Sistema\n");
		
	} else {
		printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
	}
	
	return 0;
	}

void Menu(void){
     
     system("cls");
     
     printf("********************************************\n");
     printf("*BIENVENIDOS A COMPRAS DE TICKET PARA CINE *\n");
     printf("********************************************\n");
     printf("*  [1] Registro de Administrador(Usuarios) *\n");
     printf("*  [2] Registro de Peliculas               *\n");
     printf("*  [3] Registro de Clientes                *\n");
     printf("*  [4] Registro de Tickets                 *\n");
     printf("*  [5] Registro de Salas                   *\n");
     printf("*  [6] Salir                               *\n");
     printf("********************************************\n");
     
}

void SubMenu(char *nameSubMenu){
     
     system("cls");
     // 43 espacios
     //      0123456789012345678901234567890123456789012
     printf("********************************************\n");
     printf("*              Menu secundario             *\n");
     printf("* %s", nameSubMenu);
     int i;
     for(i=strlen(nameSubMenu);i<=39;i++)
     {
      printf(" ");
     }
     printf(" *\n");
     printf("********************************************\n");
     printf("*  [1] Agregar                             *\n");
     printf("*  [2] Modificar                           *\n");
     printf("*  [3] Buscar                              *\n");
     printf("*  [4] Mostrar                             *\n");
     printf("*  [5] Eliminar                            *\n");
     printf("*  [6] Regresar                            *\n");
     printf("********************************************\n");
     
}


int main(int argc, char *argv[])
{
    inicio();
    int sistemExit = 0;
    
    while(sistemExit == 0){
    	
    	int opMenu, opSubMenu;
    
	    Menu();
	    scanf("%d",&opMenu);
	    switch(opMenu){
	       	case 1:
	            SubMenu("MENU DE REGISTRO DE ADMINISTRADOR");
	            scanf("%d",&opSubMenu);
	            switch(opSubMenu){
	            	case 1:
	            		system("cls");
	            		printf("\nAgregar Administrador\n");
	            		system("pause");
	            		break;
	            	case 2:
	            		system("cls");
	            		printf("\nModificar Administrador\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nBuscar Administrador\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nMostrar Administrador\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nEliminar Administrador\n");
	            		system("pause");
	            		break;
	            	default:
	            		system("cls");
	            		break;
				}
	            break;
	        case 2:
	        	SubMenu("MENU DE REGISTRO DE PELICULAS");
	        	scanf("%d",&opSubMenu);
	        	switch(opSubMenu){
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
	            		printf("\nEliminar pelicula\n");
	            		eliminarPelicula();
	            		system("pause");
	            		break;
	            
	            	default:
	            		system("cls");
	            		break;
				}
	            break;
	        case 3:
	        	SubMenu("MENU DE REGISTRO DE CLIENTES");
	        	scanf("%d",&opSubMenu);
	        	switch(opSubMenu){
	            	case 1:
	            		system("cls");
	            		printf("\nAgregar clientes\n");
	            		system("pause");
	            		break;
	            	case 2:
	            		system("cls");
	            		printf("\nModificar clientes\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nBuscar clientes\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nMostrar clientes\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nEliminar clientes\n");
	            		system("pause");
	            		break;
	            	default:
	            		system("cls");
	            		break;
				}
	            break;
	            
	        case 4:
	        	SubMenu("MENU DE REGISTRO DE TICKETS");
	        	scanf("%d",&opSubMenu);
	        	switch(opSubMenu){
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
	            
	        case 5:
	        	SubMenu("MENU DE REGISTRO DE SALAS");
	        	scanf("%d",&opSubMenu);
	        	switch(opSubMenu){
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
	            		printf("\nEliminar Salas\n");
	            		eliminarSalas();
	            		system("pause");
	            		break;
	            	default:
	            		system("cls");
	            		break;
				}
	            break;
	            
	        case 6:
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

//Funcion para agregar elementos a PELICULAS
void agregarPeliculas(void){
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
	scanf(" %[^\n]",nodo->tituloPeliculas);
	printf("Digite genero de pelicula: "); 			
	scanf(" %[^\n]",nodo->generoPelicula);
	printf("Digite fecha programada: ");	
	scanf(" %s",nodo->fechaProgramada);
	printf("Digite hora programada: ");	
	scanf(" %[^\n]", nodo->horario);
	printf("Digite duracion de la pelicula: ");	
	scanf(" %[^\n]",nodo->duracionPeli);
	//Apuntar a NULL el siguiente elemento de la lista
	nodo->sgte = NULL;
	//Preguntar si la lista esta vacia
	if(primero == NULL){
		primero = nodo; 		
		ultimo = nodo;
	}else{
		ultimo->sgte = nodo; 
		ultimo = nodo;
	}
}

//Funcion para mostrar PELICULAS
void mostrarPeliculas(void){
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Preguntar si la lista esta vacia
	if(i != NULL){
	printf("\n**************************************\n");
	printf("\n MOSTRAR  DATOS DE PELICULAS \n");
	printf("\n**************************************\n");
		
		//RECORRIENDO LA LISTA
		while(i != NULL){
			printf("\nCodigo: %d",i->codigoPeli);
			printf("\nTitulo de pelicula: %s",i->tituloPeliculas);
			printf("\nGenero de pelicula: %s",i->generoPelicula);
			printf("\nFecha de presentacion: %s",i->fechaProgramada);
				printf("\nHorario de pelicula: %s",i->horario);
			printf("\nDuracion de pelicula: %s",i->duracionPeli);
			printf("\n-------------------------------------\n\n");
		
			
			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		}//Fin de while
	}else{
		printf("\n\n***NO HAY ELEMENTOS PARA MOSTRAR***\n");
	}
	system("pause");
}//Fin de mostrarNodo

//Funcion para modificar PELICULAS
void modificarPeliculas(){
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Variable local
	char tituloPeliculas[100];
	int encontrado = 0;//Indicar si el nodo fue encontrado
	
	//Preguntar si la lista esta vacia
	if(i != NULL){
		printf("\n\n=====================================\n");
		printf("MODIFICAR DATOS DE PELICULAS");
		printf("\n\n=====================================\n");
		
		//PEDIR el valor a buscar en la lista
		printf("\nIngrese el titulo de pelicula a modificar: ");
		scanf(" %[^\n]",&tituloPeliculas);
		
		while(i != NULL){
			//Preguntar si son iguales los valores del nodo con el digitado
			if(strcmp(i->tituloPeliculas,tituloPeliculas)==0){//Si es valor caracter
			//if(i->codigo == descripcion){//Solo si es para valor numerico
				printf("\nIngrese el nuevo codigo: ");
				scanf("%d",&i->codigoPeli);
				printf("\nIngrese un el titulo de la pelicula a modificar: ");
				scanf(" %[^\n]",i->tituloPeliculas);
				printf("\nIngrese el genero de pelicula a modificar: ");
				scanf(" %[^\n]",i->generoPelicula);
				printf("\nIngrese la fecha de presentacion a modificar: ");
				scanf("%s",i->fechaProgramada);
				printf("\nIngrese el horario a modificar: ");
				scanf("%s",i->horario);
				printf("\nIngrese la duracion de pelicula a modificar: ");
				scanf("%s",i->duracionPeli);
				
				printf("\n\nSu informacion actualizada es");
				printf("\nCodigo: %d",i->codigoPeli);
				printf("\nNombre: %s",i->tituloPeliculas);
				printf("\nDireccion: %s",i->generoPelicula);
				printf("\nFecha de presentacion: %s",i->fechaProgramada);
				printf("\nHorario: %s",i->horario);
				printf("\nDuracion: %s",i->duracionPeli);
				printf("\n\n=====================================\n");
				printf("\n");
				encontrado = 1;//Indicar que el nodo fue encontrado
				break;	
			}//Fin de if
			
			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		}//Fin de while
		
	}else{
		printf("\n\n***NO HAY ELEMENTOS PARA MODIFICAR***\n");
	}
}

//Funcion para buscar PELICULAS
void buscarPeliculas(void){
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Variable local
	char tituloPeliculas[100];
	int  encontrado = 0;//Indicar si el nodo fue encontrado
	
	//Preguntar si la lista esta vacia
	if(i != NULL){
		printf("\n\n**************************************\n");
		printf("\nBUSQUEDA DE PELICULAS\n");
		printf("\n**************************************\n");
		
		//PEDIR el valor a buscar en la lista
		printf("\nDigite el titulo de la pelicula a buscar: ");
		scanf(" %[^\n]",&tituloPeliculas);
		
		//RECORRIENDO LA LISTA
		while(i != NULL){
			//Preguntar si son iguales los valores del nodo con el digitado
			if(strcmp(i->tituloPeliculas,tituloPeliculas)==0){//Si es valor caracter
				printf("\nCodigo: %d",i->codigoPeli);
				printf("\nTitulo de peliculas: %s",i->tituloPeliculas);
				printf("\nGenero de peliculas: %s",i->generoPelicula);
				printf("\nFecha persentacion: %s",i->fechaProgramada);
				printf("\nHorario: %s",i->horario);
				printf("\nDuracion: %s",i->duracionPeli);
				printf("\n\n=====================================\n");
				encontrado = 1;//Indicar que el nodo fue encontrado
				break;	
			}
			
			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		}//Fin de while
		
		//Preguntar si nunca entro por el while
		if(encontrado==0)
			printf("\n<<REGISTRO DE PELICULAS NO ENCONTRADO>>\n");
	}else{
		printf("\n\n<<NO HAY ELEMENTOS PARA BUSCAR>>\n");
	}
	system("pause");
}//Fin de buscarNodo

//Funcion eliminar PELICULAS
void eliminarPelicula(void){
	system("cls");

	Nodo* actual = (Nodo*)malloc(sizeof(Nodo));
	actual = primero;
	Nodo* anterior = (Nodo*)malloc(sizeof(Nodo));
	anterior = NULL;
	
	int codigo_Peli, encontrado = 0;
	
	printf("************************************\n");
	printf("*       Eliminar Registro          *\n");
	printf("************************************\n");
	
	printf("\nIngrese el codigo del registro a eliminar: >_");
	scanf("%d",&codigo_Peli);
	if(primero!=NULL){
		while(actual!=NULL && encontrado!=1){
			if(actual->codigoPeli==codigo_Peli){
				printf("\nEl registro eliminado es: %s",actual->tituloPeliculas);
				if(actual == primero){
					primero = primero->sgte;
				}else if(actual == ultimo){
					anterior->sgte = NULL;
					ultimo = anterior;
				}else{
					anterior->sgte = actual->sgte;
				}							
				printf("\n\n<<EL REGISTRO SE HA ELIMINADO CON EXITO>>\n\n");
				encontrado=1;
			}
			anterior = actual;
			actual = actual->sgte;
		}
		if(encontrado==0){
			printf("\n\n<<EL REGISTRO NO FUE ENCONTRADO>>\n\n");
		}else{
			free(anterior);
		}
	}else{
		printf("\n\n<<NO HAY REGISTROS PARA ELIMINAR>>\n\n");
	}
	
	system("pause");
}//Fin de eliminar



//Funcion para agregar elementos a la lista de SALAS
void agregarSalas(){
	Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
	printf("Ingresar el numero de sala: ");
	scanf("%d", &nuevo->nSalas);
	printf("Ingresar la capacidad de la sala: ");
	scanf("%d", &nuevo->capacidadSalas);
	nuevo->sgte = primero;
	primero = nuevo;	
}


//Funcion para mostrar SALAS
void mostrarSalas(void){
	
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Preguntar si la lista esta vacia
	if(i != NULL){
	printf("\n**************************************\n");
	printf("\n MOSTRAR  DATOS GENERALES DE SALA \n");
	printf("\n**************************************\n");
		
		//RECORRIENDO LA LISTA
		while(i != NULL){
			printf("\nN de sala: %d",i->nSalas);
			printf("\nCapacidad de sala: %d",i->capacidadSalas);
			printf("\n-------------------------------------\n\n");
			
			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		}//Fin de while
	}else{
		printf("\n\n***NO HAY ELEMENTOS PARA MOSTRAR***\n");
	}
	system("pause");
}//Fin de mostrarNodo


//Funcion para modificar SALAS
void modificarSalas(){
	Nodo* actual = (Nodo*) malloc(sizeof(Nodo));
	actual = primero;
	int nodoBuscado = 0, encontrado = 0;
	if(primero != NULL){ 
	printf(" Ingrese el numero de sala a buscar para modificar: ");
	scanf("%d", &nodoBuscado);
		while(actual != NULL){
		
		if(actual->nSalas == nodoBuscado){
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
		
		actual = actual -> sgte;
		}
		if(encontrado == 0){
			printf("\n Numero de sala no encontrado\n\n");
		}
	
	}else{
		printf("\n La lista de salas se encuentra vacia\n\n");
	}
}


//Funcion para buscar SALAS
void buscarSalas(void){
	//Limpiar pantalla
	system("cls");
	//Crear puntero centinela para el recorrido de la lista
	Nodo *i = primero;
	//Variable local
	int nSalas, capacidadSalas;
	int  encontrado = 0;//Indicar si el nodo fue encontrado
	
	//Preguntar si la lista esta vacia
	if(i != NULL){
		printf("\n\n**************************************\n");
		printf("\nBUSQUEDA DE SALAS\n");
		printf("\n**************************************\n");
		
		//PEDIR el valor a buscar en la lista
		printf("\nDigite el numero de sala a buscar: ");
		scanf(" %d",&nSalas);
		
		//RECORRIENDO LA LISTA
		while(i != NULL){
			//Preguntar si son iguales los valores del nodo con el digitado
		//	if(strcmp(i->tituloPeliculas,tituloPeliculas)==0){//Si es valor caracter
		if(i->nSalas == nSalas){
				printf("\nNumero de salas: %d",i->nSalas);
				printf("\nCapacidad de sala: %d",i->capacidadSalas);
				printf("\n-------------------------------------\n\n");
				encontrado = 1;//Indicar que el nodo fue encontrado
				break;	
			}
			
			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		}//Fin de while
		
		//Preguntar si nunca entro por el while
		if(encontrado==0)
			printf("\n<<REGISTRO DE SALAS NO ENCONTRADO>>\n");
	}else{
		printf("\n\n<<NO HAY ELEMENTOS PARA BUSCAR>>\n");
	}
	system("pause");
}//Fin de buscarNodo


//Funcion eliminar SALAS
void eliminarSalas(){
	Nodo* actual = (Nodo*) malloc(sizeof(Nodo));
	actual = primero;
	Nodo* anterior = (Nodo*) malloc(sizeof(Nodo));
	anterior = NULL;
	int nodoBuscado = 0, encontrado = 0;
	printf(" Ingrese el numero de sala a buscar para eliminar: ");
	scanf("%d", &nodoBuscado);
	if(primero != NULL){ 
		while(actual != NULL && encontrado != 1){
		
		if(actual->nSalas == nodoBuscado){
		
			if(actual == primero){
				primero = primero -> sgte;	
				}else{
				anterior -> sgte = actual -> sgte;
				}
			printf("\n El numero de sala ha sido eliminado con exito");
			printf("\n------------------------------------------------\n\n");
			encontrado = 1;
		}
		anterior = actual;
		actual = actual -> sgte;
		}
		if(encontrado == 0){
			printf("\n Numero de sala no encontrado\n\n");
		}else{
			free(anterior);
		}
	
	}else{
		printf("\n La lista se encuentra vacia\n\n");
	
	}
}


