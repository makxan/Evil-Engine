#ifndef __EVIL_FORCES__
#define __EVIL_FORCES__

#include "EvilShapes.h"
#include "VectorTypes.h"
#include "DynamicArray.h"

enum ForceType {
    NOFORCE = 0,
    CONSTANT,
    DRAG,
    BUNGEE,
    BODYSPRING,
    ANCHORSPRING,
};

typedef struct {
    enum ForceType type;
    DynamicArray bodyIndices;
    Vector2      _padding0;
    float        _padding1;
    float        _padding2;
    ArrayIndex   _padding3;
} ForceGenerator;

typedef struct {
    enum ForceType type;
    DynamicArray bodyIndices;
    Vector2      force;
    float        _padding1;
    float        _padding2;
    ArrayIndex   _padding3;
} ConstantGenerator;

typedef struct {
    enum ForceType type;
    DynamicArray bodyIndices;
    Vector2      _padding0;
    float        coefficient;
    float        _padding2;
    ArrayIndex   _padding3;
} DragGenerator;

typedef struct {
    enum ForceType type;
    DynamicArray bodyIndices;
    Vector2      _padding0;
    float        constant;
    float        restLength;
    ArrayIndex   bodyIndex;
} BodySpringGenerator;

typedef struct {
    enum ForceType type;
    DynamicArray bodyIndices;
    Vector2      anchor;
    float        constant;
    float        restLength;
    ArrayIndex   _padding3;
} AnchorSpringGenerator;

typedef DynamicArray EvilForces;

ForceGenerator* newConstantForce(ForceGenerator* generator, 
                                 const Vector2 force);

ForceGenerator* newDragForce(ForceGenerator* generator, 
                             const float coefficient);

ForceGenerator* newBodySpring(ForceGenerator* generator, 
                              const float springConstant,
                              const float restLength,
                              const ArrayIndex bodyIndex);

ForceGenerator* newAnchorSpring(ForceGenerator* generator, 
                                const float springConstant,
                                const float restLength,
                                const Vector2 anchorPoint);

int addToGenerator(ForceGenerator* generator, const ArrayIndex body);

int applyGenerators(DynamicArray* evilBodies, ForceGenerator* generator);

#endif // __EVIL_FORCES__
