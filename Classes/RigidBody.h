
#ifndef RIGIDBODY
#define RIGIDBODY

#include "ShapeTypes.h"
#include "VectorTypes.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "DrawData.h"

typedef struct {
    float*  bodyToWorldMatrix;
    Vector2 velocity;
	Vector2 acceleration;
	Vector2 forceAccumulated;
    Vector2 lastFrameAcceleration;
	float   orientationChange;
    float   rotation;
	float   torqueAccumulated;
	float   inverseInertia;
	float   damping;
	float   inverseMass;
	float   drag;
    float   restitution;
    float   friction;
} RigidBody;

#pragma mark -
#pragma mark Functions
#pragma mark -

void drawBody(RigidBody *body, HashMap *hashMap, GLVersion version, GLuint program);
void moveBody(RigidBody *body);

void integrateBody(RigidBody *body, const float duration);
void clearAccumulatedForces(RigidBody *body);
void addForce(RigidBody *body, const Vector2 force);
void addForceAtPoint(RigidBody *body, const Vector2 *force, const Vector2 *point);
void setModelToWorldMatrix(RigidBody *body);
void deallocRigidBody(RigidBody *body);
void setVelocity(RigidBody *body, const Vector2 *point);

RigidBody *createDefaultRigidBody();
RigidBody *createDynamicRigidBody(const Point2 p, const float mass, const float inertia);
RigidBody *createStaticRigidBody();

float calculateInertiaRectangle(const float mass, const float width, const float height);

float calculateInertiaCircle(const float mass, const float radius);

void addBodyShape(RigidBody *body, SShape *shape);

int containsShape(RigidBody *body, SShape *shape);

#endif
