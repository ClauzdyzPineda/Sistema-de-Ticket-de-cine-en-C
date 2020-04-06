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

int main(void){
	//Creamos el menu
	int opcionMenu = 0;
	system("cls");
	do{
		printf("\n**********VENTA DE TICKET DE CINE**********");
		printf("\n|------------------------------------|");
		printf("\n|          MENU PRINCIPAL            |");
		printf("\n|-------------------|----------------|");
		printf("\n|  1. Insertar      |  4. Eliminar   |");
		printf("\n|  2. Buscar        |  5. Salir      |");
		printf("\n|  3. Mostrar       |                |");
		printf("\n|-------------------|----------------|");
		printf("\n\n Escoja una opcion: ");
		scanf("%d", &opcionMenu);
		
		switch(opcionMenu){
			case 1:
				printf("\n\n INSERTAR TITULO DE PELICULAS EN CARTELERA \n\n");
				agregarNodo();
				break;
			case 2:
				printf("\n\n BUSCAR PELICULAS EN CARTELERA \n\n");
				buscarNodo();
				break;
			case 3:
				printf("\n\n MOSTRAR PELICULAS EN CARTELERA  \n\n");
				mostrarNodo();
				break;	
			case 4:
				printf("\n\n ELIMINAR PELICULAS EN CARTELERA  \n\n");
				eliminarNodo();
				break;
			case 5:
				printf("\n\n Programa finalizando...");
				
				break;
			default:
				printf("\n\n Opcion No valida \n\n");	
			system("pause");				
		}
		
	}while(opcionMenu != 6);	
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


