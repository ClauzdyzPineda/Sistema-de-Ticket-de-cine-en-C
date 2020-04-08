#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu(void){
     
     system("cls");
     
     printf("*******************************************\n");
     printf("*              Menu principal             *\n");
     printf("*******************************************\n");
     printf("*  [1] Salas                              *\n");
     printf("*  [2] Peliculas                          *\n");
     printf("*  [3] Clientes                           *\n");
     printf("*  [4] Salir                              *\n");
     printf("*******************************************\n");
     
}

void SubMenu(char *nameSubMenu){
     
     system("cls");
     // 43 espacios
     //      0123456789012345678901234567890123456789012
     printf("*******************************************\n");
     printf("*              Menu secundario            *\n");
     printf("* %s", nameSubMenu);
     int i;
     for(i=strlen(nameSubMenu);i<=39;i++)
     {
      printf(" ");
     }
     printf("*\n");
     printf("*******************************************\n");
     printf("*  [1] Agregar                            *\n");
     printf("*  [2] Editar                             *\n");
     printf("*  [3] Eliminar                           *\n");
     printf("*  [4] Buscar                             *\n");
     printf("*  [5] Mostrar                            *\n");
     printf("*  [6] Regresar                           *\n");
     printf("*******************************************\n");
     
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
	            SubMenu("MENU DE SALAS");
	            scanf("%d",&opSubMenu);
	            switch(opSubMenu){
	            	case 1:
	            		system("cls");
	            		printf("\nAgregar sala\n");
	            		system("pause");
	            		break;
	            	case 2:
	            		system("cls");
	            		printf("\nEditar sala\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nEliminar sala\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nBuscar sala\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nMostrar sala\n");
	            		system("pause");
	            		break;
	            	default:
	            		system("cls");
	            		break;
				}
	            break;
	        case 2:
	        	SubMenu("MENU DE PELICULAS");
	        	scanf("%d",&opSubMenu);
	        	switch(opSubMenu){
	            	case 1:
	            		system("cls");
	            		printf("\nAgregar pelicula\n");
	            		system("pause");
	            		break;
	            	case 2:
	            		system("cls");
	            		printf("\nEditar pelicula\n");
	            		system("pause");
	            		break;
	            	case 3:
	            		system("cls");
	            		printf("\nEliminar pelicula\n");
	            		system("pause");
	            		break;
	            	case 4:
	            		system("cls");
	            		printf("\nBuscar pelicula\n");
	            		system("pause");
	            		break;
	            	case 5:
	            		system("cls");
	            		printf("\nMostrar pelicula\n");
	            		system("pause");
	            		break;
	            	default:
	            		system("cls");
	            		break;
				}
	            break;
	        case 3:
	        	SubMenu("MENU DE CLIENTES");
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
