#include <stdio.h>
#include <windows.h>
#include <unistd.h>

// TODO
// Necesito crear el archivo Salas si no existe un archivo. para crear la estructura. y no tener que ordenar las salas.

// -------------------------------------------------------------------------------- Constantes
// General
#define LEN 80
#define NUM_SALAS 10
#define DISPONIBILIDAD_SALA 5
#define SALA_DISPONIBLE "Disponible"
#define TICKET_PRECIO 3.00
// #define HORARIO1 "10:00 AM"
// #define HORARIO2 "1:00 PM"
// #define HORARIO3 "4:00 PM"
// #define HORARIO4 "7:00 PM"
// #define HORARIO5 "10:00 PM"
// Informacion del super administrador
#define SUPER_ADMIN_USER "c"
#define SUPER_ADMIN_PASS "med"
#define SUPER_ADMIN_ACCESO 1
#define SUPER_ADMIN_ID 0
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
#define FUNCION "FUNCION"
#define TICKET "TICKET"
// Archivos
#define ARCHIVO_USUARIOS "Usuarios"
#define ARCHIVO_PELICULAS "Peliculas"
#define ARCHIVO_SALAS "Salas"
#define ARCHIVO_FUNCIONES "Funciones"
#define ARCHIVO_TICKETS "Tickets"
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
} Pelicula;

struct
{
    int id;
    char pelicula[LEN];
} Sala;

struct
{
    int id;
    char horario[LEN];
    char fecha[11];
    char pelicula[LEN];
    int disponibilidad;
} Funcion;

struct
{
    int id;
    char fecha[11];
    // char horario[LEN];
    int usuario;
    // int pelicula;
    char pelicula[LEN];
    int cantidadTickets;
} Ticket;

// -------------------------------------------------------------------------------- Prototipos
// General
int getch();
// Menus
void menuPrincipal();
void menuPerfil(int acceso, int usuario);
void menuPerfilUsuario(int usuario);
void menuPerfilAdmin();
void menuUsuarios();
void menuPeliculas();
void menuSalas();
// Helpers
void crearArchivos();
int seleccion(char *menu, char opcs[][LEN], int nOpcs);
void selector(int posicionReal, int posicionSelector);
int validarUsuario(char *correo, char *password);
int setId(char *registro);
int getUsuarioId(int *correo);
int getAcceso(char *correo);
int getRegistro(char *tipoRegistro, char *registro);
int inicioSesion();
void crearRegistro(char *registro);
void mostrarRegistros(char *registro);
void actualizarRegistro(char *registro);
void eliminarRegistro(char *registro);
void comprarEntradas(int usuario);
int getNoSalas();
int getNoPeliculas();
void mostrarReportes();
// Cabeceras
void titulo();
void cabeceraMenuPrincipal();
void cabeceraInicioSesion();
void cabeceraMenuPerfilAdmin();
void cabeceraMenuPerfil();
void cabeceraMenuPeliculas();
void cabeceraMenuSalas();
void cabeceraComprarTicket();

// -------------------------------------------------------------------------------- Main
int main()
{
    crearArchivos();
    menuPrincipal();
    system("cls");
    return 0;
}

// -------------------------------------------------------------------------------- Helpers
void crearArchivos()
{
    // Si archivo Salas no existe entones crearlo
    if (access("Salas", F_OK) == -1)
    {
        FILE *file;
        file = fopen(ARCHIVO_SALAS, "a");
        int i;
        for (i = 1; i <= 10; i++)
        {
            Sala.id = i;
            strcpy(Sala.pelicula, SALA_DISPONIBLE);
            fwrite(&Sala, sizeof(Sala), 1, file);
        }

        fclose(file);
    }
}

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

    if (strcmp(registro, FUNCION) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_FUNCIONES, "r");

        while (fread(&Funcion, sizeof(Funcion), 1, file))
        {
            id = Funcion.id;
        }
        fclose(file);
    }

    if (strcmp(registro, TICKET) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_TICKETS, "r");

        while (fread(&Ticket, sizeof(Ticket), 1, file))
        {
            id = Ticket.id;
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
                // La contrase�a concuerda con el usuario
                fclose(file);
                return 0;
            }

            // El correo existe pero la contrase�a no
            fclose(file);
            return 1;
        }
    }

    // El correo no existe
    fclose(file);
    return 1;
}

// Nunca deberia de regresar -1;
int getUsuarioId(int *correo)
{
    int id = -1;

    if (strcmp(correo, SUPER_ADMIN_USER) == 0)
    {
        id = SUPER_ADMIN_ID;
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
                id = Usuario.id;
            }
        }
    }

    return id;
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
        printf("\n\t\t\tINICIO DE SESION\n");
        printf("\n\t-----------------------------------------------\n");
        printf("\n\tCoreo: ");
        gets(correo);
        printf("\n\tPassword: ");
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
        menuPerfil(getAcceso(correo), getUsuarioId(correo));
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
        printf("\n\t\t\tREGISTRO DE USUARIOS\n");
        printf("\n\t--------------------------------------------\n");
        printf("\tNombre: ");
        scanf("\n%[^\n]", Usuario.nombre);
        printf("\n\t--------------------------------------------\n");
        printf("\tCorreo: ");
        scanf("\n%[^\n]", Usuario.correo);
        printf("\n\t--------------------------------------------\n");
        printf("\tPassword: ");
        scanf("\n%[^\n]", Usuario.pass);
        printf("\n\t--------------------------------------------\n");

        // TODO: logica para validar si usuario con ese correo existe.

        fwrite(&Usuario, sizeof(Usuario), 1, file);
        fclose(file);

        printf("\n\t*****Usuario registrado correctamente******\n");
        system("pause>null");
    }

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_PELICULAS, "a");
        Pelicula.id = (setId(PELICULA) + 1);

		printf("\n\t\tREGISTRO DE PELICULAS\n");
		printf("\n\t--------------------------------------------\n");
        printf("\tTitulo: ");
        scanf("\n%[^\n]", Pelicula.titulo);
        printf("\n\t--------------------------------------------\n");
        printf("\tGenero: ");
        scanf("\n%[^\n]", Pelicula.genero);
        printf("\n\t--------------------------------------------\n");

        fwrite(&Pelicula, sizeof(Pelicula), 1, file);
        fclose(file);

        printf("\n\t*****Pelicula registrada correctamente*****\n");
        system("pause>null");
    }
}

// void mostrarRegistros(char *registro)
// {
//     if (strcmp(registro, USUARIO) == 0)
//     {
//         FILE *file;
//         file = fopen(ARCHIVO_USUARIOS, "r");
//         printf("\nid\t\tNombre\t\tCorreo\t\tPassword\t\tAcceso\n\n");
//         while (fread(&Usuario, sizeof(Usuario), 1, file))
//         {
//             printf("  %i\t\t%s\t\t%s\t\t%s\t\t%i\n", Usuario.id, Usuario.nombre, Usuario.correo, Usuario.pass, Usuario.acceso);
//         }
//         fclose(file);
//         system("pause>null");
//     }

//     if (strcmp(registro, PELICULA) == 0)
//     {
//         FILE *file;
//         file = fopen(ARCHIVO_PELICULAS, "r");
//         printf("\nid\t\tTitulo\t\tGenero\n\n");
//         while (fread(&Pelicula, sizeof(Pelicula), 1, file))
//         {
//             printf("  %i\t\t%s\t\t%s\n", Pelicula.id, Pelicula.titulo, Pelicula.genero);
//         }
//         fclose(file);
//         system("pause>null");
//     }

//     if (strcmp(registro, SALA) == 0)
//     {
//         FILE *file;
//         file = fopen(ARCHIVO_SALAS, "r");
//         printf("\nid\t\tPelicula\n");
//         while (fread(&Sala, sizeof(Sala), 1, file))
//         {
//             printf("%i\t\t%s\n", Sala.id, Sala.pelicula);
//         }
//         fclose(file);
//         system("pause>null");
//     }
// }


void mostrarRegistros(char *registro)
{
    if (strcmp(registro, USUARIO) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_USUARIOS, "r");
        printf("\n\t\t\t   REGISTROS DE USUARIOS EN EL SISTEMA\n");
        printf("\n");
        printf("*-----------------------------------------------------------------------------------------*\n");
        printf("|   ID  |                Nombre                   |          Correo                       |\n");
        printf("*-----------------------------------------------------------------------------------------*\n");
        while (fread(&Usuario, sizeof(Usuario), 1, file))
        {

            int v = 0;
            int u = 0;
            int co = 0;
            int acc = 0;

            v = (log10(Usuario.id) + 1);
            printf("\n| %i", Usuario.id);
            for (v; v < 6; v++)
            {
                printf(" ");
            }
            printf("| %s", Usuario.nombre);
            for (u = strlen(Usuario.nombre); u < 40; u++)
            {
                printf(" ");
            }
            printf("| %s", Usuario.correo);
            for (co = strlen(Usuario.correo); co < 35; co++)
            {
                printf(" ");
            }

            printf("\t  |");
        }
        printf("\n*-----------------------------------------------------------------------------------------*\n");
        fclose(file);
        system("pause>null");
    }

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_PELICULAS, "r");

        printf("\n\t                   REGISTROS DE PELICULAS EN EL SISTEMA\n");
        printf("\n");
        printf("*---------------------------------------------------------------------------------*\n");
        printf("|   ID  |                   Titulo                     |          Genero          |\n");
        printf("*---------------------------------------------------------------------------------*\n");

        while (fread(&Pelicula, sizeof(Pelicula), 1, file))
        {

            int p = 0;
            int tp = 0;
            int g = 0;

            p = (log10(Pelicula.id) + 1);
            printf("\n| %i", Pelicula.id);
            for (p; p < 6; p++)
            {
                printf(" ");
            }
            printf("| %s", Pelicula.titulo);
            for (tp = strlen(Pelicula.titulo); tp < 45; tp++)
            {
                printf(" ");
            }
            printf("| %s", Pelicula.genero);
            for (g = strlen(Pelicula.genero); g < 25; g++)
            {
                printf(" ");
            }

            printf("|");
        }

        printf("\n*---------------------------------------------------------------------------------*\n");
        fclose(file);
        system("pause>null");
    }

    if (strcmp(registro, SALA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_SALAS, "r");

        printf("\n\t             REGISTROS DE SALAS EN EL SISTEMA\n");
        printf("\n");
        printf("\t*--------------------------------------------------------------*\n");
        printf("\t|    ID        |                    Titulo                     |\n");
        printf("\t*--------------------------------------------------------------*\n");

        while (fread(&Sala, sizeof(Sala), 1, file))
        {
            printf("\t\t%i\t\t%s\n", Sala.id, Sala.pelicula);
        }
        printf("\t*--------------------------------------------------------------*\n");
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

		printf("\n\tACTUALIZACION DE DATOS DE USUARIO\n");
		printf("\n--------------------------------------------------\n");
        printf("\tDigite correo: ");
        scanf("\n%[^\n]", correo);

        existe = getRegistro(USUARIO, correo);

        if (existe == 0)
        {
            printf("\n\tNo se encontraron registros para el correo: %s", correo);
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
                        "Password",
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
                            printf("Password: ");
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
            printf("\n\t******Usuario actualizado******");
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

		printf("\n\tACTUALIZAR DATOS DE PELICULAS\n");
		printf("\n------------------------------------------------------\n");
        printf("\tDigite titulo: ");
        scanf("\n%[^\n]", titulo);

        existe = getRegistro(PELICULA, titulo);

        if (existe == 0)
        {
            printf("\n\tNo se encontraron registros para el titulo: %s", titulo);
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
                            printf("\tTitulo: ");
                            scanf("\n%[^\n]", Pelicula.titulo);
                            break;
                        case 2:
                            printf("\tGenero: ");
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
            printf("\n\t*****Pelicula actualizado*****");
            system("pause>null");
        }
    }

    // TODO: refactorizar para que soporte seleccion en lugar de escribir
    if (strcmp(registro, SALA) == 0)
    {
        FILE *file;
        FILE *filePeliculas;
        FILE *tmpfile;
        int salaId;
        int SalaID;
        int numeroSalaValido = 0;
        int i = 0;
        int posicion = 1;
        int tecla = 0;
        char pelicula[LEN];
        int noPeliculas = getNoPeliculas();
        char peliculas[noPeliculas + 1][LEN];

        // int existe;
        // int opcion;
        // char *Titulo;

        // Validando el numero de sala
        do
        {
            system("cls");
            titulo();
            cabeceraMenuSalas();
            printf("Digite numero: ");
            if (scanf("%i", &salaId) == 0)
            {
                printf("[Error] El valor no es valido. El valor tiene que ser un entero");
                system("pause>null");
                fflush(stdin);
            }
            else
            {
                if (salaId < 1 || salaId > NUM_SALAS)
                {
                    printf("[Error] El valor no es valido. El valor tiene que estar en el rango de 1 a %i", NUM_SALAS);
                    system("pause>null");
                    fflush(stdin);
                }
                else
                {
                    Sala.id = salaId;
                    numeroSalaValido = 1;
                }
            }
        } while (numeroSalaValido == 0);

        filePeliculas = fopen(ARCHIVO_PELICULAS, "r");
        while (fread(&Pelicula, sizeof(Pelicula), 1, filePeliculas))
        {
            strcpy(peliculas[i], Pelicula.titulo);
            i++;
        }
        fclose(filePeliculas);

        while (tecla != ENTER)
        {
            titulo();
            cabeceraMenuSalas();

            for (i = 1; i <= noPeliculas; i++)
            {
                selector(i, posicion);
                printf("Pelicula: %s\n", peliculas[i - 1]);
            }

            selector(i, posicion);
            printf("Regresar");

            // escuchando tecla
            tecla = getch();

            if (tecla == ARRIBA && posicion != (noPeliculas + 1))
            {
                posicion++;
            }
            else if (tecla == ARRIBA && posicion == (noPeliculas + 1))
            {
                posicion = 1;
            }
            else if (tecla == ABAJO && posicion == 1)
            {
                posicion = (noPeliculas + 1);
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

        // opcion para regresar al menu anterior
        if (posicion == noPeliculas + 1)
        {
            return;
        }

        strcpy(pelicula, peliculas[posicion - 1]);

        file = fopen(ARCHIVO_SALAS, "r");
        tmpfile = fopen(ARCHIVO_TMP, "w");
        while (fread(&Sala, sizeof(Sala), 1, file))
        {
            SalaID = Sala.id;

            if (SalaID != salaId)
            {
                fwrite(&Sala, sizeof(Sala), 1, tmpfile);
            }
            else
            {
                strcpy(Sala.pelicula, pelicula);
                fwrite(&Sala, sizeof(Sala), 1, tmpfile);
            }
        }
        fclose(file);
        fclose(tmpfile);
        file = fopen(ARCHIVO_SALAS, "w");
        tmpfile = fopen(ARCHIVO_TMP, "r");
        while (fread(&Sala, sizeof(Sala), 1, tmpfile))
        {
            fwrite(&Sala, sizeof(Sala), 1, file);
        }
        fclose(file);
        fclose(tmpfile);

        // Creando el archivo de las funciones por pelicula
        FILE *fileFunciones;
        fileFunciones = fopen(ARCHIVO_FUNCIONES, "a");
        SYSTEMTIME Date;
        GetLocalTime(&Date);
        char fecha[11];

        // Parseando la fecha DD/MM/AAAA
        sprintf(fecha, "%i/%i/%i", Date.wDay, Date.wMonth, Date.wYear);

        Funcion.id = (setId(FUNCION) + 1);
        // asignando la fecha a la estructura de funcion
        strcpy(Funcion.pelicula, pelicula);
        strcpy(Funcion.fecha, fecha);
        Funcion.disponibilidad = DISPONIBILIDAD_SALA;

        fwrite(&Funcion, sizeof(Funcion), 1, fileFunciones);
        // // iteracion porque quiero crear i registros uno por cada funcion
        // for (i = 0; i < 5; i++)
        // {
        //     // Asignacion de los horarios
        //     switch (i)
        //     {
        //     case 0:
        //         strcpy(Funcion.horario, HORARIO1);
        //         break;
        //     case 1:
        //         strcpy(Funcion.horario, HORARIO2);
        //         break;
        //     case 2:
        //         strcpy(Funcion.horario, HORARIO3);
        //         break;
        //     case 3:
        //         strcpy(Funcion.horario, HORARIO4);
        //         break;
        //     case 4:
        //         strcpy(Funcion.horario, HORARIO5);
        //         break;
        //     }
        // }
        fclose(fileFunciones);

        // FILE *FILEFunciones;
        // FILEFunciones = fopen(ARCHIVO_FUNCIONES, "r");
        // printf("\nid\t\thorario\t\tfecha\t\tpelicula\t\tdisponibilidad\n\n");
        // while (fread(&Funcion, sizeof(Funcion), 1, FILEFunciones))
        // {
        //     // printf("%i\t\t%s\t\t%s\t\t%s\t\t%i\n", Usuario.id, Usuario.nombre, Usuario.correo, Usuario.pass, Usuario.acceso);
        //     printf("%i\t\t%s\t\t%s\t\t%s\t\t%i\n", Funcion.id, Funcion.horario, Funcion.fecha, Funcion.pelicula, Funcion.disponibilidad);
        // }
        // fclose(FILEFunciones);
        // system("pause>null");

        printf("\n******Sala actualizada******");
        system("pause>null");
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

		printf("\n\tELIMINAR REGISTROS DE USUARIOS\n");
		printf("\n------------------------------------------------------\n");
        printf("\tDigite correo: ");
        scanf("\n%[^\n]", correo);

        existe = getRegistro(USUARIO, correo);

        if (existe == 0)
        {
            printf("\t***No se encontraron registros para el correo:*** %s", correo);
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
            printf("\n\t*****Usuario eliminado*****");
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

		printf("\n\tELIMINAR REGISTROS DE PELICULAS");
		printf("\n------------------------------------------------------\n");
        printf("\n\tDigite titulo: ");
        scanf("\n%[^\n]", titulo);

        existe = getRegistro(PELICULA, titulo);

        if (existe == 0)
        {
            printf("\t***No se encontraron registros para el titulo:*** %s", titulo);
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
            printf("\n\t*****Pelicula eliminada*****");
            system("pause>null");
        }
    }
}

void comprarEntradas(int usuario)
{
    int i = 0;
    int posicion = 1;
    int tecla = 0;
    // char horarios[LEN][LEN] = {
    //     "10:00 AM",
    //     "1:00 PM",
    //     "4:00 PM",
    //     "7:00 PM",
    //     "10:00 PM",
    // };
    char pelicula[LEN];
    char peliculas[NUM_SALAS][LEN];
    FILE *fileSalas;
    fileSalas = fopen(ARCHIVO_SALAS, "r");

    // Llenado del vector peliculas
    while (fread(&Sala, sizeof(Sala), 1, fileSalas))
    {
        if (strcmp(Sala.pelicula, SALA_DISPONIBLE) == 0)
        {
            strcpy(peliculas[i], "No disponible");
        }
        else
        {
            strcpy(peliculas[i], Sala.pelicula);
        }
        i++;
    }
    fclose(fileSalas);

    // menu flecha
    while (tecla != ENTER)
    {
        titulo();
        cabeceraComprarTicket();

        for (i = 1; i <= NUM_SALAS; i++)
        {
            selector(i, posicion);
            printf("Sala %i: %s\n", i, peliculas[i - 1]);
        }

        selector(i, posicion);
        printf("Regresar\n");

        // escuchando tecla
        tecla = getch();

        if (tecla == ARRIBA && posicion != (NUM_SALAS + 1))
        {
            posicion++;
        }
        else if (tecla == ARRIBA && posicion == (NUM_SALAS + 1))
        {
            posicion = 1;
        }
        else if (tecla == ABAJO && posicion == 1)
        {
            posicion = (NUM_SALAS + 1);
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

    if (posicion == (NUM_SALAS + 1))
    {
        return;
    }

    // obtener pelicula por su numero de sala asignado
    FILE *fileSala;
    fileSala = fopen(ARCHIVO_SALAS, "r");
    while (fread(&Sala, sizeof(Sala), 1, fileSala))
    {
        if (Sala.id == posicion)
        {
            strcpy(pelicula, Sala.pelicula);
        }
    }
    fclose(fileSala);

    // Validar si el nombre de la pelicula es diferente de Disponible.
    if (strcmp(pelicula, SALA_DISPONIBLE) == 0)
    {
        printf("No hay ningnua pelicula disponible en esta sala\n");
        system("pause>null");
        return;
    }

    // Asignando la pelicula al ticket
    // Ticket.pelicula = pelicula;
    strcpy(Ticket.pelicula, pelicula);

    // SELECCION DE HORARIOS
    posicion = 1;
    tecla = 0;

    // menu flecha
    // while (tecla != ENTER)
    // {
    //     titulo();
    //     cabeceraComprarTicket();

    //     // Horarios
    //     selector(1, posicion);
    //     printf("%s\n", HORARIO1);
    //     selector(2, posicion);
    //     printf("%s\n", HORARIO2);
    //     selector(3, posicion);
    //     printf("%s\n", HORARIO3);
    //     selector(4, posicion);
    //     printf("%s\n", HORARIO4);
    //     selector(5, posicion);
    //     printf("%s\n", HORARIO5);
    //     selector(6, posicion);
    //     printf("Regresar");
    //     // escuchando tecla
    //     tecla = getch();

    //     if (tecla == ARRIBA && posicion != 6)
    //     {
    //         posicion++;
    //     }
    //     else if (tecla == ARRIBA && posicion == 6)
    //     {
    //         posicion = 1;
    //     }
    //     else if (tecla == ABAJO && posicion == 1)
    //     {
    //         posicion = 6;
    //     }
    //     else if (tecla == ABAJO && posicion != 1)
    //     {
    //         posicion--;
    //     }
    //     else
    //     {
    //         posicion = posicion;
    //     }
    // }
    // fflush(stdin);

    // if (posicion == 6)
    // {
    //     return;
    // }

    // Asignar el horario al ticket
    // switch (posicion)
    // {
    // case 1:
    //     strcpy(Ticket.horario, horarios[0]);
    //     break;
    // case 2:
    //     strcpy(Ticket.horario, horarios[1]);
    //     break;
    // case 3:
    //     strcpy(Ticket.horario, horarios[2]);
    //     break;
    // case 4:
    //     strcpy(Ticket.horario, horarios[3]);
    //     break;
    // case 5:
    //     strcpy(Ticket.horario, horarios[5]);
    //     break;
    // }

    // printf("Horario: %s", Ticket.horario);
    // system("pause>null");

    // Registrar venta
    FILE *fileRegTicket;
    fileRegTicket = fopen(ARCHIVO_TICKETS, "a");
    SYSTEMTIME Date;
    GetLocalTime(&Date);
    char fecha[11];

    Ticket.id = (setId(TICKET) + 1);
    // Parseando la fecha DD/MM/AAAA
    // sprintf(fecha, "%i/%i/%i", Date.wDay, Date.wMonth, Date.wYear);
    // strcpy(Ticket.fecha, fecha);
    // strcpy(Ticket.pelicula, pelicula);
    Ticket.usuario = usuario;

    int cantidadTicketsAComprar = 0;
    // validar si la cantidad esta disponible
    printf("\n\nCuantos tickets desea comprar: ");
    scanf("%i", &cantidadTicketsAComprar);

    /****************************************************************************************/
    // Checkear disponibilidad de la sala, horario, pelicula
    // Abrir tickets,
    FILE *FILETICKETS;
    SYSTEMTIME Today;
    GetLocalTime(&Today);
    char Hoy[11];
    sprintf(Hoy, "%i/%i/%i", Today.wDay, Today.wMonth, Today.wYear);
    // esta variable verificara cuantos tickets fueron comprados ya para esa funcion a esa hora.
    int ticketsRegistrados = 0;
    FILETICKETS = fopen(ARCHIVO_TICKETS, "r");
    while (fread(&Ticket, sizeof(Ticket), 1, FILETICKETS))
    {
        if (strcmp(Ticket.fecha, Hoy) == 0)
        {
            if (strcmp(Ticket.pelicula, pelicula) == 0)
            {
                ticketsRegistrados += Ticket.cantidadTickets;
            }
        }
    }
    fclose(FILETICKETS);

    if (ticketsRegistrados + cantidadTicketsAComprar > DISPONIBILIDAD_SALA)
    {
        printf("\nNo es posible realizar esta transaccion");
        system("pause>null");
        return;
    }

    sprintf(fecha, "%i/%i/%i", Date.wDay, Date.wMonth, Date.wYear);
    strcpy(Ticket.fecha, fecha);

    Ticket.cantidadTickets = cantidadTicketsAComprar;

    // Leer pelicula y la linea concuerda con la pelicula
    // Si concuerda, verificar si la fecha es ahora
    // contar tickets
    /****************************************************************************************/

    // scanf("%i", &Ticket.cantidadTickets);
    // scanf("\n%[^\n]", Ticket.cantidadTickets);
    // printf("id: %i\n", Ticket.id);
    // printf("fecha: %s\n", Ticket.fecha);
    // // printf("horario: %s\n", Ticket.horario);
    // printf("usuario: %i\n", Ticket.usuario);
    // printf("pelicula: %s\n", Ticket.pelicula);
    // printf("cantidad tickets: %i\n", Ticket.cantidadTickets);

    fwrite(&Ticket, sizeof(Ticket), 1, fileRegTicket);
    fclose(fileRegTicket);

    printf("\nCompra registrada correctamente\n");

    // Mostrar tickets
    // FILE *FILETICKET;
    // FILETICKET = fopen(ARCHIVO_TICKETS, "r");
    // printf("\nid\tfecha\t\t\tusuario\t\t\tPelicula\t\t\tcantidadTickets\n\n");
    // while (fread(&Ticket, sizeof(Ticket), 1, FILETICKET))
    // {
    //     printf("%i\t%s\t\t%i\t\t%s\t\t\t%i\n", Ticket.id, Ticket.fecha, Ticket.usuario, Ticket.pelicula, Ticket.cantidadTickets);
    // }
    // fclose(FILETICKET);
    // system("pause>null");
    // Mostrar tickets

    // printf("Contador: %i", contador);

    system("pause>null");
}

int getNoSalas()
{
    int noSalas = 0;
    FILE *file;
    file = fopen(ARCHIVO_SALAS, "r");
    while (fread(&Sala, sizeof(Sala), 1, file))
    {
        if (strcmp(Sala.pelicula, SALA_DISPONIBLE) != 0)
        {
            // TODO: porque necesitare cargar un archivo con la estructura, necesito validar si la iteracion no sea disponible. Osea que tenga asignada una pelicula
            noSalas++;
        }
    }
    fclose(file);

    return noSalas;
}

int getNoPeliculas()
{
    int noPeliculas = 0;
    FILE *file;
    file = fopen(ARCHIVO_PELICULAS, "r");
    while (fread(&Pelicula, sizeof(Pelicula), 1, file))
    {
        noPeliculas++;
    }
    fclose(file);

    return noPeliculas;
}

void mostrarReportes()
{
    // reportes();
    char fecha[11] = "";
    char fechas[LEN][LEN];
    int cantidadTicketsPorFechas[LEN] = {0};
    int cantidadTickets;
    int i = 0;
    int cont = 0;
    // Mostrar tickets
    FILE *filetickets;
    filetickets = fopen(ARCHIVO_TICKETS, "r");
    // obteniendo las fechas disponibles que estan en el reporte
    while (fread(&Ticket, sizeof(Ticket), 1, filetickets))
    {
        //comparando si la fecha es diferente o igual
        if (strcmp(fecha, Ticket.fecha) != 0)
        {
            strcpy(fecha, Ticket.fecha);
            strcpy(fechas[i], fecha);
            i++;
        }
        // // teniendo la cantidad total de tickets vendidos
        // cantidadTickets += Ticket.cantidadTickets;
    }
    fclose(filetickets);

    FILE *filetickets2;
    filetickets2 = fopen(ARCHIVO_TICKETS, "r");
    // recorriendo cada linea y comprara y obtener el total de tickets por fecha
    while (fread(&Ticket, sizeof(Ticket), 1, filetickets2))
    {
        //comparando si la fecha es diferente o igual
        if (strcmp(fechas[cont], Ticket.fecha) == 0)
        {
            cantidadTicketsPorFechas[cont] += Ticket.cantidadTickets;
        }
        else
        {
            cont++;
            cantidadTicketsPorFechas[cont] += Ticket.cantidadTickets;
        }
        // // teniendo la cantidad total de tickets vendidos
        // cantidadTickets += Ticket.cantidadTickets;
    }
    fclose(filetickets2);

    // printf("Total tickets: %i\n", cantidadTickets);
    // printf("Fechas: %s", fechas[0]);
    // printf("cantidad Tickets: %i", cantidadTicketsPorFechas[0]);
    // system("pause>null");

    printf("\nFecha\t\t\tTickets vendidos\t\tDinero\n");
    for (i = 0; i <= cont; i++)
    {
        printf("\n%s\t\t\t%i\t\t\t$%.2lf", fechas[i], cantidadTicketsPorFechas[i], (cantidadTicketsPorFechas[i] * TICKET_PRECIO));
    }

    system("pause>null");
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
            crearRegistro(USUARIO);
            break;
        case 3:
            inicioSesion();
            break;
        }
    } while (opcion != 4);
}

void menuPerfil(int acceso, int usuario)
{
    Role esAdmin = ADMIN;
    if (acceso == esAdmin)
    {
        menuPerfilAdmin();
    }
    else
    {
        menuPerfilUsuario(usuario);
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
            actualizarRegistro(SALA);
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

void menuPerfilAdmin()
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
            mostrarReportes();
            break;
        }
    } while (opcion != 5);
}

void menuPerfilUsuario(int usuario)
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
            comprarEntradas(usuario);
            // _comprarEntradas(usuario);
            break;
        case 2:
            printf("Actualizar mi perfil");
            system("pause>null");
            break;
        }
    } while (opcion != 3);
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

void cabeceraComprarTicket()
{
    puts("|------------------------------------------------------|");
    puts("|                  Escoge tu pelicula                  |");
    puts("|------------------------------------------------------|");
} 
