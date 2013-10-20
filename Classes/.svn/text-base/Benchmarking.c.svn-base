/*
 *  Benchmarking.c
 *  GL
 *
 *  Created by Sonny Karlsson on 3/27/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#include "Benchmarking.h"

#include <stdio.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

#include "MatrixOps.h"

extern void transposem4x4_c(float matrix[16]);

void benchMatrixTranspose() 
{
	
	float m0[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};
		
	#ifdef __ARM_NEON__

	float m1[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};
	
	uint64_t t0 = mach_absolute_time();
	
	load_m0_neon(m1);
	for (int i = 0; i < 11; i++)
		transpose_m0_neon();
	store_m0_neon(m1);
	
	#endif
	
	uint64_t t1 = mach_absolute_time();
	
	for (int i = 0; i < 11; i++)
		transposem4x4_c(m0);
	
	uint64_t t2 = mach_absolute_time();
	
	printf("c_transposem4x4 time:    %lld\n", t2-t1);
	#ifdef __ARM_NEON__
	printf("neon_transposem4x4 time: %lld\n", t1-t0);
	#endif
	
	for (int i = 0; i < 4; i++) {
		printf("%.2f %.2f %.2f %.2f",    m0[0+i*4], m0[1+i*4], m0[2+i*4], m0[3+i*4]);
		#ifdef __ARM_NEON__
		printf("-- %.2f %.2f %.2f %.2f", m1[0+i*4], m1[1+i*4], m1[2+i*4], m1[3+i*4]);
		#endif
		printf("\n");
	}
	printf("\n");
	
}

extern void multm4x4_c(float m0[16], const float m1[16], const float m2[16]);
extern void multm4x4_neon(float m0[16], const float m1[16], const float m2[16]);

void benchMatrixMultiply() {
	
	const float m0[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};
	
	float m2[16];

	#ifdef __ARM_NEON__
	float m1[16];
	
	uint64_t t0 = mach_absolute_time();
	
	load_m0_neon(m0);
	load_m1_neon(m1);
	for (int i = 0; i < 11; i++) {
		multm4m4_neon();
		move_d0_m1_neon();
	}
	store_d0_neon(m1);
	
	#endif
	
	uint64_t t1 = mach_absolute_time();
	
	for (int i = 0; i < 11; i++)
		multm4x4_c(m2, m0, m2);
	
	uint64_t t2 = mach_absolute_time();

	
	printf("c_multm4x4 time:          %llu\n", t2-t1);
	#ifdef __ARM_NEON__
	printf("neon_multm4x4 time:       %llu\n", t1-t0);
	printf("Result from neon_multm4x4 -- Result from c_multm4x4\n");
	#else
	printf("Result from c_multm4x4\n");
	#endif
	for (int i = 0; i < 4; i++) {
		#ifdef __ARM_NEON__
		printf("%.2f %.2f %.2f %.2f -- ", m1[0+i*4], m1[1+i*4], m1[2+i*4], m1[3+i*4]);
		#endif
		printf("%.2f %.2f %.2f %.2f\n", m2[0+i*4], m2[1+i*4], m2[2+i*4], m2[3+i*4]);
	}
}
