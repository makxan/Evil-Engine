
#ifndef COLLISION
#define COLLISION

#include "ShapeTypes.h"
#include "CollisionTypes.h"

#include "RigidBody.h"

void getContactPoints(ContactPointFunc pointFunc,
                      const float* mt0, const SShape* shape0, 
                      const float* mt1, const SShape* shape1);

int canCollide(const float* mt0, const SShape *shape0,
			   const float* mt1, const SShape *shape1);

int containsPoint(const float* mt0, const SShape *shape, const Vector2 p);

void newContact(Contact* contactData, const Vector2 p, const Vector2 cn, const float cp);

#endif
