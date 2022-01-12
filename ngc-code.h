/*
 * NIST RS274/NGC Command Codes
 *
 * Copyright (c) 2021-2022 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NGC_CODE_H
#define NGC_CODE_H  1

#include "ngc-gcode.h"
#include "ngc-mcode.h"

enum ngc_group {
	NGC_G0 = 0,
	NGC_G1,
	NGC_G2,
	NGC_G3,
	NGC_G5,
	NGC_G6,
	NGC_G7,
	NGC_G8,
	NGC_G10,
	NGC_G12,
	NGC_G13,

	NGC_M4,
	NGC_M6,
	NGC_M7,
	NGC_M8,
	NGC_M9,

	NGC_GSIZE,
};

#endif  /* NGC_CODE_H */
