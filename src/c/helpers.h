#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include "importgl.h"

// Definition of one GL object in this demo.
typedef struct {
    /* Vertex array and color array are enabled for all objects, so their
     * pointers must always be valid and non-NULL. Normal array is not
     * used by the ground plane, so when its pointer is NULL then normal
     * array usage is disabled.
     *
     * Vertex array is supposed to use GL_FIXED datatype and stride 0
     * (i.e. tightly packed array). Color array is supposed to have 4
     * components per color with GL_UNSIGNED_BYTE datatype and stride 0.
     * Normal array is supposed to use GL_FIXED datatype and stride 0.
     */
    GLfixed *vertexArray;
    GLubyte *colorArray;
    GLfixed *normalArray;
    GLint vertexComponents;
    GLsizei count;
} GlObject;

// Capped conversion from float to fixed.
long floatToFixed(float value);

#define FIXED(value) floatToFixed(value)

void freeGLObject(GlObject *object);
GlObject * newGLObject(long vertices, int vertexComponents,
                              int useNormalArray);
void drawGLObject(GlObject *object);
void setScreenSize(int width, int height);

#endif /* HELPERS_H_INCLUDED */
