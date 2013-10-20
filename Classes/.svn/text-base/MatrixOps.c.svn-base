
#include "MatrixOps.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "VectorOps.h"

#ifdef __ARM_NEON__
#import <arm_neon.h>
#endif

void multm4x4_c(float d0[16], const float m1[16], const float m2[16])
{
	float temp[16];
	temp[0] = m2[0] * m1[0] + m2[4] * m1[1] + m2[8] * m1[2] + m2[12] * m1[3];
    temp[1] = m2[1] * m1[0] + m2[5] * m1[1] + m2[9] * m1[2] + m2[13] * m1[3];
    temp[2] = m2[2] * m1[0] + m2[6] * m1[1] + m2[10] * m1[2] + m2[14] * m1[3];
    temp[3] = m2[3] * m1[0] + m2[7] * m1[1] + m2[11] * m1[2] + m2[15] * m1[3];
    
    temp[4] = m2[0] * m1[4] + m2[4] * m1[5] + m2[8] * m1[6] + m2[12] * m1[7];
    temp[5] = m2[1] * m1[4] + m2[5] * m1[5] + m2[9] * m1[6] + m2[13] * m1[7];
    temp[6] = m2[2] * m1[4] + m2[6] * m1[5] + m2[10] * m1[6] + m2[14] * m1[7];
    temp[7] = m2[3] * m1[4] + m2[7] * m1[5] + m2[11] * m1[6] + m2[15] * m1[7];
    
    temp[8] = m2[0] * m1[8] + m2[4] * m1[9]  + m2[8] * m1[10] + m2[12] * m1[11];
    temp[9] = m2[1] * m1[8] + m2[5] * m1[9]  + m2[9] * m1[10] + m2[13] * m1[11];
    temp[10] = m2[2] * m1[8] + m2[6] * m1[9] + m2[10] * m1[10] + m2[14] * m1[11];
    temp[11] = m2[3] * m1[8] + m2[7] * m1[9] + m2[11] * m1[10] + m2[15] * m1[11];
    
    temp[12] = m2[0] * m1[12] + m2[4] * m1[13] + m2[8] * m1[14] + m2[12] * m1[15];
    temp[13] = m2[1] * m1[12] + m2[5] * m1[13] + m2[9] * m1[14] + m2[13] * m1[15];
    temp[14] = m2[2] * m1[12] + m2[6] * m1[13] + m2[10] * m1[14] + m2[14] * m1[15];
    temp[15] = m2[3] * m1[12] + m2[7] * m1[13] + m2[11] * m1[14] + m2[15] * m1[15];
    memcpy(d0, temp, 16 * sizeof(float));
}

void transposem4x4_c(float matrix[16])
{
	float temp;
	
	for (int n = 0; n < 3; n++) {
		
		for (int m = n + 1; m < 4; m++) {
			temp              = matrix[n + m * 4];
			matrix[n + m * 4] = matrix[n * 4 + m];
			matrix[n * 4 + m] = temp;
		}	 
	}
}

// Generate a n*n identity matrix.
void squareIdentity(float matrix[16], const int n) 
{
	if (n == 4) {
		memcpy(matrix, IDENTITY_MATRIX, sizeof(IDENTITY_MATRIX));
		return;
	}
	for (int i = 0; i < n*n; i++) {
		if (i % (n+1) == 0)
			matrix[i] = 1.0f;
		else
			matrix[i] = 0.0f;
	}
}

void rotationMatrix(float matrix[16], const int n, const float rad) 
{
	squareIdentity(matrix, 4);
	matrix[0] = matrix[5]  = cosf(rad);
	matrix[1] =  sinf(rad);	
	matrix[4] = -sinf(rad);
}


// Translate transformation matrix.
void translate(float matrix[16], const float x, const float y)
{
	matrix[12] += x;
	matrix[13] += y;
}

// Scale transformation matrix.
void scale(float matrix[16], const float xs, const float ys, const float zs, const float s)
{
    float scaling[16];
    squareIdentity(scaling, 4);
	scaling[0]  = xs;
	scaling[5]  = ys;
	scaling[10] = zs;
	scaling[15] = 1.0f/s;
    multm4x4(matrix, scaling, matrix);
}

// Manipulation of Polygo
void rotate(float matrix[16], const float rad) 
{
	float rotate[16];
	rotationMatrix(rotate, 4, rad);
	multm4x4(matrix, matrix, rotate);
}

// Position of matrix.
Vector2 getTranslation(const float matrix[16]) 
{
	return mulv2m4x4(EMPTY_POINT, matrix);
}

// Scale of transformation matrix.
// Does not care about rotation.
Vector2 getScale(const float matrix[16])
{
	const float v[4] = {1.0f, 1.0f, 0.0f, 0.0f};
	return mulv4m4x4(v, matrix);
}

// Rotation of transformation matrix.
float getRotation(const float trans[16])
{
	const float v[4] = {1.0f, 0.0f, 0.0f, 0.0f};
	return acosf(v2dot(mulv4m4x4(v, trans), v2conv(v)));
}
