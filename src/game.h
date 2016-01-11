#ifndef _GAME_H_
#define _GAME_H_

#include "global.h"

void initGame();
void nextFrame();
extern SHIP ship;
extern MAP map;
extern float rotplus;
extern int game_start;
extern int game_end;
extern float score;

#endif
