
#include "ForceGenerator.h"

#include <math.h>
#include <stdio.h>

#include "VectorOps.h"
#include "MatrixOps.h"

void initGravity(GravityGenerator *gen, Vector2 force) {
    gen->type = GRAVITY;
    gen->force = force;
}

void initDrag(DragGenerator *gen, float coefficient) {
    gen->type = DRAG;
    gen->coefficient = coefficient;
}

void initBodyBungee(SpringGenerator *gen, float constant, float restLength, RigidBody *body) {
    gen->type = BUNGEE;
    gen->springType = BODY;
    gen->constant = constant;
    gen->restLength = restLength;
    gen->body = body;
    gen->anchor = (Vector2){INFINITY, INFINITY};
}

void initAnchorBungee(SpringGenerator *gen, float constant, float restLength, Vector2 anchor) {
    gen->type = SPRING;
    gen->springType = ANCHOR;
    gen->constant = constant;
    gen->restLength = restLength;
    gen->body = NULL;
    gen->anchor = anchor;
}

void initBodySpring(SpringGenerator *gen, float constant, float restLength, RigidBody *body) {
    gen->type = SPRING;
    gen->springType = BODY;
    gen->constant = constant;
    gen->restLength = restLength;
    gen->body = body;
    gen->anchor = (Vector2){INFINITY, INFINITY};
}

void initAnchorSpring(SpringGenerator *gen, float constant, float restLength, Vector2 anchor) {
    gen->type = SPRING;
    gen->springType = ANCHOR;
    gen->constant = constant;
    gen->restLength = restLength;
    gen->body = NULL;
    gen->anchor = anchor;
}

void updateForces(ForceRegistry *registry) {
    for (int i = 0; i < registry->size; i++) {
        updateForce(registry->registrations[i].body, registry->registrations[i].generator);
    }
}

void initForceRegistry(ForceRegistry *registry, unsigned length) {
    registry->size = 0;
    registry->length = length;
    registry->registrations = malloc(length * sizeof(ForceRegistration));
}

int registerForce(RigidBody *body, ForceGenerator *gen, ForceRegistry *registry) {
    ForceRegistration registration = (ForceRegistration){body, (ForceGenerator *)gen};
    if(registry->size < registry->length) {
        registry->registrations[registry->size++] = registration;
    }
    else {
        void *tmp = realloc(registry->registrations, 2*registry->length);
        if (tmp) {
            registry->registrations = tmp;
            registry->length *= 2;
            registry->registrations[registry->size++] = registration;
        } else {
            printf("ERROR: Memory reallocation failed\n");
            return 0;
        }
    }
    return 1;
}

void updateForce(RigidBody *body, ForceGenerator *gen) {
    switch(gen->type) {
        case GRAVITY: 
        {
            addForce(body, ((GravityGenerator *)gen)->force); 
            break;
        }
        case DRAG:
        {
            float coefficient = ((DragGenerator *)gen)->coefficient;
            float speed = v2length(body->velocity);
                
            float mag = body->drag*0.5f*coefficient*(1.0f/1000.0f)*speed*speed;
                
            Vector2 force = v2scale(v2normalize(v2neg(body->velocity)), mag);
                
            addForce(body,force);
            break;
        }
        case SPRING:
        {
            SpringGenerator *spring = (SpringGenerator *)gen;
            Vector2 force;
            if(spring->springType == BODY) {
                force = v2sub(getTranslation(body->bodyToWorldMatrix), getTranslation(spring->body->bodyToWorldMatrix));
            }
            else if (spring->springType == ANCHOR) {
                force = v2sub(getTranslation(body->bodyToWorldMatrix), spring->anchor);
            } else {
                printf("Uninitialized SpringGenerator");
                return;
            }
            
            
            // Calculate the magnitude of the force. 
            float magnitude = v2length(force); 
            magnitude = spring->constant * fabsf(magnitude - spring->restLength);
            // Calculate the final force and apply it. 
            force = v2normalize(force);
            force = v2scale(force, -magnitude);
            addForce(body, force);
            break;
        }
        case BUNGEE:
        {
            SpringGenerator *spring = (SpringGenerator *)gen;
            Vector2 force;
            if(spring->springType == BODY) {
                force = v2sub(getTranslation(body->bodyToWorldMatrix), getTranslation(spring->body->bodyToWorldMatrix));
            }
            else if (spring->springType == ANCHOR) {
                force = v2sub(getTranslation(body->bodyToWorldMatrix), spring->anchor);
            } else {
                printf("Uninitialized SpringGenerator");
                return;
            }
            
            // Calculate the magnitude of the force. 
            float magnitude = v2length(force); 
            if(magnitude <= spring->restLength) 
                return;
            
            magnitude = spring->constant * (spring->restLength - magnitude);
            // Calculate the final force and apply it. 
            force = v2normalize(force);
            force = v2scale(force, -magnitude);
            addForce(body, force);
            
            break;
        }
        default:
            break;
    }
}
