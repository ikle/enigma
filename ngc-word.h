/*
 * NIST RS274/NGC Words
 *
 * Copyright (c) 2021 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NGC_WORD_H
#define NGC_WORD_H  1

enum ngc_word {
	NGC_A		= 1 << 0,
	NGC_B		= 1 << 1,
	NGC_C		= 1 << 2,
	NGC_D		= 1 << 3,
	NGC_E		= 1 << 4,
	NGC_F		= 1 << 5,
	NGC_G		= 1 << 6,
	NGC_H		= 1 << 7,
	NGC_I		= 1 << 8,
	NGC_J		= 1 << 9,
	NGC_K		= 1 << 10,
	NGC_L		= 1 << 11,
	NGC_M		= 1 << 12,
	NGC_N		= 1 << 13,
	NGC_O		= 1 << 14,
	NGC_P		= 1 << 15,
	NGC_Q		= 1 << 16,
	NGC_R		= 1 << 17,
	NGC_S		= 1 << 18,
	NGC_T		= 1 << 19,
	NGC_U		= 1 << 20,
	NGC_V		= 1 << 21,
	NGC_W		= 1 << 22,
	NGC_X		= 1 << 23,
	NGC_Y		= 1 << 24,
	NGC_Z		= 1 << 25,

	NGC_ABC		= NGC_A | NGC_B | NGC_C,
	NGC_XYZ		= NGC_X | NGC_Y | NGC_Z,
	NGC_AXIS	= NGC_XYZ | NGC_ABC,

	NGC_XY		= NGC_X | NGC_Y,
	NGC_XZ		= NGC_X | NGC_Z,
	NGC_YZ		= NGC_Y | NGC_Z,

	NGC_IJ		= NGC_I | NGC_J,
	NGC_IK		= NGC_I | NGC_K,
	NGC_JK		= NGC_J | NGC_K,
};

#endif  /* NGC_WORD_H */
