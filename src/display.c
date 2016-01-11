#include "display.h"
#include "global.h"
#include "ship.mdl"
#include "game.h"

static void cameraTransform(){
	const float distance=10;
	float angle=ship.rot*degtorad;
	float x0=-ship.x-(float)sin(angle)*distance;
	float y0=ship.y+3;
	float z0=-ship.z-(float)cos(angle)*distance;
	float x1=-ship.x+(float)sin(angle)*100;
	float y1=ship.y;
	float z1=-ship.z+(float)cos(angle)*100;
	gluLookAt(x0,y0,z0,x1,y1,z1,0,1,0);
}

static void drawSkybox(float width,float height,float length){
	float x=-500,y=-height/2,z=-500;
	float vertex[8][3]={
		{x,y,z},{x,y+height,z},{x+width,y+height,z},{x+width,y,z},{x,y,z+length},
		{x+width,y,z+length},{x,y+height,z+length},{x+width,y+height,z+length}
	};
	int texcoord[4][2]={{1,1},{1,0},{0,0},{0,1}};
	int face[6][4]={{3,2,1,0},{4,6,7,5},{0,4,5,3},{6,1,2,7},{0,1,6,4},{5,7,2,3}};

	int i;
	for(i=0;i<6;i++){
		glBindTexture(GL_TEXTURE_2D, texture[i+2]);
		glBegin(GL_QUADS);
		int j;
		for(j=0;j<4;j++){
			int vi=face[i][j];
			glTexCoord2f(texcoord[j][0],texcoord[j][1]);
			glVertex3f(vertex[vi][0],vertex[vi][1],vertex[vi][2]);
		}
		glEnd();
	}
}

static void drawMap(MAP *map){
	int x,z,ida,idb,idc,idd;
	float ua,ub,va,vb;
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	for(z=0; z<map->height-2; z++){
		for(x=0; x<map->width-2; x++){
			float ua = (float)  x    / (map->width  - 1);
			float ub  = (float) (x+1) / (map->width  - 1);
			float va  = (float)  z    / (map->height - 1);
			float vb  = (float) (z+1) / (map->height - 1);
			int ida = ( z    * map->width) +  x   ;
			int idb = ( z    * map->width) + (x+1);
			int idc = ((z+1) * map->width) + (x+1);
			int idd = ((z+1) * map->width) +  x   ;
			glBegin(GL_QUADS);
			glTexCoord2f(ua, va);
			glVertex3f  (XSCALE*x, map->y[ida], ZSCALE*z);
			glTexCoord2f(ub, va);	
			glVertex3f  (XSCALE*(x+1), map->y[idb], ZSCALE*z);
			glTexCoord2f(ub, vb);
			glVertex3f  (XSCALE*(x+1), map->y[idc], ZSCALE*(z+1));
			glTexCoord2f(ua, vb);
			glVertex3f  (XSCALE*x, map->y[idd], ZSCALE*(z+1));
			glEnd();
		}
	}
}

static void drawShip(){
	glPushMatrix();
	glTranslatef(-ship.x,ship.y,-ship.z);
	glRotatef(ship.rot+rotplus,0,1,0);
	glScalef(0.5,0.5,0.5);
	
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_TRIANGLES);
	int i;
	for(i=0;i<sizeof(face_indicies)/sizeof(face_indicies[0]);i++){
		int j;
		for(j=0;j<3;j++){
			int vi=face_indicies[i][j];
			int ti=face_indicies[i][j+3];
			float x=vertices[vi][0];
			float z=vertices[vi][2];
			glTexCoord2f(textures[ti][0],textures[ti][1]);
			glVertex3f(vertices[vi][0],vertices[vi][1],vertices[vi][2]);
		}
	}
	glEnd();
	glPopMatrix();
}

static void drawScore(){
	int width=glutGet(GLUT_WINDOW_WIDTH);
	int height=glutGet(GLUT_WINDOW_HEIGHT);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	char str[30];
	sprintf(str,"SCORE: %.0f",score);

	glBindTexture(GL_TEXTURE_2D,0);
	glColor3f(0,0,0);
	glRectf(0,0,strlen(str)*12+12,24);
	glColor3f(0,1,0);
	glRasterPos2f(0,0);
	char* ptr;
	for(ptr=str;*ptr;ptr++)glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*ptr);
	glColor3f(1,1,1);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	cameraTransform(ship,10);
	drawSkybox(5000,3000,5000);
	drawMap(&map);
	drawShip();
	drawScore();
	glutSwapBuffers();
}
