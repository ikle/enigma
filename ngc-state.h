/*
 * NIST RS274/NGC State
 *
 * Copyright (c) 2021-2022 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NGC_STATE_H
#define NGC_STATE_H  1

#include <stddef.h>

#include "ngc-code.h"
#include "ngc-device.h"
#include "ngc-vars.h"
#include "ngc-word.h"

struct ngc_state {
	struct ngc_state *prev;
	double *var;
	const char *comment;

	int g[NGC_GSIZE];
	double word[26];
	long map;		/* explicitly set words */

	double axis[6];
};

int ngc_error (struct ngc_state *o, const char *fmt, ...);
int ngc_warn  (struct ngc_state *o, const char *fmt, ...);

int ngc_state_reset (struct ngc_state *o);

int ngc_check (struct ngc_state *o);
int ngc_exec  (struct ngc_state *o, struct ngc_device *dev);

/*
 * NGC State helpers
 */

static inline int ngc_state_end (struct ngc_state *o)
{
	o->prev = NULL;
	return 1;
}

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
