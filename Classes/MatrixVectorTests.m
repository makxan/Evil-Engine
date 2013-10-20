//
//  MatrixVectorTests.m
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-21.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "MatrixVectorTests.h"
#import "Matrix.h"
#import "TransformMatrix.h"
#import <Accelerate/Accelerate.h>

static const Matrix3x3 identityMatrix = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

static const Matrix3x3 matrix1 = {
	1.0f, 3.0f, 4.0f,
	2.0f, 1.0f, 2.0f,
	5.0f, 7.0f, 1.0f
};

static const Matrix3x3 matrix1Transpose = {
	1.0f, 2.0f, 5.0f,
	3.0f, 1.0f, 7.0f,
	4.0f, 2.0f, 1.0f
};

@implementation MatrixVectorTests

- (void)testMatrixMultiplication {

	const float m0[] = {
		5.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 6.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 7.0f, 1.0f,
		5.0f, 0.0f, 0.0f, 1.0f
	};
	
	float m1[16];
	float m2[16];
	float m3[16];
	
	vDSP_mmul((float*)m0, 1, (float*)IDENTITY_MATRIX, 1, m1, 1, 4, 4, 4);
	multm4x4(m2, m0, IDENTITY_MATRIX);
	alternative_multm4x4(m3, m0, IDENTITY_MATRIX);
	
	for (int j = 0; j < 16; j++) {
		if (m1[j] != m0[j] || m2[j] != m0[j] || m3[j] != m0[j]) {
			STFail(@"Result from vDSP_mmul -- Result from multm4x4 -- Result from alternavite_multm4x4");
			for (int i = 0; i < 4; i++) {
				STFail(@"%f %f %f %f  --  %f %f %f %f -- %f %f %f %f", 
					   m1[0+i*4], m1[1+i*4], m1[2+i*4], m1[3+i*4],
					   m2[0+i*4], m2[1+i*4], m2[2+i*4], m2[3+i*4],
					   m3[0+i*4], m3[1+i*4], m3[2+i*4], m3[3+i*4]);
			}
			return;
		}
	}
}

- (void)testMatrixTranspose {
	
	Matrix3x3 lidentityMatrix;
	matrix3x3Transpose(lidentityMatrix, identityMatrix);
	
	STAssertTrue(matrix3x3Equals(lidentityMatrix, identityMatrix), @"Matrix transpose of identity");
	
	Matrix3x3 lmatrix1Transpose;
	matrix3x3Transpose(lmatrix1Transpose, matrix1);
	
	STAssertTrue(matrix3x3Equals(lmatrix1Transpose, matrix1Transpose), @"Matrix transpose of matrix1");
}

- (void)testDotProduct {

	Vector2 vec1 = (Vector2){ 1.0f,  1.0f};
	Vector2 vec2 = (Vector2){ 0.0f,  1.0f};
	Vector2 vec3 = (Vector2){-1.0f, -1.0f};
	
	Vector2 *vector1 = &vec1;
	Vector2 *vector2 = &vec2;
	Vector2 *vector3 = &vec3;
	
	vector2Normalize(vector3);
	
	float res1 = cblas_sdot(2, (const float*)vector1, 1, (const float*)vector1, 1);
	float res2 = (vector1->x*vector1->x) + (vector1->y*vector1->y);
	
	STAssertTrue(res1 == res1, @"dot product result, %f and %f", res1, res2);
	
	float res3 = cblas_sdot(2, (const float*)vector1, 1, (const float*)vector2, 1);
	float res4 = (vector1->x*vector2->x) + (vector1->y*vector2->y);

	STAssertTrue(res3 == res4, @"dot product result, %f and %f", res3, res4);
	
	float res5 = cblas_sdot(2, (const float*)vector1, 1, (const float*)vector3, 1);
	float res6 = (vector1->x*vector3->x) + (vector1->y*vector3->y);
	
	STAssertTrue(res5 == res6, @"dot product result, %f and %f", res5, res6);
		
}

- (void)testSubstract {

	Vector2 vec1;
	Vector2 vec2;
	Vector2 vec3;
	Vector2 vec4;
	
	Vector2 *vector1 = &vec1;
	Vector2 *vector2 = &vec2;
	Vector2 *vector3 = &vec3;
	
	vec1 = (Vector2){ 1.0, 1.0};
	vec2 = (Vector2){ 1.0, 1.0};
	vDSP_vsub((float *)vector1, 1, (float *)vector2, 1, (float *)vector3, 1.0, 2.0);
	vec4.x = vec1.x - vec2.x;
	vec4.y = vec1.y - vec2.y;
	vector2AddScaled(vector1, vector2, -1.0);
	STAssertTrue(vec1.x == vec3.x && 
				 vec1.y == vec3.y &&
				 vec1.x == vec4.x &&
				 vec1.y == vec4.y, 
				 @"substract test, vec1 %f %f, vec3 %f %f, vec4 %f %f", 
				 vec1.x, vec1.y, 
				 vec3.x, vec3.y,
				 vec4.x, vec4.y);
	

	vec1 = (Vector2){ 1.0, 1.0};
	vec2 = (Vector2){-1.0,-1.0};
	vDSP_vsub((float *)vector2, 1, (float *)vector1, 1, (float *)vector3, 1.0, 2.0);
	vec4.x = vec1.x - vec2.x;
	vec4.y = vec1.y - vec2.y;
	vector2AddScaled(vector1, vector2, -1.0);
	STAssertTrue(vec1.x == vec3.x && 
				 vec1.y == vec3.y &&
				 vec1.x == vec4.x &&
				 vec1.y == vec4.y, 
				 @"substract test, vec1 %f %f, vec3 %f %f, vec4 %f %f", 
				 vec1.x, vec1.y, 
				 vec3.x, vec3.y,
				 vec4.x, vec4.y);
}

@end

