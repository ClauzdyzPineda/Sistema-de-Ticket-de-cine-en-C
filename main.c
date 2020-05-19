#include <stdio.h>
#include <windows.h>

// -------------------------------------------------------------------------------- Constantes
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
#define MENU_PERFIL_ADMIN "MENU_PERFIL_ADMIN"
// Registros
#define USUARIO "USUARIO"
// Archivos
#define ARCHIVO_USUARIOS "Usuarios"
#define TMP "Tmp"
//modelos
typedef enum
{
    NORMAL,
    ADMIN
} Role;

struct
{
    int id;
    char nombre[LEN];
    char pass[LEN];
    char correo[LEN];
    Role acceso;
} Usuario;

// -------------------------------------------------------------------------------- Prototipos
// General
int getch();
// Menus
void menuPrincipal();
void menuPerfil(int acceso);
void menuUsuarios();
void menuUsuarios();
// Helpers
int seleccion(char *menu, char opcs[][LEN], int nOpcs);
void selector(int posicionReal, int posicionSelector);
int validarUsuario(char *correo, char *password);
int setId(char *registro);
int getAcceso(char *correo);
int inicioSesion();
void crearRegistro(char *registro);
void mostrarRegistros(char *registro);
// Cabeceras
void titulo();
void cabeceraMenuPrincipal();
void cabeceraInicioSesion();
void cabeceraMenuPerfilAdmin();

// -------------------------------------------------------------------------------- Main
int main()
{
    menuPrincipal();
    system("cls");
    return 0;
}

// -------------------------------------------------------------------------------- Helpers
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
        if (strcmp(menu, MENU_PERFIL_ADMIN) == 0)
        {
            cabeceraMenuPerfilAdmin();
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

int setId(char *registro)
{
    int id = 0;

    if (strcmp(registro, USUARIO) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_USUARIOS, "r");

        while (fread(&Usuario, sizeof(Usuario), 1, file))
        {
            id++;
        }
        fclose(file);
    }

    return id;
}

int validarUsuario(char *correo, char *password)
{
    FILE *file;
    file = fopen(ARCHIVO_USUARIOS, "r");
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
    int acceso = -1;

    if (strcmp(correo, SUPER_ADMIN_USER) == 0)
    {
        acceso = SUPER_ADMIN_ACCESO;
    }
    else
    {
        FILE *file;
        file = fopen(ARCHIVO_USUARIOS, "r");
        while (!feof(file))
        {
            fread(&Usuario, sizeof(Usuario), 1, file);
            if (strcmp(correo, Usuario.correo) == 0)
            {
                acceso = Usuario.acceso;
            }
        }
    }

    return acceso;
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

        if (
            (strcmp(correo, SUPER_ADMIN_USER) == 0 && strcmp(password, SUPER_ADMIN_PASS) == 0) ||
            validarUsuario(correo, password) == 0)
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

void crearRegistro(char *registro)
{
    if (strcmp(registro, USUARIO) == 0)
    {
        FILE *file;
        Role metodoAcceso = NORMAL;
        file = fopen(ARCHIVO_USUARIOS, "a");
        Usuario.id = (setId(USUARIO) + 1);
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
    if (strcmp(registro, USUARIO) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_USUARIOS, "r");
        printf("\nid\t\tNombre\t\tCorreo\t\tPassword\t\tAcceso\n\n");
        while (fread(&Usuario, sizeof(Usuario), 1, file))
        {
            printf("  %i\t\t%s\t\t%s\t\t%s\t\t%i\n", Usuario.id, Usuario.nombre, Usuario.correo, Usuario.pass, Usuario.acceso);
        }
        fclose(file);
        system("pause>null");
    }
}

// -------------------------------------------------------------------------------- Menus
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

void menuPerfil(int acceso)
{
    Role esAdmin = ADMIN;
    if (acceso == esAdmin)
    {
        int opcion;
        char opciones[][LEN] = {
            "Administrar usuarios",
            "Administrar Peliculas",
            "Regresar",
        };

        do
        {
            opcion = seleccion(MENU_PERFIL_ADMIN, opciones, 3);
            switch (opcion)
            {
            case 1:
                menuUsuarios();
                break;
            case 2:
                printf("Menu peliculas");
                system("pause>null");
                break;
            }
        } while (opcion != 3);
    }
    else
    {
        printf("MEno de usuario normal");
        system("pause>null");
    }
}

void menuUsuarios()
{

    int opcion;
    char opciones[][LEN] = {
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
            crearRegistro(USUARIO);
            break;
        case 2:
            mostrarRegistros(USUARIO);
            break;
        case 3:
            // actualizarRegistro(USUARIO);
            printf("actualizar usuarios");
            system("cls");
            break;
        case 4:
            // eliminarRegistro(USUARIO);
            printf("eliminar usuarios");
            system("cls");
            break;
        }
    } while (opcion != 5);
}

// -------------------------------------------------------------------------------- Cabeceras
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

void cabeceraMenuPerfilAdmin()
{
    puts("|------------------------------------------------------|");
    puts("|                Perfil de administrador               |");
    puts("|------------------------------------------------------|");
}