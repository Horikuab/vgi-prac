//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2013 MULTIFINESTRA amb OpenGL, interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2018)
// visualitzacio.cpp : Funcions de visualització i pantalla
// FUNCIONS:	- Iluminació (Iluminacio)
//				- Visualització Ortogràfica (ProjeccioOrto i Ortografica)
//				- Visualització Perspectiva amb coord. esfèriques (ProjeccioPerspectiva,Vista_Esferica)
//              - Visualització Perspectiva amb navegació per tecles cursor (ProjeccioPerspectiva,Vista_Navega)
//				- Dibuixar els eixos (deixos)
//				- Dibuixar fons: blanc (FonsW) i negre (Fons)
//				- Carregar imatges de formats compatibles amb DevIL/OpenIL com a textura (loadIMA)
//				- Inicialitzar imatges textura per l'objecte Truck
//

#include "stdafx.h"
#include "visualitzacio.h"
#include "escena.h"

// TEXTURES: Vector de noms de textura
GLuint textures[NUM_MAX_TEXTURES]={0,1,2,3,4,5,6,7,8,9};

// Iluminació: Configurar iluminació de l'escena
void Iluminacio(char ilumin,bool ifix,bool ll_amb,LLUM lumin,bool textur,bool textur_map,char obj,bool bc_lin,int step)
{   
	//bool ll_amb=true;
	GLfloat angv,angh;

// Configuració de la font de llum LIGHT0
	GLfloat position[]={0.0,0.0,200.0,1.0};
	GLfloat especular[]={0.0,0.0,0.0,1.0};
    GLfloat ambientg[]={.5,.5,.5,1.0};

// Definició de llum ambient segons booleana ll_amb
	if (ll_amb) glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientg);
		else glLightModelfv(GL_LIGHT_MODEL_AMBIENT,especular);

	if (lumin.encesa) {	if (!ifix) glLightfv(GL_LIGHT0,GL_POSITION,position);
							else {	// Conversió angles graus -> radians
									angv=lumin.posicio.alfa*pi/180;
									angh=lumin.posicio.beta*pi/180;
		
									// Conversió Coord. esfèriques -> Coord. cartesianes
									position[0]=lumin.posicio.R*cos(angh)*cos(angv);	
									position[1]=lumin.posicio.R*sin(angh)*cos(angv);	
									position[2]=lumin.posicio.R*sin(angv);
									position[3]=1.0;
									glLightfv(GL_LIGHT0,GL_POSITION,position);			
								}
						glLightfv(GL_LIGHT0,GL_DIFFUSE,lumin.difusa);
						glLightfv(GL_LIGHT0,GL_SPECULAR,lumin.especular);

						// Coeficients factor atenuació f_att=1/(ad2+bd+c)
						glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,lumin.atenuacio.c);
						glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,lumin.atenuacio.b);
						glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,lumin.atenuacio.a);
						if (lumin.restringida) {
							glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,lumin.spotdirection);
							glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,lumin.cutoff);
							glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,lumin.exponent);
							}
						glEnable(GL_LIGHT0);
					}
		else glDisable(GL_LIGHT0);

	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

// Selecció del model d'iluminació segons variable ilumin
	switch(ilumin)
	{
	case PUNTS:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glEnable(GL_COLOR_MATERIAL);

		// Desactivació de l'ocultació de cares
		glDisable(GL_DEPTH_TEST);

		// Desactivació de la il.luminació
		glDisable(GL_LIGHTING);
		break;

	case FILFERROS:
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glDisable(GL_COLOR_MATERIAL);

// Desactivació de l'ocultació de cares
//		glDisable(GL_DEPTH_TEST);

// Desactivació de la il-luminació
		glDisable(GL_LIGHTING);
		break;

    case PLANA:
// Càlcul de les normals a les cares si l'objecte és un fractal
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
		if (bc_lin) glPolygonMode(GL_BACK,GL_LINE);
		
		glEnable(GL_COLOR_MATERIAL);

// Ocultació de cares
//		glEnable(GL_DEPTH_TEST);

		glEnable(GL_NORMALIZE);    
// Il.luminació per cares planes
		glShadeModel(GL_FLAT); 

// Activació de la llum
		glEnable(GL_LIGHTING);
		break;

	case GOURAUD:
// Càlcul de les normals als vertexs si l'objecte és un fractal
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
		if (bc_lin) glPolygonMode(GL_BACK,GL_LINE);
		
		glEnable(GL_COLOR_MATERIAL);

// Ocultació de cares
//    	glEnable(GL_DEPTH_TEST);

		glEnable(GL_NORMALIZE); 
		
// Il.luminació suau 
        glShadeModel(GL_SMOOTH); 

// Activació de la llum
    	glEnable(GL_LIGHTING);
		break;
	}

// Configuració de les textures.
	if (textur)
	{
// Activació de la textura 0.
	  glBindTexture(GL_TEXTURE_2D,textures[0]) ;

	  if ((obj != OBJ3DS) && (obj != OBJOBJ))
	  {
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
	 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
  		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	   }

// Pregunta 9 enunciat
	  if (textur_map) glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;
	  else glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

// Generació coordenades textura automàtiques per als objectes Fractals.
/*	  if (obj == O_FRACTAL)
	  {	  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

// Coeficicients coordenades textura per a fractals
//			      sfPlane =     p1,p2,p3,p4
		  GLfloat sfPlane[4] = {  ,  ,  ,  }; // s=p1*x0+p2*y0+p3*z0+p4*w0 on p=(x0,y0,z0,w0)
		  //	  tfPlane =     p1,p2,p3,p4
		  GLfloat tfPlane[4] = {  ,  ,  ,  }; // t=p1*x0+p2*y0+p3*z0+p4*w0 on p=(x0,y0,z0,w0)

		  glTexGenfv(GL_S, GL_OBJECT_PLANE, sfPlane);
		  glTexGenfv(GL_T, GL_OBJECT_PLANE, tfPlane);

		  glEnable(GL_TEXTURE_GEN_S);
		  glEnable(GL_TEXTURE_GEN_T);
	  }
*/
// Coeficicients generació coordenades textura automàtiques per a resta d'objectes
 /*	  else
	  {	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);

// Generació coordenades textura.
	  GLfloat sPlane[4] = { -1.0f, 1.0f, 0.0f, 1.0f };
	  GLfloat tPlane[4] = { -1.0f, 0.0f, 1.0f, 1.0f };

	  glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
	  glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

	  glEnable(GL_TEXTURE_GEN_S);
	  glEnable(GL_TEXTURE_GEN_T);
	  }
*/
	  glEnable(GL_TEXTURE_2D) ;
	}
	else { glDisable(GL_TEXTURE_2D);
	       glDisable(GL_TEXTURE_GEN_S);
	       glDisable(GL_TEXTURE_GEN_T);
		}

// Creació de la llista que dibuixarà els eixos
//   funció on està codi per dibuixar eixos
	glNewList(EIXOS,GL_COMPILE);
// Dibuix dels eixos sense il.luminació
//	if (ilumin!=FILFERROS) 
		glDisable(GL_LIGHTING);           	
// Dibuixar eixos sense textures
//	if (textura) 
		glDisable(GL_TEXTURE_2D);
	    deixos();
	    if (ilumin!=FILFERROS) glEnable(GL_LIGHTING);   
	    if (textur) glEnable(GL_TEXTURE_2D);
	glEndList();
}

// -------- Entorn VGI: ORTOGRÀFICA (Funcions Projeccio_Orto i Vista_Ortografica)

// Projeccio_Orto: Definició Viewport i glOrtho 
// ---- Entorn VGI: ATENCIÓ!!. CAL DEFINIR PARÀMETRES DE LA FUNCIÓ
void Projeccio_Orto(int minx,int miny,int maxx,int maxy)
{   
// ---- Entorn VGI: ATENCIÓ!!. ESPECIFICACIO DELS PARÀMETRES DE PROJECCIÓ ORTOGRÀFICA
//			        QUE ES CARREGUEN A LA MATRIU DE PROJECCIÓ GL_PROJECTION
	
	glViewport(minx, miny, maxx, maxy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Vista_Ortogràfica: Ilumina i dibuixa l'escena. Crida a la funció gluLookAt segons la variable prj 
//				(planta, alçat, perfil o axonometrica).
void Vista_Ortografica(int prj,GLfloat Raux,CColor col_fons,CColor col_object,char objecte,GLfloat mida,int step, 
				bool oculta,bool testv,bool bck_ln,char iluminacio,bool llum_amb,LLUM lumi,
				bool textur,bool textur_map,bool ifix,bool eix)
{

// Iluminacio movent-se amb la camara (abans gluLookAt)
	if (!ifix) Iluminacio(iluminacio,ifix,llum_amb,lumi,textur,textur_map,objecte,bck_ln,step);

// Implementació de planta,alçat,perfil i isomètrica 
// ---- Entorn VGI: ATENCIÓ!!. ESPECIFICACIO DEL PUNT DE VISTA
//								Cal definir el punt de vista (gluLookAt) en funció del
//								tipus de projecció definit a la variable prj.
	switch (prj)
	{
	case 1:
		gluLookAt(0, 10, 5, 0, 0, 5, 0,0, 1);
		break;
	case 2:
		gluLookAt(10, 5, 5, 0, 5, 5, 0, 0, 1);
		break;
	case 3:
		gluLookAt(10, 10, 0, 0, 0, 0, 0, 0, 1);
		break;
	default:
		gluLookAt(0, 0, 10, 0, 0, 0, 0, -1, 0);
		break;
	}
	
// Neteja dels buffers de color i profunditat
	Fons(col_fons);

// Iluminacio fixe respecte la camara (després gluLookAt)
	if (ifix) Iluminacio(iluminacio,ifix,llum_amb,lumi,textur,textur_map,objecte,bck_ln,step);

// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
	if (bck_ln) glPolygonMode(GL_BACK, GL_LINE);

// Dibuix dels eixos
	if (eix) glCallList(EIXOS);
}

// -------- Entorn VGI: PERSPECTIVA (Funcions Projeccio_Perspectiva i Vista_Esferica)

// Projeccio_Perspectiva: Definició Viewport i gluPerspective
void Projeccio_Perspectiva(int minx,int miny,GLsizei w,GLsizei h,float zoom)
{

// Definició Viewport
	glViewport(minx,miny,w,h);
	if (h==0) h=1;

// Activació i inicialització matriu PROJECTION
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

// PROJECCIO PERSPECTIVA.Definim volum de visualització adaptant-lo 
//	 a les mides actuals de la finestra windows	

// Amb gluPerspective
	if (w>=h) 
	gluPerspective(60.0,1.0*w/h,p_near,p_far+zoom);
	else gluPerspective(60.0*h/w,1.0*w/h,p_near,p_far+zoom);

// Activació matriu MODELVIEW (tancar matriu PROJECTION)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Perspectiva: Definició gluLookAt amb possibilitat de moure 
//				el punt de vista interactivament amb el ratolí, 
//				ilumina i dibuixa l'escena
void Vista_Esferica(CEsfe3D opv,char VPol,bool pant,CPunt3D tr,CPunt3D trF,
				 CColor col_fons,CColor col_object,char objecte,double mida,int step, 
				 bool oculta,bool testv,bool bck_ln,char iluminacio, bool llum_amb,LLUM lumi,bool textur,
				 bool textur_map,bool ifix,bool eix)
{    
	GLfloat cam[3],up[3];

// Conversió angles radians -> graus
   	opv.alfa=opv.alfa*pi/180;
    opv.beta=opv.beta*pi/180;

	if(opv.R<1.0) opv.R=1.0;

// Neteja dels buffers de color i profunditat
	Fons(col_fons);

// Posició càmera i vector cap amunt
	if (VPol==POLARZ) { cam[0]=opv.R*cos(opv.beta)*cos(opv.alfa);
						cam[1]=opv.R*sin(opv.beta)*cos(opv.alfa);
						cam[2]=opv.R*sin(opv.alfa);		
						up[0]=-cos(opv.beta)*sin(opv.alfa);
						up[1]=-sin(opv.beta)*sin(opv.alfa);
						up[2]=cos(opv.alfa);	}
		else if (VPol==POLARY) {	cam[0]=opv.R*sin(opv.beta)*cos(opv.alfa);
									cam[1]=opv.R*sin(opv.alfa);
									cam[2]=opv.R*cos(opv.beta)*cos(opv.alfa);		
									up[0]=-sin(opv.beta)*sin(opv.alfa);
									up[1]=cos(opv.alfa);
									up[2]=-cos(opv.beta)*sin(opv.alfa);		}
			else {	cam[0]=opv.R*sin(opv.alfa);
					cam[1]=opv.R*cos(opv.beta)*cos(opv.alfa);
					cam[2]=opv.R*sin(opv.beta)*cos(opv.alfa);		
					up[0]=cos(opv.alfa);
					up[1]=-cos(opv.beta)*sin(opv.alfa);
					up[2]=-sin(opv.beta)*sin(opv.alfa);		}

// Iluminacio movent-se amb la camara (abans glLookAt)
	if (!ifix) Iluminacio(iluminacio,ifix,llum_amb,lumi,textur,textur_map,objecte,bck_ln,step);

// Opció pan: desplaçament del Centre de l'esfera (pant=1)
	if (pant) glTranslatef(tr.x,tr.y,tr.z);
	glTranslatef(trF.x,trF.y,trF.z);	// Traslació fixada amb la INSERT dins l'opció pan

// Especificació del punt de vista
   gluLookAt(cam[0],cam[1],cam[2],0.,0.,0.,up[0],up[1],up[2]);

// Iluminacio fixe respecte la camara (després glLookAt)
	if (ifix) Iluminacio(iluminacio,ifix,llum_amb,lumi,textur,textur_map,objecte,bck_ln,step);

// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
	if (bck_ln) glPolygonMode(GL_BACK, GL_LINE);

//  Dibuix dels eixos
	if (eix) glCallList(EIXOS);
}


//Vista_Navega: Definició gluLookAt directament per paràmetre, sense esfèriques.
//              amb possibilitat de moure el punt de vista interactivament amb les
//				tecles de cursor per poder navegar.
void Vista_Navega(CPunt3D pv,bool pvb,GLfloat n[3],GLfloat v[3],bool pant,CPunt3D tr,CPunt3D trF,
				  CColor col_fons,CColor col_object,char objecte,bool color,
				 int step,bool oculta,bool testv,bool bck_ln, char iluminacio,bool llum_amb,LLUM lumi, 
				 bool textur,bool textur_map,bool ifix,bool eix)
{    
//    int i,j;
	double altfar=0;
//	GLfloat pvZ=0.0;

// Neteja dels buffers de color i profunditat
	Fons(col_fons);

// Iluminacio movent-se amb la camara (abans glLookAt)
	if (!ifix) Iluminacio(iluminacio,ifix,llum_amb,lumi,textur,textur_map,objecte,bck_ln,step);

// Opció pan: desplaçament del Centre de l'esfera (pant=true)
	if (pant) glTranslatef(tr.x,tr.y,tr.z);
	glTranslatef(trF.x,trF.y,trF.z);	// Traslació fixada amb la INSERT dins l'opció pan

// Especificació del punt de vista
	gluLookAt(pv.x,pv.y,pv.z,n[0],n[1],n[2],v[0],v[1],v[2]);

// Iluminacio fixe respecte la camara (després glLookAt)
	if (ifix) Iluminacio(iluminacio,ifix,llum_amb,lumi,textur,textur_map,objecte,bck_ln,step);

// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
	if (bck_ln) glPolygonMode(GL_BACK, GL_LINE);

// Dibuix dels eixos
	if (eix) glCallList(EIXOS);
}


// instancia: Aplica Transformacions Geom?triques d'instanciació, segons els par?metres 
//            definits a la persiana Transformacions
void instancia(bool TR, INSTANCIA tg, INSTANCIA tgF)
{

// Transformacions geometriques sobre objecte (Traslacio, Rotacions i Escalatge)
	if (TR) glTranslatef(tg.VTras.x, tg.VTras.y, tg.VTras.z);
	glTranslatef(tgF.VTras.x, tgF.VTras.y, tgF.VTras.z);	// Traslacio fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glRotatef(tg.VRota.x, 1, 0, 0);
	glRotatef(tgF.VRota.x, 1, 0, 0);					// Rotacio X fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glRotatef(tg.VRota.y, 0, 1, 0);
	glRotatef(tgF.VRota.y, 0, 1, 0);					// Rotacio Y fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glRotatef(tg.VRota.z, 0, 0, 1);
	glRotatef(tgF.VRota.z, 0, 0, 1);					// Rotacio Z fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glScalef(tg.VScal.x, tg.VScal.y, tg.VScal.z);
	glScalef(tgF.VScal.x, tgF.VScal.y, tgF.VScal.z);	// Escalatge fixada amb la INSERT dins l'opci? Transformacions
}


// deixos: Dibuix dels eixos coordenats
void deixos()
{
// Doblar el gruix de la linia dels eixos.
	glLineWidth(2.0);

// Eix X (vermell)
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	 glVertex3f(0.0,0.0,0.0);
	 glVertex3f(300.0,0.0,0.0);
	glEnd();

// Eix Y (verd)
    glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	 glVertex3f(0.0,0.0,0.0);
	 glVertex3f(0.0,300.0,0.0);
	glEnd();

// Eix Z (blau) 
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_LINES);
	 glVertex3f(0.0,0.0,0.0);
	 glVertex3f(0.0,0.0,300.0);
	glEnd();

// Restaurar el gruix de la linia dels eixos
	glLineWidth(1.0);
}


// Fons: Dibuixa el fons variable sefons el color int_fons
void Fons(CColor int_fons)
{
	glClearColor(int_fons.r,int_fons.g,int_fons.b,1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f,0.f,0.f,1.f);
	glClear(GL_DEPTH_BUFFER_BIT);
   glFlush();
}

// FonsN: Dibuixa el fons negre
void FonsN()
{
	glClearColor(0.f,0.f,0.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glFlush();
}

// FonsB: Dibuixa el fons blanc
void FonsB()
{
	glClearColor(1.f,1.f,1.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f,0.f,0.f,1.f);
	glClear(GL_DEPTH_BUFFER_BIT);
   glFlush();
}


// TEXTURES------------------------------------------------------
// loadIMA: This function receives as input the image filename and an 
// integer identifier (0 for the first texture) and creates an OpenGL 
// texture which is stored in the global array 'textures'
// Paràmetres:
//		- filename: Fitxer que conté la imatge de qualsevol format:
//					BMP, JPG, TIFF, TGA, GIF, i d'altres suportats per OpenIL
//		- texID: Identificador dins la taula textures on volem
//                assignar la imatge
bool loadIMA(char * filename, int texID)
{
	FILE *file = NULL;
	int errno = 0;
	char szFilePath[255];

// Open the image file for reading
//  file=fopen(nomf,"r");					// Funció Visual Studio 6.0
	errno = fopen_s(&file, filename, "rb");		// Funció Visual 2010

// If the file is empty (or non existent) print an error and return false
// if (file == NULL)
	if (errno != 0)
	{
	//	printf("Could not open file '%s'.\n",filename) ;
		return false;
	}

// Close the image file
	fclose(file);

// strcpy_s: Conversió variable char* --> char[255]
	strcpy_s(szFilePath, filename); // Copiar path sencer amb nom de fitxer.

// reinterpret_cast: Funció de converió d'una variable char * -> wchar_t *
	wchar_t *nomf = reinterpret_cast <wchar_t *> (szFilePath);

// ilutGLLoadImage: Funció que llegeix la imatge del fitxer filename
//				si és compatible amb els formats DevIL/OpenIL (BMP,JPG,GIF,TIF,TGA,etc.)
//				i defineix la imatge com a textura OpenGL retornant l'identificador 
//				de textura OpenGL.
	textures[texID] = ilutGLLoadImage(nomf);

// If execution arrives here it means that all went well. Return true
	return true;
}


// Inicialitzar imatges textures pel Truck
void Init_Textures()
{	
	loadIMA("./textures/vent.bmp",1);	

	loadIMA("./textures/plat.bmp",2);

	loadIMA("./textures/reixeta.bmp",3);	

	loadIMA("./textures/fars.bmp",4);

	loadIMA("./textures/txapa.bmp",5);

	loadIMA("./textures/metall.bmp",6); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
	 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;
}

//----------------- FONTS LLIBRERIA GLU

// gluLookAt: Funció defineix matriu de PV i la carrega a l'estructura de matrius OpenGL 
void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx,
	GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy,
	GLdouble upz)
{
	float forward[3], side[3], up[3];
	GLfloat m[4][4];

	forward[0] = centerx - eyex;
	forward[1] = centery - eyey;
	forward[2] = centerz - eyez;

	up[0] = upx;
	up[1] = upy;
	up[2] = upz;

	normalize(forward);

	/* Side = forward x up */
	cross(forward, up, side);
	normalize(side);

	/* Recompute up as: up = side x forward */
	cross(side, forward, up);

	__gluMakeIdentityf(&m[0][0]);
	m[0][0] = side[0];
	m[1][0] = side[1];
	m[2][0] = side[2];

	m[0][1] = up[0];
	m[1][1] = up[1];
	m[2][1] = up[2];

	m[0][2] = -forward[0];
	m[1][2] = -forward[1];
	m[2][2] = -forward[2];

	glMultMatrixf(&m[0][0]);
	glTranslated(-eyex, -eyey, -eyez);
}

// gluLookAt: Funció defineix matriu de Projecció Perspectiva i la carrega a l'estructura de matrius OpenGL 
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble m[4][4];
	double sine, cotangent, deltaZ;
	double radians = fovy / 2 * __glPi / 180;

	deltaZ = zFar - zNear;
	sine = sin(radians);
	if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
		return;
	}
	cotangent = cos(radians) / sine;

	__gluMakeIdentityd(&m[0][0]);

	m[0][0] = cotangent / aspect;
	m[1][1] = cotangent;
	m[2][2] = -(zFar + zNear) / deltaZ;
	m[2][3] = -1;
	m[3][2] = -2 * zNear * zFar / deltaZ;
	m[3][3] = 0;
	glMultMatrixd(&m[0][0]);
}


// gluMakeIdentityf: Funció defineix una matriu identitat 
static void __gluMakeIdentityf(GLfloat m[16])
{
	m[0 + 4 * 0] = 1; m[0 + 4 * 1] = 0; m[0 + 4 * 2] = 0; m[0 + 4 * 3] = 0;
	m[1 + 4 * 0] = 0; m[1 + 4 * 1] = 1; m[1 + 4 * 2] = 0; m[1 + 4 * 3] = 0;
	m[2 + 4 * 0] = 0; m[2 + 4 * 1] = 0; m[2 + 4 * 2] = 1; m[2 + 4 * 3] = 0;
	m[3 + 4 * 0] = 0; m[3 + 4 * 1] = 0; m[3 + 4 * 2] = 0; m[3 + 4 * 3] = 1;
}

static void __gluMakeIdentityd(GLdouble m[16])
{
	m[0 + 4 * 0] = 1; m[0 + 4 * 1] = 0; m[0 + 4 * 2] = 0; m[0 + 4 * 3] = 0;
	m[1 + 4 * 0] = 0; m[1 + 4 * 1] = 1; m[1 + 4 * 2] = 0; m[1 + 4 * 3] = 0;
	m[2 + 4 * 0] = 0; m[2 + 4 * 1] = 0; m[2 + 4 * 2] = 1; m[2 + 4 * 3] = 0;
	m[3 + 4 * 0] = 0; m[3 + 4 * 1] = 0; m[3 + 4 * 2] = 0; m[3 + 4 * 3] = 1;
}

static void normalize(float v[3])
{
	float r;

	r = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (r == 0.0) return;

	v[0] /= r;
	v[1] /= r;
	v[2] /= r;
}

static void cross(float v1[3], float v2[3], float result[3])
{
	result[0] = v1[1] * v2[2] - v1[2] * v2[1];
	result[1] = v1[2] * v2[0] - v1[0] * v2[2];
	result[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

