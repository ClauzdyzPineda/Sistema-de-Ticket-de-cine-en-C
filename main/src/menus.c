#include <stdio.h>
#include <windows.h>
#include "helpers.h"
#include "menus.h"
#include "_define.h"

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
        opcion = seleccion(MENU_PRINCIPAL, opciones, 4);
        switch (opcion)
        {
        case 1:
            printf("\nSection ver cartelera\n");
            system("pause>null"); // Si se borra, porfavor, eliminar windows
            break;
        case 2:
            printf("\nSection registrate\n");
            system("pause>null"); // Si se borra, porfavor, eliminar windows
            break;
        case 3:
            printf("\nSection Iniciar sesion\n");
            system("pause>null"); // Si se borra, porfavor, eliminar windows
            break;
        }
    } while (opcion != 4);
}