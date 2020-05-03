#ifndef HELPERS
#define HELPERS

#include <stdbool.h>
#include "_define.h"
void estadoCursor(bool visible);
void selector(int posicionReal, int posicionSelector);
int seleccion(char *menu, char opcs[][LENGTH], int noOpcs);
int getch();

// crud
void crearRegistro(char *registro);
void mostrarRegistros(char *registro);
void actualizarRegistro(char *registro);
void eliminarRegistro(char *registro);

#endif // HELPERS