
#include "EvilShapes.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

size_t sizeofShape(SShape* shape)
{
    if (shape == NULL) {
        printf("sizeofShape: Shape is NULL.\n");
        return 0;
    }
    switch (shape->type) {
    case CIRCLE:
        return sizeof(SCircle);
    case POLYGON:
        return sizeof(SPolygon);
    default:
        printf("sizeofShape: Unknown type.");
        return 0;
    };
}

EvilGameState newEvilState() 
{
    return (EvilGameState){
        newArray(16, 0, sizeof(EvilBody)),
        newCollideData(),
        newRenderData()
    };
}

int initEvilState(EvilGameState* state, 
                  GLVersion version, 
                  GLfloat screenWidth,
                  GLfloat screenHeight) 
{
    return initRenderData(&state->evilRender, 
                          version, 
                          screenWidth, 
                          screenHeight);
}

/* Todo: Register all DrawData in rigid body. */
ArrayIndex addEvilBody(EvilGameState* state, 
                       RigidBody* body, 
                       void (*update)(EvilBody*))
{
    if (body == NULL) {
        printf("addEvilBody: Tried to add NULL body.\n");
        return UINT_MAX;
    }
    EvilBody evil = {
        .body        = *body,
        .update      = update,
        .shapes      = newArray(4, 0, sizeof(SShape)),
        .drawIndices = newArray(4, 0, sizeof(ArrayIndex)),
    };
    return addLast(&state->evilBodies, &evil, sizeof(evil));
}

int addEvilShape(EvilGameState* state,
                 ArrayIndex index,
                 SShape* shape,
                 DrawData* draw)
{
    EvilBody* evil = getAtIndex(&state->evilBodies, index);

    assert(evil  != NULL);
    assert(shape != NULL);
    assert(draw  != NULL);
    
    drawSetBodyMatrix(draw, evil->body.bodyToWorldMatrix);

    if (shape->type == POLYGON)
        drawSetShapeMatrix(draw, ((SPolygon*)shape)->transShapeToBody);

    ArrayIndex indexD = addRenderable(&state->evilRender, draw);
    
    if (indexD == UINT_MAX) {
        printf("addEvilShape: DrawData could not be added to renderer");
        return 0;
    }
    if (addLast(&evil->shapes, shape, sizeofShape(shape)) == UINT_MAX) {
        printf("addEvilShape: Shape could not be added to array.");
        return 0;
    }
    if (addLast(&evil->drawIndices, &indexD, sizeof(indexD)) == UINT_MAX) {
        printf("addEvilShape: Draw indices could not be added to array.");
        return 0;
    }
    return 1;
}

int nextEvilState(EvilGameState* state) 
{
    void animateBody(EvilBody* body) {
        if (body->update == NULL)
            return;
        (*(body->update))(body);
    }
    DynamicArray* evilBodies = &state->evilBodies;
    arrayMap(evilBodies, &animateBody);
    simulateCollisions(evilBodies, &state->evilCollision);
    return 1;
}

int drawEvilState(EvilGameState* state) 
{
    return renderData(&state->evilRender);
}

void destroyEvilState(EvilGameState* state) 
{
    void deallocShapeMatrix(SShape* shape) {
        if (shape == NULL || shape->type != POLYGON)
            return;
        float* matrix = ((SPolygon*)shape)->transShapeToBody;
        free(matrix);
        matrix = NULL;
    }
    void deallocBody(EvilBody* body) {
        if (body == NULL)
            return;
        float* matrix = body->body.bodyToWorldMatrix;
        free(matrix);
        matrix = NULL;

        DynamicArray* shapes = &body->shapes;
        arrayMap(shapes, &deallocShapeMatrix);
        arrayHardEmpty(shapes);

        arrayHardEmpty(&body->drawIndices);
    }
    DynamicArray* evilBodies = &state->evilBodies;
    arrayMap(evilBodies, &deallocBody);
    arrayHardEmpty(evilBodies);

    destroyRenderData(&state->evilRender);
    destroyCollideData(&state->evilCollision);
}

