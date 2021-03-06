// Librerias
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define Np 10
#define PI 3.14159265358979323846
#define dt 0.025

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



void leapFrog(void)
{
    // make simulation
    int n, i;
    float ax, ay, az;

    for (n = 0; n < Nt-1; n++)
    {
        for (i = 0; i < Np; i++)
        {
            acelera(i, n, &ax, &ay, &az);
            V05X[i] = VX[pos(i, n)] + 0.5*ax*dt;
            V05Y[i] = VY[pos(i, n)] + 0.5*ay*dt;
            V05Z[i] = VZ[pos(i, n)] + 0.5*az*dt;

            X[pos(i, n+1)] = X[pos(i, n)] + V05X[i]*dt;
            Y[pos(i, n+1)] = Y[pos(i, n)] + V05Y[i]*dt;
            Z[pos(i, n+1)] = Z[pos(i, n)] + V05Z[i]*dt;
        }

        for(i = 0; i < Np; i++)
        {
            acelera(i, n+1, &ax, &ay, &az);
            VX[pos(i, n+1)] = V05X[i] + 0.5*ax*dt;
            VY[pos(i, n+1)] = V05Y[i] + 0.5*ay*dt;
            VZ[pos(i, n+1)] = V05Z[i] + 0.5*az*dt;
        }
    }
}



void generatxt(void)
{
    int i, j;

    FILE *filex, *filey, *filez;

    filex = fopen("xs.txt", "w");
    filey = fopen("ys.txt", "w");
    filez = fopen("zs.txt", "w");

    fprintf(filex, "Sol Mercurio Venus Tierra Marte Jupiter Saturno Urano Neptuno Pluton\n");
    fprintf(filey, "Sol Mercurio Venus Tierra Marte Jupiter Saturno Urano Neptuno Pluton\n");
    fprintf(filez, "Sol Mercurio Venus Tierra Marte Jupiter Saturno Urano Neptuno Pluton\n");
    for (j = 0; j < Nt; j++)
    {
        for (i = 0; i < Np; i++)
        {
            fprintf(filex, "%f ", X[pos(i, j)]);
            fprintf(filey, "%f ", Y[pos(i, j)]);
            fprintf(filez, "%f ", Z[pos(i, j)]);
        }
        fprintf(filex, "\n");
        fprintf(filey, "\n");
        fprintf(filez, "\n");
    }
    fclose(filex);
    fclose(filey);
    fclose(filez);
}



int main()
{
	G = 4*pow(PI,2.);
	Nt = 252/dt;

	leer();
	leapFrog();
	generatxt();

	return 0;
}
