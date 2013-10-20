
#include "VectorOps.h"

#include <string.h>
#include <math.h>

#ifdef __ARM_NEON__
#include <arm_neon.h>
#endif

inline Vector2 v2scale(const Vector2 v, const float s) {
	return (Vector2){v.x * s, v.y * s};
}

inline Vector2 v2neg(const Vector2 v) {
	return (Vector2){-v.x, -v.y};
}

inline Vector2 v2add(const Vector2 v1, const Vector2 v2) {
	return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

inline Vector2 v2sub(const Vector2 v1, const Vector2 v2) {
	return (Vector2){v1.x-v2.x, v1.y-v2.y};
}

// Returns a vector turned 90° counter clockwise.
inline Vector2 v2ortogonal(const Vector2 v) {
	return (Vector2){-v.y, v.x};
}

inline Vector2 v2normalize(const Vector2 v) {
	return v2scale(v, v2length(v));
}

inline float v2dot(const Vector2 v1, const Vector2 v2) {
	return (v1.x*v2.x + v1.y*v2.y);
}

inline float v2length(const Vector2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

// n-dimensional vector length.
inline float vlength(const float* v, const int n) 
{
	float l = 0.0f;
	for (int i = 0; i < n; i++)
		l += v[i] * v[i];
	return sqrtf(l);
}

inline float v2determinant(const Vector2 v1, const Vector2 v2) {
	return v1.x*v2.y - v1.y*v2.x;
}

// n-dimensional point to point distance.
inline float vdistance(const float* restrict v1, const float* restrict v2, const int n) {
	float d = 0.0f;
	for (int i = 0; i < n; i++)
		d += (v1[i] + v2[i]) * (v1[i] + v2[i]);
	return sqrtf(d);
}

// Does Vector4 `mul` Matrix4x4 and returns Vector2 result.
Vector2 mulv4m4x4(const float v[4], const float m[16])
{
	#ifdef __ARM_NEON__
	register Vector2 z __asm__ ("d0");
	__asm__ volatile
	(
     "vldmia %[vmem], { q1 }     \n\t"
     "vldmia %[mmem], { q8-q11 } \n\t"
     "vmul.f32 d0, d16, d2[0]    \n\t"
     "vmla.f32 d0, d18, d2[1]    \n\t"
     "vmla.f32 d0, d20, d3[0]    \n\t"
     "vmla.f32 d0, d22, d3[1]        "
	 :                                // Output registers.
	 : [vmem] "r" (v), [mmem] "r" (m) // Input registers.
	 : "q1", "q8", "q9", "q10", "q11" // Clobber registers.
	 );
	return z;
	#else
	const float x = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
	const float y = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
	return (Vector2){x, y};
	#endif
}

// Does Vector2 `mul` Matrix4x4 and returns Vector2 result.
Vector2 mulv2m4x4(const float v[2], const float m[16])
{
	#ifdef __ARM_NEON__
	register Vector2 z __asm__ ("d0");
	__asm__ volatile
	(
     "vldmia %[vmem], { q1 }     \n\t"
     "vldmia %[mmem], { q8-q11 } \n\t"
     "vmov.f32 d0, d22           \n\t"
     "vmla.f32 d0, d16, d2[0]    \n\t"
     "vmla.f32 d0, d18, d2[1]        "
	 :                                // Output registers.
	 : [vmem] "r" (v), [mmem] "r" (m) // Input registers.
	 : "q1", "q2", "q3", "q4", "q5"   // Clobber registers.
	 );
	return z;
	#else
	const float x = m[0] * v[0] + m[4] * v[1] + m[12];
	const float y = m[1] * v[0] + m[5] * v[1] + m[13];
	return (Vector2){x, y};
    #endif
}

inline Vector2 v2conv(const float* v) {
	return *(Vector2*)v;
}

inline float distanceCircleToCircle(const Vector2 p1, const float r1, const Vector2 p2, const float r2)
{
	return v2length(v2sub(p1, p2)) - (r1 + r2);
}

inline Vector2 lineIntersection(const Vector2 a, const Vector2 b, const Vector2 c, const Vector2 d)
{
	/*
	 * Implementation of Faster line intersection from
	 * http://portal.acm.org/citation.cfm?id=130777&CFID=16207717&CFTOKEN=47893490
	 *
	 * det = (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx);
	 * r   = (Ay-Cy)(Dx-Cx)-(Ax-Cx)(Dy-Cy);
	 * s   = (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay);
	 *     
	 
		 (Ay-Cy)(Dx-Cx)-(Ax-Cx)(Dy-Cy)
	 r = -----------------------------  (eqn 1)
		 (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx)
	 
		 (Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
	 s = -----------------------------  (eqn 2)
		 (Bx-Ax)(Dy-Cy)-(By-Ay)(Dx-Cx)
	 *
	 */
	const Vector2 e = v2sub(b, a);
	const Vector2 f = v2sub(d, c);
	
	const float det = v2determinant(e, f);
	
	//const float det = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
	
	if (det == 0.0f)
		return (Vector2){INFINITY, INFINITY}; // Parallell lines.
	
	//const float r = ((a.y - c.y) * (d.x - c.x) - (a.x - c.x) * (d.y - c.y)) / denom;	
	//const float s = ((a.y - c.y) * (b.x - a.x) - (a.x - c.x) * (b.y - a.y)) / denom;
	
	const Vector2 g = f;
	const Vector2 h = v2sub(a, c);
	
	const float r   = v2determinant(g, h);
	
	const Vector2 i = f;
	const Vector2 j = h;
	
	const float s   = v2determinant(i, j);
	
	if ((r < 0.0f) || (r > 1.0f) || (s < 0.0f) || (s > 1.0f))
		return (Vector2){INFINITY, INFINITY}; // No intersection.
	
	const float x = a.x + r * (b.x - a.x) / det;
	const float y = a.y + r * (b.y - a.y) / det;
	
	return (Vector2){x,y};
}
