
#ifndef VECTOROPS
#define VECTOROPS

#include "VectorTypes.h"

static const float EMPTY_POINT[4]  = {0.0f, 0.0f, 0.0f, 1.0f};
static const float EMPTY_VECTOR[4] = {0.0f, 0.0f, 0.0f, 0.0f};

Vector2 v2scale(const Vector2 v, const float s);
Vector2 v2neg(const Vector2 v) __attribute__ ((const));
Vector2 v2add(const Vector2 v1, const Vector2 v2) __attribute__ ((const));
Vector2 v2sub(const Vector2 v1, const Vector2 v2) __attribute__ ((const));
Vector2 v2ortogonal(const Vector2 v) __attribute__ ((const));
Vector2 v2normalize(const Vector2 v) __attribute__ ((const));
float v2dot(const Vector2 v1, const Vector2 v2) __attribute__ ((const));
float v2length(const Vector2 v) __attribute__ ((const));
float vlength(const float* v, const int n);
float v2determinant(const Vector2 v1, const Vector2 v2) __attribute__ ((const));

Vector2 mulv4m4x4(const float* v, const float* m);
Vector2 mulv2m4x4(const float* v, const float* m);

Vector2 v2conv(const float* v);

float distanceCircleToCircle(const Vector2 p1, const float r1, const Vector2 p2, const float r2);
Vector2 lineIntersection(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d) __attribute__ ((const));

#endif