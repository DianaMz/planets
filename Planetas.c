// Librerias
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define Np 10
#define PI 3.14159265358979323846

float *M, *X, *Y, *Z, *VX, *VY, *VZ, *V05X, *V05Y, *V05Z;
int Nt;
float G;

//Convierte entre los indices (Pointers) de un arreglo lineal y de una matriz
int pos(int i, int j)
{
    return Nt*i + j;
}



// Leer datos archivo
void leer(void)
{
	FILE *coordenadas;
	coordenadas = fopen("coordinates(2).csv", "r");

	int l = 500;
	char linea_temp[l];
	char *divlinea;

	float matrix[Np][7];

	float num;

	int i, j;

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

	// vectores
	M = malloc(Np*sizeof(float));
	V05X = malloc(Np*sizeof(float));
	V05Y = malloc(Np*sizeof(float));
	V05Z = malloc(Np*sizeof(float));

	// matrices
	X = malloc(Np*Nt*sizeof(float));
	Y = malloc(Np*Nt*sizeof(float));
	Z = malloc(Np*Nt*sizeof(float));
	VX = malloc(Np*Nt*sizeof(float));
	VY = malloc(Np*Nt*sizeof(float));
	VZ = malloc(Np*Nt*sizeof(float));

	for(i = 0; i < Np; i++)
	{
			M[i] = matrix[i][0]/matrix[0][0];
			X[pos(i, 0)] = matrix[i][1];
			Y[pos(i, 0)] = matrix[i][2];
			Z[pos(i, 0)] = matrix[i][3];
			VX[pos(i, 0)] = matrix[i][4];
			VY[pos(i, 0)] = matrix[i][5];
			VZ[pos(i, 0)] = matrix[i][6];
	}
	fclose(coordenadas);
}

void acelera(int i, int n, float *ax, float *ay, float *az)
{
    int ii;
    float dx, dy, dz, r, factor;

    *ax = 0;
    *ay = 0;
    *az = 0;

    for(ii = 0; ii < Np; ii++)
    {
        if (ii != i)
        {
            dx = X[pos(ii, n)] - X[pos(i, n)];
            dy = Y[pos(ii, n)] - Y[pos(i, n)];
            dz = Z[pos(ii, n)] - Z[pos(i, n)];
            r = pow(dx*dx + dy*dy + dz*dz, 3.0/2.0);
            factor = G*M[ii]/r;
            *ax += factor * dx;
            *ay += factor * dy;
            *az += factor * dz;
        }
    }
}


int main()
{
	G = 4*pow(PI,2.);
}
