
#ifndef COLLISIONRESOLVING
#define COLLISIONRESOLVING

#include "CollisionTypes.h"
#include "VectorTypes.h"
#include "RigidBody.h"

void resolveContacts(Contact *contacts, int contactCount);
int prepareContact(Contact *contact);
void updateContact(Contact *contact, Contact *resolvedContact, Vector2 *positionChange);
void resolveVelocities(Contact *contacts, int contactCount);
void resolveInterpenetration(Contact *contacts, int contactCount);
void resolveInterpenetrationIterative(Contact *contacts, int contactCount);
void applyVelocityChange(Contact *contact);
Vector2 *applyPositionChange(Contact *contact);

void applyImpulse(RigidBody *body0, RigidBody *body1, Vector2 *rContactPos, Vector2 *normal, float impulse);

#endif