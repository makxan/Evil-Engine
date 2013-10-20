/*
 *  ShapeCollider.h
 *  GL
 *
 *  Created by Sonny Karlsson on 4/1/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#ifndef __SHAPE_COLLIDER__
#define __SHAPE_COLLIDER__

#include "DynamicArray.h"
#include "RigidBody.h"

typedef struct EvilBody {
    RigidBody body;
    void (*update)(struct EvilBody*);
    DynamicArray shapes;
    DynamicArray drawIndices;
} EvilBody;

typedef struct {
	ArrayIndex   body0;
    ArrayIndex   body1;
    DynamicArray points;
} EvilContact;

typedef struct {
    DynamicArray collideBodies;
    DynamicArray collideContacts;
} EvilCollideData;

/* Creates a new CollideData object.
 * Contains everything needed to perform collision tests.
 */
EvilCollideData newCollideData();

/* Add new collideable.
 * Returns 0 if an error occur, otherwise 1.
 */

int addCollideable(EvilCollideData* collider, ArrayIndex body);

/* Remove collideable.
 * Returns 0 if an error occur, otherwise 1.
 */
int delCollideable(EvilCollideData* collider, EvilBody* body);

/* Simulate collisions on collideables.
 * Return 0 if an error occured, otherwise 1.
 */
int simulateCollisions(DynamicArray* evilBodies, EvilCollideData* collider);

/* Free unused resources of collider.
 * Call on memory warning.
 */
void vacuumColliderData(EvilCollideData* collider);

/* Free collider resources.
 */
void destroyCollideData(EvilCollideData* collider);

#endif // __SHAPE_COLLIDER__
