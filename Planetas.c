// Librerias
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Leer datos archivo
int main()
{
	FILE *coordenadas;
	coordenadas = fopen("coordinates(2).csv", "r");

	const char *delimiter;
	delimiter = ",";

	int l = 500;
	char linea_temp[l];

	char *div;

	while(fgets(linea_temp, l, coordenadas))
	{
		printf("Fila: %s", linea_temp);
		div = strtok(linea_temp, delimiter);
	}
}

int almacena()
{
	
}
