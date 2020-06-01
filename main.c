#include <stdio.h>
#include <windows.h>

// -------------------------------------------------------------------------------- Constantes
// General
#define LEN 80
#define NUM_SALAS 10
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
#define MENU_PERFIL "MENU_PERFIL"
#define MENU_ACTUALIZAR_USUARIO "MENU_ACTUALIZAR_USUARIO"
#define MENU_ADMINISTRAR_PELICULAS "MENU_ADMINISTRAR_PELICULAS"
#define MENU_ADMINISTRAR_SALAS "MENU_ADMINISTRAR_SALAS"
// Registros
#define USUARIO "USUARIO"
#define PELICULA "PELICULA"
#define SALA "SALA"
// Archivos
#define ARCHIVO_USUARIOS "Usuarios"
#define ARCHIVO_PELICULAS "Peliculas"
#define ARCHIVO_SALAS "Salas"
#define ARCHIVO_TMP "Tmp"
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

struct
{
    int id;
    char titulo[LEN];
    char genero[LEN];
    // DATE horarios
} Pelicula;

struct
{
    int id;
    char pelicula[LEN];
    int disponibilidad;
} Sala;

// -------------------------------------------------------------------------------- Prototipos
// General
int getch();
// Menus
void menuPrincipal();
void menuPerfil(int acceso);
void menuUsuarios();
void menuPeliculas();
void menuSalas();
// Helpers
int seleccion(char *menu, char opcs[][LEN], int nOpcs);
void selector(int posicionReal, int posicionSelector);
int validarUsuario(char *correo, char *password);
int setId(char *registro);
int getAcceso(char *correo);
int getRegistro(char *tipoRegistro, char *registro);
int inicioSesion();
void crearRegistro(char *registro);
void mostrarRegistros(char *registro);
void actualizarRegistro(char *registro);
void eliminarRegistro(char *registro);
// Cabeceras
void titulo();
void cabeceraMenuPrincipal();
void cabeceraInicioSesion();
void cabeceraMenuPerfilAdmin();
void cabeceraMenuPerfil();
void cabeceraMenuPeliculas();
void cabeceraMenuSalas();

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

    while (tecla != ENTER)
    {
        titulo();
        // titulo del menu
        if (strcmp(menu, MENU_PRINCIPAL) == 0)
        {
            cabeceraMenuPrincipal();
        }
        if (strcmp(menu, MENU_PERFIL) == 0)
        {
            cabeceraMenuPerfil();
        }
        if (strcmp(menu, MENU_PERFIL_ADMIN) == 0)
        {
            cabeceraMenuPerfilAdmin();
        }
        if (strcmp(menu, MENU_ADMINISTRAR_PELICULAS) == 0)
        {
            cabeceraMenuPeliculas();
        }
        if (strcmp(menu, MENU_ADMINISTRAR_SALAS) == 0)
        {
            cabeceraMenuSalas();
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
    fflush(stdin);

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
            id = Usuario.id;
        }
        fclose(file);
    }

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_PELICULAS, "r");

        while (fread(&Pelicula, sizeof(Pelicula), 1, file))
        {
            id = Pelicula.id;
        }
        fclose(file);
    }

    if (strcmp(registro, SALA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_SALAS, "r");

        while (fread(&Sala, sizeof(Sala), 1, file))
        {
            id = Sala.id;
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

int getRegistro(char *tipoRegistro, char *registro)
{
    int existe = 0;

    if (strcmp(tipoRegistro, USUARIO) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_USUARIOS, "r");

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

    if (strcmp(tipoRegistro, PELICULA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_PELICULAS, "r");

        while (!feof(file))
        {
            fread(&Pelicula, sizeof(Pelicula), 1, file);

            if (strcmp(registro, Pelicula.titulo) == 0)
            {
                existe = 1;
            }
        }
        fclose(file);
    }

    return existe;
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

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_PELICULAS, "a");
        Pelicula.id = (setId(PELICULA) + 1);

        printf("Titulo: ");
        scanf("\n%[^\n]", Pelicula.titulo);
        printf("Genero: ");
        scanf("\n%[^\n]", Pelicula.genero);

        fwrite(&Pelicula, sizeof(Pelicula), 1, file);
        fclose(file);

        printf("\nPelicula registrada correctamente\n");
        system("pause>null");
    }

    // TODO: refactorizar para que soporte seleccion en lugar de escribir
    if (strcmp(registro, SALA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_SALAS, "a");
        Sala.id = (setId(SALA) + 1);

        printf("Pelicula: ");
        scanf("\n%[^\n]", Sala.pelicula);
        Sala.disponibilidad = 40;

        fwrite(&Sala, sizeof(Sala), 1, file);
        fclose(file);

        printf("\nSe agrego pelicula a sala correctamente\n");
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

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_PELICULAS, "r");
        printf("\nid\t\tTitulo\t\tGenero\n\n");
        while (fread(&Pelicula, sizeof(Pelicula), 1, file))
        {
            printf("  %i\t\t%s\t\t%s\n", Pelicula.id, Pelicula.titulo, Pelicula.genero);
        }
        fclose(file);
        system("pause>null");
    }

    if (strcmp(registro, SALA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_SALAS, "r");
        int disponible;
        int i;

        printf("\nNo. Sala\t\tPelicula\t\tDisponibilidad\n\n");

        // imprimiendo salas
        for (i = 1; i <= NUM_SALAS; i++)
        {
            disponible = 0;
            // recorriendo el archivo salas
            while (fread(&Sala, sizeof(Sala), 1, file))
            {
                printf("  %i\t\t%s\t\t%i\n", Sala.id, Sala.pelicula, Sala.disponibilidad);
                disponible = 1;
            }

            if (disponible == 0)
            {
                printf(" %i\t\tDisponible\n", i);
            }
        }
        fclose(file);
        system("pause>null");
    }
}

void actualizarRegistro(char *registro)
{
    if (strcmp(registro, USUARIO) == 0)
    {
        FILE *file;
        FILE *tmpfile;
        int existe;
        int opcion;
        char correo[LEN];
        char *Correo;

        printf("Digite correo: ");
        scanf("\n%[^\n]", correo);

        existe = getRegistro(USUARIO, correo);

        if (existe == 0)
        {
            printf("No se encontraron registros para el correo: %s", correo);
            system("pause>null");
        }
        else
        {
            file = fopen(ARCHIVO_USUARIOS, "r");
            tmpfile = fopen(ARCHIVO_TMP, "w");
            while (fread(&Usuario, sizeof(Usuario), 1, file))
            {
                Correo = Usuario.correo;

                if (strcmp(correo, Correo) != 0)
                {
                    fwrite(&Usuario, sizeof(Usuario), 1, tmpfile);
                }
                else
                {
                    char opciones[][LEN] = {
                        "Nombre",
                        "Correo",
                        "Contrasenya",
                        "Acceso",
                        "Regresar",
                    };

                    do
                    {
                        opcion = seleccion(MENU_ACTUALIZAR_USUARIO, opciones, 5);

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

                    fwrite(&Usuario, sizeof(Usuario), 1, tmpfile);
                }
            }
            fclose(file);
            fclose(tmpfile);
            file = fopen(ARCHIVO_USUARIOS, "w");
            tmpfile = fopen(ARCHIVO_TMP, "r");
            while (fread(&Usuario, sizeof(Usuario), 1, tmpfile))
            {
                fwrite(&Usuario, sizeof(Usuario), 1, file);
            }
            fclose(file);
            fclose(tmpfile);
            printf("Usuario actualizado.");
            system("pause>null");
        }
    }

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *file;
        FILE *tmpfile;
        int existe;
        int opcion;
        char titulo[LEN];
        char *Titulo;

        printf("Digite titulo: ");
        scanf("\n%[^\n]", titulo);

        existe = getRegistro(PELICULA, titulo);

        if (existe == 0)
        {
            printf("No se encontraron registros para el titulo: %s", titulo);
            system("pause>null");
        }
        else
        {
            file = fopen(ARCHIVO_PELICULAS, "r");
            tmpfile = fopen(ARCHIVO_TMP, "w");
            while (fread(&Pelicula, sizeof(Pelicula), 1, file))
            {
                Titulo = Pelicula.titulo;

                if (strcmp(titulo, Titulo) != 0)
                {
                    fwrite(&Pelicula, sizeof(Pelicula), 1, tmpfile);
                }
                else
                {
                    char opciones[][LEN] = {
                        "Titulo",
                        "Genero",
                        "Regresar",
                    };

                    do
                    {
                        opcion = seleccion(MENU_ADMINISTRAR_PELICULAS, opciones, 3);

                        switch (opcion)
                        {
                        case 1:
                            printf("Titulo: ");
                            scanf("\n%[^\n]", Pelicula.titulo);
                            break;
                        case 2:
                            printf("Genero: ");
                            scanf("\n%[^\n]", Pelicula.genero);
                            break;
                        }
                    } while (opcion != 3);

                    fwrite(&Pelicula, sizeof(Pelicula), 1, tmpfile);
                }
            }
            fclose(file);
            fclose(tmpfile);
            file = fopen(ARCHIVO_PELICULAS, "w");
            tmpfile = fopen(ARCHIVO_TMP, "r");
            while (fread(&Pelicula, sizeof(Pelicula), 1, tmpfile))
            {
                fwrite(&Pelicula, sizeof(Pelicula), 1, file);
            }
            fclose(file);
            fclose(tmpfile);
            printf("Pelicula actualizado.");
            system("pause>null");
        }
    }
}

void eliminarRegistro(char *registro)
{
    if (strcmp(registro, USUARIO) == 0)
    {
        FILE *tmpfile;
        FILE *file;
        char correo[LEN];
        char *UCorreo;
        int existe;

        printf("Digite correo: ");
        scanf("\n%[^\n]", correo);

        existe = getRegistro(USUARIO, correo);

        if (existe == 0)
        {
            printf("No se encontraron registros para el correo: %s", correo);
        }
        else
        {
            file = fopen(ARCHIVO_USUARIOS, "r");
            tmpfile = fopen(ARCHIVO_TMP, "w");
            while (fread(&Usuario, sizeof(Usuario), 1, file))
            {
                UCorreo = Usuario.correo;

                if (strcmp(correo, UCorreo) != 0)
                {
                    fwrite(&Usuario, sizeof(Usuario), 1, tmpfile);
                }
            }
            fclose(file);
            fclose(tmpfile);
            file = fopen(ARCHIVO_USUARIOS, "w");
            tmpfile = fopen(ARCHIVO_TMP, "r");
            while (fread(&Usuario, sizeof(Usuario), 1, tmpfile))
            {
                fwrite(&Usuario, sizeof(Usuario), 1, file);
            }
            fclose(file);
            fclose(tmpfile);
            printf("Usuario eliminado");
            system("pause>null");
        }
    }

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *tmpfile;
        FILE *file;
        char titulo[LEN];
        char *Titulo;
        int existe;

        printf("Digite titulo: ");
        scanf("\n%[^\n]", titulo);

        existe = getRegistro(PELICULA, titulo);

        if (existe == 0)
        {
            printf("No se encontraron registros para el titulo: %s", titulo);
        }
        else
        {
            file = fopen(ARCHIVO_PELICULAS, "r");
            tmpfile = fopen(ARCHIVO_TMP, "w");
            while (fread(&Pelicula, sizeof(Pelicula), 1, file))
            {
                Titulo = Pelicula.titulo;

                if (strcmp(titulo, Titulo) != 0)
                {
                    fwrite(&Pelicula, sizeof(Pelicula), 1, tmpfile);
                }
            }
            fclose(file);
            fclose(tmpfile);
            file = fopen(ARCHIVO_PELICULAS, "w");
            tmpfile = fopen(ARCHIVO_TMP, "r");
            while (fread(&Pelicula, sizeof(Pelicula), 1, tmpfile))
            {
                fwrite(&Pelicula, sizeof(Pelicula), 1, file);
            }
            fclose(file);
            fclose(tmpfile);
            printf("Pelicula eliminada");
            system("pause>null");
        }
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
            "Administrar Salas",
            "Reporte",
            "Regresar",
        };

        do
        {
            opcion = seleccion(MENU_PERFIL_ADMIN, opciones, 5);
            switch (opcion)
            {
            case 1:
                menuUsuarios();
                break;
            case 2:
                menuPeliculas();
                break;
            case 3:
                menuSalas();
                break;
            case 4:
                printf("Reportes");
                system("pause>null");
                break;
            }
        } while (opcion != 5);
    }
    else
    {
        // PANEL DE USUARIO NORMAL
        int opcion;
        char opciones[][LEN] = {
            "Comprar entradas",
            "Mi perfil",
            "Regresar",
        };

        do
        {
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
            actualizarRegistro(USUARIO);
            break;
        case 4:
            eliminarRegistro(USUARIO);
            break;
        }
    } while (opcion != 5);
}

void menuPeliculas()
{

    int opcion;
    char opciones[][LEN] = {
        "Crear Pelicula",
        "Mostrar Peliculas",
        "Actualizar Pelicula",
        "Eliminar Pelicula",
        "Regresar",
    };

    do
    {
        opcion = seleccion(MENU_ADMINISTRAR_PELICULAS, opciones, 5);
        switch (opcion)
        {
        case 1:
            crearRegistro(PELICULA);
            break;
        case 2:
            mostrarRegistros(PELICULA);
            break;
        case 3:
            actualizarRegistro(PELICULA);
            break;
        case 4:
            eliminarRegistro(PELICULA);
            break;
        }
    } while (opcion != 5);
}

void menuSalas()
{
    int opcion;
    char opciones[][LEN] = {
        "Establecer numero de salas",
        "Mostrar salas",
        "Agregar pelicula a sala",
        "Remover pelicula de sala",
        "Regresar",
    };

    do
    {
        opcion = seleccion(MENU_ADMINISTRAR_SALAS, opciones, 5);
        switch (opcion)
        {
        case 1:
            printf("Establecer numero de salas");
            system("pause>null");
            break;
        case 2:
            mostrarRegistros(SALA);
            break;
        case 3:
            crearRegistro(SALA);
            // printf("Agregar pelicula a sala");
            // system("pause>null");
            break;
        case 4:
            printf("Remover pelicula de sala");
            system("pause>null");
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

void cabeceraMenuPerfil()
{
    puts("|------------------------------------------------------|");
    puts("|                        Perfil                        |");
    puts("|------------------------------------------------------|");
}

void cabeceraMenuPeliculas()
{
    puts("|------------------------------------------------------|");
    puts("|                 Administrar peliculas                |");
    puts("|------------------------------------------------------|");
}

void cabeceraMenuSalas()
{
    puts("|------------------------------------------------------|");
    puts("|                  Administrar Salas                   |");
    puts("|------------------------------------------------------|");
}