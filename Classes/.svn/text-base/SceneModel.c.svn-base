/*
 *  SceneModel.c
 *  GL
 *
 *  Created by Sonny Karlsson on 4/26/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#include "SceneModel.h"
#include "ShapePolygon.h"
#include "PolygonModel.h"

typedef ArrayIndex BodyIndex;

void addFourWalls(EvilGameState* state)
{
    RigidBody* wallBody = createStaticRigidBody();
    ArrayIndex iBody = addEvilBody(state, wallBody, NULL);
    free(wallBody);

	const Vector2 topr = { 3.20f,  4.8f};
    const Vector2 topl = { -3.20f,  4.8f};
	const Vector2 botr = { 3.20f, -4.8f};
    const Vector2 botl = { -3.20f, -4.8f};

    addPolygonWall(state, iBody, topr, topl, 0.5f);
    addPolygonWall(state, iBody, topl, botl, 0.5f);
    addPolygonWall(state, iBody, botr, botl, 0.5f);
    addPolygonWall(state, iBody, topr, botr, 0.5f);
}

void addSquareShape(EvilGameState* state) 
{
	static const GLfloat squareVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };
    
    static const GLubyte squareColors[] = {
        255, 255,   0, 255,
        0,   255, 255, 255,
        0,     0,   0,   0,
        255,   0, 255, 255,

    };
    DrawData squareDraw;

    useBuffer(newDrawColoured(&squareDraw,
                              GL_TRIANGLE_STRIP,
                              squareVertices,
                              3,
                              4,
                              squareColors,
                              4));

    addRenderable(&state->evilRender, &squareDraw);
    
}

void addHShape(EvilGameState* state)
{
    const float *vertices = triangulatePolygon((float *)hEdges, 3, 12);
    
    static const GLubyte colors[] = {
        0,   0,   0, 255,
        0,   0,   0, 255,
        0,   0,   0, 255,
        
        255, 255,   0, 255,
        255, 255,   0, 255,
        255, 255,   0, 255,
        
        0,   0, 255, 255,
        0,   0, 255, 255,
        0,   0, 255, 255,
        
        0, 255,   0, 255,
        0, 255,   0, 255,
        0, 255,   0, 255,
        
        255,   0, 255, 255,
        255,   0, 255, 255,
        255,   0, 255, 255,
        
        0, 255, 255, 255,
        0, 255, 255, 255,
        0, 255, 255, 255,
        
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255,
        
        255,   0,   0, 255,
        255,   0,   0, 255,
        255,   0,   0, 255,
        
        100,   0,   0, 255,
        100,   0,   0, 255,
        100,   0,   0, 255,
        
        100, 100,   0, 255,
        100, 100,   0, 255,
        100, 100,   0, 255,
    };

    const Point2 pos  = {0.0f, 0.0f};
    const float inert = calculateInertiaRectangle(10.0f, 1.2f, 1.2f);
    RigidBody* hBody = createDynamicRigidBody(pos, 10.0f, inert);

    DrawData* hDraw = useBuffer(newDrawColoured(malloc(sizeof(DrawColoured)),
                                      GL_TRIANGLES, 
                                      vertices, 
                                      3, 
                                      30,
                                      colors,
                                                4));

    BodyIndex bodyIndex = addEvilBody(state, hBody, NULL);
    SShape* hShape = initPolygon(malloc(sizeof(SShape)), hEdges, 3, 12);
    
    addEvilShape(state, bodyIndex, hShape, hDraw);
	//addRenderable(&state->evilRender, hDraw);

    free(hDraw);
    free(hBody);
    free(hShape);
}

