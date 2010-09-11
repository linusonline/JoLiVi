#include <stdlib.h>
#include <assert.h>
#include "common.h"
#include "helpers.h"

long floatToFixed(float value)
{
    if (value < -32768) value = -32768;
    if (value > 32767) value = 32767;
    return (long)(value * 65536);
}

void freeGLObject(GlObject *object)
{
    if (object == NULL)
        return;
    free(object->normalArray);
    free(object->colorArray);
    free(object->vertexArray);
    free(object);
}

GlObject * newGLObject(long vertices, int vertexComponents,
                              int useNormalArray)
{
    GlObject *result;
    result = (GlObject *)malloc(sizeof(GlObject));
    if (result == NULL)
        return NULL;
    result->count = vertices;
    result->vertexComponents = vertexComponents;
    result->vertexArray = (GLfixed *)malloc(vertices * vertexComponents *
                                            sizeof(GLfixed));
    result->colorArray = (GLubyte *)malloc(vertices * 4 * sizeof(GLubyte));
    if (useNormalArray)
    {
        result->normalArray = (GLfixed *)malloc(vertices * 3 *
                                                sizeof(GLfixed));
    }
    else
        result->normalArray = NULL;
    if (result->vertexArray == NULL ||
        result->colorArray == NULL ||
        (useNormalArray && result->normalArray == NULL))
    {
        freeGLObject(result);
        return NULL;
    }
    return result;
}

void drawGLObject(GlObject *object)
{
    assert(object != NULL);

    glVertexPointer(object->vertexComponents, GL_FIXED,
                    0, object->vertexArray);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, object->colorArray);

    if (object->normalArray)
    {
        glNormalPointer(GL_FIXED, 0, object->normalArray);
        glEnableClientState(GL_NORMAL_ARRAY);
    }
    else
        glDisableClientState(GL_NORMAL_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, object->count);
}

void setScreenSize(int width, int height)
{
    g_globals.window_width = width;
    g_globals.window_height = height;
	glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrthox(FIXED(0.0), FIXED((float)width), FIXED(0.0), FIXED((float)height), FIXED(-1.0), FIXED(1.0));
}
