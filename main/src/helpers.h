#ifndef HELPERS
#define HELPERS

#include <stdbool.h>
#include "_define.h"
void estadoCursor(bool visible);
void selector(int posicionReal, int posicionSelector);
int seleccion(char *menu, char opcs[][LENGTH], int noOpcs);
int getch();
void titulo();
void cabeceraMenuPrincipal();
void cabeceraInicioSesion();
void cabeceraMenuPerfilAdmin();

#endif // HELPERS