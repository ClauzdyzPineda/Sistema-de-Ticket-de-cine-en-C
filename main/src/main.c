#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
// #include "menus.h"

void estadoCursor(bool visible)
{
    CONSOLE_CURSOR_INFO *cursor = malloc(sizeof(CONSOLE_CURSOR_INFO));
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);

    if (visible)
    {
        cursor->bVisible = TRUE;
        cursor->dwSize = 0; //(0) is invild so the default value is set
    }
    else
    {
        cursor->bVisible = FALSE;
        cursor->dwSize = 1; //it must be assigned to a valid value
    }

    SetConsoleCursorInfo(handler, cursor);
}

void selector(int posicionReal, int posicionSelector)
{
    if (posicionReal == posicionSelector)
    {
        printf(" > ");
    }
    else
    {
        printf("   ");
    }
}

int seleccion()
{
    int posicion = 1;
    int tecla = 0;

    // tecla 13 = enter
    while (tecla != 13)
    {
        // titulo del programa
        system("cls");
        puts("|------------------------------------------------------|");
        puts("|     Administracion de sistema de tickets de cine     |");
        puts("|------------------------------------------------------|");
        // titulo del menu
        puts("|------------------------------------------------------|");
        puts("|                    Menu principal                    |");
        puts("|------------------------------------------------------|");

        selector(1, posicion);
        printf("Ver cartelera\n");

        selector(2, posicion);
        printf("Registrate\n");

        selector(3, posicion);
        printf("Iniciar sesion\n");

        selector(4, posicion);
        printf("Administrar Usuarios\n");

        selector(5, posicion);
        printf("Salir\n");

        // escuchando tecla
        tecla = getch();

        // tecla 80 = abajo
        // tecla 72 = arriba
        if (tecla == 80 && posicion != 5)
        {
            posicion++;
        }
        else if (tecla == 80 && posicion == 5)
        {
            posicion = 1;
        }
        else if (tecla == 72 && posicion == 1)
        {
            posicion = 5;
        }
        else if (tecla == 72 && posicion != 1)
        {
            posicion--;
        }
        else
        {
            posicion = posicion;
        }
    }

    return posicion;
}

void menuPrincipal()
{
    int opcion;

    do
    {
        // estadoCursor(false);
        opcion = seleccion();
        switch (opcion)
        {
        case 1:
            printf("\nSection ver cartelera\n");
            system("pause>null");
            break;
        case 2:
            printf("\nSection registrate\n");
            system("pause>null");
            break;
        case 3:
            printf("\nSection Iniciar sesion\n");
            system("pause>null");
            break;
        case 4:
            printf("\nSection Please delete\n");
            system("pause>null");
            break;
        case 5:
            printf("\nSalir\n");
            system("pause>null");
            break;
        }
    } while (opcion != 5);
}

int main()
{
    menuPrincipal();
    // this is to get the cursor back to the normal status
    // estadoCursor(true);
    system("cls");
    return 0;
}