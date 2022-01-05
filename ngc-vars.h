/*
 * NIST RS274/NGC Variables
 *
 * Copyright (c) 2021 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NGC_VARS_H
#define NGC_VARS_H  1

enum ngc_var {
	NGC_INV,
	NGC_COMP,
	NGC_PLANE,
};

enum ngc_plane {
	NGC_PLANE_XY,
	NGC_PLANE_XZ,
	NGC_PLANE_YZ,
};

#endif  /* NGC_VARS_H */
