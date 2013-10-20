//
//  CollisionTests.m
//  GL
//
//  Created by Sonny Karlsson on 2/20/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "CollisionTests.h"
#import "CollisionDetection.h"
#import <Accelerate/Accelerate.h>

static const Point2 point0 = { 0.0f,  0.0f};
static const Point2 point1 = { 1.0f,  1.0f};
static const Point2 point2 = { 1.0f, -1.0f};
static const Point2 point3 = {-1.0f,  1.0f};
static const Point2 point4 = {-1.0f, -1.0f};
static const Point2 point5 = {57.0f, 57.0f};
static const Point2 point6 = { 5.0f,  5.0f};

static const Vector2 normal0 = { 1.0f,  0.0f};
static const Vector2 normal1 = { 0.0f,  1.0f};
static const Vector2 normal2 = {-1.0f,  0.0f};
static const Vector2 normal3 = { 0.0f, -1.0f};

@implementation CollisionTests

- (void) testDataStructSize {
	// This is necesarry for some optimizations.
	STAssertTrue(sizeof(SShape) == sizeof(float), @"shape size differ, should add padding");
}

- (void) testPointCollisions {
	
	// Create Rectangle and Plane
	Vector2 normal4 = { 1.0f,  1.0f};
	vector2Normalize(&(normal4));
	
	const SPlane plane0   = {PLANE, normal0, 1.0f};
	const SPlane plane1   = {PLANE, normal1, 1.0f};
	const SPlane plane2   = {PLANE, normal2, 1.0f};
	const SPlane plane3   = {PLANE, normal3, 1.0f};
	const SPlane plane4   = {PLANE, normal4, 1.0f};
	
	const SRectangle rect = {RECTANGLE, {plane0, plane1, plane2, plane3}};
	
	
	// Create triangle
	Vector2 normal5 = {0.0f, 1.0f};
	Vector2 normal6 = normal5;
	Vector2 normal7 = normal6;
	
	vector2RotateUsingRadians(&normal6, -2.0 * M_PI / 3.0);
	vector2RotateUsingRadians(&normal7, -4.0 * M_PI /3.0);
	
	vector2Normalize(&normal6);
	vector2Normalize(&normal7);
	
	const SPlane plane5 = {PLANE, normal5, 1.0f};
	const SPlane plane6 = {PLANE, normal6, 1.0f};
	const SPlane plane7 = {PLANE, normal7, 1.0f};
	
	const STriangle triangle = {TRIANGLE,{plane5, plane6, plane7}};
	
	
	// Create circle
	const SCircle circle  = {CIRCLE, point0, 2.0f};


	STAssertTrue(pointWithPlane(&point0, &plane0), @"point0 with plane0.");
	STAssertTrue(pointWithPlane(&point0, &plane1), @"point0 with plane1.");
	STAssertTrue(pointWithPlane(&point0, &plane2), @"point0 with plane2.");
	STAssertTrue(pointWithPlane(&point0, &plane3), @"point0 with plane3.");
	STAssertTrue(pointWithPlane(&point0, &plane4), @"point0 with plane3.");
	
	STAssertTrue(pointWithCircle(&point0, &circle), @"point0 with circle failed.");
	STAssertFalse(pointWithRectangle(&point5, &rect), @"point0 with rectangle.");	

	STAssertFalse(pointWithCircle(&point5, &circle), @"false point5 with circle.");
	STAssertFalse(pointWithPlane(&point5, &plane0), @"false point5 with plane0.");
	STAssertFalse(pointWithPlane(&point5, &plane1), @"false point5 with plane1.");
	STAssertFalse(pointWithPlane(&point5, &plane4), @"false point5 with plane3.");
	STAssertFalse(pointWithRectangle(&point5, &rect), @"false point5 with rectangle.");	
	
	STAssertTrue(pointWithTriangle(&point0, &triangle),@"Point0 with triangle"); // Point inside triangle
	STAssertFalse(pointWithTriangle(&point5, &triangle),@"Point5 with triangle"); // Point far away from triangle
}


- (void) testTriangleOrigo {
	Vector2 norm0 = {1,0};
	Vector2 norm1 = {1,0};
	Vector2 norm2 = {1,0};
	
	const SPlane plane0 = {PLANE, norm0, 1.0f};
	vector2RotateUsingRadians(&norm1, 2*M_PI/3);
	const SPlane plane1 = {PLANE, norm1, 1.0f};
	vector2RotateUsingRadians(&norm2, 4*M_PI/3);
	const SPlane plane2 = {PLANE, norm2, 1.0f};
	
	const STriangle tri = {TRIANGLE, {plane0,plane1,plane2}};
	
	Point2 middle = middleOfTriangle(&tri);
	STAssertTrue(0 + middle.x < 0.000001f &&  0 + middle.y < 0.000001f, @"wrong middle point %f,%f", middle.x,middle.y);
}

- (void) testCircleCollisions {
	// Create a triangle
	Vector2 normal5 = {0.0f,1.0f};
	Vector2 normal6 = normal5;
	Vector2 normal7 = normal5;
	
	vector2RotateUsingRadians(&normal5, -2.0 * M_PI / 3.0);
	vector2RotateUsingRadians(&normal6, -4.0 * M_PI / 3.0);
	
	vector2Normalize(&normal5);
	vector2Normalize(&normal6);
	
	const SPlane plane5 = {PLANE, normal5, 1.0f};
	const SPlane plane6 = {PLANE, normal6, 1.0f};
	const SPlane plane7 = {PLANE, normal7, 1.0f};
	
	const STriangle triangle = {TRIANGLE,{plane5,plane6,plane7}};
	
	// Create plane
	Vector2 normal4 = { 0.5f,  0.5f};
	vector2Normalize(&normal4);
	const SPlane plane4   = {PLANE, normal4, 1.0f};
	
	// Create rectangle
	const SPlane plane0   = {PLANE, normal0, 1.0f};
	const SPlane plane1   = {PLANE, normal1, 1.0f};
	const SPlane plane2   = {PLANE, normal2, 1.0f};
	const SPlane plane3   = {PLANE, normal3, 1.0f};

	const SRectangle rect1 = {RECTANGLE, {plane0, plane1, plane2, plane3}};
	const SRectangle rect2 = {RECTANGLE, {plane0, plane1, plane2, plane3}};

	// Create circles
	const SCircle circle1  = {CIRCLE, point0, 10.0f};
	const SCircle circle2  = {CIRCLE, point5,  1.0f};
	const SCircle circle3  = {CIRCLE, point6,  1.0f};
	const SCircle circle4 = {CIRCLE, point0, 0.5f};
	const SCircle circle5 = {CIRCLE, point1, 0.5f};
	
	STAssertFalse(circleWithCircle(&circle1, &circle2), @"circle1 with circle2");
	STAssertTrue(circleWithCircle(&circle1, &circle3), @"circle1 with circle3");
	STAssertFalse(circleWithCircle(&circle2, &circle3), @"fales circle2 with circle3");
	
	STAssertTrue(circleWithRectangle(&circle1, &rect1), @"circle1 with rect1");

	STAssertTrue(circleWithRectangle(&circle1, &rect2), @"circle1 with rect2");
	STAssertFalse(circleWithRectangle(&circle2, &rect2), @"circle2 with rect2");
	
	STAssertTrue(circleWithPlane(&circle1, &plane4), @"circle1 with plane4");
	STAssertFalse(circleWithPlane(&circle3, &plane4), @"circle3 with plane4");
	
	// Tringle inside circle, should collide
	STAssertTrue(circleWithTriangle(&circle1, &triangle), @"circle1 with triangle");
	
	// Circle far away from triangle, should not collide
	STAssertFalse(circleWithTriangle(&circle2, &triangle), @"Circle2 with triangle");
	
	// Circle inside triangle, should collide
	STAssertTrue(circleWithTriangle(&circle4, &triangle), @"Circle3 with triangle");
	
	// Circle partly inside triangle, should collide
	STAssertTrue(circleWithTriangle(&circle5, &triangle), @"Circle4 with triangle");
	
}


- (void) testRectangleCollisions {
	
	const SPlane plane0   = {PLANE, normal0, 1.0f};
	const SPlane plane1   = {PLANE, normal1, 1.0f};
	const SPlane plane2   = {PLANE, normal2, 1.0f};
	const SPlane plane3   = {PLANE, normal3, 1.0f};

	const SPlane plane4   = {PLANE, normal0, 0.5f};
	const SPlane plane5   = {PLANE, normal1, 0.5f};
	const SPlane plane6   = {PLANE, normal2, 0.5f};
	const SPlane plane7   = {PLANE, normal3, 0.5f};
	
	SRectangle rect1 = {RECTANGLE, {plane0, plane1, plane2, plane3}};
	SRectangle rect2 = {RECTANGLE, {plane4, plane5, plane6, plane7}};
	SRectangle rect3 = {RECTANGLE, {plane0, plane1, plane2, plane3}};
	moveRectangle(&rect3, &point5);
	
	// Something is up with these.
	STAssertTrue(rectangleWithRectangle(&rect1, &rect2), @"Arect1 with rect2");
	STAssertTrue(rectangleWithRectangle(&rect2, &rect1), @"Brect2 with rect1");
	
	// Smothing is up with this one too. 
	STAssertFalse(rectangleWithRectangle(&rect1, &rect3), @"false rect1 with rect3");
	
}

- (void) testRectangleOperations {
	
	const SPlane plane0   = {PLANE, normal0, 1.0f};
	const SPlane plane1   = {PLANE, normal1, 1.0f};
	const SPlane plane2   = {PLANE, normal2, 1.0f};
	const SPlane plane3   = {PLANE, normal3, 1.0f};
	SRectangle rect1 = {RECTANGLE, {plane0, plane1, plane2, plane3}};
	
	moveRectangle(&rect1, &point5);
		
	const Point2 pointA = middleOfRectangle(&rect1);
	STAssertTrue(pointA.x == 57.0f && pointA.y == 57.0f, @"center point test 1 %f %f", pointA.x, pointA.y); 

	Vector2 normal4 = { 0.5f,  0.5f};
	Vector2 normal5 = { 0.5f, -0.5f};
	Vector2 normal6 = {-0.5f,  0.5f};
	Vector2 normal7 = {-0.5f, -0.5f};
	vector2Normalize(&normal4);
	vector2Normalize(&normal5);
	vector2Normalize(&normal6);
	vector2Normalize(&normal7);
	const SPlane plane4   = {PLANE, normal4, 1.0f};
	const SPlane plane5   = {PLANE, normal5, 1.0f};
	const SPlane plane6   = {PLANE, normal6, 1.0f};
	const SPlane plane7   = {PLANE, normal7, 1.0f};
	
	const SRectangle rect2 = {RECTANGLE, {plane4, plane5, plane6, plane7}};
	
	const Point2 pointB = middleOfRectangle(&rect2);
	STAssertTrue(pointB.x == 0.0f && pointB.y == 0.0f, @"center point test 2 %f %f", pointB.x, pointB.y);
}

- (void) testMoveRectangle {
	
	const SPlane plane0   = {PLANE, normal0, 1.0f};
	const SPlane plane1   = {PLANE, normal1, 1.0f};
	const SPlane plane2   = {PLANE, normal2, 1.0f};
	const SPlane plane3   = {PLANE, normal3, 1.0f};
	SRectangle rect1 = {RECTANGLE, {plane0, plane1, plane2, plane3}};
	
	moveRectangle(&rect1, &point5);
		
	const Point2 newPosition = middleOfRectangle(&rect1);	
	
	float diffX = newPosition.x - point5.x;
	float diffY = newPosition.y - point5.y;
	
	STAssertTrue(diffX < 0.0001f && diffY < 0.0001f, @"not close enough. old pos is %f %f", newPosition.x, newPosition.y);
	
}

- (void) testMoveAndMiddleOfTriangle {
	Vector2 normal4 = { 0.0f,1.0f};
	Vector2 normal5 = normal4;
	Vector2 normal6 = normal4;
	
	vector2RotateUsingRadians(&normal5, - 2.0 * M_PI / 3.0);
	vector2RotateUsingRadians(&normal6, - 4.0 * M_PI / 3.0);

	vector2Normalize(&normal5);
	vector2Normalize(&normal6);
	
	const SPlane plane0   = {PLANE, normal4, 1.0f};
	const SPlane plane1   = {PLANE, normal5, 1.0f};
	const SPlane plane2   = {PLANE, normal6, 1.0f};
	
	STriangle triangle = {TRIANGLE, {plane0, plane1, plane2}};

	Point2 oldPosition = middleOfTriangle(&triangle);
	
	float diffX = oldPosition.x - point0.x;
	float diffY = oldPosition.y - point0.y;
	
	STAssertTrue(diffX < 0.0001f && diffY < 0.0001f, @"not close enough. old pos is %f %f", oldPosition.x, oldPosition.y);
	
	moveTriangle(&triangle, &point5);
	Point2 newPosition = middleOfTriangle(&triangle);
	
	diffX = newPosition.x - point5.x;
	diffY = newPosition.y - point5.y;
	
	STAssertTrue(diffX < 0.0001f && diffY < 0.0001f, @"not close enough. new pos is %f %f", newPosition.x, newPosition.y);

}

- (void) testCornersOfTriangle {
	
	Vector2 normal4 = { 0.0f,1.0f};
	Vector2 normal5 = normal4;
	Vector2 normal6 = normal4;
	
	vector2RotateUsingRadians(&normal5, - 2.0 * M_PI / 3.0);
	vector2RotateUsingRadians(&normal6, - 4.0 * M_PI / 3.0);
	
	vector2Normalize(&normal5);
	vector2Normalize(&normal6);
	
	const SPlane plane0   = {PLANE, normal4, 1.0f};
	const SPlane plane1   = {PLANE, normal5, 1.0f};
	const SPlane plane2   = {PLANE, normal6, 1.0f};
	
	STriangle triangle = {TRIANGLE, {plane0, plane1, plane2}};
	
	Point2 expectPoints[3];
	expectPoints[0] = (Point2){-0.866025f, 0.5f};
	expectPoints[1] = (Point2){      0.0f,-1.0f};
	expectPoints[2] = (Point2){ 0.866025f, 0.5f};
	
	Point2 points[3];
	cornersOfTriangle(points, &triangle);
	
	Point2 diffOnPoint[3];
	
	for (int i = 0; i < 3; i++) {
		diffOnPoint[i].x = expectPoints[i].x - points[i].x;
		diffOnPoint[i].y = expectPoints[i].y - points[i].y;
	}
	
	for (int i = 0; i < 3; i++) {
		//STAssertTrue(diffOnPoint[i].x < 0.00001f && diffOnPoint[i].y < 0.00001f, @"point %i diff, %f %f", i, diffOnPoint[i].x, diffOnPoint[i].y);
	}
	
}



- (void) testCornersOfRectangle {
	const SPlane plane0   = {PLANE, normal0, 1.0f};
	const SPlane plane1   = {PLANE, normal1, 1.0f};
	const SPlane plane2   = {PLANE, normal2, 1.0f};
	const SPlane plane3   = {PLANE, normal3, 1.0f};
	
	const SRectangle rectangle = {RECTANGLE, {plane0, plane1, plane2, plane3}};
	
	Point2 expectPoints[4];
	expectPoints[0] = (Point2){ 1.0f, 1.0f};
	expectPoints[1] = (Point2){-1.0f, 1.0f};
	expectPoints[2] = (Point2){-1.0f,-1.0f};
	expectPoints[3] = (Point2){ 1.0f,-1.0f};
	
	Point2 points[4];
	cornersOfRectangle(points, &rectangle);
	
	Point2 diffOnPoint[4];
	
	for (int i = 0; i < 4; i++) {
		diffOnPoint[i].x = expectPoints[i].x - points[i].x;
		diffOnPoint[i].y = expectPoints[i].y - points[i].y;
	}
	
	for (int i = 0; i < 4; i++) {
		STAssertTrue(diffOnPoint[i].x < 0.00001f && diffOnPoint[i].y < 0.00001f, @"point %i diff, %f %f", i, diffOnPoint[i].x, diffOnPoint[i].y);
	}
	
}

-(void) testTriangleCollisions {
	
	// Create a triangles
	Vector2 normal4 = {0.0f,1.0f};
	Vector2 normal5 = normal4;
	Vector2 normal6 = normal4;
	
	vector2RotateUsingRadians(&normal5, -2.0 * M_PI / 3.0);
	vector2RotateUsingRadians(&normal6, -4.0 * M_PI / 3.0);
	
	vector2Normalize(&normal5);
	vector2Normalize(&normal6);
	
	const SPlane plane0 = {PLANE, normal4, 1.0f};
	const SPlane plane1 = {PLANE, normal5, 1.0f};
	const SPlane plane2 = {PLANE, normal6, 1.0f};
	
	const STriangle triangle0 = {TRIANGLE,{plane0,plane1,plane2}};
	const STriangle triangle1 = {TRIANGLE,{plane0,plane1,plane2}};
	
	
	Vector2 normal8 = {0.0f,1.0f};
	Vector2 normal9 = normal4;
	Vector2 normal10 = normal4;
	
	vector2RotateUsingRadians(&normal9, -2.0 * M_PI / 3.0);
	vector2RotateUsingRadians(&normal10, -4.0 * M_PI / 3.0);
	
	vector2Normalize(&normal9);
	vector2Normalize(&normal10);
	
	const SPlane plane8 = {PLANE, normal8, 1.0f};
	const SPlane plane9 = {PLANE, normal9, 1.0f};
	const SPlane plane10 = {PLANE, normal10, 1.0f};
	

	STriangle triangle2 = {TRIANGLE,{plane8,plane9,plane10}};
	moveTriangle(&triangle2, &point5);
	
	// Create rectangle
	const SPlane plane3   = {PLANE, normal0, 1.0f};
	const SPlane plane4   = {PLANE, normal1, 1.0f};
	const SPlane plane5   = {PLANE, normal2, 1.0f};
	const SPlane plane6   = {PLANE, normal3, 1.0f};
	
	const SRectangle rectangle = {RECTANGLE, {plane3, plane4, plane5, plane6}};
	
	//Create plane
	Vector2 normal7 = {0.0f, 1.0f};
	vector2Normalize(&normal7);
	
	
	
	const SPlane plane7 = {PLANE, normal7, 10.0f};
	
	// Test triangle and triangle collision
	STAssertTrue(triangleWithTriangle(&triangle0, &triangle1), @"Triangle0 with triangle1"); // Inside each other, should return true
	STAssertFalse(triangleWithTriangle(&triangle0, &triangle2), @"Traingle0 with triangle2"); // Far away from each other, should return false
	
	// Test triangle and rectangle
	STAssertTrue(triangleWithRectangle(&triangle0, &rectangle), @"Triangle0 with rectangle"); // Inside each other, should return true
	STAssertFalse(triangleWithRectangle(&triangle2, &rectangle), @"Triangle2 with rectange"); // Far away from each other, should return false
	
	// Test triangle and plane
	STAssertTrue(triangleWithPlane(&triangle0, &plane7), @"Triangle0 with plane7"); // Triangle collide with plane, should return true
	STAssertFalse(triangleWithPlane(&triangle2, &plane7), @"Trangle2 with plane7"); // Triangle far away from plane, should return false
}

- (void)testPlaneIntersectionPoint {
	// Create Rectangle and Plane
	Vector2 normal4 = { 1.0f,  1.0f};
	vector2Normalize(&(normal4));
	Vector2 normal5 = normal4;
	vector2RotateUsingRadians(&normal5, M_PI/2);
	
	const SPlane plane0   = {PLANE, normal0, 1.0f};
	const SPlane plane1   = {PLANE, normal1, 1.0f};
	const SPlane plane2   = {PLANE, normal2, 1.0f};
	const SPlane plane3   = {PLANE, normal3, 1.0f};
	const SPlane plane4   = {PLANE, normal4, sqrt(2.0)};
	
	Point2 point = planeIntersectionPoint(&plane0, &plane1);
	
	STAssertTrue(point.x == 1.0 && point.y == 1.0,@"Plane0 vs plane1 %f %f", point.x, point.y);
	point = planeIntersectionPoint(&plane2, &plane3);
	
	STAssertTrue(point.x == -1.0 && point.y == -1.0,@"Plane0 vs plane1 %f %f", point.x, point.y);
	Point2 point2 = planeIntersectionPoint(&plane4, &plane2);
	
	STAssertTrue(point2.x == 1.0 && point2.y == -1.0,@"Plane0 vs plane1 %f %f", point2.x, point2.y);
}

- (void) testPass {
	STAssertTrue(TRUE, @"");
}

@end
