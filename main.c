#include <stdio.h>
#include <windows.h>

// -------------------------------------------------- Constantes
// General
#define LEN 80
// Informacion del super administrador
#define SUPER_ADMIN_USER "c"
#define SUPER_ADMIN_PASS "med"
#define SUPER_ADMIN_ACCESO 1
// Tecla
#define ENTER 13
#define BACKSPACE 8
#define ARRIBA 80
#define ABAJO 72
// Menus
#define MENU_PRINCIPAL "MENU_PRINCIPAL"
// Registros
#define USUARIO "USUARIO"
// Archivos
#define ARCHIVO_USUARIOS "Usuarios"
#define TMP "Tmp"

// -------------------------------------------------- Prototipos
// General
int getch();
// Menus
void menuPrincipal();
// Helpers
int seleccion(char *menu, char opcs[][LEN], int nOpcs);
void selector(int posicionReal, int posicionSelector);
int inicioSesion();
// Cabeceras
void titulo();
void cabeceraMenuPrincipal();
void cabeceraInicioSesion();

// -------------------------------------------------- Main
int main()
{
    menuPrincipal();
    system("cls");
    return 0;
}

// -------------------------------------------------- Helpers
int seleccion(char *menu, char opcs[][LEN], int nOpcs)
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

        for (i = 0; i < nOpcs; i++)
        {
            selector((i + 1), posicion);
            printf("%s\n", opcs[i]);
        }

        // escuchando tecla
        tecla = getch();

        // tecla 80 = abajo
        // tecla 72 = arriba
        if (tecla == ARRIBA && posicion != nOpcs)
        {
            posicion++;
        }
        else if (tecla == ARRIBA && posicion == nOpcs)
        {
            posicion = 1;
        }
        else if (tecla == ABAJO && posicion == 1)
        {
            posicion = nOpcs;
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

int inicioSesion()
{
    char correo[LEN];
    char password[LEN];
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
                if (i < LEN)
                {
                    printf("*");
                    password[i] = caracter;
                    i++;
                }
            }
        }

        // if (
        //     // Si es el super usuario quemado en el codigo
        //     (strcmp(correo, SUPER_ADMIN_USER) == 0 && strcmp(password, SUPER_ADMIN_PASS) == 0) ||
        //     (validarUsuario(correo, password) == 0) // si es un usuario en la base de datos
        // )
        // Si es el super usuario quemado en el codigo
        if (strcmp(correo, SUPER_ADMIN_USER) == 0 && strcmp(password, SUPER_ADMIN_PASS) == 0)
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
        printf("\n\tInicio de sesion correcto\n");
        system("pause>null");
    }
    else
    {
        printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
        system("pause>null");
    }

    return 0;
}

// -------------------------------------------------- Menus
void menuPrincipal()
{
    int opcion;
    char opciones[][LEN] = {
        "Ver cartelera",
        "Registrate",
        "Iniciar sesion",
        "Salir",
    };

    do
    {
        opcion = seleccion(MENU_PRINCIPAL, opciones, 4);
        switch (opcion)
        {
        case 1:
            printf("\nSection ver cartelera\n");
            system("pause>null"); // Si se borra, porfavor, eliminar windows
            break;
        case 2:
            printf("\nSection Registrarse\n");
            system("pause>null"); // Si se borra, porfavor, eliminar windows
            break;
        case 3:
            inicioSesion();
            break;
        }
    } while (opcion != 4);
}

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

// -------------------------------------------------- Cabeceras
void titulo()
{
    system("cls");
    puts("|------------------------------------------------------|");
    puts("|     Administracion de sistema de tickets de cine     |");
    puts("|------------------------------------------------------|");
}

void cabeceraMenuPrincipal()
{
    puts("|------------------------------------------------------|");
    puts("|                    Menu principal                    |");
    puts("|------------------------------------------------------|");
}

void cabeceraInicioSesion()
{
    puts("|------------------------------------------------------|");
    puts("|                   Inicio de sesion                   |");
    puts("|------------------------------------------------------|");
}