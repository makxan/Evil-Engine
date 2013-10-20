
#include "PolygonModel.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "MatrixOps.h"
#include "VectorOps.h"
#include "ShapePolygon.h"
#include "EvilShapes.h"

void addPolygonWall(EvilGameState* state, ArrayIndex bodyIndex, const Vector2 start, const Vector2 end, const float width)
{
    
	const Vector2 v = v2sub(start, end);
	const Vector2 p = v2add(start, v2scale(v, -0.5));
	const float   r = acosf(v2dot(v, (Vector2){1.0f, 0.0f}) / v2length(v));
	
    DrawData* wallDraw  = malloc(sizeof(DrawData));
    SPolygon* wallShape = malloc(sizeof(SShape));

    useBuffer(newDrawColoured(wallDraw,
                              GL_TRIANGLE_STRIP, 
                              squareVertices, 
                              3, 
                              4, 
                              squareColors, 
                              4));
	
	initPolygon((SShape*)wallShape, squareHull, 3, 4);
    
    scale(wallShape->transShapeToBody, v2length(v), width, 1.0, 1.0);
	rotate(wallShape->transShapeToBody, r);	
    translate(wallShape->transShapeToBody, p.x, p.y);

    addEvilShape(state, bodyIndex, (SShape*)wallShape, wallDraw);

    free(wallShape);
    free(wallDraw);
}

