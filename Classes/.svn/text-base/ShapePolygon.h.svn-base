
#ifndef SHAPEPOLYGON
#define SHAPEPOLYGON

#import "ShapeTypes.h"
#import "DrawData.h"
#import "CollisionTypes.h"

// Initialization of polygon.
SShape* initPolygon(SShape* polygon,
                    const float* hullEdges, 
                    const unsigned int size,
                    const unsigned int length);

float maxVectorLength(const float* vectors, const int vectorSize, const int length);
float* triangulatePolygon(const float* hullEdges, const int pointSize, const int hullLength);
int checkValidTri(const Vector2* start, const Vector2* mid , const Vector2* end);

// Constructors of polygons.
int    numberOfVertices(int hullLength);
float* generateEdges(float* hullEdges, int edgeSize, int hullLength);

// Manipulation of Polygons.
int scalePolygon(SPolygon* poly, const float xs, const float ys, const float zs, const float s);
int movePolygon(SPolygon* poly, const float x, const float y);
int rotatePolygon(SPolygon* poly, const float rad);

// Level 1 collision check.
int checkPolygonCircle(const float* mt1, const SPolygon* poly, const float* mt2, const SCircle* circle);
int checkPolygonPolygon(const float* mt1, const SPolygon* poly1, const float* mt2, const SPolygon* poly2);
int checkPolygonPoint(const float* mt1, const SPolygon* poly, const Vector2 p);

// Level 2 collision check.
void contactPolygonCircle(ContactPointFunc pointFunc,
						  const float* mt1, 
						  const SPolygon* poly, 
						  const float* mt2, 
						  const SCircle* circle);
void contactPolygonPolygon(ContactPointFunc pointFunc,
						   const float* mt1,
						   const SPolygon* poly1, 
						   const float* mt2,
						   const SPolygon* poly2);

#endif
