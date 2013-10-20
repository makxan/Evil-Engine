
#ifndef SHAPECIRCLE
#define SHAPECIRCLE

#include "ShapeTypes.h"
#include "DrawData.h"
#include "CollisionTypes.h"

int checkCircleCircle(const float* mt1, const SCircle* circle1,
					  const float* mt2, const SCircle* circle2);

int checkCirclePoint(const float* mt1, const SCircle* circle, const Vector2 p);

void contactCircleCircle(ContactPointFunc pointFunc,
						 const float* restrict mt1, 
						 const SCircle* circle1, 
						 const float* restrict mt2, 
						 const SCircle* circle2);

#endif
