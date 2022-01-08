/*
 * NIST RS274/NGC State
 *
 * Copyright (c) 2021 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NGC_STATE_H
#define NGC_STATE_H  1

#include "ngc-gcode.h"
#include "ngc-mcode.h"
#include "ngc-vars.h"

struct ngc_state {
	struct ngc_state *prev;
	double *var;
	const char *comment;

	int G[NGC_GGSIZE];
	int M[NGC_MGSIZE];
	double word[26];
	long map;		/* explicitly set words */
};

int ngc_error (struct ngc_state *o, const char *fmt, ...);
int ngc_warn  (struct ngc_state *o, const char *fmt, ...);
int ngc_check (struct ngc_state *o);
int ngc_exec  (struct ngc_state *o);

/*
 * NGC State helpers
 */

static inline int ngc_is_inv_mode (struct ngc_state *o)
{
	return o->var[NGC_INV] != 0;
}

static inline int ngc_is_comp_mode (struct ngc_state *o)
{
	return o->var[NGC_COMP] != 0;
}

static inline double ngc_word (struct ngc_state *o, int c)
{
	return o->word[c - 'A'];
}

#endif  /* NGC_STATE_H */
