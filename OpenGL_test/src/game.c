#include "global.h"
#include "game.h"


#include <windows.h>

MAP map;
SHIP ship;
float rot_plus;
int game_start;
int game_end;
float score;
int previous_time;


void initGame(){
	ship.rotation_velocity  =0;
	ship.vel                =0;
	ship.direction          =0;
	ship.rotation_direction =0;
	ship.rotation           =180;
	ship.x                  =-XSCALE*10;
	ship.z                  = -ZSCALE * 10;;
	game_start              =0;
	game_end                =0;
	score                   =0;
}
void startGame(){
	game_start    = 1;
	previous_time = GetTickCount();
}


/* Get the height at x,z from the Loaded Map */
float getheight(float x, float z) {
	x /= XSCALE;
	z /= ZSCALE;
	int xf = floor(x);
	int zf = floor(z);
	float ay = map.y[((zf + 0)*map.width) + xf + 0];
	float by = map.y[((zf + 0)*map.width) + xf + 1];
	float cy = map.y[((zf + 1)*map.width) + xf + 1];
	float dy = map.y[((zf + 1)*map.width) + xf + 0];
	float k1 = x - xf;
	float k2 = z - zf;
	float y;
	y = k1 > k2
		? ay*(1 - k1) + by*(k1 - k2) + cy*k2	// in triangle abc
		: ay*(2 - k1 - k2) + by*(k1 - 1) + dy*k2;	// in triangle acd
	return y;
}
 
static float get_fps(){
	int current_time = GetTickCount();
	float fps = 1000.0/(current_time - previous_time);
	previous_time = current_time;
	return fps;
}
void nextFrame(void){
	float adjust  = (100.0/get_fps());			/* Framerate Correction */
  
	/* Player Constants */
	ship.max_vel=5;
	ship.acceleration=0.01*adjust;
	ship.max_rotation_velocity=1;
	ship.rotation_acceleration=0.025*adjust;
	ship.rotation-=ship.rotation>360?-360:0;
	ship.rotation+=ship.rotation<0?360:0;

	if(ship.rotation_direction==1){
		rot_plus+=1.0*adjust;
		if(rot_plus>30) rot_plus=30;
	}else if(ship.rotation_direction==-1){
		rot_plus-=1.0*adjust;
		if(rot_plus<-30) rot_plus=-30;
	}else{
		if(rot_plus>0){
			rot_plus-=1.0*adjust;
			if(rot_plus<0) rot_plus=0;
		}else if(rot_plus<0){
			rot_plus+=1.0*adjust;
			if(rot_plus>0) rot_plus=0;
		}
	}

	if(game_end)return;

	/* Player Movement */
	ship.x+=ship.vel*sin(ship.rotation*degtorad)*adjust;
	ship.y=getheight(-ship.x,-ship.z)+YSHIFT;
	if(ship.y>YSHIFT+50){
		game_end=1;
		return;
	}
	ship.z+=ship.vel*cos(ship.rotation*degtorad)*adjust;
	ship.rotation+=ship.rotation_velocity*adjust;


	/* Velocity Calculations */
	if(ship.direction < 0){
		ship.vel-=ship.acceleration;
		ship.vel =ship.vel<-ship.max_vel?-ship.max_vel:ship.vel;
	}else{
		ship.vel+=3*ship.acceleration;
		ship.vel =ship.vel>0?0:ship.vel;
	}
  
	if(ship.rotation_direction>0){
		ship.rotation_velocity+=ship.rotation_acceleration;
		if(ship.rotation_velocity>ship.max_rotation_velocity)
			ship.rotation_velocity=ship.max_rotation_velocity;
	}else if(ship.rotation_direction<0){
		ship.rotation_velocity-=ship.rotation_acceleration;
		if(ship.rotation_velocity<-ship.max_rotation_velocity)
			ship.rotation_velocity=-ship.max_rotation_velocity;
	}else{
		if(ship.rotation_velocity > 0){
			ship.rotation_velocity -= ship.rotation_acceleration;
			if(ship.rotation_velocity<0)
				ship.rotation_velocity=0;
		}else if(ship.rotation_velocity < 0){
			ship.rotation_velocity += ship.rotation_acceleration;
			if(ship.rotation_velocity>0)
				ship.rotation_velocity=0;
		}
	}

	if(game_start)score+=ship.direction?1*adjust:-2*adjust;
}
