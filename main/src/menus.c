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
    Role esAdmin = ADMIN;
    if (acceso == esAdmin)
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
    else
    {
        // PANEL DE USUARIO NORMAL
        int opcion;
        char opciones[][LENGTH] = {
            "Comprar entradas",
            "Mi perfil",
            "Regresar",
        };

        do
        {
            // estadoCursor(false);
            opcion = seleccion(MENU_PERFIL, opciones, 3);
            switch (opcion)
            {
            case 1:
                printf("Comprar entradas");
                system("pause>null");
                break;
            case 2:
                printf("Actualizar mi perfil");
                system("pause>null");
                break;
            }
        } while (opcion != 3);
    }
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
            eliminarUsuario();
            break;
        }
    } while (opcion != 5);
}