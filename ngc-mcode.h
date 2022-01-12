/*
 * NIST RS274/NGC M-Codes
 *
 * Copyright (c) 2021 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NGC_MCODE_H
#define NGC_MCODE_H  1

enum ngc_mgroup {
	NGC_M4 = 0,
	NGC_M6,
	NGC_M7,
	NGC_M8,
	NGC_M9,

	NGC_MGSIZE,
};

enum ngc_mcode {
	/*
	 * Modal M-code group 4: stopping
	 */
	NGC_M0000 = 1,	/* program stop					*/
	NGC_M0010,	/* optional program stop			*/
	NGC_M0020,	/* program end					*/
	NGC_M0300,	/* program end, pallet shuttle, and reset	*/
	NGC_M0600,	/* pallet shuttle and program stop		*/

	/*
	 * Modal M-code group 6: tool change
	 */
	NGC_M0060,	/* tool change					*/

	/*
	 * Modal M-code group 7: spindle turning
	 */
	NGC_M0030,	/* turn spindle clockwise			*/
	NGC_M0040,	/* turn spindle counterclockwise		*/
	NGC_M0050,	/* stop spindle turning				*/

	/*
	 * Modal M-code group 8: coolant
	 *
	 * Special case: M7 and M8 may be active at the same time
	 */
	NGC_M0070,	/* mist coolant on				*/
	NGC_M0080,	/* flood coolant on				*/
	NGC_M0090,	/* mist and flood coolant off			*/

	/*
	 * Modal M-code group 9: feed and speed override switches
	 */
	NGC_M0480,	/* enable speed and feed overrides		*/
	NGC_M0490,	/* disable speed and feed overrides		*/

	NGC_MSIZE,
};

#endif  /* NGC_MCODE_H */
