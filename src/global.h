#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#if defined(__APPLE__)
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
#endif

//#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"

#define TITLE		"Race Game"
#define VERSION		"0.5"
#define NUM_TEXTURES	14				/* Number of textures to load */
#define radtodeg	57.295779513			/* 180 / pi */
#define degtorad	0.0174532925			/* pi / 180 */
#define MAP_WIDTH	64
#define MAP_HEIGHT	64
#define XSCALE		50
#define YSCALE		200
#define ZSCALE		50
#define YSHIFT		20
#define COURSES		3

typedef struct{
  GLfloat	x;
  GLfloat	y;
  GLfloat	z;
} VERTEX;

typedef struct{
  GLfloat 	x;
  GLfloat	y;
  GLfloat	z;
} VECTOR;

typedef struct{
  GLfloat	a;
  GLfloat	b;
  GLfloat	c;
  GLfloat	d;
} PLANE;

typedef struct{
  int	 width;
  int	 height;
  float *y;
  float *u;
  float *v;
} MAP;

typedef struct{
  GLfloat y,u,v;
} MODEL;

typedef struct{
  GLfloat 	x,y,z;					/* position co-ordinates  */
  GLfloat 	vel;					/* x and z velocity	  */
  GLfloat 	dir;					/* motion direction	  */
  GLfloat 	maxvel;					/* maximum velocity	  */
  GLfloat	accel;					/* ship acceleration	  */  
  GLfloat 	rot;					/* rotation (degrees)	  */
  GLfloat 	rotvel;					/* rotation velocity	  */
  GLfloat 	rotdir;					/* rotation direction	  */ 
  GLfloat 	rotmax;					/* maximum rotation rate  */
  GLfloat 	rotacc;					/* rotation acceleration  */
} SHIP;

GLuint		texture[NUM_TEXTURES];			/* Texture Memory */

#endif
