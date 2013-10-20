//
//  ContactTests.m
//  GL
//
//  Created by Sonny Karlsson on 2/21/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "ContactTests.h"
#import "Shape.h"
#import "CollisionContact.h"

static const Point2 point0 = { 0.0f,  0.0f};
static const Point2 point1 = { 3.0f,  0.0f};
static const Point2 point2 = { 1.0f, -1.0f};
static const Point2 point3 = {-1.0f,  1.0f};
static const Point2 point4 = {-1.0f, -1.0f};
static const Point2 point5 = {57.0f, 57.0f};
static const Point2 point6 = { 5.0f,  5.0f};

static const Vector2 normal0 = { 1.0f,  0.0f};
static const Vector2 normal1 = { 0.0f,  1.0f};
static const Vector2 normal2 = {-1.0f,  0.0f};
static const Vector2 normal3 = { 0.0f, -1.0f};
@implementation ContactTests

- (void)testPointPenetration {
	const SPlane plane0 = {PLANE, normal0, 2.0f};
	Contact contact[10];
	
	contactPointPlane(contact+0, &point0, &plane0);
	
	STAssertTrue((contact+0)->penetration == 2.0, @"Point0 penetration plane0");
	
	const SCircle circle0  = {CIRCLE, point0, 1.0f};
	contactPointCircle(contact+1, &point0, &circle0);
	
	STAssertTrue((contact+1)->penetration == 1.0 ,@"Circle1 penetrate circle0");
}

- (void)testCirclePenetration {
	const SPlane plane0 = {PLANE, normal0, 2.0f};
	
	
	const SCircle circle0 = {CIRCLE, point0, 2.0f};
	const SCircle circle1 = {CIRCLE, point1, 2.0f};
	Contact contact[10];
	
	contactCircleCircle(contact+0, &circle0, &circle1);
	
	STAssertTrue((contact+0)->penetration == 1.0, @"Circle0 penetrate circle1");
	
	contactCirclePlane(contact+1, &circle1, &plane0);
	
	STAssertTrue((contact+1)->penetration == 1.0 ,@"Circle1 penetrate plane0");
}
/* TODO: Tests for sheared rectangles*/
- (void)testRectanglePenetration {
	
	const SPlane plane0 = {PLANE, normal0, 1.0f};
	const SPlane plane1 = {PLANE, normal1, 1.0f};
	const SPlane plane2 = {PLANE, normal2, 1.0f};
	const SPlane plane3 = {PLANE, normal3, 1.0f};
	
	const SRectangle rect0 = {RECTANGLE, {plane0,plane1,plane2,plane3}};
	
	const SPlane testPlane0 = {PLANE, normal0, -0.5f};
	Contact contact;
	
	contactRectanglePlane(&contact, &rect0, &testPlane0);
	/* tests a rect round origo against a plane which is located 0.5 to the left of origo
	 * with a normal straight to the right.
	 * since the rect streches 1 to the left of origo, penetration should be 0.5
	 * this also ensures that 2-corner collision works.
	 */
	STAssertTrue(contact.penetration == 0.5f, @"test 1 penetration wrong, %f", contact.penetration);
	
	Vector2 vector = {1.0f,1.0f};
	vector2Normalize(&vector);
	const SPlane testPlane1 = {PLANE, vector, -0.01f};
	
	contactRectanglePlane(&contact, &rect0, &testPlane1);
	
	/* Tests penetration with 45 degree angled plane. 
	 */
	STAssertTrue(contact.penetration - (sqrt(2)-0.01) < 0.00001, @"test 2 penetration wrong, %f", contact.penetration);
	
	const SPlane plane4 = {PLANE, normal0, -1.5f};
	const SPlane plane5 = {PLANE, normal1, 1.0f};
	const SPlane plane6 = {PLANE, normal2, 3.5f};
	const SPlane plane7 = {PLANE, normal3, 1.0f};
	
	const SRectangle rect1 = {RECTANGLE, {plane4,plane5,plane6,plane7}};
	
	Vector2 norm0 = {1,0};
	Vector2 norm1 = {1,0};
	Vector2 norm2 = {1,0};
	SPlane triPlane0 = {PLANE, norm0, 1.0f};
	vector2RotateUsingRadians(&norm1, 2*M_PI/3);
	//triPlane0.offset = 1.0f;
	SPlane triPlane1 = {PLANE, norm1, 1.0f};
	vector2RotateUsingRadians(&norm2, 4*M_PI/3);
	//triPlane1.offset = 1.0f;
	SPlane triPlane2 = {PLANE, norm2, 1.0f};
	
	const STriangle tri0 = {TRIANGLE, {triPlane0,triPlane1,triPlane2}};
	contactRectangleTriangle(&contact, &rect1, &tri0);
	
	/* Tests that a triangle centered in origo intersects exactly 0.5 into a rect that has right side in -1.5
	 */
	STAssertTrue(contact.penetration == 0.5f, @"test 3 penetration wrong, %f", contact.penetration);
	
	const SPlane plane8 = {PLANE, normal0, 0.5f};
	const SPlane plane9 = {PLANE, normal1, 0.5f};
	const SPlane plane10 = {PLANE, normal2, 0.5f};
	const SPlane plane11 = {PLANE, normal3, 0.5f};
	
	Point2 p =  {-2.0f, 0.0f};
	SRectangle rect3 = {RECTANGLE, {plane8,plane9,plane10,plane11}};
	moveRectangle(&rect3, &p);
	
	contactRectangleTriangle(&contact, &rect3, &tri0);
	
	/* As above, but now with a rect that has been moved from origo to (-2.5,0.0), should give same result!
	 */
	STAssertTrue(contact.penetration == 0.5f, @"test 4 penetration wrong, %f", contact.penetration);
	
	Point2 p2 = {-1.0f, -0.0f};
	moveRectangle(&rect3, &p2);
	
	contactRectangleRectangle(&contact, &rect0, &rect3);
	/* Test rectangle rectangle contact, TODO: seems to be worthless for exactly the same sized rects.
	 */
	STAssertTrue(contact.penetration == 0.5f, @"test 5 penetration wrong, penetration %f", contact.penetration);

}

- (void)testTrianglePenetration {
	
	/* Tests all possible triangle-random shape contact functions. this will in turn due to hierarchical build in collisionContact
	 * test all lower level contact functions, i.e. planeTri and pointPlane.
	 */
	
	Vector2 norm0 = {1,0};
	Vector2 norm1 = {1,0};
	Vector2 norm2 = {1,0};
	SPlane triPlane0 = {PLANE, norm0, 1.0f};
	vector2RotateUsingRadians(&norm1, 2*M_PI/3);
	SPlane triPlane1 = {PLANE, norm1, 1.0f};
	vector2RotateUsingRadians(&norm2, 4*M_PI/3);
	SPlane triPlane2 = {PLANE, norm2, 1.0f};
	
	const STriangle tri0 = {TRIANGLE, {triPlane0,triPlane1,triPlane2}};
	STriangle tri1 = {TRIANGLE, {triPlane0,triPlane1,triPlane2}};
	
	Point2 p = {-0.5f,0.0f};
	moveTriangle(&tri1, &p);
	
	Contact contact;	
	
	contactTriangleTriangle(&contact, &tri0, &tri1);
	STAssertTrue(contact.penetration == 0.5f, @"Tri Test 1 failed. penetration %f",contact.penetration);
	
	/*
	 * TODO: if 2 tris (same size) collide plane against plane, aligned. one of the corners will pass the tri in 
	 * almost all cases, only case we will get 2-corner collision is when the corners are at the same positions, 
	 * otherwise one of the corners will pass the other and we will only get 1-corner collision which will result 
	 * in wierd contact normal!
	 */
	
	SCircle circle0 = {CIRCLE, point0, 1.0f};
	p.x = 1.0f;
	moveCircle(&circle0, &p);
	
	contactCircleTriangle(&contact, &circle0, &tri0);
	STAssertTrue(contact.penetration == 1.0f, @"Tri Test 2 failed. penetration %f",contact.penetration);
}

- (void)testPointContactNormal {
}

- (void)testCircleContactNormal {
}

- (void)testRectangleContactNormal {
}

- (void)testTriangleContactNormal {
}

- (void)testCircleContactPoint {
}

- (void)testRectangleContactPoint {
}

- (void)testTriangleContactPoint {
}


@end
