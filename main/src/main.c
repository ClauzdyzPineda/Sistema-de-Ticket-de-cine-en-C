#include <stdio.h>
#include <windows.h>

int main()
{
    int opcion;
    do
    {
        system("cls");
        puts("+----------------------------------------------+");
        puts("|          Sistema de Tickets de cine          |");
        puts("+----------------------------------------------+");
        puts("+----------------------------------------------+");
        puts("|                Menu principal                |");
        puts("+----------------------------------------------+");
        puts("1. Cartelera\n2. Registrate\n3. Iniciar sesion\n4. Salir");
        printf("Digite la opcion: ");
        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:
            puts("Seccion de la cartelera");
            system("pause>null");
            break;
        case 2:
            puts("Seccion de Registro");
            system("pause>null");
            break;
        case 3:
            puts("Seccion de Inicio de sesion");
            system("pause>null");
            break;
        }

    } while (opcion != 4);

    return 0;
}