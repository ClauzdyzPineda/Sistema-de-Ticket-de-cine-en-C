#ifndef PELICULA
#define PELICULA

struct
{
    int id;
    char titulo[30];
    char genero[30];
    char horario[5][30]; // 5 horarios por pelicula
} Pelicula;

#endif // PELICULA