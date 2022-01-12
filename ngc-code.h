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

enum ngc_code {
	/*
	 * Non-modal G-code group 0
	 */
	NGC_G0040 = 1,	/* dwell					*/
	NGC_G0100,	/* coordinate system origin setting		*/
	NGC_G0280,	/* return to home				*/
	NGC_G0300,	/* return to secondary home			*/
	NGC_G0530,	/* motion in machine coordinate system		*/
	NGC_G0920,	/* offset coordinate systems and set parameters	*/
	NGC_G0921,	/* cancel offset CSs and set params to zero	*/
	NGC_G0922,	/* cancel offset CSs but do not reset params	*/
	NGC_G0923,	/* apply parameters to offset coord. systems	*/

	/*
	 * Modal G-code group 1: motion
	 */
	NGC_G0000,	/* rapid positioning				*/
	NGC_G0010,	/* linear interpolation				*/
	NGC_G0020,	/* circular/helical interpolation (CW)		*/
	NGC_G0030,	/* circular/helical interpolation (CCW)		*/
	NGC_G0382,	/* straight probe				*/
	NGC_G0800,	/* cancel motion mode (incl. any canned cycle)	*/
	NGC_G0810,	/* CC: drilling					*/
	NGC_G0820,	/* CC: drilling with dwell			*/
	NGC_G0830,	/* CC: peck drilling				*/
	NGC_G0840,	/* CC: right hand tapping			*/
	NGC_G0850,	/* CC: boring, no dwell, feed out		*/
	NGC_G0860,	/* CC: boring, spindle stop, rapid out		*/
	NGC_G0870,	/* CC: back boring				*/
	NGC_G0880,	/* CC: boring, spindle stop, manual out		*/
	NGC_G0890,	/* CC: boring, dwell, feed out			*/

	/*
	 * Modal G-code group 2: plane selection
	 */
	NGC_G0170,	/* XY-plane selection				*/
	NGC_G0180,	/* XZ-plane selection				*/
	NGC_G0190,	/* YZ-plane selection				*/

	/*
	 * Modal G-code group 3: distance mode
	 */
	NGC_G0900,	/* absolute distance mode			*/
	NGC_G0910,	/* incremental distance mode			*/

	/*
	 * Modal G-code group 5: feed rate mode
	 */
	NGC_G0930,	/* inverse time feed rate mode			*/
	NGC_G0940,	/* units per minute feed rate mode		*/

	/*
	 * Modal G-code group 6: units
	 */
	NGC_G0200,	/* inch system selection			*/
	NGC_G0210,	/* millimeter system selection			*/

	/*
	 * Modal G-code group 7: cutter radius compensation
	 */
	NGC_G0400,	/* cancel cutter radius compensation		*/
	NGC_G0410,	/* start cutter radius compensation left	*/
	NGC_G0420,	/* start cutter radius compensation right	*/

	/*
	 * Modal G-code group 8: tool length offset
	 */
	NGC_G0430,	/* tool length offset (plus)			*/
	NGC_G0490,	/* cancel tool length offset			*/

	/*
	 * Modal G-code group 10: return mode in canned cycles
	 */
	NGC_G0980,	/* initial level return in canned cycles	*/
	NGC_G0990,	/* R-point level return in canned cycles	*/

	/*
	 * Modal G-code group 12: coordinate system selection
	 */
	NGC_G0540,	/* use preset work coordinate system 1		*/
	NGC_G0550,	/* use preset work coordinate system 2		*/
	NGC_G0560,	/* use preset work coordinate system 3		*/
	NGC_G0570,	/* use preset work coordinate system 4		*/
	NGC_G0580,	/* use preset work coordinate system 5		*/
	NGC_G0590,	/* use preset work coordinate system 6		*/
	NGC_G0591,	/* use preset work coordinate system 7		*/
	NGC_G0592,	/* use preset work coordinate system 8		*/
	NGC_G0593,	/* use preset work coordinate system 9		*/

	/*
	 * Modal G-code group 13: path control mode
	 */
	NGC_G0610,	/* set path control mode: exact path		*/
	NGC_G0611,	/* set path control mode: exact stop		*/
	NGC_G0640,	/* set path control mode: continuous		*/

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
};

#endif  /* NGC_CODE_H */
