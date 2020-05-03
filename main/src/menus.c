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
            // registro();
            crearRegistro(REGISTRO_USUARIO);
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
            "Administrar Peliculas",
            "Regresar",
        };

        do
        {
            // estadoCursor(false);
            opcion = seleccion(MENU_PERFIL_ADMIN, opciones, 3);
            switch (opcion)
            {
            case 1:
                menuUsuarios();
                break;
            case 2:
                menuPeliculas();
                break;
            }
        } while (opcion != 3);
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
            crearRegistro(REGISTRO_USUARIO);
            break;
        case 2:
            mostrarRegistros(REGISTRO_USUARIO);
            break;
        case 3:
            actualizarRegistro(REGISTRO_USUARIO);
            break;
        case 4:
            eliminarRegistro(REGISTRO_USUARIO);
            break;
        }
    } while (opcion != 5);
}

void menuPeliculas()
{

    int opcion;
    char opciones[][LENGTH] = {
        "Crear pelicula",
        "Mostrar peliculas",
        "Actualizar pelicula",
        "Eliminar pelicula",
        "Regresar",
    };

    do
    {
        // estadoCursor(false);
        opcion = seleccion(MENU_PERFIL_ADMIN, opciones, 5);
        switch (opcion)
        {
        case 1:
            crearRegistro(REGISTRO_PELICULA);
            break;
        case 2:
            mostrarRegistros(REGISTRO_PELICULA);
            break;
        case 3:
            actualizarRegistro(REGISTRO_PELICULA);
            break;
        case 4:
            eliminarRegistro(REGISTRO_PELICULA);
            break;
        }
    } while (opcion != 5);
}