
#ifndef FORCEGENERATOR
#define FORCEGENERATOR

#include <stdlib.h>

#include "WorldArray.h"
#include "VectorTypes.h"
#include "RigidBody.h"

enum GeneratorType {
    GRAVITY,
    DRAG,
    SPRING,
    BUNGEE
    };

enum SpringType {
    ANCHOR,
    BODY
    };

typedef struct {
    enum GeneratorType type;
} ForceGenerator;

typedef struct {
    enum GeneratorType type;
    Vector2 force;
} GravityGenerator;

typedef struct {
    enum GeneratorType type;
    float coefficient;
} DragGenerator;

typedef struct {
    enum GeneratorType type;
    enum SpringType springType;
    float constant;
    float restLength;
    RigidBody *body;
    Vector2 anchor;
} SpringGenerator;

typedef struct {
    RigidBody *body;
    ForceGenerator *generator;
} ForceRegistration;

typedef struct {
    ForceRegistration *registrations;
    unsigned length;
    unsigned size;
} ForceRegistry;

void initGravity(GravityGenerator *gen, Vector2 force);

void initDrag(DragGenerator *gen, float coefficient);

void initBodyBungee(SpringGenerator *gen, float constant, float restLength, RigidBody *body);

void initAnchorBungee(SpringGenerator *gen, float constant, float restLength, Vector2 anchor);

void initBodySpring(SpringGenerator *gen, float constant, float restLength, RigidBody *body);

void initAnchorSpring(SpringGenerator *gen, float constant, float restLength, Vector2 anchor);

void initForceRegistry(ForceRegistry *registry, unsigned length);

void updateForces(ForceRegistry *registry);

int registerForce(RigidBody *body, ForceGenerator *gen, ForceRegistry *registry);

void updateForce(RigidBody *body, ForceGenerator *gen);

#endif