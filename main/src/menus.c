#include <stdio.h>
#include <windows.h>
#include "helpers.h"
#include "menus.h"
#include "_define.h"
#include "usuario.h"

void menuPrincipal()
{
    int opcion;

    char opciones[][LENGTH] = {
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
            registro();
            break;
        case 3:
            inicioSesion();
            break;
        }
    } while (opcion != 4);
}

void menuPerfil(int acceso)
{
    int opcion;
    char opciones[][LENGTH] = {
        "Administrar usuarios",
        "Regresar",
    };

    do
    {
        // estadoCursor(false);
        opcion = seleccion(MENU_PERFIL_ADMIN, opciones, 2);
        switch (opcion)
        {
        case 1:
            menuUsuarios();
            break;
        }
    } while (opcion != 2);
}

void menuUsuarios()
{

    int opcion;
    char opciones[][LENGTH] = {
        "Crear usuario",
        "Mostrar usuarios",
        "Actualizar usuario",
        "Eliminar usuario",
        "Regresar",
    };

    do
    {
        // estadoCursor(false);
        opcion = seleccion(MENU_PERFIL_ADMIN, opciones, 5);
        switch (opcion)
        {
        case 1:
            registro();
            break;
        case 2:
            mostrarUsuarios();
            break;
        case 3:
            actualizarUsuario();
            break;
        case 4:
            printf("\nEliminar usuarios\n");
            system("pause>null");
            break;
        }
    } while (opcion != 2);
}