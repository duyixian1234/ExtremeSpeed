#ifndef _GAME_H_
#define _GAME_H_

#include "global.h"

void initGame(void);
void nextFrame(void);
void startGame(void);
extern SHIP ship;
extern MAP map;
extern float rot_plus;
extern int game_start;
extern int game_end;
extern float score;

#endif
