#include "global.h"
#include "game.h"
#include "messages.h"
#include "resourse.h"
#include "display.h"

void redrawFunc(void){
	nextFrame();
	display();
}

void reshapeFunc(int width,int height){
	height=height?height:1;
	float ratio=(float)width/height;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,ratio,0.1,10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idleFunc(void){
	glutPostRedisplay();
}

void mouseFunc(int button,int state,int x,int y){
	switch(state){
	case GLUT_DOWN:
		switch(button){
		case GLUT_LEFT_BUTTON:
			ship.rotation_direction=1;
			break;
		case GLUT_RIGHT_BUTTON:
			ship.rotation_direction=-1;
			break;
		}
		break;
	case GLUT_UP:
		switch(button){
		case GLUT_LEFT_BUTTON:
			if(ship.rotation_direction==1)ship.rotation_direction=0;
			break;
		case GLUT_RIGHT_BUTTON:
			if(ship.rotation_direction==-1)ship.rotation_direction=0;
			break;
		}
		break;
	}
}

void keyboardFunc(unsigned char key,int x,int y){
	switch(key){
		case 27:
			exit(0);
			break;
		case 'w':
			ship.direction=-1;
			startGame();
			break;
		case 's':
			ship.direction=0;
			startGame();
			break;
		case ' ':
			if(game_end){
				initGame();
			}
	}
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(800,600);
	glutCreateWindow("Final");
	glutDisplayFunc(redrawFunc);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(keyboardFunc);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glEnable(GL_DEPTH_TEST);

	loadResourse();
	initGame();
	glutMainLoop();
	return 0;
}
