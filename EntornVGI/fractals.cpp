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
int pasos;
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
FILE *fitx = fopen(nomf, "r");
int t_matriuz_x = 0;
int t_matriuz_y = 0;
char c;
char *linia = "";

fscanf(fitx, "%d %d ", &t_matriuz_x, &t_matriuz_y);
int aux = 0;
int aux1 = 0;
if (t_matriuz_x % 2 != 0) aux = t_matriuz_x - 1;
else aux = t_matriuz_x;

step = FMAX / aux;
int npunts = 0;
double max = 0;
double min = zz[i][j];
for (int i = 0; i < FMAX+1 ; i+=step) {
	for (int j = 0; j < FMAX + 1; j += step) {
		fscanf(fitx, "%lf ", &zz[i][j]);
		++npunts;
		if (max < zz[i][j]) max = zz[i][j];
		if (min > zz[i][j]) min = zz[i][j];
	}
}
zmax = max;
zmin = min;
// 4. LLEGIR EL NOMBRE DE PICS I ELS VALORS (CENTRE,RADI 
//    I AL�ADA M�XIMA.

fscanf(fitx, "%d ", &npics);
for (int i = 0; i < npics; ++i) {
	fscanf(fitx, "%lf %lf %lf %lf ", &cx[i], &cy[i], &radi[i], &hmax[i]);
}

// 5. INICIALITZAR LA VARIABLE ALEAT�RIA
srand( (unsigned) time(NULL));
r=(double) rand()/RAND_MAX;

// 6. CALCUL DEL MAXIM I MINIM DE LES AL�ADES INICIALS
double n = t_matriuz_x * t_matriuz_y;


// Funci� retorna el pas entre al�ades a la variable step, 
// calculat en funci� del nombre d'al�ades inicials i del
// tamany de la matriu.
pasos = step;
return step;

}


int get_K(double a) {
	if (a > zmax) zmax = a; // actualitza l'al�ada maxima si apareix una major

	double k_percentage = 1.0 / 24.0, diff;

	if(a < 0) diff = zmin - a; // alturas negativas
	else diff = -zmin + a; // alturas positivas

	if (diff < 0) { diff *= -1; }

	double percentage = diff / (zmax - zmin);
	int K = (int)trunc(percentage / k_percentage);

	return K;
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
	pasos = paso;
	int npunts = 0;

	// Iterar per la malla del fractal deixant fora els contorns laterals que no hauran de canviar mai
	for (int i = 0; i < FMAX; i += paso) {
		for (int j = 0; j < FMAX; j += paso) {
			int inx = j + paso / 2;
			zz[i][inx] = (zz[i][j] + zz[i][j + paso])/2 + soroll(i,inx,paso,bruit);
			int iny = i + paso / 2;
			zz[iny][j] = (zz[i][j] + zz[i + paso][j]) / 2 + soroll(iny, j, paso, bruit);
			zz[iny][j + paso] = (zz[i][j + paso] + zz[i + paso][j + paso])/2 + soroll(iny, j+paso, paso, bruit);
			zz[i + paso][inx] = (zz[i + paso][j] + zz[i + paso][j + paso]) / 2 + soroll(i+paso, inx, paso, bruit); 
			zz[iny][inx] = (zz[i][j] + zz[i + paso][j] + zz[i + paso][j + paso] + zz[i][j + paso]) / 4 + soroll(iny, inx, paso, bruit); 
		}
	}
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
#include "normals.h"
void fract(char iluminacio,bool paletaColor,bool sw_mater[4],int step)
{
	int i,j;
	step = pasos;	
	CColor color_puntF; // Color del v�rtex del fractal.

	i=0;	j=0;
	color_puntF.r=0.0;		color_puntF.g=0.0;		color_puntF.b=0.0;
	
	glPushMatrix();
// 1. CENTRAR EL FRACTAL EN EL (0,0,0).
	glTranslatef(-FMAX/2, -FMAX/2, 0);

// 2. DIBUIXAR ELS V�RTEXS DELS TRIANGLES SEGONS EL PAS (step)
//    I DEFINIR ELS VECTORS NORMALS DE CADA V�RTEX EN FUNCI� DE
//	  LA ILUMINACI� (iluminacio)
	bool b = true;
	for (int i = 0; i < FMAX; i += step) {
		for (int j = 0; j < FMAX; j += step) {
			int K = get_K(zz[i][j]);
			if (iluminacio == 'f') {
				glBegin(GL_TRIANGLES);
					glColor3f(med_colorR[K], med_colorG[K], med_colorB[K]);
					glVertex3f(i, j, zz[i][j]);                     // V1
					glVertex3f(i + step, j, zz[i + step][j]);        // V2
					glVertex3f(i + step, j + step, zz[i + step][j + step]); // V3
				glEnd();
				glBegin(GL_TRIANGLES);
					glVertex3f(i, j, zz[i][j]);                     // V1
					glVertex3f(i + step, j + step, zz[i + step][j + step]); // V3
					glVertex3f(i, j + step, zz[i][j + step]);       // V4
				glEnd();

			}
			else if (iluminacio == 'p') {
				glBegin(GL_TRIANGLES);
					glNormal3f(normalsC[i][j][0], normalsC[i][j][1], normalsC[i][j][2]); // VNorm.  
					glVertex3f(i, j, zz[i][j]);                    // V1
					glVertex3f(i + step, j, zz[i + step][j]);        // V2
					glVertex3f(i + step, j + step, zz[i + step][j+step]);    // V3
				glEnd();
				glBegin(GL_TRIANGLES);
					glNormal3f(normalsV[i][j][0], normalsV[i][j][1], normalsV[i][j][2]); // VNorm.        
					glVertex3f(i, j, zz[i][j]);                        // V1
					glVertex3f(i + step, j + step, zz[i + step][j + step]);     // V3
					glVertex3f(i, j + step, zz[i][j + step]);        // V4
				glEnd();
				// Donar color al punt del vertex en funci� de la reflexi� de materials.
				color_puntF.r = med_colorR[K];	color_puntF.g = med_colorG[K];	color_puntF.b = med_colorB[K];	color_puntF.a = 0.5*0.005*i;

				b = true;
				SeleccionaMaterialiColor(MAT_CAP, sw_mater, b, color_puntF);
				glVertex3f(i, j, zz[i][j]);
			}
			else { // iluminacio = 's'
				glBegin(GL_TRIANGLES);
					glNormal3f(normalsV[i][j][0], normalsV[i][j][1], normalsV[i][j][2]);// Normal a V1
					glVertex3f(i, j, zz[i][j]);                             // V1
					glNormal3f(normalsV[i + step][j][0], normalsV[i + step][j][1],normalsV[i + step][j][2]);      // Normal a V2
					glVertex3f(i + step, j, zz[i + step][j]);                  // V2
					glNormal3f(normalsV[i + step][j + step][0], normalsV[i + step][j + step][1],normalsV[i + step][j + step][2]);  // Normal a V3
					glVertex3f(i + step, j + step, zz[i + step][j + step]);           // V3
				glEnd();
				glBegin(GL_TRIANGLES);
					glNormal3f(normalsV[i][j][0], normalsV[i][j][1], normalsV[i][j][2]); //Normal a V1
					glVertex3f(i, j, zz[i][j]);                              // V1
					glNormal3f(normalsV[i + step][j + step][0], normalsV[i + step][j + step][1],normalsV[i + step][j + step][2]);  // Normal a V3
					glVertex3f(i + step, j + step, zz[i + step][j + step]);           // V3
					glNormal3f(normalsV[i][j + step][0], normalsV[i][j + step][1],normalsV[i][j + step][2]);         // Normal a V4
					glVertex3f(i, j + step, zz[i][j + step]);              // V4
				glEnd();
			}
		}
	}
	
	glPopMatrix();
	
//  3. DIBUIX DEL MAR A L'AL�ADA Z=0.
	
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.2f,0.75f,0.9f,0.5f);
		// Donar color al punt en funci� de la reflexi� de materials.
		color_puntF.r = 0.2;	color_puntF.g = 0.75;	color_puntF.b = 0.9;	color_puntF.a = 0.5;
		SeleccionaMaterialiColor(MAT_CAP, sw_mater, b, color_puntF);
		glRectf(-FMAX/2,-FMAX/2,FMAX/2,FMAX/2);
	glDisable(GL_BLEND);
	
}

// Comprova si el punt passat est� dins del radi del npic
double is_in_pic(int npic, int x, int y) {
	double dist = sqrt(pow((x - cx[npic]), 2) + pow((y - cy[npic]), 2)); // Dist�cia Euclideana del punt x,y al npic
	if (dist > radi[npic]) {
		dist = 0;
	}
	return dist;
}

//------------------ CALCUL DELS SOROLLS  --------------------/

// C�lcul del soroll linial segons la posici� del punt (x,y)
double soroll_lin(int x,int y)
{ 
double aux_sl=0;
double d = 0;
int j = 0;
for (int i = 0; i < npics;++i) { // Per cada pic
	d = 0;
	d = is_in_pic(i, x, y); // C�lcul de la dist�ncia del punt x,y al pic i
	if (d > 0) {
		d = hmax[i] * (1 - (d / radi[i]));
		j++;
	}
	aux_sl += d;
}

return aux_sl;
}

// C�lcul del soroll quadr�tic segons la posici� del punt (x,y)
double soroll_quad(int x,int y)
{ 
double aux_sq=0;
double d;
int j=0;
for (int i = 0; i < npics; ++i) {
	d = 0;
	d = is_in_pic(i, x, y); // C�lcul de la dist�ncia del punt x,y al pic i
	if (d > 0) {
		d = hmax[i] * (1 - ((d*d)/(radi[i]*radi[i])));
		j++;
	}
	aux_sq += d;
}
return aux_sq;
}

// C�lcul del soroll arrel quadrada segons la posici� del punt (x,y)
double soroll_sq(int x,int y)
{ 
double aux_sq=0;
double d;
int j=0;
for (int i = 0; i < npics; ++i) {
	d = 0;
	d = is_in_pic(i, x, y); // C�lcul de la dist�ncia del punt x,y al pic i
	if (d > 0) {
		d = hmax[i] * (1 - (sqrt(d) / sqrt(radi[i]))); 
		j++;
	}
	aux_sq += d;
}
return aux_sq;
}

// C�lcul del soroll diferenciable segons la posici� del punt (x,y)
double soroll_dif(int x,int y)
{ 
double aux_sd=0;
double d;
int j=0;
for (int i = 0; i < npics; ++i) {
	d = 0;
	d = is_in_pic(i, x, y); // C�lcul de la dist�ncia del punt x,y al pic i
	if (d > 0) {
		d = hmax[i] * (1 - (d / radi[i]))*(1 - (d / radi[i]));
		j++;
	}
	aux_sd += d;
}
return aux_sd;
}
