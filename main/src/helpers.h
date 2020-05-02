#ifndef HELPERS
#define HELPERS

#include <stdbool.h>
void estadoCursor(bool visible);
void selector(int posicionReal, int posicionSelector);
int seleccion(char *menu, char opcs[][20], int noOpcs);
int getch();
void titulo();
void cabeceraMenuPrincipal();
void cabeceraInicioSesion();

#endif // HELPERS