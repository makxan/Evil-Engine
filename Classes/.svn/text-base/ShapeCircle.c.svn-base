
#include "ShapeCircle.h"

#include "VectorOps.h"
#include "Collision.h"

int checkCircleCircle(const float* restrict mt1, const SCircle* circle1,
					  const float* restrict mt2, const SCircle* circle2)
{
	const Vector2 a = v2add(mulv4m4x4(EMPTY_POINT, mt1), circle1->position);
	const Vector2 b = v2add(mulv4m4x4(EMPTY_POINT, mt2), circle2->position);
	
	return distanceCircleToCircle(a, circle1->radius, b, circle2->radius) > 0.0f;
}

int checkCirclePoint(const float* restrict mt1, const SCircle* circle, const Vector2 p)
{
	const Vector2 a = v2add(mulv4m4x4(EMPTY_POINT, mt1), circle->position);

	return v2length(v2sub(a, p)) < circle->radius;
}

void contactCircleCircle(ContactPointFunc pointFunc,
						 const float* restrict mt1, 
						 const SCircle* circle1, 
						 const float* restrict mt2, 
						 const SCircle* circle2)
{
	const Vector2 a  = v2add(mulv4m4x4(EMPTY_POINT, mt1), circle1->position);
	const Vector2 b  = v2add(mulv4m4x4(EMPTY_POINT, mt2), circle2->position);
	
	const float cp   = v2length(v2sub(a, b)) - (circle1->radius - circle2->radius);
	
	if (cp > 0) {
		const Vector2 cn = v2normalize(v2sub(a, b));
		const Vector2 p  = v2add(a, v2scale(cn, circle1->radius));
        (*pointFunc)(p, cn, cp);
	}
}
