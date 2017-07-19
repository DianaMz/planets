// Librerias
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define Np 10

// Leer datos archivo

void main()
{

	FILE *coordenadas;
	coordenadas = fopen("coordinates(2).csv", "r");

	int l = 500;
	char linea_temp[l];
	char *divlinea;

	float matrix[Np][7];

	int i, j;

	float num;

	for (i = 0; i < Np; i++)
	{
			fgets(linea_temp, l, coordenadas);
			divlinea = strtok(linea_temp, ",");
			for (j = 0; j < 8; j++)
			{
					if(j != 0)
					{
							matrix[i][j-1] = atof(divlinea);
					}
					divlinea = strtok(NULL, ",");
			}
	}
	printf("%p\n", divlinea);
}



int almacena()
{

}

/*
int array[1000];

int i=0;
while(!coordenadas.eof()){
coordenadas>>array[i];
i++;
}
*/
