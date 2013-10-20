
#include "CollisionResolving.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "LinkedList.h"
#include "TransformMatrix.h"
#include "VectorOps.h"

void resolveContacts(Contact *contacts, int contactCount) {
    // Make sure we have something to resolve.
    if(contactCount == 0)
        return;
    
    resolveInterpenetrationIterative(contacts, contactCount);
    
    resolveVelocities(contacts, contactCount);
}


void resolveVelocities(Contact *contacts, int contactCount) {
    for(int i = 0; i < contactCount; i++) {
        applyVelocityChange(&contacts[i]);
    }
    
}

void resolveInterpenetration(Contact *contacts, int contactCount) {
    for(int i = 0; i < contactCount; i++) {
        // Prepare the contact
        if(!prepareContact(&contacts[i])) {
            printf("Contact not valid.\n");
            break;
        }
        
        Vector2 *positionChange = applyPositionChange(&contacts[i]);
        free(positionChange);
    }
}

void resolveInterpenetrationIterative(Contact *contacts, int contactCount) {
    int iteration = 0;
    int iterations = 5;
    int totalIterations = iterations * contactCount;
    
    while(iteration < totalIterations) {
        // Find the deepest penetration
        int maxIndex = contactCount;
        float maxPenetration = -1.0f;
        for(int i = 0; i < contactCount; i++) {
            if(contacts[i].penetration > maxPenetration) {
                maxIndex = i;
                maxPenetration = contacts[i].penetration;
            }
        }
        
        // Check that we found something
        if(maxIndex == contactCount) {
            break;
        }
        
        // Prepare the contact
        if(!prepareContact(&contacts[maxIndex])) {
            printf("Contact not valid.\n");
            break;
        }
        if(maxPenetration > 0.0f) {
            // Apply the position change.
            Vector2 *positionChange = applyPositionChange(&contacts[maxIndex]);
            // Update all other contacts as they could have been influenced by the change.
            for(int i = 0; i < contactCount; i++) {
                updateContact(&contacts[i], &contacts[maxIndex], positionChange);
            }
            free(positionChange);
        }
        iteration++;
    }
}

//void swapBodies(Contact contact) __attribute__ ((const));
void swapBodies(Contact *contact) {
    RigidBody *temp = contact->body0;
    contact->body0 = contact->body1;
    contact->body1 = temp;
}

int prepareContact(Contact *contact) {
    // Check if it is a real contact
    if(contact->point.x == INFINITY)
        return 0;
    
	/* TODO: Fix this if needed */
	/*
	// Can't be done like this anymore. 
	 
    Vector2 position = middleOfShape(contact->shape0);
	
	Vector2 v1 = vector2MakeWithStartAndEndPoints(&(contact->point), &position);
	
	if (vector2DotProduct(&v1, &(contact->normal)) <= 0.0f) {
        swapBodies(contact);
	}
    */
	 
    return 1;
}

void updateContact(Contact *contact, Contact *resolvedContact, Vector2 *positionChange) {
    if(contact->body0 == resolvedContact->body0) {
        contact->penetration -= v2dot(positionChange[0], contact->normal);
    } else if(contact->body0 == resolvedContact->body1) {
        contact->penetration -= v2dot(positionChange[1], contact->normal);
    } 
    if(contact->body1 == resolvedContact->body0) {
        contact->penetration += v2dot(positionChange[0], contact->normal);
    } else if(contact->body1 == resolvedContact->body1) {
        contact->penetration += v2dot(positionChange[1], contact->normal);
    }
}

void applyVelocityChange(Contact *contact) {
    Vector2 normalOrt = v2ortogonal(contact->normal);
    
    Vector2 rContactPos[2];
    
    Vector2 position[2];
    position[0] = getTranslation(contact->body0->bodyToWorldMatrix);
    position[1] = getTranslation(contact->body1->bodyToWorldMatrix);
    
    rContactPos[0] = v2sub(position[0], contact->point);
    rContactPos[1] = v2sub(position[1], contact->point);
    
    Vector2 relativeVelocity = v2add(contact->body0->velocity, 
                                     (Vector2){-contact->body0->rotation * rContactPos[0].y, 
                                         contact->body0->rotation * rContactPos[0].x});
    
    relativeVelocity = v2sub(relativeVelocity, v2add(contact->body1->velocity, 
                                                     (Vector2){-contact->body1->rotation * rContactPos[1].y, 
                                                         contact->body1->rotation * rContactPos[1].x}));
    
    float restitution = 0.3f;
    float friction = 0.3f;
	
    float realRestitution = restitution;
    // Remove restitution at very low speeds to remove some vobbling.
    
	float relativeSpeed = v2length(relativeVelocity);
	if (relativeSpeed < 5.0f) {
		realRestitution = 0.0f;
	}
    
    float velocityFromAcc = v2dot(contact->body0->lastFrameAcceleration, contact->normal) * 0.016f;
	
	velocityFromAcc -= v2dot(contact->body1->lastFrameAcceleration, contact->normal) * 0.016f;
	
	float normalVelocity = v2dot(relativeVelocity, contact->normal);
	
	float desiredNormalVelocity = -normalVelocity - realRestitution * (normalVelocity - velocityFromAcc);
        
    float linearInertia[2];
    float angularInertia[2];
    
    linearInertia[0] = contact->body0->inverseMass;
    linearInertia[1] = contact->body1->inverseMass;
    
    angularInertia[0] = powf(v2determinant(rContactPos[0], contact->normal), 2.0f) * contact->body0->inverseInertia;
    angularInertia[1] = powf(v2determinant(rContactPos[1], contact->normal), 2.0f) * contact->body1->inverseInertia;
    
    float totalInertia = linearInertia[0] + linearInertia[1] + angularInertia[0] + angularInertia[1];
    float inverseInertia = 1.0f/totalInertia;
    
    float impulse = desiredNormalVelocity * inverseInertia;
    
    applyImpulse(contact->body0, contact->body1, rContactPos, &(contact->normal), impulse);
    
    float planarImpulse = -(1+friction)*v2determinant(relativeVelocity, contact->normal) * inverseInertia;
    
    if(fabsf(planarImpulse) > impulse * friction) {
        planarImpulse /= fabsf(planarImpulse);
        planarImpulse *= impulse * friction;
    }
    applyImpulse(contact->body0, contact->body1, rContactPos, &normalOrt, planarImpulse);
}


void applyImpulse(RigidBody *body0, RigidBody *body1, Vector2 *rContactPos, Vector2 *normal, float impulse) {
    body0->velocity = v2add(body0->velocity, v2scale(*normal, impulse * body0->inverseMass));
    body1->velocity = v2add(body1->velocity, v2scale(*normal, -impulse * body1->inverseMass));
    
    body0->rotation += v2determinant(rContactPos[0], v2scale(*normal, impulse)) * body0->inverseInertia;
    body1->rotation -= v2determinant(rContactPos[1], v2scale(*normal, impulse)) * body1->inverseInertia;
}

Vector2 *applyPositionChangeLinearAngular(Contact *contact) {
    contact->penetration += 0.0001;
    Vector2 rContactPos[2];
    
    rContactPos[0] = v2sub(getTranslation(contact->body0->bodyToWorldMatrix), contact->point);
    rContactPos[1] = v2sub(getTranslation(contact->body1->bodyToWorldMatrix), contact->point);
    
    float linearInertia[2];
    float angularInertia[2];
    
    linearInertia[0] = contact->body0->inverseMass;
    linearInertia[1] = contact->body1->inverseMass;
    
    angularInertia[0] = powf(v2determinant(rContactPos[0], contact->normal), 2.0f) * contact->body0->inverseInertia;
    angularInertia[1] = powf(v2determinant(rContactPos[1], contact->normal), 2.0f) * contact->body1->inverseInertia;
    
    float totalInertia = linearInertia[0] + linearInertia[1] + angularInertia[0] + angularInertia[1];
    float inverseInertia = 1.0f/totalInertia;
    
    Vector2 linearMove[2];
    Vector2 angularMove[2];
    linearMove[0] = v2scale(contact->normal, contact->penetration * linearInertia[0] * inverseInertia);
    linearMove[1] = v2scale(contact->normal, -contact->penetration * linearInertia[1] * inverseInertia);
    
    angularMove[0] = v2scale(contact->normal, contact->penetration * angularInertia[0] * inverseInertia);
    angularMove[1] = v2scale(contact->normal, -contact->penetration * angularInertia[1] * inverseInertia);
    
    float angularLimitConstant = 0.2f;
    
    float limit[2];
    
    // Scale the angular component to not be to big.
    
    for(int i = 0; i < 2; i++) {
        limit[i] = angularLimitConstant * v2length(rContactPos[i]);
        if(fabsf(v2length(angularMove[i])) > limit[i]) {
            Vector2 totalMove = v2add(linearMove[i], angularMove[i]);
            
            angularMove[i] = v2scale(v2normalize(angularMove[i]), limit[i]);
            
            linearMove[i] = v2sub(totalMove, angularMove[i]);
        }
    }
    
    translate(contact->body0->bodyToWorldMatrix, linearMove[0].x, linearMove[0].y);
    translate(contact->body1->bodyToWorldMatrix, linearMove[1].x, linearMove[1].y);
    
    rotate(contact->body0->bodyToWorldMatrix, v2determinant(rContactPos[0], angularMove[0]));
    rotate(contact->body1->bodyToWorldMatrix, v2determinant(rContactPos[1], angularMove[1]));
    
    Vector2 *positionChange = malloc(2*sizeof(Vector2));
    
    positionChange[0] = v2add(linearMove[0], angularMove[0]);
    positionChange[1] = v2add(linearMove[1], angularMove[1]);
    
    return positionChange;
}
/*
Vector2 *applyPositionChangeLinearOnly(Contact *contact) {
    Vector2 linearMove[2];
    linearMove[0] = (Vector2){0.0f, 0.0f};
    linearMove[1] = (Vector2){0.0f, 0.0f};
    
    float scale = 1.0f;
    if (contact->body0->inverseMass > 0.0f && contact->body1->inverseMass > 0.0f) {
        linearMove[0] = contact->normal;
        linearMove[1] = contact->normal;
        
        vector2Scale(&linearMove[0], scale * 0.5f * contact->penetration);
        vector2Scale(&linearMove[1], -scale * 0.5f * contact->penetration);
    } else if (contact->body0->inverseMass > 0.0f) {
        linearMove[0] = contact->normal;
        
        vector2Scale(&linearMove[0], scale * 1.0f * contact->penetration);
    } else if (contact->body1->inverseMass > 0.0f) {
        linearMove[1] = contact->normal;
        
        vector2Scale(&linearMove[1], -scale * 1.0f * contact->penetration);
    }
    
    translate(contact->body0->bodyToWorldMatrix, linearMove[0].x, linearMove[0].y);
    translate(contact->body1->bodyToWorldMatrix, linearMove[1].x, linearMove[1].y);
    
    Vector2 *positionChange = malloc(2*sizeof(Vector2));
    
    positionChange[0] = linearMove[0];
    
    positionChange[1] = linearMove[1];
    
    return positionChange;
}
 */
Vector2 *applyPositionChange(Contact *contact) {
    return applyPositionChangeLinearAngular(contact);
}