#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "helpers.h"
#include "usuario.h"
#include "menus.h"
#include "_define.h"
#include "cabeceras.h"

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
    file = fopen(REGISTRO_USUARIO, "r");
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