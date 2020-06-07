void mostrarRegistros(char *registro)
{
    if (strcmp(registro, USUARIO) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_USUARIOS, "r");
        printf("\n\t\t\tREGISTROS DE USUARIOS EN EL SISTEMA\n");
		printf("\n");
		printf("*----------------------------------------------------------------------*\n");
		printf("|   ID   |       Nombre      |        Correo               |   acceso  |\n");
		printf("*----------------------------------------------------------------------*\n");
        while (fread(&Usuario, sizeof(Usuario), 1, file))
        {
   	printf("\n| %i",Usuario.id);
   	printf(" ");
    printf("\t | %s",Usuario.nombre);
    printf(" ");
    printf("\t     | %s",Usuario.correo);
    printf(" ");
	printf("\t           | %i",Usuario.acceso);
    
	printf(" ");
	printf("\t       |");
        }
        
        printf("\n*----------------------------------------------------------------------*\n");
        fclose(file);
        system("pause>null");
    }

    if (strcmp(registro, PELICULA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_PELICULAS, "r");
        
        printf("\n\t         REGISTROS DE PELICULAS EN EL SISTEMA\n");
		printf("\n");
		printf("*-----------------------------------------------------------------*\n");
		printf("|   ID   |               Titulo                 |        Genero   |\n");
		printf("*-----------------------------------------------------------------*\n");
        
        while (fread(&Pelicula, sizeof(Pelicula), 1, file))
        {
           printf("\n| %i",Pelicula.id);
   	printf(" ");
    printf("\t |   %s",Pelicula.titulo);
    printf(" ");
    printf("\t\t\t\t|%s",Pelicula.genero);
    printf(" ");
	printf("\t  |");
        }
        
       printf("\n*-----------------------------------------------------------------*\n");
        fclose(file);
        system("pause>null");
    }

    if (strcmp(registro, SALA) == 0)
    {
        FILE *file;
        file = fopen(ARCHIVO_SALAS, "r");
        
        printf("\n\t         REGISTROS DE SALAS EN EL SISTEMA\n");
		printf("\n");
		printf("\t*---------------------------------------------*\n");
		printf("\t|    ID        |           Titulo             |\n");
		printf("\t*---------------------------------------------*\n");
         
        while (fread(&Sala, sizeof(Sala), 1, file))
        {
            printf("\t\t%i\t\t%s\n", Sala.id, Sala.pelicula);
        }
        printf("\t*---------------------------------------------*\n");
        fclose(file);
        system("pause>null");
    }
}
