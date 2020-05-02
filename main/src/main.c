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

void dispStrings(char opcs[][20], int noOpcs)
{
    int i = 0;
    for (i = 0; i < noOpcs; i++)
    {
        printf("%s\n", opcs[i]);
    }
}

int seleccion(char *menu, char opcs[][20], int noOpcs)
{
    int posicion = 1;
    int tecla = 0;
    int i;

    // tecla 13 = enter
    while (tecla != 13)
    {
        // titulo del programa
        system("cls");
        puts("|------------------------------------------------------|");
        puts("|     Administracion de sistema de tickets de cine     |");
        puts("|------------------------------------------------------|");
        // titulo del menu
        if (strcmp(menu, "MENU_PRINCIPAL") == 0)
        {
            puts("|------------------------------------------------------|");
            puts("|                    Menu principal                    |");
            puts("|------------------------------------------------------|");
        }

        for (i = 0; i < noOpcs; i++)
        {
            selector((i + 1), posicion);
            printf("%s\n", opcs[i]);
        }

        // escuchando tecla
        tecla = getch();

        // tecla 80 = abajo
        // tecla 72 = arriba
        if (tecla == 80 && posicion != noOpcs)
        {
            posicion++;
        }
        else if (tecla == 80 && posicion == noOpcs)
        {
            posicion = 1;
        }
        else if (tecla == 72 && posicion == 1)
        {
            posicion = noOpcs;
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

    char opciones[][20] = {
        "Ver cartelera",
        "Registrate",
        "Iniciar sesion",
        "Salir",
    };

    do
    {
        // estadoCursor(false);
        opcion = seleccion("MENU_PRINCIPAL", opciones, 4);
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
        }
    } while (opcion != 4);
}

int main()
{
    menuPrincipal();
    // this is to get the cursor back to the normal status
    // estadoCursor(true);
    system("cls");
    return 0;
}

// void printing(char *string)
// {
//     if (strcmp(string, "menu") == 0)
//     {
//         printf("correcto");
//     }
// }

// int main()
// {
//     printing("menu,");
//     return 0;
// }