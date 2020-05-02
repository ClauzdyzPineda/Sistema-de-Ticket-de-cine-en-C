#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "helpers.h"
#include "_define.h"

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
int seleccion(char *menu, char opcs[][20], int noOpcs)
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

int inicioSesion()
{
    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];
    int intento = 0;
    int ingresa = 0;
    char caracter;
    int i = 0;

    do
    {
        titulo();
        cabeceraInicioSesion();
        printf("\nUSUARIO: ");
        gets(usuario);
        printf("CLAVE: ");
        while ((caracter = getch()))
        {
            if (caracter == ENTER)
            {
                clave[i] = '\0';
                break;
            }
            else if (caracter == BACKSPACE)
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
        printf("\n\tBienvenido al Sistema.. Aqui es donde tiene que ir la funcion. de usuario vs admin\n");
        system("pause>null");
    }
    else
    {
        printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
        system("pause>null");
    }

    return 0;
}