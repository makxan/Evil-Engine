
#ifndef __EVIL_SHAPES__
#define __EVIL_SHAPES__

#include "DynamicArray.h"
#include "RigidBody.h"
#include "EvilCollider.h"
#include "EvilRenderer.h"

typedef DynamicArray EvilBodies;

typedef struct {
    EvilBodies      evilBodies;
    EvilCollideData evilCollision;
    EvilRenderData  evilRender;
} EvilGameState;

/* Create new empty EvilGameState.
 */
EvilGameState newEvilState();

/* Initiate EvilGameState.
 * Prepare EvilGameState for use.
 */
int initEvilState(EvilGameState* state, 
                  GLVersion version, 
                  GLfloat screenWidth,
                  GLfloat screenHeight);

/* Add a RigidBody to engine.
 * Copies all related data in RigidBody,
 * but reference to matrix is keept. 
 * Obs: Don't dealloc matrix!
 * Note: ArrayIndex used for further refereses.
 */
ArrayIndex addEvilBody(EvilGameState* state, 
                       RigidBody* body, 
                       void (*update)(EvilBody*));

/* Add a Shape and related DrawData to engine.
 * Copies Shape and DrawData into GameState and associate 
 * with RigidBody, but referce to matrix is keept. 
 * Obs: Don't dealloc matrix!
 */
int addEvilShape(EvilGameState* state,
                 ArrayIndex index,
                 SShape* shape,
                 DrawData* draw);

/* Update EvilGameState.
 */
int nextEvilState(EvilGameState* state);

/* Draws EvilGameState.
 */
int drawEvilState(EvilGameState* state);

/* Should vacuum EvilGameState for unused memory.
 */
void vacuumEvilState(EvilGameState* state);

/* Dealloc all EvilGameState resources.
 */
void destroyEvilState(EvilGameState* state);

#endif // __EVIL_SHAPES__
