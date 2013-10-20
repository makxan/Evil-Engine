
#include "RigidBody.h"

#include <stdlib.h>
#include <math.h>

#include "VectorOps.h"
#include "MatrixOps.h"

//updates the position and velocity depending on the forces and accelerations.
void integrateBody(RigidBody *body, const float duration){
	// Add velocity*duration to the matrix (move the particle)
    
    Vector2 positionChange = v2scale(body->velocity, duration);
    
    // Translate
    translate(body->bodyToWorldMatrix, positionChange.x, positionChange.y);
    
	//vector2AddScaled(&(body->position), &(body->velocity), duration);
	
	// Add the rotation speed * duration to the matrix
    body->orientationChange = body->rotation*duration;
    
    rotate(body->bodyToWorldMatrix, body->rotation*duration);
    
    /*
	body->orientation += body->rotation*duration;
	//use mod to prevent orientation growing to infinity
	body->orientation = fmod((body->orientation),(360/(2*M_PI)));
	body->orientationChange = body->rotation*duration;
     */
	Vector2 resAcc = v2add(body->acceleration, v2scale(body->forceAccumulated, body->inverseMass));
	
	// Calculate the resulting acceleration depending on the accumulated force.	
    body->lastFrameAcceleration = resAcc;
    
	// Calculate resulting angular acceleration from the torque.
	GLfloat resAngularAcc = body->torqueAccumulated*body->inverseInertia;
	
	// Add the acceleration
	body->rotation += resAngularAcc*duration;
	
	// Add acceleration*duration to velocity
    body->velocity = v2add(body->velocity, v2scale(resAcc, duration));
	
	// Damping 
	body->velocity = v2scale(body->velocity, powf(body->damping, duration));
	body->rotation *= powf(body->damping, duration);
	
	// Clear accumulated force.
	clearAccumulatedForces(body);
}

// Clears all accumulated forces.
void clearAccumulatedForces(RigidBody *body) {
	body->forceAccumulated.x = 0.0;
	body->forceAccumulated.y = 0.0;
	body->torqueAccumulated = 0.0;
}

// Adds a force to the accumulated forces of a particle.
void addForce(RigidBody *body, const Vector2 force) {
    body->forceAccumulated = v2add(body->forceAccumulated, force);
}

void addForceAtPoint(RigidBody *body, const Vector2 *force, const Vector2 *point) {
    Vector2 position = getTranslation(body->bodyToWorldMatrix);
	Vector2 arm = v2sub(position, *point);
	body->torqueAccumulated += v2determinant(*force, arm);
}

void setVelocity(RigidBody *body, const Vector2 *point) {
	body->velocity = *point;
}

/*
 * TODO: DOCUMENT
 */
RigidBody *createDefaultRigidBody() {
	RigidBody *body = malloc(sizeof(RigidBody));
    body->bodyToWorldMatrix = malloc(16 * sizeof(float));
    squareIdentity(body->bodyToWorldMatrix, 4);
	body->acceleration.x = 0.0;
	body->acceleration.y = 0.0;
	body->velocity.x = 0.0;
	body->velocity.y = 0.0;
	body->forceAccumulated.x = 0.0;
	body->forceAccumulated.y = 0.0;
	body->inverseMass = 1.0;
	body->inverseInertia = 1.0;
	body->damping = 0.995;
	body->rotation = 0.0;
	body->torqueAccumulated = 0.0;
	body->drag = 0.99;
	return body;
}

RigidBody *createDynamicRigidBody(const Point2 p, const float mass, const float inertia) {
	RigidBody *body = createDefaultRigidBody();
    translate(body->bodyToWorldMatrix, p.x, p.y);
    float realMass = mass;
    float realInertia = inertia;
    if(realMass <= 0.0f) {
        realMass = 1.0f;
    }
    if(realInertia <= 0.0f) {
        realInertia = 1.0f;
    }
    body->inverseMass = 1.0f/realMass;
    body->inverseInertia = 1.0f/realInertia;
    
    return body;
}

RigidBody *createStaticRigidBody() {
    RigidBody *body = createDefaultRigidBody();
    body->inverseMass = 0.0f;
    body->inverseInertia = 0.0f;
    return body;
}

float calculateInertiaRectangle(const float mass, const float width, const float height) {
    return mass * (width * width + height * height) / 12.0f;
}

float calculateInertiaCircle(const float mass, const float radius) {
    return mass * radius * radius / 2.0f;
}

void moveBody(RigidBody *body) {
    integrateBody(body, 0.016);
}
