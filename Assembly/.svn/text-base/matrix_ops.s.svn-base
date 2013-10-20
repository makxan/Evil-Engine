
#ifdef __ARM_NEON__
		@ Setup file code type and alignment.
		.thumb
        .align  2

        .globl          _load_m0_neon
        .private_extern _load_m0_neon
        .thumb_func     _load_m0_neon
        @ Load m0 matrix into NEON registers.
        @ { q12-q15 } = m0
_load_m0_neon:
        vldmia  r0, { q0 - q3 }
        mov		pc, lr

        .globl          _load_m1_neon
        .private_extern _load_m1_neon
        .thumb_func     _load_m1_neon
        @ Load m1 matrix into NEON registers.
        @ { q18-q11 } = m1
_load_m1_neon:
        vldmia  r0, { q8 - q11 }
        mov		pc, lr

        .globl          _load_d0_neon
        .private_extern _load_d0_neon
        .thumb_func     _load_d0_neon
        @ Load d0 matrix into NEON registers.
        @ { q0 - q3 } = d0
_load_d0_neon:
        vldmia  r0, { q12 - q15 }
        mov		pc, lr

		.globl          _store_m0_neon
        .private_extern _store_m0_neon
        .thumb_func     _store_m0_neon
        @ Store matrix from NEON registers.
_store_m0_neon:
        vstmia  r0, { q0 - q3 }
		mov		pc, lr

        .globl          _store_m1_neon
        .private_extern _store_m1_neon
        .thumb_func     _store_m1_neon
        @ Store matrix from NEON registers.
_store_m1_neon:
        vstmia  r0, { q8 - q11 }
		mov		pc, lr

        .globl          _store_d0_neon
        .private_extern _store_d0_neon
        .thumb_func     _store_d0_neon
        @ Store matrix from NEON registers.
_store_d0_neon:
        vstmia  r0, { q12 - q15 }
		mov		pc, lr

		.globl          _move_d0_m0_neon
		.private_extern _move_d0_m0_neon
		.thumb_func     _move_d0_m0_neon
		@ Move d0 data into m0 registers.
_move_d0_m0_neon:
		vmov	q0, q12
		vmov	q1, q13
		vmov	q2, q14
		vmov	q3, q15
		mov		pc,  lr

		.globl          _move_d0_m1_neon
		.private_extern _move_d0_m1_neon
		.thumb_func     _move_d0_m1_neon
		@ Move d0 data into m1 registers.
_move_d0_m1_neon:
		vmov	q8,  q12
		vmov	q9,  q13
		vmov	q10, q14
		vmov	q11, q15
		mov		pc,  lr

        .globl          _transpose_m0_neon
        .private_extern _transpose_m0_neon
        .thumb_func     _transpose_m0_neon
        @ Transpose m0 in { q0 - q3 } registers.
        @ m0 = m0^T
_transpose_m0_neon:
        @ Transpose internal matrices.
        vtrn.32 q0, q1
        vtrn.32 q2, q3
        @ Swap snd and thrd internal matrices.
        vswp    d1, d4
        vswp    d3, d6
        mov		pc, lr

        .globl          _multm4m4_neon
        .private_extern _multm4m4_neon
        .thumb_func     _multm4m4_neon
        @ Matrix multiplication
        @ m0 in {q0-q3},  column major
		@ m1 in {q8-q11}, column major
        @ Resulting matrix in d0 {q12-q15}
        @ d0 = m0 * m1
        @ Rows of m0 is multiplied by columns in m1.
_multm4m4_neon:
        @ Multiply fst row of m0 with fst column of m1.
        vmul.f32    q12, q8, d0[0]
        vmul.f32    q13, q8, d2[0]
        vmul.f32    q14, q8, d4[0]
        vmul.f32    q15, q8, d6[0]
        @ Multiply snd row of m0 with snd column of m1.
        vmla.f32    q12, q9, d0[1]
        vmla.f32    q13, q9, d2[1]
        vmla.f32    q14, q9, d4[1]
        vmla.f32    q15, q9, d6[1]
        @ Multiply trd row of m0 with trd column of m1.
        vmla.f32    q12, q10, d1[0]
        vmla.f32    q13, q10, d3[0]
        vmla.f32    q14, q10, d5[0]
        vmla.f32    q15, q10, d7[0]
        @ Multiply fth row of m0 with fth column of m1.
        vmla.f32    q12, q11, d1[1]
        vmla.f32    q13, q11, d3[1]
        vmla.f32    q14, q11, d5[1]
        vmla.f32    q15, q11, d7[1]
        mov			pc, lr
#endif