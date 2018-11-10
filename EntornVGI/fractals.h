//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Entorn MFC o Qt en OpenGL)
//******** Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Octubre 2018)
// fractals.h : interface de fractals.cpp
//

#ifndef FRACTALS
#define FRACTALS

// -------------- Entorn VGI: VALORS CONSTANTS ----------------------------------------------------------

// -------------- Entorn VGI: Alçades (fractals)
#define F_CIRCUIT   'Q'
#define F_RIU       'R'
#define F_MUNTANYA  'M'
#define F_PAISSATGE 'P'
#define F_FITXER    'P'

// Tipus de sorolls (fractals)
#define S_SENSE     'C'
#define S_LINIAL    'L'
#define S_QUADRATIC 'Q'
#define S_SQRT      'S'
#define S_DIFERENCIABLE 'D'

// -------------- Entorn VGI: Objectes precompilats OpenGL amb glNewList
#define FRACTAL 2  // Fractal

// Maxim tamany del fractal
#define FMAX 512

//-------------------- VGI: PALETES PER A PINTAR FRACTALS.

// Màxim tamany paleta
#define MAX_PALETA_FRACTAL 24
// Tipus de paletes
#define MEDITERRANI  'M'
#define TUNDRA       'T'
#define GLACIAR     'G'

//  Paleta ECOSISTEMA MEDITERRANI
const double
med_colorR[] = { 0.0, 0.0, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 0.7, 0.7, 0.7, 0.7, 0.2, 0.4, 0.8, 0.8, 0.2, 0.2, 0.2, 0.4, 1.0, 1.0, 1.0, 1.0 };
const double
med_colorG[] = { 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.2, 0.65, 0.65, 0.7, 0.7, 0.7, 1.0, 0.8, 0.8, 1.0, 0.8, 0.6, 0.6, 0.4, 1.0, 1.0, 1.0, 1.0 };
const double
med_colorB[] = { 0.2, 0.3, 0.5, 0.5, 0.5, 0.7, 0.8, 0.8, 0.9, 0.0, 0.4, 0.4, 0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.2, 1.0, 1.0, 1.0, 1.0 };

// Paleta ECOSISTEMA TUNDRA per pintar fractals
const double
tundra_colorR[] = { 0.05, 0.01, 0.1, 0.15, 0.2, 0.1, 0.15, 0.2, 0.24, 0.28, 0.213, 0.25, 0.30, 0.33, 0.40, 0.144, 0.164, 0.2, 0.3, 0.4, 1.0, 1.0, 1.0, 1.0 };
const double
tundra_colorG[] = { 0.001, 0.005, 0.05, 0.08, 0.1, 0.015, 0.02, 0.028, 0.032, 0.09, 0.107, 0.13, 0.18, 0.21, 0.29, 0.145, 0.165, 0.2, 0.3, 0.4, 1.0, 1.0, 1.0, 1.0 };
const double
tundra_colorB[] = { 0.001, 0.005, 0.05, 0.08, 0.1, 0.015, 0.02, 0.028, 0.032, 0.04, 0.057, 0.065, 0.085, 0.1, 0.15, 0.165, 0.2, 0.25, 0.365, 0.465, 1.0, 1.0, 1.0, 1.0 };

// Paleta ECOSISTEMA GLACIAR per pintar fractals
const double
glaciar_colorR[] = { 0.05, 0.01, 0.1, 0.170, 0.6, 0.4, 0.170, 0.200, 0.240, 0.250, 0.520, 0.7, 0.6, 0.520, 0.240, 0.25, 0.3, 0.6, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0 };
const double
glaciar_colorG[] = { 0.001, 0.005, 0.05, 0.308, 0.6, 0.4, 0.308, 0.338, 0.378, 0.388, 0.796, 0.7, 0.6, 0.796, 0.378, 0.25, 0.3, 0.6, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0 };
const double
glaciar_colorB[] = { 0.001, 0.005, 0.05, 0.400, 0.65, 0.45, 0.400, 0.430, 0.470, 0.480, 0.800, 0.75, 0.65, 0.800, 0.380, 0.3, 0.365, 0.695, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0 };


// -------------- Entorn VGI: DEFINICIÓ DE FUNCIONS -----------------------------------------------------

// -------------- Entorn VGI: Lectura i escriptura fitxers de fractals.
int llegir_pts(char *nomf);
bool escriure_pts(char *nomf,int paso);

// -------------- Entorn VGI: Càlcul d'alçades intermitges
void itera_fractal(char bruit,int paso);

// -------------- Entorn VGI: Càlcul del soroll per cada alçada (i,j)
double soroll(int i,int j,double alf,char noise);

// -------------- Entorn VGI: Soroll linial segons la posició del punt (x,y)
double soroll_lin(int x,int y);
// -------------- Entorn VGI: Soroll quadràtic segons la posició del punt (x,y)
double soroll_quad(int x,int y);
// -------------- Entorn VGI: Soroll arrel quadrada segons la posició del punt (x,y)
double soroll_sq(int x,int y);
// -------------- Entorn VGI: Soroll diferenciable segons la posició del punt (x,y)
double soroll_dif(int x,int y);

// -------------- Entorn VGI: Dibuix i triangulació del terreny
void fract(char iluminacio,bool paletaColor,bool sw_mater[4],int step);

#endif
