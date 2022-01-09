/*
 * NIST RS274/NGC G-Code Checker
 *
 * Copyright (c) 2021 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <limits.h>
#include <math.h>

#include "ngc-state.h"
#include "ngc-vars.h"
#include "ngc-word.h"

static int ngc_eq (double a, double b, double precision)
{
	return fabs (a - b) < precision;
}

static int ngc_is_int (double x)
{
	long long X = x;

	return ngc_eq (x, X, 0.0001);
}

static int ngc_motion_check (struct ngc_state *o, const char *cmd)
{
	if ((o->map & NGC_AXIS) == 0)
		return ngc_warn (o, "No axis word for %s", cmd);

	return 1;
}

static int ngc_g0000_check (struct ngc_state *o)
{
	return ngc_motion_check (o, "G0");
}

static int ngc_feed_check (struct ngc_state *o, const char *cmd)
{
	if (ngc_is_inv_mode (o) && (o->map & NGC_F) == 0)
		return ngc_error (o, "No F word in inverse time feed rate "
				     "mode for %s", cmd);
	return 1;
}

static int ngc_g0010_check (struct ngc_state *o)
{
	return ngc_feed_check   (o, "G1") &&
	       ngc_motion_check (o, "G1");
}

static int ngc_arc_check (struct ngc_state *o, const char *cmd)
{
	if (!ngc_feed_check (o, cmd))
		return 0;

	switch ((int) o->var[NGC_PLANE]) {
	case NGC_PLANE_XY:
		if ((o->map & NGC_XY) == 0)
			return ngc_error (o, "No end point coordinate in XY "
					     "plane for %s", cmd);
		break;
	case NGC_PLANE_XZ:
		if ((o->map & NGC_XZ) == 0)
			return ngc_error (o, "No end point coordinate in XZ "
					     "plane for %s", cmd);
		break;
	case NGC_PLANE_YZ:
		if ((o->map & NGC_YZ) == 0)
			return ngc_error (o, "No end point coordinate in YZ "
					     "plane for %s", cmd);
		break;
	}

	if ((o->map & NGC_R) != 0) {
		/*
		 * Tha case of the end point of the arc is the same as the
		 * current point is checked at execution time.
		 */
		return 1;
	}

	switch ((int) o->var[NGC_PLANE]) {
	case NGC_PLANE_XY:
		if ((o->map & NGC_IJ) == 0)
			return ngc_error (o, "No center coordinate in XY "
					     "plane for %s", cmd);
		break;
	case NGC_PLANE_XZ:
		if ((o->map & NGC_IK) == 0)
			return ngc_error (o, "No center coordinate in XZ "
					     "plane for %s", cmd);
		break;
	case NGC_PLANE_YZ:
		if ((o->map & NGC_JK) == 0)
			return ngc_error (o, "No center coordinate in YZ "
					     "plane for %s", cmd);
		break;
	}

	/*
	 * The radius deviation (the distance from the current point to
	 * the center differs from the distance from the end point to the
	 * center) is checked at execution time.
	 */
	return 1;
}

static int ngc_g0020_check (struct ngc_state *o)
{
	return ngc_arc_check (o, "G2");
}

static int ngc_g0030_check (struct ngc_state *o)
{
	return ngc_arc_check (o, "G3");
}

static int ngc_delay_check (struct ngc_state *o, const char *cmd)
{
	double period = ngc_word (o, 'P');

	if (period < 0.0)
		return ngc_error (o, "Negative period for %s", cmd);

	return 1;
}

static int ngc_g0040_check (struct ngc_state *o)
{
	return ngc_delay_check (o, "G4");
}

static int ngc_int_check (struct ngc_state *o, char word, long lo, long hi,
			  const char *name)
{
	unsigned index = word - 'A';
	long mask = 1 << index;
	double v = o->word[index];

	if ((o->map & mask) == 0)
		return ngc_error (o, "%s (word %c) required", name, word);

	if (!ngc_is_int (v))
		return ngc_error (o, "%s must be an integer", name);

	if (v < lo || v > hi)
		return ngc_error (o, "%s must be in range from %ld to %ld",
				  name, lo, hi);
	return 1;
}

static int ngc_g0100_check (struct ngc_state *o)
{
	int L = ngc_word (o, 'L');

	if (!ngc_int_check (o, 'L', 0, 1000, "Subcommand"))
		return 0;

	if (o->G[1] != 0)
		return ngc_error (o, "G10 cannot be used with any motion "
				     "command");

	switch (L) {
	case 2:
		return ngc_int_check (o, 'P', 1, 9, "Coordinate system number");
	}

	return ngc_error (o, "Unknown command G10 L%d", L);
}

static int ngc_g0170_check (struct ngc_state *o)
{
	return 1;  /* No conditions for XY-plane selection */
}

static int ngc_g0180_check (struct ngc_state *o)
{
	return 1;  /* No conditions for XZ-plane selection */
}

static int ngc_g0190_check (struct ngc_state *o)
{
	return 1;  /* No conditions for YZ-plane selection */
}

static int ngc_g0200_check (struct ngc_state *o)
{
	return 1;  /* No conditions to use inches for length units */
}

static int ngc_g0210_check (struct ngc_state *o)
{
	return 1;  /* No conditions to use millimeters for length units */
}

static int ngc_g0280_check (struct ngc_state *o)
{
	if (o->G[1] != 0)
		return ngc_error (o, "G28 cannot be used with any motion "
				     "command");

	return 1;
}

static int ngc_g0300_check (struct ngc_state *o)
{
	if (o->G[1] != 0)
		return ngc_error (o, "G30 cannot be used with any motion "
				     "command");

	return 1;
}

static int ngc_g0382_check (struct ngc_state *o)
{
	if ((o->map & NGC_XYZ) == 0)
		return ngc_error (o, "No X, Y, or Z-axis word for G38.2");

	if (ngc_is_inv_mode (o))
		return ngc_error (o, "Cannot run G38.2 in inverse time feed "
				     "rate mode");
	/*
	 * The minimum movement and roration conditions are checked at
	 * execution time.
	 */
	return 1;
}

static int ngc_g0400_check (struct ngc_state *o)
{
	return 1;  /* No conditions to turn cutter radius compensation off */
}

static int ngc_comp_check (struct ngc_state *o, const char *name)
{
	if (ngc_is_comp_mode (o))
		return ngc_error (o, "The cutter compensation active alrady");

	if (!ngc_int_check (o, 'D', 0, LONG_MAX, name))
		return 0;

	if (o->var[NGC_PLANE] != NGC_PLANE_XY)
		return ngc_error (o, "The XY-plane is not active for cutter "
				     "compensation");
	/*
	 * The tool availability is checked at execution time.
	 */
	return 1;
}

static int ngc_g0410_check (struct ngc_state *o)
{
	return ngc_comp_check (o, "Tool number for cutter radius "
				  "compensation on left");
}

static int ngc_g0420_check (struct ngc_state *o)
{
	return ngc_comp_check (o, "Tool number for cutter radius "
				  "compensation on right");
}

static int ngc_g0430_check (struct ngc_state *o)
{
	if (!ngc_int_check (o, 'H', 0, 1000, "Tool number to get tool "
					     "offset length"))
		return 0;
	/*
	 * The tool availability is checked at execution time.
	 */
	return 1;
}

static int ngc_g0490_check (struct ngc_state *o)
{
	return 1;  /* No conditions to turn a tool length offset off */
}

static int ngc_g0530_check (struct ngc_state *o)
{
	if (o->G[1] != NGC_G0000 && o->G[1] != NGC_G0010)
		return ngc_error (o, "G53 is used without G0 or G1 being "
				     "active");
	if (ngc_is_comp_mode (o))
		return ngc_error (o, "Cannot use absolute coordinates while "
				     "cutter compensation is active");
	return 1;
}

static int ngc_scs_check (struct ngc_state *o, const char *name)
{
	if (ngc_is_comp_mode (o))
		return ngc_error (o, "Cannot select coordinate system while "
				     "cutter compensation is active");
	return 1;
}

static int ngc_g0540_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G54");
}

static int ngc_g0550_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G55");
}

static int ngc_g0560_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G56");
}

static int ngc_g0570_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G57");
}

static int ngc_g0580_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G58");
}

static int ngc_g0590_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G59");
}

static int ngc_g0591_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G59.1");
}

static int ngc_g0592_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G59.2");
}

static int ngc_g0593_check (struct ngc_state *o)
{
	return ngc_scs_check (o, "G59.3");
}

static int ngc_g0610_check (struct ngc_state *o)
{
	return 1;  /* No conditions for exact path mode */
}

static int ngc_g0611_check (struct ngc_state *o)
{
	return 1;  /* No conditions for exact stop mode */
}

static int ngc_g0640_check (struct ngc_state *o)
{
	return 1;  /* No conditions for continuous mode */
}

static int ngc_g0800_check (struct ngc_state *o)
{
	int g0_axis = o->G[0] == NGC_G0100 || o->G[0] == NGC_G0280 ||
		      o->G[0] == NGC_G0300 || o->G[0] == NGC_G0920;

	if (!g0_axis && (o->map & NGC_AXIS) != 0)
		return ngc_warn (o, "Useless axis word specified for G80");

	return 1;
}

static int ngc_canned_check (struct ngc_state *o, const char *cmd)
{
	if ((o->map & NGC_XYZ) == 0)
		return ngc_error (o, "No X, Y, or Z-axis word for %s", cmd);

	if ((o->map & NGC_L) != 0 &&
	    !ngc_int_check (o, 'L', 1, LONG_MAX, "The number of repeats"))
		return 0;

	switch ((int) o->var[NGC_PLANE]) {
	case NGC_PLANE_XY:
		if ((o->map & NGC_Z) == 0 && o->G[1] != o->prev->G[1])
			return ngc_error (o, "No Z word for first %s", cmd);

		if (ngc_word (o, 'R') < ngc_word (o, 'Z'))
			return ngc_error (o, "R < Z for canned cycle in XY "
					     "plane for %s", cmd);
		break;
	case NGC_PLANE_XZ:
		if ((o->map & NGC_Y) == 0 && o->G[1] != o->prev->G[1])
			return ngc_error (o, "No Y word for first %s", cmd);

		if (ngc_word (o, 'R') < ngc_word (o, 'Y'))
			return ngc_error (o, "R < Y for canned cycle in XZ "
					     "plane for %s", cmd);
		break;
	case NGC_PLANE_YZ:
		if ((o->map & NGC_X) == 0 && o->G[1] != o->prev->G[1])
			return ngc_error (o, "No X word for first %s", cmd);

		if (ngc_word (o, 'R') < ngc_word (o, 'X'))
			return ngc_error (o, "R < X for canned cycle in YZ "
					     "plane for %s", cmd);
		break;
	}

	if (ngc_is_inv_mode (o))
		return ngc_error (o, "Cannot run canned cycle in inverse time "
				     "feed rate mode for %s", cmd);

	if (ngc_is_comp_mode (o))
		return ngc_error (o, "Cannot run canned cycle while cutter "
				     "compensation is active for %s", cmd);
	/*
	 * TODO: The rotation axis movement is checked at execution time.
	 */
	return 1;
}

static int ngc_g0810_check (struct ngc_state *o)
{
	return ngc_canned_check (o, "G81");
}

static int ngc_g0820_check (struct ngc_state *o)
{
	return ngc_delay_check  (o, "G82") &&
	       ngc_canned_check (o, "G82");
}

static int ngc_g0830_check (struct ngc_state *o)
{
	return ngc_canned_check (o, "G83");
}

static int ngc_g0840_check (struct ngc_state *o)
{
	return ngc_canned_check (o, "G84");
}

static int ngc_g0850_check (struct ngc_state *o)
{
	return ngc_canned_check (o, "G85");
}

static int ngc_g0860_check (struct ngc_state *o)
{
	return ngc_delay_check  (o, "G86") &&
	       ngc_canned_check (o, "G86");
}

static int ngc_g0870_check (struct ngc_state *o)
{
	return ngc_canned_check (o, "G87");
}

static int ngc_g0880_check (struct ngc_state *o)
{
	return ngc_delay_check  (o, "G88") &&
	       ngc_canned_check (o, "G88");
}

static int ngc_g0890_check (struct ngc_state *o)
{
	return ngc_delay_check  (o, "G89") &&
	       ngc_canned_check (o, "G89");
}

static int ngc_g0900_check (struct ngc_state *o)
{
	return 1;  /* No conditions for absolute distance mode */
}

static int ngc_g0910_check (struct ngc_state *o)
{
	return 1;  /* No conditions for incremental distance mode */
}

static int ngc_g0920_check (struct ngc_state *o)
{
	if (o->G[1] != 0)
		return ngc_error (o, "G92 cannot be used with any motion "
				     "command");

	return ngc_motion_check (o, "G92");
}

static int ngc_g0921_check (struct ngc_state *o)
{
	return 1;  /* No conditions to off and reset axis offsets to zero */
}

static int ngc_g0922_check (struct ngc_state *o)
{
	return 1;  /* No conditions to off axis offsets */
}

static int ngc_g0923_check (struct ngc_state *o)
{
	return 1;  /* No conditions to on axix offsets */
}

static int ngc_g0930_check (struct ngc_state *o)
{
	return 1;  /* No conditions to start the inverse time mode */
}

static int ngc_g0940_check (struct ngc_state *o)
{
	return 1;  /* No conditions to start the units per minute mode */
}

static int ngc_g0980_check (struct ngc_state *o)
{
	return 1;  /* No conditions to retract to previous position mode */
}

static int ngc_g0990_check (struct ngc_state *o)
{
	return 1;  /* No conditions to retract to R mode */
}

static int ngc_check_gcode (struct ngc_state *o, int gcode)
{
	switch (gcode) {
	case NGC_G0000:	return ngc_g0000_check (o);
	case NGC_G0010:	return ngc_g0010_check (o);
	case NGC_G0020:	return ngc_g0020_check (o);
	case NGC_G0030:	return ngc_g0030_check (o);
	case NGC_G0040:	return ngc_g0040_check (o);
	case NGC_G0100:	return ngc_g0100_check (o);
	case NGC_G0170:	return ngc_g0170_check (o);
	case NGC_G0180:	return ngc_g0180_check (o);
	case NGC_G0190:	return ngc_g0190_check (o);
	case NGC_G0200:	return ngc_g0200_check (o);
	case NGC_G0210:	return ngc_g0210_check (o);
	case NGC_G0280:	return ngc_g0280_check (o);
	case NGC_G0300:	return ngc_g0300_check (o);
	case NGC_G0382:	return ngc_g0382_check (o);
	case NGC_G0400:	return ngc_g0400_check (o);
	case NGC_G0410:	return ngc_g0410_check (o);
	case NGC_G0420:	return ngc_g0420_check (o);
	case NGC_G0430:	return ngc_g0430_check (o);
	case NGC_G0490:	return ngc_g0490_check (o);
	case NGC_G0530:	return ngc_g0530_check (o);
	case NGC_G0540:	return ngc_g0540_check (o);
	case NGC_G0550:	return ngc_g0550_check (o);
	case NGC_G0560:	return ngc_g0560_check (o);
	case NGC_G0570:	return ngc_g0570_check (o);
	case NGC_G0580:	return ngc_g0580_check (o);
	case NGC_G0590:	return ngc_g0590_check (o);
	case NGC_G0591:	return ngc_g0591_check (o);
	case NGC_G0592:	return ngc_g0592_check (o);
	case NGC_G0593:	return ngc_g0593_check (o);
	case NGC_G0610:	return ngc_g0610_check (o);
	case NGC_G0611:	return ngc_g0611_check (o);
	case NGC_G0640:	return ngc_g0640_check (o);
	case NGC_G0800:	return ngc_g0800_check (o);
	case NGC_G0810:	return ngc_g0810_check (o);
	case NGC_G0820:	return ngc_g0820_check (o);
	case NGC_G0830:	return ngc_g0830_check (o);
	case NGC_G0840:	return ngc_g0840_check (o);
	case NGC_G0850:	return ngc_g0850_check (o);
	case NGC_G0860:	return ngc_g0860_check (o);
	case NGC_G0870:	return ngc_g0870_check (o);
	case NGC_G0880:	return ngc_g0880_check (o);
	case NGC_G0890:	return ngc_g0890_check (o);
	case NGC_G0900:	return ngc_g0900_check (o);
	case NGC_G0910:	return ngc_g0910_check (o);
	case NGC_G0920:	return ngc_g0920_check (o);
	case NGC_G0921:	return ngc_g0921_check (o);
	case NGC_G0922:	return ngc_g0922_check (o);
	case NGC_G0923:	return ngc_g0923_check (o);
	case NGC_G0930:	return ngc_g0930_check (o);
	case NGC_G0940:	return ngc_g0940_check (o);
	case NGC_G0980:	return ngc_g0980_check (o);
	case NGC_G0990:	return ngc_g0990_check (o);
	}

	return ngc_error (o, "Inernal error: unknown G-code");
}

int ngc_check (struct ngc_state *o)
{
	int i;

	for (i = 0; i < NGC_GGSIZE; ++i)
		if (o->G[i] != 0 && !ngc_check_gcode (o, o->G[i]))
			return 0;

	return 1;
}
