//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Entorn pràctiques)
//******** marc Vivet, Carme Julià, Débora Gil, Enric Martí  (Octubre 2018)
// normals.cpp : Funcions de càlcul de vectors normals per
//               visualització de fractals 

#include "StdAfx.h"

#include <math.h>

#include "fractals.h"
#include "normals.h"

// -------------- Entorn VGI: CALCUL DE LES NORMALS A UNA TRIANGULACIO  D'UNA QUADRÍCULA zz ---------------

// normal: Càlcul del producte vectorial normalitzat de dos vectors v1,v2.
//         Resultat a la variable n.
void normal(double v1[3],double v2[3],double n[3])
{
    
	float longitud;

	n[0] = v1[1] * v2[2] - v2[1] * v1[2];
	n[1] = v1[2] * v2[0] - v2[2] * v1[0];
	n[2] = v1[0] * v2[1] - v1[1] * v2[0];

// Normalitzem el vector
	longitud = sqrt( n[0] * n[0] +
		n[1] * n[1]+ n[2] * n[2]);
	n[0] = n[0] / longitud;
	n[1] = n[1] / longitud;
	n[2] = n[2] / longitud;
}

// normalvertex: Càlcul de les normals unitàries als VERTEXS
//				 a una triangulació de la matriu zz segons el pas 'step'
//				 tenint en compte les normals de les superfícies veïnes.
//               S'utilitza en la il.luminació SUAU del fractal
// FMAX: Index màxim de la matriu d'alçades definida a constants.h (valor:512).
// normalsV: Es guarda el vector normal de cada vèrtex.
void normalvertex(int step)
{
	int i,j;
	double v1[3],v2[3],n[3];
	float longitut;

	for(i=step;i<FMAX;i=i+step)
	{
	 for(j=step;j<FMAX;j=j+step)
	 {

	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[i+step][j]-zz[i][j];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[i+step][j+step]-zz[i][j];

	  normal(v1,v2,n);

      normalsV[i][j][0]=normalsV[i][j][0]+n[0];
      normalsV[i][j][1]=normalsV[i][j][1]+n[1];
      normalsV[i][j][2]=normalsV[i][j][2]+n[2];

	  v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[i+step][j+step]-zz[i][j];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[i][j+step]-zz[i][j];
	  
	  normal(v1,v2,n);

	  normalsV[i][j][0]=normalsV[i][j][0]+n[0];
      normalsV[i][j][1]=normalsV[i][j][1]+n[1];
      normalsV[i][j][2]=normalsV[i][j][2]+n[2];

      v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[i][j-step]-zz[i-step][j-step];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[i][j]-zz[i-step][j-step];

	  normal(v1,v2,n);

	  normalsV[i][j][0]=normalsV[i][j][0]+n[0];
      normalsV[i][j][1]=normalsV[i][j][1]+n[1];
      normalsV[i][j][2]=normalsV[i][j][2]+n[2];

      v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[i][j]-zz[i-step][j-step];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[i-step][j]-zz[i-step][j-step];
	  
	  normal(v1,v2,n);

	  normalsV[i][j][0]=normalsV[i][j][0]+n[0];
      normalsV[i][j][1]=normalsV[i][j][1]+n[1];
      normalsV[i][j][2]=normalsV[i][j][2]+n[2];

      v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[i+step][j]-zz[i][j-step];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[i][j]-zz[i][j-step];
	  
	  normal(v1,v2,n);

	  normalsV[i][j][0]=normalsV[i][j][0]+n[0];
      normalsV[i][j][1]=normalsV[i][j][1]+n[1];
      normalsV[i][j][2]=normalsV[i][j][2]+n[2];

 
	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[i][j]-zz[i-step][j];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[i][j+step]-zz[i-step][j];

	  normal(v1,v2,n);

	  normalsV[i][j][0]=normalsV[i][j][0]+n[0];
      normalsV[i][j][1]=normalsV[i][j][1]+n[1];
      normalsV[i][j][2]=normalsV[i][j][2]+n[2];

      longitut=sqrt( normalsV[i][j][0]* normalsV[i][j][0]+
		   normalsV[i][j][1]* normalsV[i][j][1]+
		    normalsV[i][j][2]* normalsV[i][j][2]);
	   
	  normalsV[i][j][0]= normalsV[i][j][0]/longitut;
      normalsV[i][j][1]= normalsV[i][j][1]/longitut;
      normalsV[i][j][2]= normalsV[i][j][2]/longitut;
	 }
	}

	for(int k=step;k<FMAX;k=k+step)
	{
      
	//j=0	
	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[k+step][0]-zz[k][0];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[k+step][step]-zz[k][0];

	  normal(v1,v2,n);

      normalsV[k][0][0]=normalsV[k][0][0]+n[0];
      normalsV[k][0][1]=normalsV[k][0][1]+n[1];
      normalsV[k][0][2]=normalsV[k][0][2]+n[2];

	  v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[k+step][step]-zz[k][0];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[k][step]-zz[k][0];
	  
	  normal(v1,v2,n);

	  normalsV[k][0][0]=normalsV[k][0][0]+n[0];
      normalsV[k][0][1]=normalsV[k][0][1]+n[1];
      normalsV[k][0][2]=normalsV[k][0][2]+n[2];

	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[k][0]-zz[k-step][0];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[k][step]-zz[k-step][0];
	  
	  normal(v1,v2,n);

	  
	  normalsV[k][0][0]=normalsV[k][0][0]+n[0];
      normalsV[k][0][1]=normalsV[k][0][1]+n[1];
      normalsV[k][0][2]=normalsV[k][0][2]+n[2];

	  longitut=sqrt( normalsV[k][0][0]* normalsV[k][0][0]+
		   normalsV[k][0][1]* normalsV[k][0][1]+
		    normalsV[k][0][2]* normalsV[k][0][2]);
	   
	  normalsV[k][0][0]= normalsV[k][0][0]/longitut;
      normalsV[k][0][1]= normalsV[k][0][1]/longitut;
      normalsV[k][0][2]= normalsV[k][0][2]/longitut;
	

	  //j=max
      v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[k][FMAX-step]-zz[k-step][FMAX-step];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[k][FMAX]-zz[k-step][FMAX-step];

	  normal(v1,v2,n);

	  normalsV[k][FMAX][0]=normalsV[k][FMAX][0]+n[0];
      normalsV[k][FMAX][1]=normalsV[k][FMAX][1]+n[1];
      normalsV[k][FMAX][2]=normalsV[k][FMAX][2]+n[2];

      v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[k][FMAX]-zz[k-step][FMAX-step];
	  v2[0]=step;
	  v2[1]=0;
	  v2[2]=zz[k-step][FMAX]-zz[k-step][FMAX-step];
	  
	  normal(v1,v2,n);

      normalsV[k][FMAX][0]=normalsV[k][FMAX][0]+n[0];
      normalsV[k][FMAX][1]=normalsV[k][FMAX][1]+n[1];
      normalsV[k][FMAX][2]=normalsV[k][FMAX][2]+n[2];

      v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[k+step][FMAX]-zz[k][FMAX-step];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[k][FMAX]-zz[k][FMAX-step];

	  normal(v1,v2,n);

	  normalsV[k][FMAX][0]=normalsV[k][FMAX][0]+n[0];
      normalsV[k][FMAX][1]=normalsV[k][FMAX][1]+n[1];
      normalsV[k][FMAX][2]=normalsV[k][FMAX][2]+n[2];

      longitut=sqrt( normalsV[k][FMAX][0]* normalsV[k][FMAX][0]+
		   normalsV[k][FMAX][1]* normalsV[k][FMAX][1]+
		    normalsV[k][FMAX][2]* normalsV[k][FMAX][2]);
	   
	  normalsV[k][FMAX][0]= normalsV[k][FMAX][0]/longitut;
      normalsV[k][FMAX][1]= normalsV[k][FMAX][1]/longitut;
      normalsV[k][FMAX][2]= normalsV[k][FMAX][2]/longitut;
	
	  // i=max
	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[FMAX][k-step]-zz[FMAX-step][k-step];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[FMAX][k]-zz[FMAX-step][k-step];

	  normal(v1,v2,n);

      normalsV[FMAX][k][0]=normalsV[FMAX][k][0]+n[0];
      normalsV[FMAX][k][1]=normalsV[FMAX][k][1]+n[1];
      normalsV[FMAX][k][2]=normalsV[FMAX][k][2]+n[2];

	  v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[FMAX][k]-zz[FMAX-step][k-step];
	  v2[0]=step;
	  v2[1]=0;
	  v2[2]=zz[FMAX-step][k]-zz[FMAX-step][k-step];
	  
	  normal(v1,v2,n);

      normalsV[FMAX][k][0]=normalsV[FMAX][k][0]+n[0];
      normalsV[FMAX][k][1]=normalsV[FMAX][k][1]+n[1];
      normalsV[FMAX][k][2]=normalsV[FMAX][k][2]+n[2];

	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[FMAX][k]-zz[FMAX-step][k];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[FMAX][k+step]-zz[FMAX-step][k];

	  normal(v1,v2,n);

	  normalsV[FMAX][k][0]=normalsV[FMAX][k][0]+n[0];
      normalsV[FMAX][k][1]=normalsV[FMAX][k][1]+n[1];
      normalsV[FMAX][k][2]=normalsV[FMAX][k][2]+n[2];


	    longitut=sqrt( normalsV[FMAX][k][0]* normalsV[FMAX][k][0]+
		   normalsV[FMAX][k][1]* normalsV[FMAX][k][1]+
		    normalsV[FMAX][k][2]* normalsV[FMAX][k][2]);
	   
	  normalsV[FMAX][k][0]= normalsV[FMAX][k][0]/longitut;
      normalsV[FMAX][k][1]= normalsV[FMAX][k][1]/longitut;
      normalsV[FMAX][k][2]= normalsV[FMAX][k][2]/longitut;
	
	  //i=0
	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[step][k]-zz[0][k];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[step][k+step]-zz[0][k];

	  normal(v1,v2,n);

	  normalsV[0][k][0]=normalsV[0][k][0]+n[0];
      normalsV[0][k][1]=normalsV[0][k][1]+n[1];
      normalsV[0][k][2]=normalsV[0][k][2]+n[2];

      v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[step][k+step]-zz[0][k];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[0][k+step]-zz[0][k];

	  normal(v1,v2,n);

      normalsV[0][k][0]=normalsV[0][k][0]+n[0];
      normalsV[0][k][1]=normalsV[0][k][1]+n[1];
      normalsV[0][k][2]=normalsV[0][k][2]+n[2];

     
	  v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[step][k]-zz[0][k-step];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[0][k]-zz[0][k-step];
	  
	  normal(v1,v2,n);

	  normalsV[0][k][0]=normalsV[0][k][0]+n[0];
      normalsV[0][k][1]=normalsV[0][k][1]+n[1];
      normalsV[0][k][2]=normalsV[0][k][2]+n[2];

	  
	   longitut=sqrt( normalsV[0][k][0]* normalsV[0][k][0]+
		   normalsV[0][k][1]* normalsV[0][k][1]+
		    normalsV[0][k][2]* normalsV[0][k][2]);
	   
	  normalsV[0][k][0]= normalsV[0][k][0]/longitut;
      normalsV[0][k][1]= normalsV[0][k][1]/longitut;
      normalsV[0][k][2]= normalsV[0][k][2]/longitut;
	}

	// Extrems

	  //n[0][0]
	  v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[step][step]-zz[0][0];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[0][step]-zz[0][0];
	  
	  normal(v1,v2,n);

	  normalsV[0][0][0]=n[0];
	  normalsV[0][0][1]=n[1];
	  normalsV[0][0][2]=n[2];

	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[step][0]-zz[0][0];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[step][step]-zz[0][0];
	  
	  normal(v1,v2,n);

	  normalsV[0][0][0]=normalsV[0][0][0]+n[0];
      normalsV[0][0][1]=normalsV[0][0][1]+n[1];
      normalsV[0][0][2]=normalsV[0][0][2]+n[2];

	   longitut=sqrt( normalsV[0][0][0]* normalsV[0][0][0]+
		   normalsV[0][0][1]* normalsV[0][0][1]+
		    normalsV[0][0][2]* normalsV[0][0][2]);
	   
	  normalsV[0][0][0]= normalsV[0][0][0]/longitut;
      normalsV[0][0][1]= normalsV[0][0][1]/longitut;
      normalsV[0][0][2]= normalsV[0][0][2]/longitut;

	  //n[max][0]
	  v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[FMAX][0]-zz[FMAX-step][0];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[FMAX][step]-zz[FMAX-step][0];
	 
	  normal(v1,v2,n);

	  normalsV[FMAX][0][0]=n[0];
	  normalsV[FMAX][0][1]=n[1];
	  normalsV[FMAX][0][2]=n[2];

	  //n[max][max]
      v1[0]=step;
	  v1[1]=0;
	  v1[2]=zz[FMAX][FMAX-step]-zz[FMAX-step][FMAX-step];
	  v2[0]=step;
	  v2[1]=step;
	  v2[2]=zz[FMAX][FMAX]-zz[FMAX-step][FMAX-step];
	 
	  normal(v1,v2,n);

	  normalsV[FMAX][FMAX][0]=n[0];
	  normalsV[FMAX][FMAX][1]=n[1];
	  normalsV[FMAX][FMAX][2]=n[2];

      v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[FMAX][FMAX]-zz[FMAX-step][FMAX-step];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[FMAX-step][FMAX]-zz[FMAX-step][FMAX-step];
	 
	  normal(v1,v2,n);

      normalsV[FMAX][FMAX][0]=normalsV[FMAX][FMAX][0]+n[0];
      normalsV[FMAX][FMAX][1]=normalsV[FMAX][FMAX][1]+n[1];
      normalsV[FMAX][FMAX][2]=normalsV[FMAX][FMAX][2]+n[2];

	  
	   longitut=sqrt( normalsV[FMAX][FMAX][0]* normalsV[FMAX][FMAX][0]+
		   normalsV[FMAX][FMAX][1]* normalsV[FMAX][FMAX][1]+
		    normalsV[FMAX][FMAX][2]* normalsV[FMAX][FMAX][2]);
	   
	  normalsV[FMAX][FMAX][0]= normalsV[FMAX][FMAX][0]/longitut;
      normalsV[FMAX][FMAX][1]= normalsV[FMAX][FMAX][1]/longitut;
      normalsV[FMAX][FMAX][2]= normalsV[FMAX][FMAX][2]/longitut;

	  //n[0][max]
      v1[0]=step;
	  v1[1]=step;
	  v1[2]=zz[step][FMAX]-zz[0][FMAX-step];
	  v2[0]=0;
	  v2[1]=step;
	  v2[2]=zz[0][FMAX]-zz[0][FMAX-step];

	  normal(v1,v2,n);

	  normalsV[0][FMAX][0]=n[0];
	  normalsV[0][FMAX][1]=n[1];
	  normalsV[0][FMAX][2]=n[2];

}

// normalcara: Càlcul de les normals unitàries a les CARES 
//				per una triangulació de la matriu zz segons el pas 'step'
//				tenint en compte les normals de les superfícies veïnes.
//              S'utilitza en la il.luminació PLANA del fractal
// FMAX: Index màxim de la matriu d'alçades definida a constants.h (valor:512).
// normalsC: Es guarda el vector normal del triangle 1 (V1,V2,V3).
// normalsV: Es guarda el vector normal del triangle 2 (V1,V3,V4).
void normalcara(int step)
{
	int i,j;
	double v1[3],v2[3],n[3];
	for (int i = 0; i < FMAX + 1; i += step) {
		for (int j = 0; j < FMAX + 1; j += step) {
			v1[0] = abs(j-(j+step));
			v1[1] = abs(i);
			v1[2] = abs(zz[i][j]-zz[i][j+step]);
			v2[0] = abs(j);
			v2[1] = abs(i - (i + step));
			v2[2] = abs(zz[i][j] - zz[i + step][j]);
			normal(v1, v2, n);

			normalsC[i][j][0] = n[0];
			normalsC[i][j][1] = n[1];
			normalsC[i][j][2] = n[2];
		}
	}

}

