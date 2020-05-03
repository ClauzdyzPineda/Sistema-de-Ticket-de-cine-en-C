#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "helpers.h"
#include "_define.h"
#include "usuario.h"
#include "pelicula.h"
#include "cabeceras.h"

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
        if (strcmp(menu, MENU_ACTUALIZAR_USER) == 0)
        {
            cabeceraActualizarUsuario();
        }
        if (strcmp(menu, MENU_PERFIL) == 0)
        {
            cabeceraMenuPerfil();
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

int setId(char *registro)
{
    int id = 0;

    if (strcmp(registro, REGISTRO_USUARIO) == 0)
    {
        FILE *file;
        file = fopen("Record", "r");

        while (fread(&Usuario, sizeof(Usuario), 1, file))
        {
            id++;
        }
        fclose(file);
    }

    if (strcmp(registro, REGISTRO_PELICULA) == 0)
    {
        FILE *file;
        file = fopen("Pelicula", "r");

        while (fread(&Pelicula, sizeof(Pelicula), 1, file))
        {
            id++;
        }
        fclose(file);
    }

    return id;
}

int getRegistro(char *tipoRegistro, char *registro)
{
    int existe = 0;

    if (strcmp(tipoRegistro, REGISTRO_USUARIO) == 0)
    {
        FILE *file;
        file = fopen("Record", "r");

        while (!feof(file))
        {
            fread(&Usuario, sizeof(Usuario), 1, file);

            if (strcmp(registro, Usuario.correo) == 0)
            {
                existe = 1;
            }
        }
        fclose(file);
    }

    return existe;
}

void crearRegistro(char *registro)
{
    if (strcmp(registro, REGISTRO_USUARIO) == 0)
    {
        FILE *file;
        Role metodoAcceso = NORMAL;
        file = fopen("Record", "a");
        Usuario.id = (setId(REGISTRO_USUARIO) + 1);
        Usuario.acceso = metodoAcceso;
        printf("Nombre: ");
        scanf("\n%[^\n]", Usuario.nombre);
        printf("Correo: ");
        scanf("\n%[^\n]", Usuario.correo);
        printf("Contrasenya: ");
        scanf("\n%[^\n]", Usuario.pass);

        fwrite(&Usuario, sizeof(Usuario), 1, file);
        fclose(file);

        printf("\nUsuario registrado correctamente\n");
        system("pause>null");
    }
    if (strcmp(registro, REGISTRO_PELICULA) == 0)
    {
        FILE *file;
        file = fopen("Pelicula", "a");
        Usuario.id = (setId(REGISTRO_PELICULA) + 1);
        printf("Titulo: ");
        scanf("\n%[^\n]", Pelicula.titulo);
        printf("Genero: ");
        scanf("\n%[^\n]", Pelicula.genero);
        // printf("Contrasenya: ");
        // scanf("\n%[^\n]", Usuario.pass);

        fwrite(&Pelicula, sizeof(Pelicula), 1, file);
        fclose(file);

        printf("\nPelicula registrada correctamente\n");
        system("pause>null");
    }
}

void mostrarRegistros(char *registro)
{
    if (strcmp(registro, REGISTRO_USUARIO) == 0)
    {
        FILE *file;
        file = fopen("Record", "r");
        printf("\nid\t\tNombre\t\tCorreo\t\tPassword\t\tAcceso\n\n");
        while (fread(&Usuario, sizeof(Usuario), 1, file))
        {
            printf("  %i\t\t%s\t\t%s\t\t%s\t\t%i\n", Usuario.id, Usuario.nombre, Usuario.correo, Usuario.pass, Usuario.acceso);
        }
        fclose(file);
        system("pause>null");
    }

    if (strcmp(registro, REGISTRO_PELICULA) == 0)
    {
        FILE *file;
        file = fopen("Pelicula", "r");
        printf("\nid\t\tTitulo\t\tGenero\t\tHorarios\n\n");
        while (fread(&Pelicula, sizeof(Pelicula), 1, file))
        {
            printf("  %i\t\t%s\t\t%s\n", Pelicula.id, Pelicula.titulo, Pelicula.genero);
        }
        fclose(file);
        system("pause>null");
    }
}

void actualizarRegistro(char *registro)
{
    if (strcmp(registro, REGISTRO_USUARIO) == 0)
    {
        FILE *file;
        FILE *tmpfile;
        int existe;
        int opcion;
        char correo[LENGTH];
        char *UCorreo;

        printf("Digite correo: ");
        scanf("\n%[^\n]", correo);

        existe = getRegistro(REGISTRO_USUARIO, correo);

        if (existe == 0)
        {
            printf("No se encontraron registros para el correo: %s", correo);
        }
        else
        {
            tmpfile = fopen("Record", "r");
            file = fopen("TempFile", "w");
            while (fread(&Usuario, sizeof(Usuario), 1, tmpfile))
            {
                UCorreo = Usuario.correo;

                if (strcmp(correo, UCorreo) != 0)
                {
                    fwrite(&Usuario, sizeof(Usuario), 1, file);
                }
                else
                {
                    char opciones[][LENGTH] = {
                        "Nombre",
                        "Correo",
                        "Contrasenya",
                        "Acceso",
                        "Regresar",
                    };

                    do
                    {
                        opcion = seleccion(MENU_ACTUALIZAR_USER, opciones, 5);

                        switch (opcion)
                        {
                        case 1:
                            printf("Nombre: ");
                            scanf("\n%[^\n]", Usuario.nombre);
                            break;
                        case 2:
                            printf("Correo: ");
                            scanf("\n%[^\n]", Usuario.correo);
                            break;
                        case 3:
                            printf("Contrasenya: ");
                            scanf("\n%[^\n]", Usuario.pass);
                            break;
                        case 4:
                            printf("Acceso: ");
                            system("pause>null");
                            break;
                        }
                    } while (opcion != 5);

                    fwrite(&Usuario, sizeof(Usuario), 1, file);
                }
            }
            fclose(tmpfile);
            fclose(file);
            tmpfile = fopen("Record", "w");
            file = fopen("TempFile", "r");
            while (fread(&Usuario, sizeof(Usuario), 1, file))
            {
                fwrite(&Usuario, sizeof(Usuario), 1, tmpfile);
            }
            fclose(tmpfile);
            fclose(file);
            printf("RECORD UPDATED");
        }
    }

    // if (strcmp(registro, REGISTRO_PELICULA) == 0)
    // {
    //     FILE *file;
    //     FILE *tmpfile;
    //     int existe;
    //     int opcion;
    //     char Titulo[LENGTH];
    //     char *UTitulo;

    //     printf("Digite titulo: ");
    //     scanf("\n%[^\n]", titulo);

    //     existe = getCorreo(correo);

    //     if (existe == 0)
    //     {
    //         printf("No se encontraron registros para el correo: %s", correo);
    //     }
    //     else
    //     {
    //         tmpfile = fopen("Record", "r");
    //         file = fopen("TempFile", "w");
    //         while (fread(&Usuario, sizeof(Usuario), 1, tmpfile))
    //         {
    //             UCorreo = Usuario.correo;

    //             if (strcmp(correo, UCorreo) != 0)
    //             {
    //                 fwrite(&Usuario, sizeof(Usuario), 1, file);
    //             }
    //             else
    //             {
    //                 char opciones[][LENGTH] = {
    //                     "Nombre",
    //                     "Correo",
    //                     "Contrasenya",
    //                     "Acceso",
    //                     "Regresar",
    //                 };

    //                 do
    //                 {
    //                     opcion = seleccion(MENU_ACTUALIZAR_USER, opciones, 5);

    //                     switch (opcion)
    //                     {
    //                     case 1:
    //                         printf("Nombre: ");
    //                         scanf("\n%[^\n]", Usuario.nombre);
    //                         break;
    //                     case 2:
    //                         printf("Correo: ");
    //                         scanf("\n%[^\n]", Usuario.correo);
    //                         break;
    //                     case 3:
    //                         printf("Contrasenya: ");
    //                         scanf("\n%[^\n]", Usuario.pass);
    //                         break;
    //                     case 4:
    //                         printf("Acceso: ");
    //                         system("pause>null");
    //                         break;
    //                     }
    //                 } while (opcion != 5);

    //                 fwrite(&Usuario, sizeof(Usuario), 1, file);
    //             }
    //         }
    //         fclose(tmpfile);
    //         fclose(file);
    //         tmpfile = fopen("Record", "w");
    //         file = fopen("TempFile", "r");
    //         while (fread(&Usuario, sizeof(Usuario), 1, file))
    //         {
    //             fwrite(&Usuario, sizeof(Usuario), 1, tmpfile);
    //         }
    //         fclose(tmpfile);
    //         fclose(file);
    //         printf("RECORD UPDATED");
    //     }
    // }
}

void eliminarRegistro(char *registro)
{
    if (strcmp(registro, REGISTRO_USUARIO) == 0)
    {
        FILE *tmpfile;
        FILE *file;
        char correo[LENGTH];
        char *UCorreo;
        int existe;

        printf("Digite correo: ");
        scanf("\n%[^\n]", correo);

        existe = getRegistro(REGISTRO_USUARIO, correo);

        if (existe == 0)
        {
            printf("No se encontraron registros para el correo: %s", correo);
        }
        else
        {
            tmpfile = fopen("Record", "r");
            file = fopen("TempFile", "w");
            while (fread(&Usuario, sizeof(Usuario), 1, tmpfile))
            {
                UCorreo = Usuario.correo;

                if (strcmp(correo, UCorreo) != 0)
                {
                    fwrite(&Usuario, sizeof(Usuario), 1, file);
                }
            }
            fclose(tmpfile);
            fclose(file);
            tmpfile = fopen("Record", "w");
            file = fopen("TempFile", "r");
            while (fread(&Usuario, sizeof(Usuario), 1, file))
            {
                fwrite(&Usuario, sizeof(Usuario), 1, tmpfile);
            }
            fclose(tmpfile);
            fclose(file);
            printf("Usuario eliminado");
            system("pause>null");
        }
    }
}