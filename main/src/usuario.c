#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include <windows.h>

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