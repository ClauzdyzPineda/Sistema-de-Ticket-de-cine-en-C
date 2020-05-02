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
    char nombre[30];
    char pass[30];
    char correo[30];
    Role acceso;
} Usuario;

void registro();
int inicioSesion();
void mostrarUsuarios();
int setId();
int getCorreo(char *correo);
int validarUsuario(char *correo, char *password);
int getAcceso(char *correo);
int getch();

#endif // USUARIO