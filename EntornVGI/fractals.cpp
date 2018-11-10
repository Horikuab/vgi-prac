//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA
//******** Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Octubre 2018)
// fractals.cpp : Funcions de lectura i generació de fractals 


#include "StdAfx.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "material.h"
#include "fractals.h"

// -------------- Entorn VGI: VARIABLES utilitzades en els fractals
// FMAX: Index màxim de la matriu d'alçades. Definida a fractals.h (valor:512)
double zz[FMAX+1][FMAX+1];				// Matriu d'alçades (i,j,zz[i][j]).
double normalsC[FMAX+1][FMAX+1][3];		// Matriu que guarda Vectors Normals per cares.
double normalsV[FMAX+1][FMAX+1][3];		// Matriu que guarda Vectors Normals per a vèrtexs.

// -------------- Entorn VGI: Valors màxim i mínim de Z necessaris per interpolar
//                            correctament la paleta de colors (iluminació suau del fractal)
double zmax=0; 
double zmin=0;

// -------------- Entorn VGI: Variables pics
double cx[6],cy[6],radi[6],hmax[6]; // Centres, radis i alçades de les muntanyes
double a=1.0*FMAX*(0.65);			// Parametre lemniscata

// -------------- Entorn VGI: Número de pics
int npics=0;

double r;

// -------------- Entorn VGI: DEFINICIÓ DE LES FUNCIONS

// llegir_pts: Funció de lectura d'un fitxer fractal amb pics.
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
//    I ALÇADA MÀXIMA.

// 5. INICIALITZAR LA VARIABLE ALEATÒRIA
srand( (unsigned) time(NULL));
r=(double) rand()/RAND_MAX;

// 6. CALCUL DEL MAXIM I MINIM DE LES ALÇADES INICIALS

// Funció retorna el pas entre alçades a la variable step, 
// calculat en funció del nombre d'alçades inicials i del
// tamany de la matriu.
return step;

}

// escriure_pts: Funció d'escriptura en un fitxer de les alçades i pics 
//               d'un fractal segons la resolució actual.
// Variables:	- nomf: Nom del fitxer a escriure.
//				- paso: Resolució del fractal a escriure.
bool escriure_pts(char *nomf,int paso)
{	int i,j;
	FILE *fd;

// 1. OBRIR FITXER

// 2. ESCRIURE ALÇADES
// 2.1 Capçalera n n segons la variable paso

// 2.2 Alçades Z (una per línia)

// 3. ESCRIURE PICS
// 3.1 Escriure número de pics <cr>
// 3.2 Escriure centre cx,cy, radi i alçada dels pics (un pic per línia).

// retorna true si escritura s'ha realitzat amb èxit.
return true;

}

// itera_fractal: Càlcul de les alçades intermitges.
// Variables: - bruit: Tipus de soroll (Linial,Quadràtic,SQRT o diferenciable)
//            - paso: Pas d'iteració del fractal.
void itera_fractal(char bruit,int paso)
{
	
}


//soroll: Calcul del soroll en les alsades segons la distància
//        als picsdistancia.
// Variables: - i,j: Posició de l'alçada a calcular el soroll..
// 			  - alf: Màxim valor permès. En el nostre cas, el valor del
//                   de la variable pas que ens dóna la resolució del fractal.
//            - noise: Tipus de soroll (linial, quadràtic,sqrt o diferenciable).
double soroll(int i,int j,double alf,char noise)
{
	double ff,s,r;

// Càlcul de la variable aleatòria entre (0,1).
	r=(double) rand()/RAND_MAX;

// Càlcul del soroll segons el tipus.
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
// Variables: - Iluminació: Defineix el tipus d'iluminació (filferros, plana o suau).
//            - step: Pas de dibuix del fractal.
void fract(char iluminacio,bool paletaColor,bool sw_mater[4],int step)
{
	int i,j;
	CColor color_puntF; // Color del vèrtex del fractal.

	i=0;	j=0;
	color_puntF.r=0.0;		color_puntF.g=0.0;		color_puntF.b=0.0;
	
	glPushMatrix();
// 1. CENTRAR EL FRACTAL EN EL (0,0,0).

// 2. DIBUIXAR ELS VÈRTEXS DELS TRIANGLES SEGONS EL PAS (step)
//    I DEFINIR ELS VECTORS NORMALS DE CADA VÈRTEX EN FUNCIÖ DE
//	  LA ILUMINACIÖ (iluminacio)

	glBegin(GL_TRIANGLES);
// Donar color al punt del vertex en funció de la reflexió de materials.
		color_puntF.r = 0.2;	color_puntF.g = 0.75;	color_puntF.b = 0.9;	color_puntF.a = 0.5;
		SeleccionaMaterialiColor(MAT_CAP, sw_mater, true, color_puntF);
		glVertex3f(i,j,zz[i][j]);
	glEnd();

	glPopMatrix();
	
//  3. DIBUIX DEL MAR A L'ALÇADA Z=0.
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.2f,0.75f,0.9f,0.5f);
		// Donar color al punt en funció de la reflexió de materials.
		color_puntF.r = 0.2;	color_puntF.g = 0.75;	color_puntF.b = 0.9;	color_puntF.a = 0.5;
		SeleccionaMaterialiColor(MAT_CAP, sw_mater, true, color_puntF);
		glRectf(-FMAX/2,-FMAX/2,FMAX/2,FMAX/2);
	glDisable(GL_BLEND);
	
}

//------------------ CALCUL DELS SOROLLS  --------------------/

// Càlcul del soroll linial segons la posició del punt (x,y)
double soroll_lin(int x,int y)
{ 
double aux_sl=0;

return aux_sl;
}

// Càlcul del soroll quadràtic segons la posició del punt (x,y)
double soroll_quad(int x,int y)
{ 
double aux_sq=0;

return aux_sq;
}

// Càlcul del soroll arrel quadrada segons la posició del punt (x,y)
double soroll_sq(int x,int y)
{ 
double aux_sq=0;

return aux_sq;
}

// Càlcul del soroll diferenciable segons la posició del punt (x,y)
double soroll_dif(int x,int y)
{ 
double aux_sd=0;

return aux_sd;
}
