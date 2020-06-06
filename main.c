#include <stdio.h>
#include <windows.h>
#include <unistd.h>

// TODO
// Necesito crear el archivo Salas si no existe un archivo. para crear la estructura. y no tener que ordenar las salas.

// -------------------------------------------------------------------------------- Constantes
// General
#define LEN 80
#define NUM_SALAS 10
#define SALA_DISPONIBLE "Disponible"
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
    // TODO: cambiar esto a int
    char pelicula[LEN];
    // int disponibilidad;
} Sala;

struct
{
    int id;
    char horario[LEN];
    int day;
    int month;
    int year;
    int disponibilidad;
} Funcion;

struct
{
    int id;
    char fecha;
    int usuario;
    int pelicula;
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
        printf("Nombre: ");
        scanf("\n%[^\n]", Usuario.nombre);
        printf("Correo: ");
        scanf("\n%[^\n]", Usuario.correo);
        printf("Contrasenya: ");
        scanf("\n%[^\n]", Usuario.pass);

        // TODO: logica para validar si usuario con ese correo existe.

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
        printf("\nid\t\tPelicula\n");
        while (fread(&Sala, sizeof(Sala), 1, file))
        {
            printf("%i\t\t%s\n", Sala.id, Sala.pelicula);
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

        //TODO: Seleccionar la pelicula
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
        printf("\nSala actualizado.");
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

void comprarEntradas(int usuario)
{
    int i = 0;
    int posicion = 1;
    int tecla = 0;
    char pelicula[LEN];
    char peliculas[NUM_SALAS][LEN];
    // printf("\nNumero de salas: %i\n", getNoSalas());
    // leear sala y mostrar pelicula
    // sala: X pelicula Y
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

    //
    while (fread(&Sala, sizeof(Sala), 1, fileSala))
    {
        if (Sala.id == posicion)
        {
            strcpy(pelicula, Sala.pelicula);
        }
    }
    fclose(fileSala);

    // Validar si el nombre de la pelicula es diferente de Disponible.
    printf("Validacion: %s", pelicula);

    system("pause>null");

    //llenado del vector con las salas
    // TODO: igual, como voy a tener una estructura necesito validar != disponible. OSea que ya tienen una pelicula asignada
    // FILE *file;
    // file = fopen(ARCHIVO_SALAS, "r");
    // int contador = 0;
    // while (fread(&Sala, sizeof(Sala), 1, file))
    // {
    //     *opciones[contador] = Sala.pelicula;
    // }
    // fclose(file);

    // for (int i = 0; i < noSalas; i++)
    // {
    //     printf("Pelicula: %s\n", opciones[i]);
    // }
    printf("\nSeleccionar horario\n");
    printf("\nCheckear disponibilidad del horario\n");
    printf("\nRegistrar venta\n");
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
            printf("Reportes");
            system("pause>null");
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