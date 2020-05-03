#ifndef USUARIO
#define USUARIO

typedef enum
{
    NORMAL,
    ADMIN
} Role;

struct
{
    int id;
    char nombre[LENGTH];
    char pass[LENGTH];
    char correo[LENGTH];
    Role acceso;
} Usuario;

int inicioSesion();
int setId();
int getCorreo(char *correo);
int validarUsuario(char *correo, char *password);
int getAcceso(char *correo);
int getch();

#endif // USUARIO