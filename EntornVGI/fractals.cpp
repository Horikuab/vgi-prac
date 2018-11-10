//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA
//******** Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Octubre 2018)
// fractals.cpp : Funcions de lectura i generaci� de fractals 


#include "StdAfx.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "material.h"
#include "fractals.h"

// -------------- Entorn VGI: VARIABLES utilitzades en els fractals
// FMAX: Index m�xim de la matriu d'al�ades. Definida a fractals.h (valor:512)
double zz[FMAX+1][FMAX+1];				// Matriu d'al�ades (i,j,zz[i][j]).
double normalsC[FMAX+1][FMAX+1][3];		// Matriu que guarda Vectors Normals per cares.
double normalsV[FMAX+1][FMAX+1][3];		// Matriu que guarda Vectors Normals per a v�rtexs.

// -------------- Entorn VGI: Valors m�xim i m�nim de Z necessaris per interpolar
//                            correctament la paleta de colors (iluminaci� suau del fractal)
double zmax=0; 
double zmin=0;

// -------------- Entorn VGI: Variables pics
double cx[6],cy[6],radi[6],hmax[6]; // Centres, radis i al�ades de les muntanyes
double a=1.0*FMAX*(0.65);			// Parametre lemniscata

// -------------- Entorn VGI: N�mero de pics
int npics=0;

double r;

// -------------- Entorn VGI: DEFINICI� DE LES FUNCIONS

// llegir_pts: Funci� de lectura d'un fitxer fractal amb pics.
// Variables:	- nomf: Nom del fitxer a llegir.
int llegir_pts(char *nomf)
{	int i,j,step;
	FILE *fd;
	step=1;
// 1. INICIALITZAR MATRIUS zz i normals
for(i=0;i<=512;i=i++)
	{ for(j=0;j<=FMAX;j=j++)
		{	zz[i][j]=0.0;
			normalsC[i][j][0]=0.0;
			normalsC[i][j][1]=0.0;
			normalsC[i][j][2]=0.0;
			normalsV[i][j][0]=0.0;
			normalsV[i][j][1]=0.0;
			normalsV[i][j][2]=0.0;
		}
	}

// 2. INICIALITZAR PICS
for(i=0;i<=6;i=i++)
	{ cx[i]=0; cy[i]=0; radi[i]=0; hmax[i]=0;
	}

// 3. OBRIR FITXER FRACTAL I LLEGIR ALC,ADES ASSIGNANT-LES
//    A LA MATRIU ZZ DE FORMA EQUIESPAIADA.

// 4. LLEGIR EL NOMBRE DE PICS I ELS VALORS (CENTRE,RADI 
//    I AL�ADA M�XIMA.

// 5. INICIALITZAR LA VARIABLE ALEAT�RIA
srand( (unsigned) time(NULL));
r=(double) rand()/RAND_MAX;

// 6. CALCUL DEL MAXIM I MINIM DE LES AL�ADES INICIALS

// Funci� retorna el pas entre al�ades a la variable step, 
// calculat en funci� del nombre d'al�ades inicials i del
// tamany de la matriu.
return step;

}

// escriure_pts: Funci� d'escriptura en un fitxer de les al�ades i pics 
//               d'un fractal segons la resoluci� actual.
// Variables:	- nomf: Nom del fitxer a escriure.
//				- paso: Resoluci� del fractal a escriure.
bool escriure_pts(char *nomf,int paso)
{	int i,j;
	FILE *fd;

// 1. OBRIR FITXER

// 2. ESCRIURE AL�ADES
// 2.1 Cap�alera n n segons la variable paso

// 2.2 Al�ades Z (una per l�nia)

// 3. ESCRIURE PICS
// 3.1 Escriure n�mero de pics <cr>
// 3.2 Escriure centre cx,cy, radi i al�ada dels pics (un pic per l�nia).

// retorna true si escritura s'ha realitzat amb �xit.
return true;

}

// itera_fractal: C�lcul de les al�ades intermitges.
// Variables: - bruit: Tipus de soroll (Linial,Quadr�tic,SQRT o diferenciable)
//            - paso: Pas d'iteraci� del fractal.
void itera_fractal(char bruit,int paso)
{
	
}


//soroll: Calcul del soroll en les alsades segons la dist�ncia
//        als picsdistancia.
// Variables: - i,j: Posici� de l'al�ada a calcular el soroll..
// 			  - alf: M�xim valor perm�s. En el nostre cas, el valor del
//                   de la variable pas que ens d�na la resoluci� del fractal.
//            - noise: Tipus de soroll (linial, quadr�tic,sqrt o diferenciable).
double soroll(int i,int j,double alf,char noise)
{
	double ff,s,r;

// C�lcul de la variable aleat�ria entre (0,1).
	r=(double) rand()/RAND_MAX;

// C�lcul del soroll segons el tipus.
	switch(noise)
	{
	case S_LINIAL:
		ff=soroll_lin(i,j);
		break;
	case S_QUADRATIC:
		ff=soroll_quad(i,j);
		break;
	case S_SQRT:
		ff=soroll_sq(i,j);
		break;
	case S_DIFERENCIABLE:
		ff=soroll_dif(i,j);
		break;
	default:
		ff=0;
	} 
	s=ff*r*alf;
//Retorn del valor del soroll.
	return s;	
}

// TRIANGULACIO DEL TERRENY. Dibuix de la muntanya fractal
// Variables: - Iluminaci�: Defineix el tipus d'iluminaci� (filferros, plana o suau).
//            - step: Pas de dibuix del fractal.
void fract(char iluminacio,bool paletaColor,bool sw_mater[4],int step)
{
	int i,j;
	CColor color_puntF; // Color del v�rtex del fractal.

	i=0;	j=0;
	color_puntF.r=0.0;		color_puntF.g=0.0;		color_puntF.b=0.0;
	
	glPushMatrix();
// 1. CENTRAR EL FRACTAL EN EL (0,0,0).

// 2. DIBUIXAR ELS V�RTEXS DELS TRIANGLES SEGONS EL PAS (step)
//    I DEFINIR ELS VECTORS NORMALS DE CADA V�RTEX EN FUNCI� DE
//	  LA ILUMINACI� (iluminacio)

	glBegin(GL_TRIANGLES);
// Donar color al punt del vertex en funci� de la reflexi� de materials.
		color_puntF.r = 0.2;	color_puntF.g = 0.75;	color_puntF.b = 0.9;	color_puntF.a = 0.5;
		SeleccionaMaterialiColor(MAT_CAP, sw_mater, true, color_puntF);
		glVertex3f(i,j,zz[i][j]);
	glEnd();

	glPopMatrix();
	
//  3. DIBUIX DEL MAR A L'AL�ADA Z=0.
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.2f,0.75f,0.9f,0.5f);
		// Donar color al punt en funci� de la reflexi� de materials.
		color_puntF.r = 0.2;	color_puntF.g = 0.75;	color_puntF.b = 0.9;	color_puntF.a = 0.5;
		SeleccionaMaterialiColor(MAT_CAP, sw_mater, true, color_puntF);
		glRectf(-FMAX/2,-FMAX/2,FMAX/2,FMAX/2);
	glDisable(GL_BLEND);
	
}

//------------------ CALCUL DELS SOROLLS  --------------------/

// C�lcul del soroll linial segons la posici� del punt (x,y)
double soroll_lin(int x,int y)
{ 
double aux_sl=0;

return aux_sl;
}

// C�lcul del soroll quadr�tic segons la posici� del punt (x,y)
double soroll_quad(int x,int y)
{ 
double aux_sq=0;

return aux_sq;
}

// C�lcul del soroll arrel quadrada segons la posici� del punt (x,y)
double soroll_sq(int x,int y)
{ 
double aux_sq=0;

return aux_sq;
}

// C�lcul del soroll diferenciable segons la posici� del punt (x,y)
double soroll_dif(int x,int y)
{ 
double aux_sd=0;

return aux_sd;
}
