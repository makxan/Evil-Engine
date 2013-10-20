/*
 *  ShapeCollider.c
 *  GL
 *
 *  Created by Sonny Karlsson on 4/1/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#include "EvilCollider.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Collision.h"
#include "RigidBody.h"
#include "CollisionResolving.h"

EvilCollideData newCollideData()
{
    DynamicArray bodies   = newArray(4,  0, sizeof(ArrayIndex));
    DynamicArray contacts = newArray(16, 1, sizeof(EvilContact));

    return (EvilCollideData){bodies, contacts};
}

int hasCollideable(EvilCollideData* collider, const ArrayIndex body0)
{
    if (body0 == NOINDEX)
        return 0;
    DynamicArray* array = &collider->collideBodies;
    for (int i = 1; i <= arrayUsed(array); i++) {
        const ArrayIndex* body1 = getAtIndex(array, i);
        if (*body1 != NOINDEX && body0 == *body1)
            return 1;
    }
    return 0;
}

/* Add new collideable.
 * Returns 0 if an error occur, otherwise 1.
 * Note: Uses nested functions.
 * Todo: This won't hold if dynamic array is relocaleted, fix by index.
 */
int addCollideable(EvilCollideData* collider, 
                   ArrayIndex body0)
{
    if (hasCollideable(collider, body0))
        return 0;

    void addContacts(ArrayIndex* body1) {
        if (*body1 != NOINDEX && body0 != *body1) {
            EvilContact con = {
                body0,
                *body1,
                newArray(4, 1, sizeof(ContactPoint))
            };
            addLast(&collider->collideContacts, &con, sizeof(con));
        }
    }
    DynamicArray* bodyArray = &collider->collideBodies;
    arrayMap(bodyArray, &addContacts);
    addLast(bodyArray, &body0, sizeof(body0));
    return 1;
}

/* Remove collideable.
 * Returns 0 if an error occur, otherwise 1.
 * Note: Since DynamicArray does not support deleting object we overwrite with 0s.
 * Note: Sensitive memset functions could fail anytime.
 */
int delCollidable(EvilCollideData* collider, ArrayIndex body0)
{
    void delContacts(EvilContact* con) {
        if (con == NULL || (con->body0 != body0 && con->body1 != body0))
            return;
        arrayHardEmpty(&con->points);
        memset(con, 0, sizeof(con));
    }
    const DynamicArray* contactArray = &collider->collideContacts;
    arrayMap(contactArray, &delContacts);
    
    void delBody(ArrayIndex* body1) {
        if (body0 == *body1)
            memset(body1, 0, sizeof(body1));
    }
    const DynamicArray* bodyArray = &collider->collideBodies;
    arrayMap(bodyArray, &delBody);

    return 1;
}

void simulateContact(DynamicArray* evilBodies, EvilContact* contact);

int simulateCollisions(DynamicArray* evilBodies, EvilCollideData* collider)
{
    void collideFunc(EvilContact* con) {
        if (con->body0 == NOINDEX && con->body1 == NOINDEX)
            return;
        simulateContact(evilBodies, con);
    }
    const DynamicArray* contactArray = &collider->collideContacts;
    arrayMap(contactArray, &collideFunc);

    //resolveContacts(evilBodies, &collider->collideContacts);

    void clearContactPoints(EvilContact* con) {
        if (con->points.array == NULL)
            return;
        arraySoftEmpty(&con->points);
    }
    arrayMap(contactArray, &clearContactPoints);
    return 1;
}

void simulateContact(DynamicArray* evilBodies, EvilContact* contact)
{
    EvilBody* body0 = getAtIndex(evilBodies, contact->body0);
    EvilBody* body1 = getAtIndex(evilBodies, contact->body1);
    
	const float* mt0 = body0->body.bodyToWorldMatrix;
	const float* mt1 = body1->body.bodyToWorldMatrix;

    const DynamicArray* shapeArray0 = &body0->shapes;
    const DynamicArray* shapeArray1 = &body1->shapes;

    void addContactPoint(const Vector2 p, const Vector2 cn, const float cp) {
        ContactPoint point = {p, cn, cp};
        addLast(&contact->points, &point, sizeof(point));
    }

    const SShape* shape0;

    void layer1Shapes(SShape* shape1) {
        if (shape1 == NULL && canCollide(mt0, shape0, mt1, shape1) != 0)
            return;
        getContactPoints(&addContactPoint, mt0, shape0, mt1, shape1);
    }
    void layer0Shapes(SShape* shapeTemp) {
        if (shapeTemp == NULL)
            return;
		shape0 = shapeTemp;
        arrayMap(shapeArray1, &layer1Shapes);
    }
    arrayMap(shapeArray0, &layer0Shapes);
}

void destroyCollideData(EvilCollideData* collider)
{
    void destroyContacts(void* vcon) {
        EvilContact* con = (EvilContact*)vcon;
        if (con->points.array == NULL)
            return;
        arrayHardEmpty(&con->points);
    }
    arrayHardEmpty(&collider->collideBodies);
    arrayHardEmpty(&collider->collideContacts);
}
