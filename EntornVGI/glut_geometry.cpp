//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2013 MULTIFINESTRA amb interfície MFC, Status Bar i primitives GLET
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2018)
// glut_geometry.cpp : Codi font de les primitives gràfiques freeglut i GLU adaptades a VS2013.
// FUNCIONS:		- Primitives sòlides (glutSolid<primitiva>)
//					- Primitives filferros (glutWire<primitiva>)
//					- Primitives punts (glutPoint<primitiva>)
//					- Interficie de primitives (glet<primitiva>)
//					- Primitives sòlides (gluCilindre, gluDisc, GluParcialDisc, GluEsfera)

/*
* glut_geometry.cpp
 *
 * Codi adaptat de Freeglut geometry rendering methods.
 *
 * Copyright (c) 2017 Nosferatu Software. All Rights Reserved.
 * Adaptat per Enric Martí Gòdia, <enric.marti@uab.cat>
 * Creation date: Dimarts 9 Maig 2017
 * Update date: Dimarts 28 Novembre 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "stdafx.h"
#include "glut_geometry.h"

/*
 * TODO BEFORE THE STABLE RELEASE:
 *
 * Following functions have been contributed by Andreas Umbach.
 *
 *      glutWireCube()          -- looks OK
 *      glutSolidCube()         -- OK
 *
 * Those functions have been implemented by John Fay.
 *
 *      glutWireTorus()         -- looks OK
 *      glutSolidTorus()        -- looks OK
 *      glutWireDodecahedron()  -- looks OK
 *      glutSolidDodecahedron() -- looks OK
 *      glutWireOctahedron()    -- looks OK
 *      glutSolidOctahedron()   -- looks OK
 *      glutWireTetrahedron()   -- looks OK
 *      glutSolidTetrahedron()  -- looks OK
 *      glutWireIcosahedron()   -- looks OK
 *      glutSolidIcosahedron()  -- looks OK
 *
 *  The Following functions have been updated by Nigel Stewart, based
 *  on FreeGLUT 2.0.0 implementations:
 *
 *      glutWireSphere()        -- looks OK
 *      glutSolidSphere()       -- looks OK
 *      glutWireCone()          -- looks OK
 *      glutSolidCone()         -- looks OK

 *  The Following functions have been updated by Enric Martí, based
 *  on GLU 9.0.0 implementations (include texture coordinates):
 *
 *      gluCilindre()			-- looks OK
 *      gluDisc()				-- looks OK
 *      gluParcialDisc()       -- looks OK
 *      gluEsfera()			-- looks OK
 */


/* -- INTERFACE FUNCTIONS -------------------------------------------------- */
/* ----------CUBE -----------------------------------------------------------*/

/*
 * Draws a solid cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
 */
void glutSolidCube( GLdouble dSize )
{
    double size = dSize * 0.5;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCube" );

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

//---- DEFINICIÓ COORDENADES TEXTURA
//	Activa_Coordenades_Textura();

// PWO: Again, I dared to convert the code to use macros... 
    glBegin( GL_QUADS );
	
// Cub SENSE Textura incrustada glTexCoord2f() -> Activar Coordenades Textura
/*		N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
		N(0.0, 1.0, 0.0);  V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
        N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
        N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
        N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
        N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
*/

// Cub AMB Textura incrustada glTexCoord2f()
		N(1.0, 0.0, 0.0);
		glTexCoord2f(0.0, 1.0); V(+, -, +); glTexCoord2f(0.0, 0.0); V(+, -, -); glTexCoord2f(1.0, 0.0); V(+, +, -); glTexCoord2f(1.0, 1.0); V(+, +, +);
		N(0.0, 1.0, 0.0);
		glTexCoord2f(0.0, 1.0); V(+, +, +); glTexCoord2f(0.0, 0.0); V(+, +, -); glTexCoord2f(1.0, 0.0); V(-, +, -); glTexCoord2f(1.0, 1.0); V(-, +, +);
		N(0.0, 0.0, 1.0);
		glTexCoord2f(0.0, 1.0); V(+, +, +); glTexCoord2f(0.0, 0.0); V(-, +, +); glTexCoord2f(1.0, 0.0); V(-, -, +); glTexCoord2f(1.0, 1.0); V(+, -, +);
		N(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0, 1.0); V(-, +, +); glTexCoord2f(0.0, 0.0); V(-, +, -); glTexCoord2f(1.0, 0.0);  V(-, -, -); glTexCoord2f(1.0, 1.0); V(-, -, +);
		N(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 1.0); V(-, -, +); glTexCoord2f(0.0, 0.0); V(-, -, -); glTexCoord2f(1.0, 0.0); V(+, -, -); glTexCoord2f(1.0, 1.0); V(+, -, +);
		N(0.0, 0.0, -1.0);
		glTexCoord2f(0.0, 1.0); V(-, -, -); glTexCoord2f(0.0, 0.0); V(-, +, -); glTexCoord2f(1.0, 0.0); V(+, +, -); glTexCoord2f(1.0, 1.0); V(+, -, -);

    glEnd();

//---- DEFINICIÓ COORDENADES TEXTURA
//	Desactiva_Coordenades_Textura();

#   undef V
#   undef N
}


/*
* Draws a solid cube with RGB color model. Code contributed by Andreas Umbach <marvin@dataway.ch>
*/
void glutSolidCubeRGB(GLdouble dSize)
{
	double size = dSize * 0.5;
	GLuint vboId = 0;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCube" );

//#   define V(a,b,c) glVertex3d( a size, b size, c size );
//#   define N(a,b,c) glNormal3d( a, b, c );

// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 108 floats (36 * 3 = 108).
	GLfloat vertices[] = { size, size, size, -size, size, size, -size, -size, size,      // v0-v1-v2 (front)
		-size, -size, size, size, -size, size, size, size, size,      // v2-v3-v0

		size, size, size, size, -size, size, size, -size, -size,      // v0-v3-v4 (right)
		size, -size, -size, size, size, -size, size, size, size,      // v4-v5-v0

		size, size, size, size, size, -size, -size, size, -size,      // v0-v5-v6 (top)
		-size, size, -size, -size, size, size, size, size, size,      // v6-v1-v0

		-size, size, size, -size, size, -size, -size, -size, -size,      // v1-v6-v7 (left)
		-size, -size, -size, -size, -size, size, -size, size, size,      // v7-v2-v1

		-size, -size, -size, size, -size, -size, size, -size, size,      // v7-v4-v3 (bottom)
		size, -size, size, -size, -size, size, -size, -size, -size,      // v3-v2-v7

		size, -size, -size, -size, -size, -size, -size, size, -size,      // v4-v7-v6 (back)
		-size, size, -size, size, size, -size, size, -size, -size };    // v6-v5-v4

// Normal array
	GLfloat normals[] = { 0, 0, 1, 0, 0, 1, 0, 0, 1,      // v0-v1-v2 (front)
		0, 0, 1, 0, 0, 1, 0, 0, 1,      // v2-v3-v0

		1, 0, 0, 1, 0, 0, 1, 0, 0,      // v0-v3-v4 (right)
		1, 0, 0, 1, 0, 0, 1, 0, 0,      // v4-v5-v0

		0, 1, 0, 0, 1, 0, 0, 1, 0,      // v0-v5-v6 (top)
		0, 1, 0, 0, 1, 0, 0, 1, 0,      // v6-v1-v0

		-1, 0, 0, -1, 0, 0, -1, 0, 0,    // v1-v6-v7 (left)
		-1, 0, 0, -1, 0, 0, -1, 0, 0,    // v7-v2-v1

		0, -1, 0, 0, -1, 0, 0, -1, 0,   // v7-v4-v3 (bottom)
		0, -1, 0, 0, -1, 0, 0, -1, 0,   // v3-v2-v7

		0, 0, -1, 0, 0, -1, 0, 0, -1,   // v4-v7-v6 (back)
		0, 0, -1, 0, 0, -1, 0, 0, -1 }; // v6-v5-v4

// Color array
	GLfloat colors[] = { 1, 1, 1, 0, 1, 1, 0, 0, 1,      // v0-v1-v2 (front)
		0, 0, 1, 1, 0, 1, 1, 1, 1,      // v2-v3-v0

		1, 1, 1, 1, 0, 1, 1, 0, 0,      // v0-v3-v4 (right)
		1, 0, 0, 1, 1, 0, 1, 1, 1,      // v4-v5-v0

		1, 1, 1, 1, 1, 0, 0, 1, 0,      // v0-v5-v6 (top)
		0, 1, 0, 0, 1, 1, 1, 1, 1,      // v6-v1-v0

		0, 1, 1, 0, 1, 0, 0, 0, 0,      // v1-v6-v7 (left)
		0, 0, 0, 0, 0, 1, 0, 1, 1,      // v7-v2-v1

		0, 0, 0, 1, 0, 0, 1, 0, 1,      // v7-v4-v3 (bottom)
		1, 0, 1, 0, 0, 1, 0, 0, 0,      // v3-v2-v7

		1, 0, 0, 0, 0, 0, 0, 1, 0,      // v4-v7-v6 (back)
		0, 1, 0, 1, 1, 0, 1, 0, 0 };    // v6-v5-v4

// Texture Array
	GLfloat textures[] = { 1, 1, 1, 0, 0, 0,      // v0-v1-v2 (front)
		1, 0, 0, 1, 1, 1,      // v2-v3-v0

		1, 1, 0, 1, 0, 0,      // v0-v3-v4 (right)
		0, 0, 1, 0, 1, 1,      // v4-v5-v0

		1, 1, 1, 0, 0, 1,      // v0-v5-v6 (top)
		0, 1, 1, 0, 1, 1,      // v6-v1-v0

		1, 1, 0, 0, 1, 0,      // v1-v6-v7 (left)
		0, 0, 0, 1, 1, 1,      // v7-v2-v1

		0, 0, 0, 1, 1, 0,      // v7-v4-v3 (bottom)
		1, 0, 1, 1, 0, 0,      // v3-v2-v7

		0, 0, 1, 0, 1, 0,      // v4-v7-v6 (back)
		0, 1, 0, 0, 1, 1 };    // v6-v5-v4


// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors) + sizeof(textures), 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);                             // copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), sizeof(normals), normals);                // copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);  // copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors), sizeof(textures), textures);  // copy textures after colours

// bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals) + sizeof(colors)));
	glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// it is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);

//#   undef V
//#   undef N
}


/* ---------- SPHERE -----------------------------------------------------*/

/*
 * Compute lookup table of cos and sin values forming a cirle
 *
 * Notes:
 *    It is the responsibility of the caller to free these tables
 *    The size of the table is (n+1) to form a connected loop
 *    The last entry is exactly the same as the first
 *    The sign of n can be flipped to get the reverse loop
 */

/*
 * Draws a solid sphere
 */
void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    int i,j;

/* Adjust z and radius as stacks are drawn. */
    double z0,z1;
    double r0,r1;

/* Pre-computed circle */
    double *sint1,*cost1;
    double *sint2,*cost2;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidSphere" );

//---- DEFINICIÓ COORDENADES TEXTURA
	Activa_Coordenades_Textura();

    fghCircleTable(&sint1,&cost1,-slices);
    fghCircleTable(&sint2,&cost2,stacks*2);

/* The top stack is covered with a triangle fan */
    z0 = 1.0;
    z1 = cost2[(stacks>0)?1:0];
    r0 = 0.0;
    r1 = sint2[(stacks>0)?1:0];

    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0,0,1);
        glVertex3d(0,0,radius);

        for (j=slices; j>=0; j--)
        {   glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
            glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
        }
    glEnd();

/* Cover each stack with a quad strip, except the top and bottom stacks */
    for( i=1; i<stacks-1; i++ )
    {
        z0 = z1; z1 = cost2[i+1];
        r0 = r1; r1 = sint2[i+1];
        glBegin(GL_QUAD_STRIP);
            for(j=0; j<=slices; j++)
            {   glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
                glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
                glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
                glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
            }
        glEnd();
    }

/* The bottom stack is covered with a triangle fan */
    z0 = z1;
    r0 = r1;

    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0,0,-1);
        glVertex3d(0,0,-radius);

        for (j=0; j<=slices; j++)
        {   glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
            glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
        }
    glEnd();

//---- DEFINICIÓ COORDENADES TEXTURA
	Desactiva_Coordenades_Textura();

// Release sin and cos tables
    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}


void fghCircleTable(double **sint,double **cost,const int n)
{
    int i;

/* Table size, the sign of n flips the circle direction */
    const int size = abs(n);

/* Determine the angle between samples */
    const double angle = 2*pi/(double)( ( n == 0 ) ? 1 : n );

/* Allocate memory for n samples, plus duplicate of first entry at the end */
    *sint = (double *) calloc(sizeof(double), size+1);
    *cost = (double *) calloc(sizeof(double), size+1);

/* Bail out if memory allocation fails, fgError never returns */
    if (!(*sint) || !(*cost))
    {   free(*sint);
        free(*cost);
		AfxMessageBox(_T("Failed to allocate memory in fghCircleTable"));
    }

/* Compute cos and sin around the circle */
    (*sint)[0] = 0.0;
    (*cost)[0] = 1.0;

    for (i=1; i<size; i++)
    {
        (*sint)[i] = sin(angle*i);
        (*cost)[i] = cos(angle*i);
    }

/* Last sample is duplicate of the first */
    (*sint)[size] = (*sint)[0];
    (*cost)[size] = (*cost)[0];
}


/* ---------- CONE -----------------------------------------------------*/
/*
 * Draws a solid cone
 */
void glutSolidCone( GLdouble base, GLdouble height, GLint slices, GLint stacks )
{
    int i,j;

/* Step in z and radius as stacks are drawn. */
    double z0,z1;
    double r0,r1;

    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );
    const double rStep = base / ( ( stacks > 0 ) ? stacks : 1 );

/* Scaling factors for vertex normals */
    const double cosn = ( height / sqrt ( height * height + base * base ));
    const double sinn = ( base   / sqrt ( height * height + base * base ));

/* Pre-computed circle */
    double *sint,*cost;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCone" );

//---- DEFINICIÓ COORDENADES TEXTURA
	Activa_Coordenades_Textura();

    fghCircleTable(&sint,&cost,-slices);

/* Cover the circular base with a triangle fan... */
    z0 = 0.0;
    z1 = zStep;

    r0 = base;
    r1 = r0 - rStep;

    glBegin(GL_TRIANGLE_FAN);
	    glNormal3d(0.0,0.0,-1.0);
        glVertex3d(0.0,0.0, z0 );
        for (j=0; j<=slices; j++)
            glVertex3d(cost[j]*r0, sint[j]*r0, z0);
    glEnd();

/* Cover each stack with a quad strip, except the top stack */
    for( i=0; i<stacks-1; i++ )
    {
        glBegin(GL_QUAD_STRIP);
            for(j=0; j<=slices; j++)
            {   glNormal3d(cost[j]*cosn, sint[j]*cosn, sinn);
                glVertex3d(cost[j]*r0,   sint[j]*r0,   z0  );
                glVertex3d(cost[j]*r1,   sint[j]*r1,   z1  );
            }
            z0 = z1; z1 += zStep;
            r0 = r1; r1 -= rStep;
        glEnd();
    }

/* The top stack is covered with individual triangles */
    glBegin(GL_TRIANGLES);
	    glNormal3d(cost[0]*sinn, sint[0]*sinn, cosn);

        for (j=0; j<slices; j++)
        {   glVertex3d(cost[j+0]*r0,   sint[j+0]*r0,   z0    );
            glVertex3d(0,              0,              height);
            glNormal3d(cost[j+1]*sinn, sint[j+1]*sinn, cosn  );
            glVertex3d(cost[j+1]*r0,   sint[j+1]*r0,   z0    );
        }
    glEnd();

//---- DEFINICIÓ COORDENADES TEXTURA
	Desactiva_Coordenades_Textura();

/* Release sin and cos tables */
    free(sint);
    free(cost);
}


/* ---------- CYLINDER --------------------------------------------------*/
/*
 * Draws a solid cylinder
 */
void glutSolidCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks)
{
    int i,j;

/* Step in z and radius as stacks are drawn. */
    double z0,z1;
    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );

/* Pre-computed circle */
    double *sint,*cost;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCylinder" );

//---- DEFINICIÓ COORDENADES TEXTURA
	Activa_Coordenades_Textura();

    fghCircleTable(&sint,&cost,-slices);

/* Cover the base and top */

    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0.0, 0.0, -1.0 );
        glVertex3d(0.0, 0.0,  0.0 );
        for (j=0; j<=slices; j++)
          glVertex3d(cost[j]*radius, sint[j]*radius, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0.0, 0.0, 1.0   );
        glVertex3d(0.0, 0.0, height);
        for (j=slices; j>=0; j--)
          glVertex3d(cost[j]*radius, sint[j]*radius, height);
    glEnd();

/* Do the stacks */
    z0 = 0.0;
    z1 = zStep;

    for (i=1; i<=stacks; i++)
    {   if (i==stacks) z1 = height;
	    glBegin(GL_QUAD_STRIP);
            for (j=0; j<=slices; j++ )
            {   glNormal3d(cost[j],        sint[j],        0.0 );
                glVertex3d(cost[j]*radius, sint[j]*radius, z0  );
                glVertex3d(cost[j]*radius, sint[j]*radius, z1  );
            }
        glEnd();
        z0 = z1; z1 += zStep;
    }

//---- DEFINICIÓ COORDENADES TEXTURA
	Desactiva_Coordenades_Textura();

/* Release sin and cos tables */
    free(sint);
    free(cost);
}


/* ---------- TORUS -----------------------------------------------------*/
/*
 * Draws a solid torus
 */
void glutSolidTorus( GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings )
{
  double  iradius = dInnerRadius, oradius = dOuterRadius, phi, psi, dpsi, dphi;
  double *vertex, *normal;
  int    i, j;
  double spsi, cpsi, sphi, cphi ;

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidTorus" );

//---- DEFINICIÓ COORDENADES TEXTURA
  Activa_Coordenades_Textura();

  if ( nSides < 1 ) nSides = 1;
  if ( nRings < 1 ) nRings = 1;

/* Increment the number of sides and rings to allow for one more point than surface */
  nSides ++ ;
  nRings ++ ;

/* Allocate the vertices array */
  vertex = (double *)calloc( sizeof(double), 3 * nSides * nRings );
  normal = (double *)calloc( sizeof(double), 3 * nSides * nRings );

  glPushMatrix();

  dpsi =  2.0 * pi / (double)(nRings - 1) ;
  dphi = -2.0 * pi / (double)(nSides - 1) ;
  psi  = 0.0;

  for( j=0; j<nRings; j++ )
  { cpsi = cos ( psi ) ;
    spsi = sin ( psi ) ;
    phi = 0.0;

    for( i=0; i<nSides; i++ )
    { int offset = 3 * ( j * nSides + i ) ;
      cphi = cos ( phi ) ;
      sphi = sin ( phi ) ;
      *(vertex + offset + 0) = cpsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 1) = spsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 2) =                    sphi * iradius  ;
      *(normal + offset + 0) = cpsi * cphi ;
      *(normal + offset + 1) = spsi * cphi ;
      *(normal + offset + 2) =        sphi ;
      phi += dphi;
    }
    psi += dpsi;
  }

  glBegin( GL_QUADS );
    for( i=0; i<nSides-1; i++ )
    { for( j=0; j<nRings-1; j++ )
      { int offset = 3 * ( j * nSides + i ) ;
        glNormal3dv( normal + offset );
        glVertex3dv( vertex + offset );
        glNormal3dv( normal + offset + 3 );
        glVertex3dv( vertex + offset + 3 );
        glNormal3dv( normal + offset + 3 * nSides + 3 );
        glVertex3dv( vertex + offset + 3 * nSides + 3 );
        glNormal3dv( normal + offset + 3 * nSides );
        glVertex3dv( vertex + offset + 3 * nSides );
      }
    }
  glEnd();

  free ( vertex ) ;
  free ( normal ) ;
  glPopMatrix();

//---- DEFINICIÓ COORDENADES TEXTURA
  Desactiva_Coordenades_Textura();
}


/* ---------- DODECAHEDRON -----------------------------------------------------*/
/*
 * Draws a solid dodecahedron
 */
void glutSolidDodecahedron( void )
{
//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidDodecahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
	Activa_Coordenades_Textura();

  /* Magic Numbers:  It is possible to create a dodecahedron by attaching two pentagons to each face of
   * of a cube.  The coordinates of the points are:
   *   (+-x,0, z); (+-1, 1, 1); (0, z, x )
   * where x = (-1 + sqrt(5))/2, z = (1 + sqrt(5))/2 or
   *       x = 0.61803398875 and z = 1.61803398875.
   */
  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.0,  0.525731112119,  0.850650808354 ) ; glVertex3d (  0.0,  1.61803398875,  0.61803398875 ) ; glVertex3d ( -1.0,  1.0,  1.0 ) ; glVertex3d ( -0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d (  0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d (  1.0,  1.0,  1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.0,  0.525731112119, -0.850650808354 ) ; glVertex3d (  0.0,  1.61803398875, -0.61803398875 ) ; glVertex3d (  1.0,  1.0, -1.0 ) ; glVertex3d (  0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d ( -0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d ( -1.0,  1.0, -1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.0, -0.525731112119,  0.850650808354 ) ; glVertex3d (  0.0, -1.61803398875,  0.61803398875 ) ; glVertex3d (  1.0, -1.0,  1.0 ) ; glVertex3d (  0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d ( -0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d ( -1.0, -1.0,  1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.0, -0.525731112119, -0.850650808354 ) ; glVertex3d (  0.0, -1.61803398875, -0.61803398875 ) ; glVertex3d ( -1.0, -1.0, -1.0 ) ; glVertex3d ( -0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d (  0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d (  1.0, -1.0, -1.0 ) ;
  glEnd () ;

  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.850650808354,  0.0,  0.525731112119 ) ; glVertex3d (  0.61803398875,  0.0,  1.61803398875 ) ; glVertex3d (  1.0, -1.0,  1.0 ) ; glVertex3d (  1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d (  1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d (  1.0,  1.0,  1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d ( -0.850650808354,  0.0,  0.525731112119 ) ; glVertex3d ( -0.61803398875,  0.0,  1.61803398875 ) ; glVertex3d ( -1.0,  1.0,  1.0 ) ; glVertex3d ( -1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d ( -1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d ( -1.0, -1.0,  1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.850650808354,  0.0, -0.525731112119 ) ; glVertex3d (  0.61803398875,  0.0, -1.61803398875 ) ; glVertex3d (  1.0,  1.0, -1.0 ) ; glVertex3d (  1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d (  1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d (  1.0, -1.0, -1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d ( -0.850650808354,  0.0, -0.525731112119 ) ; glVertex3d ( -0.61803398875,  0.0, -1.61803398875 ) ; glVertex3d ( -1.0, -1.0, -1.0 ) ; glVertex3d ( -1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d ( -1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d ( -1.0,  1.0, -1.0 ) ;
  glEnd () ;

  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.525731112119,  0.850650808354,  0.0 ) ; glVertex3d (  1.61803398875,  0.61803398875,  0.0 ) ; glVertex3d (  1.0,  1.0, -1.0 ) ; glVertex3d ( 0.0,  1.61803398875, -0.61803398875 ) ; glVertex3d ( 0.0,  1.61803398875,  0.61803398875 ) ; glVertex3d (  1.0,  1.0,  1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d (  0.525731112119, -0.850650808354,  0.0 ) ; glVertex3d (  1.61803398875, -0.61803398875,  0.0 ) ; glVertex3d (  1.0, -1.0,  1.0 ) ; glVertex3d ( 0.0, -1.61803398875,  0.61803398875 ) ; glVertex3d ( 0.0, -1.61803398875, -0.61803398875 ) ; glVertex3d (  1.0, -1.0, -1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d ( -0.525731112119,  0.850650808354,  0.0 ) ; glVertex3d ( -1.61803398875,  0.61803398875,  0.0 ) ; glVertex3d ( -1.0,  1.0,  1.0 ) ; glVertex3d ( 0.0,  1.61803398875,  0.61803398875 ) ; glVertex3d ( 0.0,  1.61803398875, -0.61803398875 ) ; glVertex3d ( -1.0,  1.0, -1.0 ) ;
  glEnd () ;
  glBegin ( GL_POLYGON ) ;
    glNormal3d ( -0.525731112119, -0.850650808354,  0.0 ) ; glVertex3d ( -1.61803398875, -0.61803398875,  0.0 ) ; glVertex3d ( -1.0, -1.0, -1.0 ) ; glVertex3d ( 0.0, -1.61803398875, -0.61803398875 ) ; glVertex3d ( 0.0, -1.61803398875,  0.61803398875 ) ; glVertex3d ( -1.0, -1.0,  1.0 ) ;
  glEnd () ;

 //---- DEFINICIÓ COORDENADES TEXTURA
  Desactiva_Coordenades_Textura();
}


/* ---------- OCTAHEDRON -----------------------------------------------------*/

/*
* Draws a solid octahedron
 */
void glutSolidOctahedron( void )
{
//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidOctahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
	Activa_Coordenades_Textura();

#define RADIUS    1.0f
  glBegin( GL_TRIANGLES );
    glNormal3d( 0.577350269189, 0.577350269189, 0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, RADIUS, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS );
    glNormal3d( 0.577350269189, 0.577350269189,-0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS ); glVertex3d( 0.0, RADIUS, 0.0 );
    glNormal3d( 0.577350269189,-0.577350269189, 0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS ); glVertex3d( 0.0,-RADIUS, 0.0 );
    glNormal3d( 0.577350269189,-0.577350269189,-0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0,-RADIUS, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS );
    glNormal3d(-0.577350269189, 0.577350269189, 0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS ); glVertex3d( 0.0, RADIUS, 0.0 );
    glNormal3d(-0.577350269189, 0.577350269189,-0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, RADIUS, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS );
    glNormal3d(-0.577350269189,-0.577350269189, 0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0,-RADIUS, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS );
    glNormal3d(-0.577350269189,-0.577350269189,-0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS ); glVertex3d( 0.0,-RADIUS, 0.0 );
  glEnd();
#undef RADIUS

 //---- DEFINICIÓ COORDENADES TEXTURA
  Desactiva_Coordenades_Textura();
}

/* ---------- TETRAHEDRON -----------------------------------------------------*/
/*
* Draws a solid tetrahedron
 */
void glutSolidTetrahedron( void )
{
//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidTetrahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
  Activa_Coordenades_Textura();

  glBegin( GL_TRIANGLES ) ;
	glNormal3d ( -tet_r[0][0], -tet_r[0][1], -tet_r[0][2] ) ; glVertex3dv ( tet_r[1] ) ; glVertex3dv ( tet_r[3] ) ; glVertex3dv ( tet_r[2] ) ;
	glNormal3d ( -tet_r[1][0], -tet_r[1][1], -tet_r[1][2] ) ; glVertex3dv ( tet_r[0] ) ; glVertex3dv ( tet_r[2] ) ; glVertex3dv ( tet_r[3] ) ;
	glNormal3d ( -tet_r[2][0], -tet_r[2][1], -tet_r[2][2] ) ; glVertex3dv ( tet_r[0] ) ; glVertex3dv ( tet_r[3] ) ; glVertex3dv ( tet_r[1] ) ;
	glNormal3d ( -tet_r[3][0], -tet_r[3][1], -tet_r[3][2] ) ; glVertex3dv ( tet_r[0] ) ; glVertex3dv ( tet_r[1] ) ; glVertex3dv ( tet_r[2] ) ;
  glEnd() ;

//---- DEFINICIÓ COORDENADES TEXTURA
  Desactiva_Coordenades_Textura();
}


/* ---------- ICOSAHEDRON -----------------------------------------------------*/
/*
* Draws a solid Icosahedron
 */
void glutSolidIcosahedron( void )
{
  int i ;
  double normal[3] ;

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidIcosahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
  Activa_Coordenades_Textura();

  glBegin ( GL_TRIANGLES ) ;
    for ( i = 0; i < 20; i++ )
	{ // double normal[3];
      normal[0] = ( icos_r[icos_v[i][1]][1] - icos_r[icos_v[i][0]][1] ) * ( icos_r[icos_v[i][2]][2] - icos_r[icos_v[i][0]][2] ) - ( icos_r[icos_v[i][1]][2] - icos_r[icos_v[i][0]][2] ) * ( icos_r[icos_v[i][2]][1] - icos_r[icos_v[i][0]][1] ) ;
      normal[1] = ( icos_r[icos_v[i][1]][2] - icos_r[icos_v[i][0]][2] ) * ( icos_r[icos_v[i][2]][0] - icos_r[icos_v[i][0]][0] ) - ( icos_r[icos_v[i][1]][0] - icos_r[icos_v[i][0]][0] ) * ( icos_r[icos_v[i][2]][2] - icos_r[icos_v[i][0]][2] ) ;
      normal[2] = ( icos_r[icos_v[i][1]][0] - icos_r[icos_v[i][0]][0] ) * ( icos_r[icos_v[i][2]][1] - icos_r[icos_v[i][0]][1] ) - ( icos_r[icos_v[i][1]][1] - icos_r[icos_v[i][0]][1] ) * ( icos_r[icos_v[i][2]][0] - icos_r[icos_v[i][0]][0] ) ;
      glNormal3dv ( normal ) ;
      glVertex3dv ( icos_r[icos_v[i][0]] ) ;
      glVertex3dv ( icos_r[icos_v[i][1]] ) ;
      glVertex3dv ( icos_r[icos_v[i][2]] ) ;
    }

  glEnd () ;

//---- DEFINICIÓ COORDENADES TEXTURA
  Desactiva_Coordenades_Textura();
}


/* ---------- ROMBIC DODECAHEDRON -----------------------------------------------------*/

/*
* Draws a solid Rhombic Dodecahedron
 */
void glutSolidRhombicDodecahedron( void )
{
  int i ;

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidRhombicDodecahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
  Activa_Coordenades_Textura();

  glBegin ( GL_QUADS ) ;
    for ( i = 0; i < 12; i++ )
    {   glNormal3dv ( rdod_n[i] ) ;
        glVertex3dv ( rdod_r[rdod_v[i][0]] ) ;
        glVertex3dv ( rdod_r[rdod_v[i][1]] ) ;
        glVertex3dv ( rdod_r[rdod_v[i][2]] ) ;
        glVertex3dv ( rdod_r[rdod_v[i][3]] ) ;
    }
  glEnd () ;

//---- DEFINICIÓ COORDENADES TEXTURA
  Desactiva_Coordenades_Textura();
}


/* ---------- SIERPPINSKI SPONGE ------------------------------------------------*/
/*
* Draws a solid Sierpinski Sponge
*/
void glutSolidSierpinskiSponge ( int num_levels, GLdouble offset[3], GLdouble scale )
{
  int i, j ;

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidSierpinskiSponge" );

//---- DEFINICIÓ COORDENADES TEXTURA
  Activa_Coordenades_Textura();

  if ( num_levels == 0 )
  { glBegin ( GL_TRIANGLES ) ;
    for ( i = 0 ; i < NUM_TETR_FACES ; i++ )
    {
      glNormal3d ( -tet_r[i][0], -tet_r[i][1], -tet_r[i][2] ) ;
      for ( j = 0; j < 3; j++ )
      {
        double x = offset[0] + scale * tet_r[tet_i[i][j]][0] ;
        double y = offset[1] + scale * tet_r[tet_i[i][j]][1] ;
        double z = offset[2] + scale * tet_r[tet_i[i][j]][2] ;
        glVertex3d ( x, y, z ) ;
      }
    }
    glEnd () ;
  }
  else if ( num_levels > 0 )
  { GLdouble local_offset[3] ;  /* Use a local variable to avoid buildup of roundoff errors */
    num_levels -- ;
    scale /= 2.0 ;
    for ( i = 0 ; i < NUM_TETR_FACES ; i++ )
    { local_offset[0] = offset[0] + scale * tet_r[i][0] ;
      local_offset[1] = offset[1] + scale * tet_r[i][1] ;
      local_offset[2] = offset[2] + scale * tet_r[i][2] ;
      glutSolidSierpinskiSponge ( num_levels, local_offset, scale ) ;
    }
  }

//---- DEFINICIÓ COORDENADES TEXTURA
  Desactiva_Coordenades_Textura();
}

/* ---------- TEAPOT -----------------------------------------------------*/

static void fghTeapot(GLint grid, GLdouble scale, GLenum type)
{
	int i, numV = sizeof(strip_vertices) / 4, numI = sizeof(strip_normals) / 4;

	glBegin(GL_TRIANGLE_STRIP);
	  for (i = 0; i < numV - 1; i++)
	  { int vidx = strip_vertices[i],
		nidx = strip_normals[i];

		if (vidx != -1)
		{	glNormal3fv(normals[nidx]);
			glVertex3fv(vertices[vidx]);
		}
		else {	glEnd();
				glBegin(GL_TRIANGLE_STRIP);
			}
	  }
	glEnd();
}


/* -- TEAPOT INTERFACE FUNCTIONS -------------------------------------------------- */

/*
* Renders a beautiful filled teapot...
*/
void glutSolidTeapot(GLdouble size)
{
//	FREEGLUT_EXIT_IF_NOT_INITIALISED("glutSolidTeapot");

//---- DEFINICIÓ COORDENADES TEXTURA
	Activa_Coordenades_Textura();

/* We will use the general teapot rendering code */
	fghTeapot(10, size, GL_FILL);

//---- DEFINICIÓ COORDENADES TEXTURA
	Desactiva_Coordenades_Textura();
}


// ------------------- PRIMITIVES GLU (CYLINDER, DISC, SPHERE) -------------------------
/* Make it not a power of two to avoid cache thrashing on the chip */
#define CACHE_SIZE	240
#define PI	      3.14159265358979323846

// --- CILINDRE
void gluCilindre(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks)
{
	GLint i, j;
	GLfloat sinCache[CACHE_SIZE];
	GLfloat cosCache[CACHE_SIZE];
	GLfloat sinCache2[CACHE_SIZE];
	GLfloat cosCache2[CACHE_SIZE];
	GLfloat angle;
	GLfloat zLow, zHigh;
	GLfloat length;
	GLfloat deltaRadius;
	GLfloat zNormal;
	GLfloat xyNormalRatio;
	GLfloat radiusLow, radiusHigh;
	int needCache2, needCache3;

	if (slices >= CACHE_SIZE) slices = CACHE_SIZE - 1;

	if (slices < 2 || stacks < 1 || baseRadius < 0.0 || topRadius < 0.0 ||
		height < 0.0)	return;

/* Compute length (needed for normal calculations) */
	deltaRadius = baseRadius - topRadius;
	length = sqrt(deltaRadius*deltaRadius + height*height);
	if (length == 0.0) return;

/* Cache2 is the various normals at the vertices themselves */
	needCache2 = needCache3 = 0;
	needCache2 = 1;
	zNormal = deltaRadius / length;
	xyNormalRatio = height / length;

	for (i = 0; i < slices; i++) {
		angle = 2 * PI * i / slices;
		sinCache2[i] = xyNormalRatio * sin(angle);
		cosCache2[i] = xyNormalRatio * cos(angle);
		sinCache[i] = sin(angle);
		cosCache[i] = cos(angle);
	}

	sinCache[slices] = sinCache[0];
	cosCache[slices] = cosCache[0];
	sinCache2[slices] = sinCache2[0];
	cosCache2[slices] = cosCache2[0];
	for (j = 0; j < stacks; j++) {
		zLow = j * height / stacks;
		zHigh = (j + 1) * height / stacks;
		radiusLow = baseRadius - deltaRadius * ((float)j / stacks);
		radiusHigh = baseRadius - deltaRadius * ((float)(j + 1) / stacks);

		glBegin(GL_QUAD_STRIP);
		for (i = 0; i <= slices; i++) {
			glNormal3f(sinCache2[i], cosCache2[i], zNormal);
			glTexCoord2f(1 - (float)i / slices, (float)j / stacks);
			glVertex3f(radiusLow * sinCache[i], radiusLow * cosCache[i], zLow);
			glTexCoord2f(1 - (float)i / slices, (float)(j + 1) / stacks);
			glVertex3f(radiusHigh * sinCache[i], radiusHigh * cosCache[i], zHigh);
		}
		glEnd();
	}
}

// --- DISC
void gluDisc(GLdouble innerRadius, GLdouble outerRadius,
	GLint slices, GLint loops)
{
	gluParcialDisc(innerRadius, outerRadius, slices, loops, 0.0, 360.0);
}


// --- PARCIAL DISC
void gluParcialDisc(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops, GLdouble startAngle, GLdouble sweepAngle)
{
	GLint i, j;
	GLfloat sinCache[CACHE_SIZE];
	GLfloat cosCache[CACHE_SIZE];
	GLfloat angle;
	GLfloat deltaRadius;
	GLfloat radiusLow, radiusHigh;
	GLfloat texLow = 0.0, texHigh = 0.0;
	GLfloat angleOffset;
	GLint slices2;
	GLint finish;

	if (slices >= CACHE_SIZE) slices = CACHE_SIZE - 1;
	if (slices < 2 || loops < 1 || outerRadius <= 0.0 || innerRadius < 0.0 ||
		innerRadius > outerRadius) {
		return;
	}
	if (sweepAngle < -360.0) sweepAngle = 360.0;
	if (sweepAngle > 360.0) sweepAngle = 360.0;
	if (sweepAngle < 0) {	startAngle += sweepAngle;
							sweepAngle = -sweepAngle;
						}

	if (sweepAngle == 360.0)	slices2 = slices;
		else slices2 = slices + 1;

/* Compute length (needed for normal calculations) */
	deltaRadius = outerRadius - innerRadius;

/* Cache is the vertex locations cache */
	angleOffset = startAngle / 180.0 * PI;
	for (i = 0; i <= slices; i++) {
		angle = angleOffset + ((PI * sweepAngle) / 180.0) * i / slices;
		sinCache[i] = sin(angle);
		cosCache[i] = cos(angle);
		}

	if (sweepAngle == 360.0) {
		sinCache[slices] = sinCache[0];
		cosCache[slices] = cosCache[0];
		}

	glNormal3f(0.0, 0.0, 1.0);


	if (innerRadius == 0.0) {
		finish = loops - 1;

/* Triangle strip for inner polygons */
		glBegin(GL_TRIANGLE_FAN);
		  glTexCoord2f(0.5, 0.5);
		  glVertex3f(0.0, 0.0, 0.0);
		  radiusLow = outerRadius - deltaRadius * ((float)(loops - 1) / loops);
		  texLow = radiusLow / outerRadius / 2;
		  for (i = slices; i >= 0; i--) {
			  glTexCoord2f(texLow * sinCache[i] + 0.5, texLow * cosCache[i] + 0.5);
			  glVertex3f(radiusLow * sinCache[i], radiusLow * cosCache[i], 0.0);
			  }
		glEnd();
	}
	else finish = loops;
	for (j = 0; j < finish; j++) {
		radiusLow = outerRadius - deltaRadius * ((float)j / loops);
		radiusHigh = outerRadius - deltaRadius * ((float)(j + 1) / loops);
		texLow = radiusLow / outerRadius / 2;
		texHigh = radiusHigh / outerRadius / 2;
		glBegin(GL_QUAD_STRIP);
		for (i = 0; i <= slices; i++) {
			glTexCoord2f(texLow * sinCache[i] + 0.5, texLow * cosCache[i] + 0.5);
			glVertex3f(radiusLow * sinCache[i], radiusLow * cosCache[i], 0.0);
			glTexCoord2f(texHigh * sinCache[i] + 0.5, texHigh * cosCache[i] + 0.5);
			glVertex3f(radiusHigh * sinCache[i], radiusHigh * cosCache[i], 0.0);
		}
		glEnd();
	}
}

// --- ESFERA : Texturització compatible amb superficie planetes
void gluEsfera(GLdouble radius, GLint slices, GLint stacks)
{
	GLint i, j;
	GLfloat sinCache1a[CACHE_SIZE];
	GLfloat cosCache1a[CACHE_SIZE];
	GLfloat sinCache2a[CACHE_SIZE];
	GLfloat cosCache2a[CACHE_SIZE];
	GLfloat sinCache1b[CACHE_SIZE];
	GLfloat cosCache1b[CACHE_SIZE];
	GLfloat sinCache2b[CACHE_SIZE];
	GLfloat cosCache2b[CACHE_SIZE];
	GLfloat angle;
	GLfloat zLow, zHigh;
	GLfloat sintemp1 = 0.0, sintemp2 = 0.0, sintemp3 = 0.0, sintemp4 = 0.0;
	GLfloat costemp1 = 0.0, costemp2 = 0.0, costemp3 = 0.0, costemp4 = 0.0;
	GLboolean needCache2;
	GLint start, finish;

	if (slices >= CACHE_SIZE) slices = CACHE_SIZE - 1;
	if (stacks >= CACHE_SIZE) stacks = CACHE_SIZE - 1;
	if (slices < 2 || stacks < 1 || radius < 0.0) return;

/* Cache2 is the various normals at the vertices themselves */
	needCache2 = GL_TRUE;

	for (i = 0; i < slices; i++) {
		angle = 2 * PI * i / slices;
		sinCache1a[i] = sin(angle);
		cosCache1a[i] = cos(angle);
		sinCache2a[i] = sinCache1a[i];
		cosCache2a[i] = cosCache1a[i];
	}

	for (j = 0; j <= stacks; j++) {
		angle = PI * j / stacks;
		sinCache2b[j] = sin(angle);
		cosCache2b[j] = cos(angle);
		sinCache1b[j] = radius * sin(angle);
		cosCache1b[j] = radius * cos(angle);
	}

/* Make sure it comes to a point */
	sinCache1b[0] = 0;
	sinCache1b[stacks] = 0;

	sinCache1a[slices] = sinCache1a[0];
	cosCache1a[slices] = cosCache1a[0];

	sinCache2a[slices] = sinCache2a[0];
	cosCache2a[slices] = cosCache2a[0];

//	** When texturing we need to respecify the
//	** texture coordinates of the apex for every adjacent vertex (because
//	** it isn't a constant for that point)
	start = 0;
	finish = stacks;

	for (j = start; j < finish; j++) {
		zLow = cosCache1b[j];
		zHigh = cosCache1b[j + 1];
		sintemp1 = sinCache1b[j];
		sintemp2 = sinCache1b[j + 1];
		sintemp3 = sinCache2b[j + 1];
		costemp3 = cosCache2b[j + 1];
		sintemp4 = sinCache2b[j];
		costemp4 = cosCache2b[j];

		glBegin(GL_QUAD_STRIP);
		for (i = 0; i <= slices; i++) {
			glNormal3f(sinCache2a[i] * sintemp3, cosCache2a[i] * sintemp3, costemp3);
			glTexCoord2f(1 - (float)i / slices,	1 - (float)(j + 1) / stacks);
			glVertex3f(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i], zHigh);

			glNormal3f(sinCache2a[i] * sintemp4, cosCache2a[i] * sintemp4, costemp4);
			glTexCoord2f(1 - (float)i / slices,	1 - (float)j / stacks);
			glVertex3f(sintemp1 * sinCache1a[i], sintemp1 * cosCache1a[i], zLow);
		}
		glEnd();
	}
}

// ------------------- FI PRIMITIVES GLU (CYLINDER, DISC, SPHERE) -------------------------

// --- ACTIVACIÓ DEFINICIÓ COORDENADES TEXTURA PER A OBJECTES GLUT ------------------------ 
void Activa_Coordenades_Textura()
{
//---- DEFINICIÓ COORDENADES TEXTURA
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

// Generació coordenades textura.
	GLfloat sPlane[4] = { -1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat tPlane[4] = { -1.0f, 0.0f, 1.0f, 1.0f };

	glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
//--- FI DEFINICIÓ COORDENADES TEXTURA
}

void Desactiva_Coordenades_Textura()
{
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}
/*** END OF FILE ***/
