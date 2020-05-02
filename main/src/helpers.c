#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "helpers.h"
#include "_define.h"
#include "usuario.h"

// Funcion para poder ocultar el cursor
// Osea para que no parpade. establecer visible a false
void estadoCursor(bool visible)
{
    CONSOLE_CURSOR_INFO *cursor = malloc(sizeof(CONSOLE_CURSOR_INFO));
    HANDLE handler = GetStdHandle(STD_OUTPUT_HANDLE);

    if (visible)
    {
        cursor->bVisible = TRUE;
        cursor->dwSize = 0;
    }
    else
    {
        cursor->bVisible = FALSE;
        cursor->dwSize = 1;
    }

    SetConsoleCursorInfo(handler, cursor);
}

// funcion para poder mostrar la flecha en que opcion esta ubicada
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

// Funcion que permite que el menu se comporte como seleccion junto con la funcion de selector
int seleccion(char *menu, char opcs[][LENGTH], int noOpcs)
{
    int posicion = 1;
    int tecla = 0;
    int i;

    // tecla 13 = enter
    while (tecla != ENTER)
    {
        titulo();
        // titulo del menu
        if (strcmp(menu, MENU_PRINCIPAL) == 0)
        {
            cabeceraMenuPrincipal();
        }
        if (strcmp(menu, MENU_PERFIL_ADMIN) == 0)
        {
            cabeceraMenuPerfilAdmin();
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
        if (tecla == ARRIBA && posicion != noOpcs)
        {
            posicion++;
        }
        else if (tecla == ARRIBA && posicion == noOpcs)
        {
            posicion = 1;
        }
        else if (tecla == ABAJO && posicion == 1)
        {
            posicion = noOpcs;
        }
        else if (tecla == ABAJO && posicion != 1)
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

void titulo()
{
    system("cls");
    puts("|------------------------------------------------------|");
    puts("|     Administracion de sistema de tickets de cine     |");
    puts("|------------------------------------------------------|");
}

void cabeceraMenuPrincipal()
{
    puts("|------------------------------------------------------|");
    puts("|                    Menu principal                    |");
    puts("|------------------------------------------------------|");
}

void cabeceraInicioSesion()
{
    puts("|------------------------------------------------------|");
    puts("|                   Inicio de sesion                   |");
    puts("|------------------------------------------------------|");
}

void cabeceraMenuPerfilAdmin()
{
    puts("|------------------------------------------------------|");
    puts("|                Perfil de administrador               |");
    puts("|------------------------------------------------------|");
}