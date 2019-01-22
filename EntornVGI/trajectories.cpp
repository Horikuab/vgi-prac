//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Codi Pr�ctica 4)
//********  Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Novembre 2018)
// trajectories.cpp: Codi de les funcions per la traject�ria spline:
//                    * spline: Calcula les coordenades del punt (x,y,z) segons t  
//                    * Dspline: Calcula la tangent (tx,ty,tz) segons t

#include "stdafx.h"
#include "constants.h"
#include "trajectories.h"

#include <math.h>

// bspline: Calcul del punt (x,y,z) de l'spline (tangent) en coordenades 3D (CPunt3D)
// Par�metres:	t: Par�metre de la corba (t=[0,1])
//				ctr: Punts de control de la corba
CPunt3D bspline(float t, CPunt3D * ctr)
{
	CPunt3D p={(0,0,0)};
	float coef[4];
	int i,j;
  
//Polinomis que multipliquen els punts de control del patch
	for(i=0;i<4;i++)
	{
		coef[i]=0;
		for(j=0;j<4;j++)
		 coef[i]=coef[i]*t+A[i][j];
	}

//C�lcul de la Posici�
	for(i=0;i<4;i++)
	{
		p.x+=coef[i]*ctr[i].x;
		p.y+=coef[i]*ctr[i].y;
		p.z+=coef[i]*ctr[i].z;
	}
	return p;
   
}

// Dbspline: Calcul de la derivada de l'spline (tangent) en coordenades 3D (CPunt3D)
// Par�metres:	t: Par�metre de la corba (t=[0,1])
//				ctr: Punts de control de la corba
CPunt3D Dbspline(float t, CPunt3D * ctr)
{

	CPunt3D dp={0,0,0};
	float coef[4];
	int i,j;


//Polinomis que multipliquen els punts de control del patch
	for(i=0;i<4;i++)
	{
		coef[i]=0;
		for(j=0;j<3;j++)
		 coef[i]=coef[i]*t+(3-j)*A[i][j];
	}

//C�lcul de la Derivada
	for(i=0;i<4;i++)
	{
		dp.x+=coef[i]*ctr[i].x;
		dp.y+=coef[i]*ctr[i].y;
		dp.z+=coef[i]*ctr[i].z;
	}
	return dp;
}   


//----------------------------  LEMNISCATA

// lemniscata2D: Calcul de la posici� (x,y,z) segons lemniscata 2D (CPoint3D)
CPunt3D lemniscata2D(float t)
{
	CPunt3D p = { (0, 0, 0) };
	//	float angle;
	const double a = 1.0*FMAX*(0.6); // par�metre lemniscata

	float bet = sqrtf(2.0) / 2;
	float x1 = a*cos(2 * t*pi / 180)*cos(t*pi / 180);
	float y1 = a*cos(2 * t*pi / 180)*sin(t*pi / 180);

// C�lcul de la Posici�
	p.x = bet*x1 + bet*y1;
	p.y = -bet*x1 + bet*y1;
	p.z = 0;
	return p;

}

CPunt3D Dlemniscata2D(float t)
{
	const double a = 1.0*FMAX*(0.6); // par�metre lemniscata

	CPunt3D dp = { 0, 0, 0 };

	float bet = sqrtf(2.0) / 2;

	float dx1 = -2 * a*sin(2 * t*pi / 180)*cos(t*pi / 180) - a*cos(2 * t*pi / 180)*sin(t*pi / 180);
	float dy1 = -2 * a*sin(2 * t*pi / 180)*sin(t*pi / 180) + a*cos(2 * t*pi / 180)*cos(t*pi / 180);

//	C�lcul de la Derivada
	dp.x = bet*dx1 + bet*dy1;
	dp.y = -bet*dx1 + bet*dy1;
	dp.z = 0;

	return dp;
}


// lemniscata3D: Calcul de la posici� (x,y,z) segons lemniscata 3D (CPoint3D)
CPunt3D lemniscata3D(float t)
{
	CPunt3D p = { (0, 0, 0) };
	const double a = 1.0*FMAX*(0.6); // par�metre lemniscata

	float bet = sqrtf(2.0) / 2;
	float x1 = a*cos(2 * t*pi / 180)*cos(t*pi / 180);
	float y1 = a*cos(2 * t*pi / 180)*sin(t*pi / 180);
	float z1 = a*(sin(t*pi / 180) + cos(t*pi / 180));	// Traject�ria 1
//	float z1=a*sin(t*pi/180);							// Traject�ria 2

// C�lcul de la Posici�
	p.x = bet*x1 + bet*y1;
	p.y = -bet*x1 + bet*y1;
	p.z = (bet / 4)*z1 + 82;	// Elevaci� 3
	return p;
}

// Dlemniscata3D: Calcul de la posici� (x,y,z) de la tangent de lemniscata 3D (CPoint3D)
CPunt3D Dlemniscata3D(float t)
{
	const double a = 1.0*FMAX*(0.6); // par�metre lemniscata

	CPunt3D dp = { 0, 0, 0 };

	float bet = sqrtf(2.0) / 2;

	float dx1 = -2 * a*sin(2 * t*pi / 180)*cos(t*pi / 180) - a*cos(2 * t*pi / 180)*sin(t*pi / 180);
	float dy1 = -2 * a*sin(2 * t*pi / 180)*sin(t*pi / 180) + a*cos(2 * t*pi / 180)*cos(t*pi / 180);
	float dz1 = a*(cos(t*pi / 180) - sin(t*pi / 180));	// Traject�ria 1
	//	float dz1=a*cos(t*pi/180);					// Traject�ria 2

// C�lcul de la Derivada
	dp.x = bet*dx1 + bet*dy1;
	dp.y = -bet*dx1 + bet*dy1;
	dp.z = bet*dz1;

	return dp;
}

//-------------------------------- FI LEMNISCATA


// ComputeAngleZ:	C�lcul de l'angle de rotaci� Z entre els vectors
//					eix i tangent projectats sobre el pla X-Y.
float ComputeAngleZ(CPunt3D eix,CPunt3D tangent)
{  
	float sinus,cosinus,normeix,normtg,angle;

	sinus=eix.x*tangent.y-eix.y*tangent.x;
	normeix=sqrt(eix.x*eix.x+eix.y*eix.y);
	normtg=sqrt(tangent.x*tangent.x+tangent.y*tangent.y);
	cosinus=(eix.x*tangent.x+eix.y*tangent.y)/(normeix*normtg);

	if(sinus>=0) angle=180.0*acos(cosinus)/pi;
	if(sinus<0) angle=-180.0*acos(cosinus)/pi;

	return angle;
}


// ComputeAngleX:	C�lcul de l'angle de rotaci� X entre els vectors
//					eix i tangent projectats sobre el pla Y-Z.
float ComputeAngleX(CPunt3D eix,CPunt3D tangent)
{  
//	float sinus,cosinus,normeix,normtg
	float angle=0;

	return angle;
}


// C�lcul de l'angle de rotaci� Y a partir del diferencial de dos angles Z
float ComputeAngleY(float angle_nou,float angle_vell)
{  
	float angle;

	return angle;
}
