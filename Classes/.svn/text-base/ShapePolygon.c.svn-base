
#include "ShapePolygon.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "MatrixOps.h"
#include "VectorOps.h"
#include "Collision.h"
#include "DrawData.h"
#include "RigidBody.h"

/*
 * Return length of longest vector in array.
 * Loops over all vector and update longest each time one further from origo is found.
 */
float maxVectorLength(const float* vectors, const int vectorSize, const int length)
{
	float max = 0.0f;
	for (int i = 0; i < length; i += vectorSize) {
		const float d = v2length(v2conv(vectors + i));
		if (d > max)
			max = d;
	}
	return max;
}

/*
 *Calculates and returns the tris that divide a shape poly into only tris.
 */
/*TODO: check that the tri is valid in order to be able to use concave polys*/

float* triangulatePolygon(const float* hullEdges, const int pointSize, const int hullLength)
{
    //removed array is meant to keep track of all vertices in the hull that are already "removed" while doing triangulation
    int *removed = calloc(hullLength, sizeof(int));
    //indexesOfNewTri is supposed to store the index in hullEdges/pointSize where the 3 vertices are stored.
    int indexesOfNewTri[3] = {0,0,0};
    
    //initial value 3 because there will be 3 vertices left when triangulation is done.
    int totalRemoved = 2;
    
    //tris created
    float *newTris = malloc(sizeof(float) * pointSize * numberOfVertices(hullLength));
    int index = 0;
    
    while(totalRemoved < hullLength){
        float currentShortestDistance = INFINITY;
        int indexToBeRemoved = 0;
        
        //loop over all 
        for(int i = 0; i < hullLength; i++) {
            //check that the start vertex is not yet excluded.
            if(removed[i] != 1){
                int indexMid = (i + 1) % hullLength;
                //find the middle vertex
                while(removed[indexMid] == 1){
                    indexMid = (indexMid + 1) % hullLength;
                }
                
                int indexEnd = (indexMid + 1) % hullLength;
                //find the end vertex
                while(removed[indexEnd] == 1){
                    indexEnd = (indexEnd + 1) % hullLength;
                }
                
                //create the vertices to check distance between
                Vector2 start,mid,end;
                start.x = hullEdges[i * pointSize];
                start.y = hullEdges[i * pointSize + 1];
                mid.x = hullEdges[indexMid * pointSize];
                mid.y = hullEdges[indexMid * pointSize +1];
                end.x = hullEdges[indexEnd * pointSize];
                end.y = hullEdges[indexEnd * pointSize + 1];
                
                //only check if it is shortest distance if the tri is valid.
                if(checkValidTri(&start, &mid, &end)){
                    //check if this is the shortest distance so far.
                    float temp = v2length(v2sub(start, end));
                    if(temp < currentShortestDistance){
                        currentShortestDistance = temp;
                        indexToBeRemoved = indexMid;
                        indexesOfNewTri[0] = i;
                        indexesOfNewTri[1] = indexMid;
                        indexesOfNewTri[2] = indexEnd;
                    }
                }
            }
        }
        //indexToBeRemoved is the index of the vertex that will be excluded on next pass
        removed[indexToBeRemoved] = 1;
        totalRemoved++;
		
		//add all the floats of the vertices that the tri consist of.
        for(int i = 0; i < 3; i++){
            memcpy(newTris + index, hullEdges + indexesOfNewTri[i] * pointSize, pointSize * sizeof(float));
            index += pointSize;
        }
    }
	
	free(removed);
    
    return newTris;
}

/*
 * Check that a edge between 2 vertices is within the polygon body.
 * returns 1 when valid and 0 when not valid.
 */
int checkValidTri(const Vector2* start, const Vector2* mid , const Vector2* end)
{
    Vector2 edge = v2sub(*start, *end);
    Vector2 normal = v2ortogonal(edge);
    
    return v2dot(*mid, normal) > 0.0;
}

//when triangulation is done a float* with numberOfVertices will be returned
int numberOfVertices(int hullLength)
{
    //3 vertices per tri, a shape will be divided into hullLength-3+1 tris
    return 3 * (hullLength - 3 + 1);
}

/* This is obviously not a good initFunction. It can only create boring rectangles.
 * Imagening prototype like this:
 * SPolygon* initPolygon(const SPolygon* template_poly) 
 */

SShape* initPolygon(SShape* shape,
                 const float* hullEdges, 
                 const unsigned int size,
                 const unsigned int length)
{    	
	const SPolygon poly = {
		.type             = POLYGON,
		.radius           = maxVectorLength(hullEdges, size, length),
		.pointSize        = size,
		.hullEdges        = hullEdges,
		.hullLength       = length,
        .transShapeToBody = malloc(16 * sizeof(float)),
	};
    memcpy(poly.transShapeToBody, IDENTITY_MATRIX, 16 * sizeof(float));
    memcpy(shape, &poly, sizeof(poly));
    return shape;
}

/* Level 1 collision check on poly and circle.
 * Check if poly and circle are close enought to collide.
 */
int checkPolygonCircle(const float mt1[16], const SPolygon* poly, 
					   const float mt2[16], const SCircle* circle)
{
	const Vector2 a = v2add(mulv4m4x4(EMPTY_POINT, mt1), mulv4m4x4(EMPTY_POINT, poly->transShapeToBody));
	const Vector2 b = v2add(mulv4m4x4(EMPTY_POINT, mt2), circle->position);
    
	return distanceCircleToCircle(a, poly->radius, b, circle->radius) > 0.0f;
}

/* Level 1 collision check on poly1 and poly2.
 * Check if poly1 and poly2 are close enought to collide.
 */
int checkPolygonPolygon(const float* restrict mt1, const SPolygon* poly1, 
						const float* restrict mt2, const SPolygon* poly2)
{
	const Vector2 a = v2add(mulv4m4x4(EMPTY_POINT, mt1), mulv4m4x4(EMPTY_POINT, poly1->transShapeToBody));
	const Vector2 b = v2add(mulv4m4x4(EMPTY_POINT, mt2), mulv4m4x4(EMPTY_POINT, poly2->transShapeToBody));
	
	return distanceCircleToCircle(a, poly1->radius, b, poly2->radius) > 0.0f;
}

/* Level 1 collision check on poly and point.
 * Check point is within poly's radius.
 */
int checkPolygonPoint(const float* restrict mt1, const SPolygon* poly, const Vector2 p)
{
	const Vector2 a = v2add(mulv4m4x4(EMPTY_POINT, mt1), mulv4m4x4(EMPTY_POINT, poly->transShapeToBody));
	
	return v2length(v2sub(a, p)) > poly->radius;
}

/* Generate all contacts between polygon and circle.
 * Variables:
 * m:       Poly transformation matrix.
 * a:       circle translation.
 * b, c:    circle point closet to edge.
 * r:       poly hull edges.
 * e, f, d: edge points.
 * s:       Size of point.
 * p:       Contact point.
 * cn:      Contact normal.
 * cp:      Contact penetration.
 * cn:      Contact normal.
 * 
 * Arguments:
 * pointFunc: Function to execute for each contact point.
 * mt1:       poly body's translation matrix.
 * mt2:       circle body's translation matrix.
 * 
 * Function:
 * Take vector from circle center to point in circle shell
 * closest to edge and test intersection with edge.
 *
 * Note: Assuming counter clockwise ordering of hull edges when calculating cn.
 * Note: Collision test only performed in two first dimensions.
 */
void contactPolygonCircle(ContactPointFunc pointFunc,
						  const float* restrict mt1, 
						  const SPolygon* poly, 
						  const float* restrict mt2, 
						  const SCircle* circle)
{	
	assert(mt1    != NULL);
	assert(mt2    != NULL);
	assert(poly   != NULL);
	assert(circle != NULL);
    
	const float* restrict r    = poly->hullEdges;
	const unsigned int rLength = poly->hullLength;
	const unsigned int s       = poly->pointSize;
	
	if ( ! (rLength > 0))
		return;
	
	float m[16];
	multm4x4(m, mt1, poly->transShapeToBody);

	const Vector2 a  = v2add(mulv4m4x4(EMPTY_POINT, mt2), circle->position);
	Vector2 d        = mulv2m4x4(r + s * (rLength - 1), m);
	
	for (int i = 0; i < rLength * s; i+=s) {
		const Vector2 e  = mulv2m4x4(r + i, m);
		const Vector2 cn = v2ortogonal(v2normalize(v2sub(e, d)));
		const Vector2 b  = v2add(a, v2scale(cn, -circle->radius));
		
		const Vector2 p  = lineIntersection(a, b, d, e);
		
		if (p.x != INFINITY && p.y != INFINITY) {
			const float cp = v2dot(v2sub(p, b), cn);
			(*pointFunc)(p, cn, cp);
		}
		d = e;
	}
}

/* Generate all contacts between polygons.
 * Valiables:
 * m1:         poly1 translation matrix.
 * m2:         poly2 translation matrix.
 * c:          poly1 hull edges.
 * d:          poly2 hull edges.
 * e, f, g, h: Points of first and second edge.
 * p:          Contact point.
 * cn:         Contact normal.
 * cp:         Contact penetration.
 * n:          Contact index.
 *
 * Arguments:
 * pointFunc: Function to execute for each contact point.
 * mt1:       poly1 body's translation matrix.
 * mt2:       poly2 body's translation matrix.
 *
 * Function:
 * For every edge in poly1 hull, test for edge intersection with poly2's hull.
 * 
 * Note: Assuming counter clockwise ordering of hull edges when calculating cn.
 * Note: Collision test only performed in two first dimensions.
 */
void contactPolygonPolygon(ContactPointFunc pointFunc, 
						  const float* restrict mt1,
						  const SPolygon* poly1, 
						  const float* restrict mt2,
						  const SPolygon* poly2)
{
	assert(mt1   != NULL);
	assert(mt2   != NULL);
	assert(poly1 != NULL);
	assert(poly2 != NULL);
	
	const unsigned int cLength = poly1->hullLength;
	const unsigned int dLength = poly2->hullLength;
	
	if ( ! (cLength > 0 && dLength > 0))
		return;
	
	const float* restrict c = poly1->hullEdges;
	const float* restrict d = poly2->hullEdges;
	
	assert(c != NULL);
	assert(d != NULL);
	
	const unsigned int s = poly1->pointSize;
	const unsigned int t = poly2->pointSize;
	
	assert(s > 0);
	assert(t > 0);

	float m1[16];
	float m2[16];
	
	multm4x4(m1, mt1, poly1->transShapeToBody);
	multm4x4(m2, mt2, poly2->transShapeToBody);
		
	Vector2 e = mulv2m4x4(c + s * (cLength - 1), m1);
	
	for (int i = 0; i < cLength * s; i+=s) {
		const Vector2 f  = mulv2m4x4(c + i, m1);
		const Vector2 cn = v2ortogonal(v2normalize(v2sub(f, e)));
		
		Vector2 g = mulv2m4x4(d + t * (dLength - 1), m2);
        
		for (int j = 0; j < dLength * t; j+=t) {
			const Vector2 h = mulv2m4x4(d + j, m2);
			const Vector2 p = lineIntersection(e, f, g, h);
			
			if (p.x != INFINITY && p.y != INFINITY) {
				float cp = v2dot(v2sub(g, p), cn);
				if (cp > 0.0) 
					cp = v2dot(v2sub(h, p), cn);
                (*pointFunc)(p, cn, cp);
            }
			g = h;
		}
		e = f;
	}
}

int scalePolygon(SPolygon* poly, const float xs, const float ys, const float zs, const float s)
{
	scale(poly->transShapeToBody, xs, ys, zs, s);
	return 1;
}

int movePolygon(SPolygon* poly, const float x, const float y) 
{
	translate(poly->transShapeToBody, x, y);
	return 1;
}

int rotatePolygon(SPolygon* poly, const float rad)
{
	rotate(poly->transShapeToBody, rad);
	return 1;
}
