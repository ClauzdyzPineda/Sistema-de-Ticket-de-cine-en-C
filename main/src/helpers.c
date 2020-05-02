#include <stdio.h>
#include "helpers.h"

void mainHeader()
{
    system("cls");
    puts("|------------------------------------------------------|");
    puts("|     Administracion de sistema de tickets de cine     |");
    puts("|------------------------------------------------------|");
}

void mainMenuHeader()
{
    puts("|------------------------------------------------------|");
    puts("|                    Menu principal                    |");
    puts("|------------------------------------------------------|");
}

void showArrow(int realPosition, int arrowPosition)
{
    if (realPosition == arrowPosition)
    {
        printf(" > ");
    }
    else
    {
        printf("   ");
    }
}

int mainMenu()
{
    int position = 1;
    int key = 0;

    // key 13 = enter
    while (key != 13)
    {
        mainHeader();
        mainMenuHeader();

        // Showing the arrows and the options all together
        showArrow(1, position);
        printf("Ver cartelera\n");

        showArrow(2, position);
        printf("Registrate\n");

        showArrow(3, position);
        printf("Iniciar sesion\n");

        showArrow(4, position);
        printf("Administrar Usuarios\n");

        showArrow(5, position);
        printf("Salir\n");

        // listen to the key
        key = getch(); // check if this could be replace for getChar()

        // key 80 = keydown
        // key 72 = keyup
        if (key == 80 && position != 5)
        {
            position++;
        }
        else if (key == 80 && position == 5)
        {
            position = 1;
        }
        else if (key == 72 && position == 1)
        {
            position = 5;
        }
        else if (key == 72 && position != 1)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }

    return position;
}