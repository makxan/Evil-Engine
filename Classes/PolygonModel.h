
#ifndef POLYGONMODEL
#define POLYGONMODEL

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "ShapeTypes.h"
#include "EvilShapes.h"


typedef struct {
    // Number of GLfloats per vertex.
	int size;
	// Number of vertices.
	int length;
	// Array of Vertices
	const GLfloat *vertices;
} PolygonData;

static const float squareVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
};

static const float squareHull[] = {
    -0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
};

static const GLubyte squareColors[] = {
	255, 255,   0, 255,
	0,   255, 255, 255,
	0,     0,   0,   0,
	255,   0, 255, 255,
};

static const float hexagonVertices[] = {
    -0.4f, -0.4f, 0.0f,
    -0.8f,  0.0f, 0.0f,
    -0.4f,  0.4f, 0.0f,
     0.4f,  0.4f, 0.0f,
     0.8f,  0.0f, 0.0f,
     0.4f, -0.4f, 0.0f,
};

static const float aVertices[] = {
    -0.5f, -1.0f, 0.0f,
     1.0f, -0.5f, 0.0f,
     1.0f,  0.5f, 0.0f,
     0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,
};

static const float starEdges[] = {
     0.6f,  0.2f,  0.0f,
     1.5f,  1.0f,  0.0f,
     0.4f,  1.0f,  0.0f,
     0.0f,  2.0f,  0.0f,
    -0.4f,  1.0f,  0.0f,
    -1.5f,  1.0f,  0.0f,
    -0.6f,  0.2f,  0.0f,
    -1.0f, -1.0f,  0.0f,
     0.0f, -0.25f, 0.0f,
     1.0f, -1.0,   0.0f,
};

static const float hEdges[] = {
    -1.0f,  1.0f,  0.0f,
    -1.0f, -1.0f,  0.0f,
    -0.5f, -1.0f,  0.0f,
    -0.5f, -0.25f, 0.0f,
     0.5f, -0.25f, 0.0f,
     0.5f, -1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,
     1.0f,  1.0f,  0.0f,
     0.5f,  1.0f,  0.0f,
     0.5f,  0.25f, 0.0f,
    -0.5f,  0.25f, 0.0f,
    -0.5f,  1.0f,  0.0f,
};

static const PolygonData square = {
    3,
    4,
    squareVertices,
};

void addPolygonWall(EvilGameState* state, ArrayIndex bodyIndex, const Vector2 start, const Vector2 end, const float width);

#endif
