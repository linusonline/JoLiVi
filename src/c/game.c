#include <stdlib.h>
#include "importgl.h"
#include "helpers.h"
#include "game.h"

static GLOBJECT* the_square = NULL;

static GLOBJECT* newSquare(float x, float y, float width, float height)
{
	GLOBJECT* square;
	square = (GLOBJECT*)malloc(sizeof(GLOBJECT));
	square->count = 6;
	square->vertexComponents = 2;
    square->vertexArray = (GLfixed*)malloc(12 * sizeof(GLfixed));
    square->colorArray = (GLubyte*)malloc(24 * sizeof(GLubyte));
	square->vertexArray[0] = FIXED(x);
	square->vertexArray[1] = FIXED(y);

	square->vertexArray[2] = FIXED(x+width);
	square->vertexArray[3] = FIXED(y);

	square->vertexArray[4] = FIXED(x+width);
	square->vertexArray[5] = FIXED(y+height);

	square->vertexArray[6] = FIXED(x+width);
	square->vertexArray[7] = FIXED(y+height);

	square->vertexArray[8] = FIXED(x);
	square->vertexArray[9] = FIXED(y+height);

	square->vertexArray[10] = FIXED(x);
	square->vertexArray[11] = FIXED(y);

	{
		square->colorArray[0] = 0xFF;
		square->colorArray[1] = 0x00;
		square->colorArray[2] = 0x00;
		square->colorArray[3] = 0xFF;

		square->colorArray[4] = 0x00;
		square->colorArray[5] = 0xFF;
		square->colorArray[6] = 0x00;
		square->colorArray[7] = 0xFF;

		square->colorArray[8] = 0x00;
		square->colorArray[9] = 0x00;
		square->colorArray[10] = 0xFF;
		square->colorArray[11] = 0xFF;

		square->colorArray[12] = 0x00;
		square->colorArray[13] = 0x00;
		square->colorArray[14] = 0xFF;
		square->colorArray[15] = 0xFF;

		square->colorArray[16] = 0xFF;
		square->colorArray[17] = 0x00;
		square->colorArray[18] = 0xFF;
		square->colorArray[19] = 0xFF;

		square->colorArray[20] = 0xFF;
		square->colorArray[21] = 0x00;
		square->colorArray[22] = 0x00;
		square->colorArray[23] = 0xFF;
	}
	square->normalArray = NULL;
	return square;
}

void appInit()
{
    importGLInit();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
	the_square = newSquare(0, 0, 100, 100);
	glClearColorx(FIXED(1.0f), FIXED(0.0f), FIXED(0.0f), FIXED(1.0f));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void appDeinit()
{
	freeGLObject(the_square);
    importGLDeinit();
}

void appRender(int windowWidth, int windowHeight)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawGLObject(the_square);
}
