
#ifndef COLLISIONTYPES
#define COLLISIONTYPES

#include "RigidBody.h"
#include "DynamicArray.h"
#include "VectorTypes.h"

typedef struct {
	Vector2 normal;
	Vector2 point;
	float   penetration;
} ContactPoint;

typedef struct {
	RigidBody *body0;
    RigidBody *body1;
	float restitution;
	float friction;
    DynamicArray points;
} Contact;

typedef void (*ContactPointFunc)(const Vector2 p, const Vector2 cn, const float cp);

#endif
