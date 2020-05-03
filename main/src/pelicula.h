#ifndef PELICULA
#define PELICULA

struct
{
    int id;
    char titulo[LENGTH];
    char genero[LENGTH];
    char horario[5][LENGTH]; // 5 horarios por pelicula
} Pelicula;

#endif // PELICULA