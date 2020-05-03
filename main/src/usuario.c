#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "helpers.h"
#include "usuario.h"
#include "menus.h"
#include "_define.h"

void crearRegistro(char *registro)
{
    if (strcmp(registro, REGISTRO_USUARIO) == 0)
    {
        FILE *file;
        Role metodoAcceso = NORMAL;
        file = fopen("Record", "a");
        Usuario.id = (setId() + 1);
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

        existe = getCorreo(correo);

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
}

void eliminarUsuario()
{
    FILE *tmpfile;
    FILE *file;
    char correo[LENGTH];
    char *UCorreo;
    int existe;

    printf("Digite correo: ");
    scanf("\n%[^\n]", correo);

    existe = getCorreo(correo);

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

int inicioSesion()
{
    char correo[LENGTH];
    char password[LENGTH];
    int intento = 0;
    int loginOk = 0;
    char caracter;
    int i = 0;

    do
    {
        titulo();
        cabeceraInicioSesion();
        printf("\nCoreo: ");
        gets(correo);
        printf("Contrasenya: ");
        while ((caracter = getch()))
        {
            if (caracter == ENTER)
            {
                password[i] = '\0';
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
                if (i < LENGTH)
                {
                    printf("*");
                    password[i] = caracter;
                    i++;
                }
            }
        }

        if (
            // Si es el super usuario quemado en el codigo
            (strcmp(correo, SUPER_ADMIN_USUARIO) == 0 && strcmp(password, SUPER_ADMIN_PASSWORD) == 0) ||
            (validarUsuario(correo, password) == 0) // si es un usuario en la base de datos
        )
        {
            loginOk = 1;
        }
        else
        {
            printf("\n\tCorreo y/o contrasenya son incorrectos\n");
            intento++;
            getchar();
        }

    } while (intento < 3 && loginOk == 0);

    if (loginOk == 1)
    {
        menuPerfil(getAcceso(correo));
    }
    else
    {
        printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
        system("pause>null");
    }

    return 0;
}

int setId()
{
    FILE *file;
    file = fopen("Record", "r");
    int id = 0;

    while (fread(&Usuario, sizeof(Usuario), 1, file))
    {
        id++;
    }
    fclose(file);
    return id;
}

// Funcion para verificar si el usuario existe
// Si correo existe devuelve 1
int getCorreo(char *correo)
{
    FILE *file;
    file = fopen("Record", "r");
    int existe = 0;

    while (!feof(file))
    {
        fread(&Usuario, sizeof(Usuario), 1, file);

        if (strcmp(correo, Usuario.correo) == 0)
        {
            existe = 1;
        }
    }

    fclose(file);
    return existe;
}

// Validar usuario.
int validarUsuario(char *correo, char *password)
{
    FILE *file;
    file = fopen("Record", "r");
    while (!feof(file))
    {
        fread(&Usuario, sizeof(Usuario), 1, file);

        if (strcmp(correo, Usuario.correo) == 0)
        {
            // Se encontro el correo electronico
            if (strcmp(password, Usuario.pass) == 0)
            {
                // La contraseña concuerda con el usuario
                fclose(file);
                return 0;
            }

            // El correo existe pero la contraseña no
            fclose(file);
            return 1;
        }
    }

    // El correo no existe
    fclose(file);
    return 1;
}

// Nunca deberia de regresar -1
// Porque se supone que a este punto el usuario ya esta validado con usuario y contraseña
int getAcceso(char *correo)
{
    FILE *file;
    file = fopen("Record", "r");
    int acceso = -1;

    if (strcmp(correo, SUPER_ADMIN_USUARIO) == 0)
    {
        acceso = SUPER_ADMIN_ACCESO;
    }
    else
    {
        while (!feof(file))
        {
            fread(&Usuario, sizeof(Usuario), 1, file);

            if (strcmp(correo, Usuario.correo) == 0)
            {
                acceso = Usuario.acceso;
            }
        }
    }

    fclose(file);
    return acceso;
}