/*
 *  TransformMatrix.h
 *  GL
 *
 *  Created by Sonny Karlsson on 3/23/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#ifndef MATRIXOPS
#define MATRIXOPS

#include "VectorTypes.h"

static const float IDENTITY_MATRIX[16] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

#ifdef __ARM_NEON__
// Include symbols from matrix_ops.s
extern void load_m0_neon(const float m[16]);
extern void load_m1_neon(const float m[16]);
extern void load_d0_neon(const float m[16]);

extern void store_m0_neon(float m[16]);
extern void store_m1_neon(float m[16]);
extern void store_d0_neon(float m[16]);

extern void move_d0_m0_neon(void);
extern void move_d0_m1_neon(void);

extern void transpose_m0_neon(void);
extern void multm4m4_neon(void);

#define multm4x4(d0, m0, m1) {\
	load_m0_neon(m0);         \
	load_m1_neon(m1);         \
	multm4m4_neon();          \
	store_d0_neon(d0);        \
}

#define transposem4x4(m0) {\
	load_m0_neon(m0);      \
	transpose_m0_neon();   \
	store_m0_neon(m0);	   \
}

#else

void multm4x4_c(float d0[16], const float m0[16], const float m1[16]);
void transposem4x4_c(float m0[16]);

#define multm4x4(d0, m0, m1) multm4x4_c(d0, m0, m1);

#define transposem4x4(m0) transposem4x4_c(m0);

#endif


// Constructor functions.
// Identity matrix.
void squareIdentity(float matrix[16], const int n);

// Generate rotation matrix.
void rotationMatrix(float matrix[16], const int n, const float rad);

// Manipulation functions.
// Apply translation.
void translate(float matrix[16], const float x, const float y);

// Apply scale.
void scale(float matrix[16], const float xs, const float ys, const float zs, const float s);

// Apply rotation.
void rotate(float matrix[16], const float rad);

// Matrix transpose.
// Access functions.
// Get position from matrix.
Vector2 getTranslation(const float matrix[16]);

// Get scale from matrix.
Vector2 getScale(const float matrix[16]);

// Get rotation from matrix.
float getRotation(const float trans[16]);

// Vector length.
float vlength(const float* v, const int n);

#endif