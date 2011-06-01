#include <windows.h>
#include <gl/Glee.h>
//#define FREEGLUT_STATIC
#include <gl/glut.h>
#include <cassert>
#include <string>
#include "resource.h"
#include <cmath>
#include <ctime>
#include "helpers.hpp"
#include "kerm.h"

// Define an ID for the "Quit" menu item.
static const int QUIT_VALUE( 99 );

FILE *err;

static void display()
{
    glClear( GL_COLOR_BUFFER_BIT );

    // Modeling transform, move geometry 4 units back in Z.
    glLoadIdentity();
    glTranslatef( 0.f, 0.f, -4.f );

	glLoadIdentity();
    glTranslatef( -2.42f, -1.85f, -4.1f );

	KermGame::GetInstance()->Draw();

	glutSwapBuffers();
	GL_ERR_CHECK
}

//
// GLUT resize callback, called when window size changes.
static void reshape( int w, int h )
{
    // Update the viewport to draw to the full window
    glViewport( 0, 0, w, h );

    // Update the projection matrix / aspect ratio
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 50., (double)w/(double)h, 1., 10. );

    // Leave us in model-view mode for our display routine
    glMatrixMode( GL_MODELVIEW );

	GL_ERR_CHECK
}

//
// GLUT menu callback, called when user selects a menu item.
static void mainMenuCB( int value )
{
    if (value == QUIT_VALUE)
        exit( 0 );
}
static void timer_exp(int value)
{
	int updateInterval=KermGame::GetInstance()->updateInterval;
	KermGame::GetInstance()->Update(updateInterval);
    glutPostRedisplay();	
	glutTimerFunc(updateInterval,timer_exp,updateInterval);
}

static void SpecialKey(int key, int x, int y)
{
	KermGame::GetInstance()->SetLastPressedKey(key);
}

static void init()
{
   // Dither is on by default but not needed, disable it.
    glDisable( GL_DITHER );

    assert( glGetError() == GL_NO_ERROR );

    // Register our display and resize callbacks with GLUT.
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );

    // Create a right-mouse menu to allow users to exit.
    int mainMenu = glutCreateMenu( mainMenuCB );
    glutAddMenuEntry( "Quit", QUIT_VALUE );
    glutAttachMenu( GLUT_RIGHT_BUTTON );
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nShowCmd)
{
	int argc;
	LPWSTR *argv= CommandLineToArgvW(GetCommandLine(),&argc);

	glutInit(&argc,(char **)(argv));

	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize( 800, 600 );
	glutCreateWindow( "" );

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	int updateInterval=KermGame::GetInstance()->updateInterval;

	glutTimerFunc(updateInterval,timer_exp, updateInterval);
	glutSpecialFunc(SpecialKey);

    init();

	char title[64];
	sprintf_s(title,64,"OpenGL Version %s",glGetString( GL_VERSION ));
	glutSetWindowTitle(title);
    // Loop for events.
    glutMainLoop();
    return 0;
}