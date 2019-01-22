//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Codi Pràctica 4)
//********   Marc Vivet, Carme julià, Débora Gil, Enric Martí (Novembre 2018)
// far.cpp: Codi del far i de la rutina cilindre 
//           INSERIU AQUESTES FUNCIONS EN EL FITXER escena.cpp

// DECLARACIONS FUNCIONS (a escena.h)-----------------------------
void cilindre(double r1,double r2,double h, int slices, int stacks);
void far();
//----------------------------------------------------------------

// CODI DE LES FUNCIONS (a escena.cpp)----------------------------

//Cilindre amb tapes: 
//usage: cilindre(double Rinferior,double Rsuperior,double h,GLUquadricObj *);
void cilindre(double r1,double r2,double h, int slices, int stacks)
{       
	gluCilindre(cilin,r1,r2,h,slices,stacks);
	glPushMatrix();
	 glTranslatef(0,0,h);
	 gluDisc(0,r2,20,20);
	glPopMatrix();

	glPushMatrix();
     glRotatef(180,1,0,0);
	 gluDisc(cilin,0,r1,20,20);
	glPopMatrix();

}

///////////////////////////////////////////////////////////////////////////////////////////

// faro: Far amb llum rotatoria. Cal passar de paràmetrel'angle de rotació (obligatori) i si la llum és encesa o no (opcional)
void faro()
{
//	Variables del focus direccional
	float spot[]={0};         // CODI A INSERIR: Paràmetres de la direcció de la llum spot (GL_SPOT_DIRECTION) de la llum GL_LIGHT1
	float difuse1[]={1.0,1.0,1.0};
	float position[]={0};     // CODI A INSERIR: Posició de la font de llum

//	Definicio de la llum del far com GL_LIGHT1 (si encesa)
//	(font de llum restringida amb atenuació constant 0.5)
/* //	CODI A INSERIR----------------------------------
				glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, <numeric enter>);
				glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, <numeric enter>);
				glLightfv(GL_LIGHT1, GL_AMBIENT, <vector>);

				glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, <numeric enter>);
				glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, <numeric enter>); 
//	FI CODI A INSERIR-------------------------------*/

//	Cos del far
	glColor3f(1.0,0.5,0.0);
    cilindre(5,3,10,20,20);

//	Tapa superior
	glPushMatrix();
	  glTranslatef(0.0f,0.0f,14.0f);
      cilindre(4,4,0.5,20,20);
	glPopMatrix();

//	Llum rotatoria
	glPushMatrix();

//	Codi per a la rotació de la llum del far GL_LIGHT1, si llum encesa
/*	// CODI A INSERIR----------------------------------
	   glRotatef();
	   glColor3f();
	   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, <vector>);
	   glLightfv(GL_LIGHT1, GL_POSITION, <vector>);
	   //	Activar la llum
	   glEnable(GL_LIGHT1);
//	FI CODI A INSERIR------------------------------- */	
	glPopMatrix();

//	Vidre transparent del far
	glEnable(GL_BLEND);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1.0,1.0,174/255,0.5f);

	  glPushMatrix();
	    glTranslatef(0, 0, 10);
	    cilindre(3, 3, 4, 20, 20);
	  glPopMatrix();

	glDisable(GL_BLEND);
}