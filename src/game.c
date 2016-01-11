#include "global.h"
#include "game.h"
#include "messages.h"
#include <stdio.h>
#include "vector.h"
#include "timing.h"

#include "ship.mdl"

MAP map;
SHIP ship;
float rotplus;
int game_start;
int game_end;
float score;

void initGame(){
	ship.rotvel=0;
	ship.vel=0;
	ship.dir=0;
	ship.rotdir=0;
	ship.rot=180;
	ship.x=-600;
	ship.z=-1000;
	game_start=0;
	game_end=0;
	score=0;
}

/* Get the Equation of the plane at x,z from the Loaded Map */
static PLANE getplane(float x, float z){
  PLANE pi;
  int xf,zf,ida,idb,idc;
  VERTEX a,b,c;
  VECTOR ab,bc,normal;

  xf  = floor(x / XSCALE);
  zf  = floor(z / ZSCALE);

  ida = ((zf)   * map.width) + (xf);
  idb = ((zf)   * map.width) + (xf+1);
  idc = ((zf+1) * map.width) + (xf+1);

  a.x = xf;			b.x = xf + 1;
  a.y = map.y[ida];	b.y = map.y[idb];
  a.z = zf;			b.z = zf;

  c.x = xf + 1;
  c.y = map.y[idc];
  c.z = zf + 1;

  ab     = posvector(a,b);
  bc     = posvector(b,c);
  normal = crossproduct(ab,bc);
  pi     = makeplane(a,normal);

  return pi;
}

/* Get the height at x,z from the Loaded Map */
float getheight(float x, float z){
  PLANE alpha;
  float currentheight,xloc,zloc;

  xloc  = x / XSCALE;
  zloc  = z / ZSCALE;
  alpha = getplane(x,z);

  currentheight = planeheight(alpha,xloc,zloc);
  
  return currentheight+5;
}

void nextFrame(void){
	timeframe();
	//float adjust=2;
	float adjust  = (100.0/get_fps());			/* Framerate Correction */
  
	/* Player Constants */
	ship.maxvel=5;
	ship.accel=0.01*adjust;
	ship.rotmax=1;
	ship.rotacc=0.025*adjust;
	ship.rot-=ship.rot>360?-360:0;
	ship.rot+=ship.rot<0?360:0;
	if(ship.rotdir==1){
		if(rotplus<=30) rotplus+=1*adjust;
	}else if(ship.rotdir==-1){
		if(rotplus >= -30) rotplus-=1* adjust;
	}else{
		if(rotplus>0)
			rotplus-=1*adjust;
		else if(rotplus<0)
			rotplus+=1*adjust;
	}

	if(game_end)return;

	/* Player Movement */
	ship.x   += ship.vel * sin(ship.rot*degtorad) 	* adjust;
	ship.y    = getheight(-ship.x, -ship.z) + YSHIFT;
	if(ship.y>YSHIFT+50){
		game_end=1;
		return;
	}	
	ship.z   += ship.vel * cos(ship.rot*degtorad) 	* adjust;
	ship.rot += ship.rotvel * adjust;


	/* Velocity Calculations */
	if(ship.dir < 0){
		ship.vel-=ship.accel;
		ship.vel=ship.vel<-ship.maxvel?-ship.maxvel:ship.vel;
	}else{
		ship.vel+=3*ship.accel;
		ship.vel=ship.vel>0?0:ship.vel;
	}
  
	/* Rotational Velocity Calculations */
	if(ship.rotdir > 0){				/* Right Rotation */
		if(ship.rotvel <= ship.rotmax)
			ship.rotvel += ship.rotacc * ship.rotdir;	/* Accelerate to Max Rotation */
	}else if(ship.rotdir < 0){				/* Left Rotation */
		if(ship.rotvel >= -ship.rotmax)
			ship.rotvel += ship.rotacc * ship.rotdir;	/* Accelerate to Max Rotation */
	}else{
		if(ship.rotvel > 0)
			ship.rotvel -= ship.rotacc;			/* Left Deccel */
		else if (ship.rotvel < 0)
			ship.rotvel += ship.rotacc;			/* Right Deccel */
		else
			ship.rotvel = 0;				/* Stop Rotating*/
	}

	if(game_start)score+=ship.dir?1*adjust:-2*adjust;
}
