#include <stdio.h>
#include <stdlib.h>

//Definir la estructura a utilizar
typedef struct{
	int codigo;
	char tituloPeliculas[100];
	char generoPelicula[100];
	char fechaProgramada[10];
	struct Nodo *sgte;
}Nodo;

//Crear punteros para el primero y ultimo elemento de la lista
Nodo *primero = NULL;
Nodo *ultimo = NULL;


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
	            		printf("\nEditar Administrador\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nEliminar Administrador\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nBuscar Administrador\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nMostrar Administrador\n");
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
	            		agregarNodo();
	            		system("pause");
	            		break;
	            	case 2:
	            		system("cls");
	            		printf("\nModificar pelicula\n");
	            		modificarNodo();
	            		system("pause");
	            		break;
	            	
	            	case 3:
	            		system("cls");
	            		printf("\nBuscar pelicula\n");
	            		buscarNodo();
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nMostrar pelicula\n");
	            		mostrarNodo();
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nEliminar pelicula\n");
	            		eliminarNodo();
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
	            		printf("\nEditar clientes\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nEliminar clientes\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nBuscar clientes\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nMostrar clientes\n");
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
	            		printf("\nEditar Tickets\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nEliminar Tickets\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nBuscar Tickets\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nMostrar Tickets\n");
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
	            		system("pause");
	            		break;
	            	case 2:
	            		system("cls");
	            		printf("\nEditar Salas\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nEliminar Salas\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nBuscar Salas\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nMostrar Salas\n");
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

//Funcion para agregar elementos a la lista
void agregarNodo(void){
	//Reservar en memoria el nuevo nodo
	Nodo *nodo = malloc(sizeof(Nodo));
	//Limpiar pantalla
	system("cls");
	//Solicitar los valores del nodo
	printf("\n**************************************\n");
	printf("\nREGISTRO DE DATOS DE PELICULAS \n");
	printf("\n**************************************\n");
	printf("Digite codigo: ");		
	scanf("%d", &nodo->codigo);
	printf("Digite titulo de pelicula: ");	
	scanf(" %[^\n]",nodo->tituloPeliculas);
	printf("Digite genero de pelicula: "); 			
	scanf(" %[^\n]",nodo->generoPelicula);
	printf("Digite fecha programada: ");	
	scanf(" %s",nodo->fechaProgramada);
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

//Funcion para mostrar nodos
void mostrarNodo(void){
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
			printf("\nCodigo: %d",i->codigo);
			printf("\nTitulo de pelicula: %s",i->tituloPeliculas);
			printf("\nGenero de pelicula: %s",i->generoPelicula);
			printf("\nFecha de presentacion: %s",i->fechaProgramada);
			printf("\n-------------------------------------\n");
			
			//Mover el valor de i al siguiente nodo
			i = i->sgte;
		}//Fin de while
	}else{
		printf("\n\n***NO HAY ELEMENTOS PARA MOSTRAR***\n");
	}
	system("pause");
}//Fin de mostrarNodo

//Funcion para modificar
void modificarNodo(){
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
				scanf("%d",&i->codigo);
				printf("\nIngrese un el titulo de la pelicula a modificar: ");
				scanf(" %[^\n]",i->tituloPeliculas);
				printf("\nIngrese el genero de pelicula a modificar: ");
				scanf(" %[^\n]",i->generoPelicula);
				printf("\nIngrese la fecha de presentacion a modificar: ");
				scanf("%s",i->fechaProgramada);
				
				printf("\n\nSu informacion actualizada es");
				printf("\nCodigo: %d",i->codigo);
				printf("\nNombre: %s",i->tituloPeliculas);
				printf("\nDireccion: %s",i->generoPelicula);
				printf("\nFecha de nacimiento: %s",i->fechaProgramada);
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

//Funcion para buscar
void buscarNodo(void){
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
				printf("\nCodigo: %d",i->codigo);
				printf("\nTitulo de peliculas: %s",i->tituloPeliculas);
				printf("\nGenero de peliculas: %s",i->generoPelicula);
				printf("\nFecha persentacion: %s",i->fechaProgramada);
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

//Funcion eliminar
void eliminarNodo(void){
	//limpiar pantalla
	system("cls");
	//Variable local
	char tituloPeliculas[100];
	Nodo *lista = primero;//Puntero auxiliar 
	//Preguntar si la lista esta vacia
	if(lista != NULL){
		printf("\n\n**************************************\n");
		printf("\nELIMINACION DE REGISTROS DE PELICULAS\n");
		printf("\n**************************************\n");
		printf("\nDigite titulo  de la pelicula: ");
		scanf(" %[^\n]",&tituloPeliculas);
		
		//Puntero axuliar
		Nodo *aux_borrar;
		aux_borrar = lista;
		Nodo *anterior = NULL;
		//Recorrer la lista
		while(aux_borrar !=NULL &&(strcmp(aux_borrar->tituloPeliculas,tituloPeliculas)!=0)){
			anterior 	= aux_borrar;
			aux_borrar 	= aux_borrar->sgte;
		}//Fin de while
		//Preguntar si fue encontrado el nodo a eliminar
		if(aux_borrar == NULL){
			printf("\n***DESCRIPCION DE PELICULA NO ENCONTRADA***\n");
		}else if(anterior == NULL){
			lista = lista->sgte;
			free(aux_borrar);//Eliminar nodo
			printf("\n\n***ELEMENTO ELIMINADO DE PELICULAS 2***\n");
		}else{
			anterior->sgte = aux_borrar->sgte;
			free(aux_borrar);
			printf("\n\n***ELEMENTO ELIMINADO DE LA PELICULA 3***\n");
		}
	}else
		printf("\n\n***NO HAY ELEMENTOS PARA ELIMINAR***\n");
	system("pause");	
}//Fin de eliminar


