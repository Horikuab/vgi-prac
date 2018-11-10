//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Entorn Basic)
//******** Marc Vivet, Carme Julià, Débora Gil, Enric Martí  (Octubre 2018)
// normals.h : interface de normals.cpp
//             Declaracions de les funcions de càlcul de 
//			   vectors normals per la visualització dels fractals 


#ifndef NORMALS
#define NORMALS

// -------------- Entorn VGI: Referència a les quadrícules zz i normals, definides
//                            a fractals.cpp.
extern double zz[513][513];
extern double normalsC[513][513][3];
extern double normalsV[513][513][3];

// normal: Càlcul del producte vectorial normalitzat de dos vectors v1,v2.
//         Resultat a la variable n.
void normal(double v1[3],double v2[3],double n[3]);

/// normalvertex: Càlcul de les normals unitàries als VERTEXS
//				  a una triangulació de la matriu zz segons el pas 'step'
//				  tenint en compte les normals de les superfícies veïnes.
//                S'utilitza en la il.luminació SUAU del fractal
void normalvertex(int step);

// normalcara:	Càlcul de les normals unitàries a les CARES 
//				per una triangulació de la matriu zz segons el pas 'step'
//				tenint en compte les normals de les superfícies veïnes.
//              S'utilitza en la il.luminació PLANA del fractal
void normalcara(int step);

#endif
