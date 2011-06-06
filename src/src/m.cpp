#include <Windows.h>
#include <gl/Glee.h>
#include <gl/freeglut.h>
#include "resource.h"
#include "MaarGame.h"
#include "SDL.h"

using namespace MAAR;

// Define an ID for the "Quit" menu item.
static const int QUIT_VALUE( 99 );
FILE *err;
static void display()
{
    glClear( GL_COLOR_BUFFER_BIT );

    // Modeling transform, move geometry 4 units back in Z.
	glLoadIdentity();

	MaarGame::GetInstance()->Draw();

	glutSwapBuffers();
	GL_ERR_CHECK
}

//
// GLUT resize callback, called when window size changes.
static void reshape( int w, int h )
{
    // Update the viewport to draw to the full window
    glViewport( 0, 0, w, h );
	MaarGame::GetInstance()->SetSize(w,h);
    // Update the projection matrix / aspect ratio
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	glOrtho(0,MaarGame::windowDimensions.x,0,MaarGame::windowDimensions.y,-1,1);

    // Leave us in model-view mode for our display routine
    glMatrixMode( GL_MODELVIEW );

	GL_ERR_CHECK
}

//
// GLUT menu callback, called when user selects a menu item.
static void mainMenuCB( int value )
{
    if (value == QUIT_VALUE)
        glutLeaveMainLoop();
}
static void timer_exp(int value)
{
	int updateInterval=MaarGame::GetInstance()->updateInterval;
	MaarGame::GetInstance()->Update(updateInterval);
    glutPostRedisplay();	
	glutTimerFunc(updateInterval,timer_exp,updateInterval);
}

static void SpecialKey(int key, int x, int y)
{
	MaarGame::GetInstance()->SetLastPressedKey(key);
}

int WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
}