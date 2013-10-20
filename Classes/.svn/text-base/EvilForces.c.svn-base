#include "EvilForces.h"

#include <stdio.h>
#include <string.h>

ForceGenerator* newConstantForce(ForceGenerator* generator, 
                                   const Vector2 force)
{
    ConstantGenerator constant = {
        .type        = CONSTANT,
        .bodyIndices = newArray(4, 0, sizeof(ArrayIndex)),
        .force       = force,
    };
    memcpy(generator, &constant, sizeof(constant));
    return generator;
}

ForceGenerator* newDragForce(ForceGenerator* generator, 
                             const float coefficient)
{
    DragGenerator drag = {
        .type        = DRAG,
        .bodyIndices = newArray(4, 0, sizeof(ArrayIndex)),
        .coefficient = coefficient,
    };
    memcpy(generator, &drag, sizeof(drag));
    return generator;
}

ForceGenerator* newBodySpring(ForceGenerator* generator, 
                              const float springConstant,
                              const float restLength,
                              const ArrayIndex bodyIndex)
{
    BodySpringGenerator bodySpring = {
        .type        = BODYSPRING,
        .bodyIndices = newArray(4, 0, sizeof(ArrayIndex)),
        .constant    = springConstant,
        .restLength  = restLength,
        .bodyIndex   = bodyIndex,
    };
    memcpy(generator, &bodySpring, sizeof(bodySpring));
    return generator;
}

ForceGenerator* newAnchorSpring(ForceGenerator* generator, 
                                const float springConstant,
                                const float restLength,
                                const Vector2 anchorPoint) 
{
    AnchorSpringGenerator anchorSpring = {
        .type        = ANCHORSPRING,
        .bodyIndices = newArray(4, 0, sizeof(ArrayIndex)),
        .constant    = springConstant,
        .restLength  = restLength,
        .anchor      = anchorPoint,
    };
    memcpy(generator, &anchorSpring, sizeof(anchorSpring));
    return generator;

}

int addToGenerator(ForceGenerator* generator, const ArrayIndex body) 
{
    return (addLast(&generator->bodyIndices, &body, sizeof(body)) > 0);
}

void applyConstantForce(DynamicArray* evilBodies, ConstantGenerator* constant);

void applyGenerator(DynamicArray* evilBodies, ForceGenerator* generator)
{
    switch(generator->type) {
    case CONSTANT:
        applyConstantForce(evilBodies, (ConstantGenerator*)generator);
        break;
    case DRAG:
    case BODYSPRING:
    case ANCHORSPRING:
		printf("applyGenerator: Not yet implemented.\n");
		break;
    default:
        printf("applyGenerator: Unknown generator.\n");
        break;
    }
}

void applyConstantForce(DynamicArray* evilBodies, ConstantGenerator* constant)
{
    void applyForce(ArrayIndex* bodyIndex) {
        EvilBody* body = getAtIndex(evilBodies, *bodyIndex);
        if (body == NULL)
            return;
        addForce(&body->body, constant->force);
    }
    arrayMap(&constant->bodyIndices, &applyForce);
}

void destroyGenerator(ForceGenerator* generator)
{
    arrayHardEmpty(&generator->bodyIndices);
}
