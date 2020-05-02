#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "usuario.h"
#include "_define.h"

void registro()
{
    FILE *file;
    Role metodoAcceso = NORMAL;
    file = fopen("Record", "a");
    Usuario.id = (setId() + 1);
    Usuario.acceso = metodoAcceso;
    printf("Digite su nombre :");
    scanf("\n%[^\n]", &Usuario.nombre);
    printf("Digite su correo :");
    scanf("\n%[^\n]", &Usuario.correo);
    printf("Digite su contrasenya :");
    scanf("\n%[^\n]", &Usuario.pass);

    fwrite(&Usuario, sizeof(Usuario), 1, file);
    fclose(file);
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
            (strcmp(correo, SUPER_ADMIN_USUARIO) == 0 && strcmp(password, SUPER_ADMIN_USUARIO) == 0) ||
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
        getAcceso(correo);
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

void mostrarUsuarios()
{
    FILE *file;
    file = fopen("Record", "r");
    printf("\nid\t\tNombre\t\tCorreo\t\tPassword\t\tAcceso\n\n");
    while (fread(&Usuario, sizeof(Usuario), 1, file))
    {
        printf("  %i\t\t%s\t\t%s\t\t%s\t\t%i\n", Usuario.id, Usuario.nombre, Usuario.correo, Usuario.pass, Usuario.acceso);
    }
    fclose(file);
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
int getCorreo(char *correo)
{
    FILE *file;
    int c = 0;
    file = fopen("Record", "r");
    while (!feof(file))
    {
        fread(&Usuario, sizeof(Usuario), 1, file);

        if (strcmp(correo, Usuario.correo) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Validar usuario.
int validarUsuario(char *correo, char *password)
{
    FILE *file;
    int c = 0;
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

int getAcceso(char *correo)
{
    FILE *file;
    file = fopen("Record", "r");
    int acceso;
    while (!feof(file))
    {
        fread(&Usuario, sizeof(Usuario), 1, file);

        if (strcmp(correo, Usuario.correo) == 0)
        {
            acceso = Usuario.acceso;
            fclose(file);
            return acceso;
        }
    }

    // No deberia de llegar aqui.
    fclose(file);
    return -1;
}