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
        	int acc =0;
        	
			v= (log10(Usuario.id)+1);
				printf("\n| %i",Usuario.id);
			for(v;v<6;v++){
				printf(" ");
			}
				printf("| %s",Usuario.nombre);
			for(u=strlen(Usuario.nombre);u<40;u++){
				printf(" ");
			}
				printf("| %s",Usuario.correo);
			for(co=strlen(Usuario.correo);co<35;co++){
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
        	
			p= (log10(Pelicula.id)+1);
				printf("\n| %i",Pelicula.id);
			for(p;p<6;p++){
				printf(" ");
			}
				printf("| %s",Pelicula.titulo);
			for(tp=strlen(Pelicula.titulo);tp<45;tp++){
				printf(" ");
			}
				printf("| %s",Pelicula.genero);
			for(g=strlen(Pelicula.genero);g<25;g++){
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
