
#include "Collision.h"

#include <stdlib.h>
#include <assert.h>

#include "VectorOps.h"
#include "RigidBody.h"
#include "ShapePolygon.h"
#include "ShapeCircle.h"

/* Detects shapes and test for collision.
 * Return values:
 *  0: No collision.
 *  1: Collision.
 * -1: Not implemented.
 */

int canCollide(const float* mt0, const SShape *shape0,
			   const float* mt1, const SShape *shape1)
{
	const enum ShapeType type0 = shape0->type;
	const enum ShapeType type1 = shape1->type;
	
	if (type0 == POLYGON && type1 == POLYGON)
		return checkPolygonPolygon(mt0, (const SPolygon*)shape0, mt1, (const SPolygon*)shape1);
	
	if (type0 == POLYGON && type1 == CIRCLE)
		return checkPolygonCircle(mt0, (const SPolygon*)shape0, mt1, (const SCircle*)shape1);
	
	if (type0 == CIRCLE && type1 == POLYGON)
		return checkPolygonCircle(mt1, (const SPolygon*)shape1, mt0, (const SCircle*)shape0);
	
	if (type0 == CIRCLE && type1 == POLYGON)
		return checkCircleCircle(mt0, (const SCircle*)shape0, mt1, (const SCircle*)shape1);
	
	return -1;
}

// TODO: Fix accuracy for point in polygon test.
int containsPoint(const float* mt0, const SShape *shape, const Vector2 p)
{
	const enum ShapeType type = shape->type;
	if (type == POLYGON)
		return checkPolygonPoint(mt0, (const SPolygon *)shape, p);
	
	if (type == CIRCLE)
		return checkCirclePoint(mt0, (const SCircle *)shape, p);
	
	return -1;
}

void getContactPoints(ContactPointFunc pointFunc,
                      const float* mt0, const SShape* shape0, 
                      const float* mt1, const SShape* shape1)
{
	const enum ShapeType type0 = shape0->type;
	const enum ShapeType type1 = shape1->type;
	
	if (type0 == POLYGON && type1 == POLYGON) {
		contactPolygonPolygon(pointFunc, 
							  mt0, (const SPolygon *)shape0, 
							  mt1, (const SPolygon *)shape1);
	} 
	if (type0 == POLYGON && type1 == CIRCLE) {
		contactPolygonCircle(pointFunc, 
							 mt0, (const SPolygon *)shape0, 
							 mt1, (const SCircle *)shape1);
		
	}
	if (type0 == CIRCLE && type1 == POLYGON) {
        void negNormalFunc(const Vector2 p, const Vector2 cn, const float cp) {
            (*pointFunc)(p, v2neg(cn), cp);
        }
		contactPolygonCircle(negNormalFunc, 
							 mt1, (const SPolygon *)shape1, 
							 mt0, (const SCircle *)shape0);
	} 
	if (type0 == CIRCLE && type1 == CIRCLE) {
		contactCircleCircle(pointFunc, 
							mt0, (const SCircle *)shape0, 
							mt1, (const SCircle *)shape1);
	}
}
