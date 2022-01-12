/*
 * NIST RS274/NGC Executer
 *
 * Copyright (c) 2021-2022 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <strings.h>

#include "ngc-state.h"

/*
 * 1. comment (includes message)
 */
static int ngc_exec_comment (struct ngc_state *o, struct ngc_device *dev)
{
	const char *p = o->comment;

	if (p == NULL)
		return 1;

	if (strncasecmp (p, "MSG,", 4) == 0)
		return ngc_device_message (dev, p + (p[4] == ' ' ? 5 : 4));

	return ngc_device_comment (dev, p);
}

/*
 * 2. set feed rate mode (G93, G94 — inverse time or per minute)
 */
static
int ngc_exec_set_feed_rate_mode (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_G5]) {
	case NGC_G0930:
		o->var[NGC_INV] = 1;
		return ngc_device_mode (dev, NGC_MODE_RATE, NGC_RATE_CPM);

	case NGC_G0940:
		o->var[NGC_INV] = 0;
		return ngc_device_mode (dev, NGC_MODE_RATE, NGC_RATE_UPM);
	}

	return 1;
}

/*
 * 3. set feed rate (F)
 */
static int ngc_exec_set_feed_rate (struct ngc_state *o, struct ngc_device *dev)
{
	if ((o->map & NGC_F) != 0)
		return ngc_device_conf (dev, NGC_CONF_RATE, ngc_word (o, 'F'));

	return 1;
}

/*
 * 4. set spindle speed (S)
 */
static
int ngc_exec_set_spindle_speed (struct ngc_state *o, struct ngc_device *dev)
{
	if ((o->map & NGC_S) != 0)
		return ngc_device_conf (dev, NGC_CONF_SPEED, ngc_word (o, 'S'));

	return 1;
}

/*
 * 5. select tool (T)
 * 6. change tool (M6)
 */
static int ngc_exec_change_tool (struct ngc_state *o, struct ngc_device *dev)
{
	int slot = ngc_word (o, 'T');

	if ((o->map & NGC_T) != 0)
		return ngc_device_tool (dev, NGC_TOOL_SELECT, slot);

	if (o->g[NGC_M6] == NGC_M0060)
		return ngc_device_tool (dev, NGC_TOOL_CHANGE, slot);

	return 1;
}

/*
 * 7. spindle on or off (M3, M4, M5)
 */
static int ngc_exec_conf_spindle (struct ngc_state *o, struct ngc_device *dev)
{
	double speed = ngc_word (o, 'S');

	switch (o->g[NGC_M7]) {
	case NGC_M0030:
		return ngc_device_spindle (dev, NGC_SPINDLE_CW, speed);

	case NGC_M0040:
		return ngc_device_spindle (dev, NGC_SPINDLE_CCW, speed);

	case NGC_M0050:
		return ngc_device_spindle (dev, NGC_SPINDLE_STOP, 0);
	}

	return 1;
}

/*
 * 8. coolant on or off (M7, M8, M9)
 */
static int ngc_exec_conf_coolant (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_M8]) {
	case NGC_M0070:
		return ngc_device_coolant (dev, NGC_COOLANT_MIST, 1);

	case NGC_M0080:
		return ngc_device_coolant (dev, NGC_COOLANT_FLOOD, 1);

	case NGC_M0090:
		return ngc_device_coolant (dev, ~0, 0);
	}

	return 1;
}

/*
 * 9. enable or disable overrides (M48, M49)
 */
static int ngc_exec_conf_overrides (struct ngc_state *o, struct ngc_device *dev)
{
	int mask = NGC_OPT_OVERRIDE_FEED | NGC_OPT_OVERRIDE_SPEED;

	switch (o->g[NGC_M9]) {
	case NGC_M0480:
		return ngc_device_opt (dev, mask, 1);

	case NGC_M0490:
		return ngc_device_opt (dev, mask, 0);
	}

	return 1;
}

/*
 * 10. dwell (G4)
 */
static int ngc_exec_dwell (struct ngc_state *o, struct ngc_device *dev)
{
	if (o->g[NGC_G0] == NGC_G0040)
		return ngc_device_dwell (dev, ngc_word (o, 'P'));

	return 1;
}

/*
 * 11. set active plane (G17, G18, G19)
 */
static
int ngc_exec_set_active_plane (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_G2]) {
	case NGC_G0170:
		return ngc_device_mode (dev, NGC_MODE_PLANE, NGC_PLANE_XY);

	case NGC_G0180:
		return ngc_device_mode (dev, NGC_MODE_PLANE, NGC_PLANE_XZ);

	case NGC_G0190:
		return ngc_device_mode (dev, NGC_MODE_PLANE, NGC_PLANE_YZ);
	}

	return 1;
}

/*
 * 12. set length units (G20, G21)
 */
static int ngc_exec_set_units (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_G6]) {
	case NGC_G0200:
		return ngc_device_mode (dev, NGC_MODE_UNITS, NGC_UNITS_INCHES);

	case NGC_G0210:
		return ngc_device_mode (dev, NGC_MODE_UNITS, NGC_UNITS_MM);
	}

	return 1;
}

/*
 * 13. cutter radius compensation on or off (G40, G41, G42)
 */
static int
ngc_exec_conf_cutter_radius_comp (struct ngc_state *o, struct ngc_device *dev)
{
	int slot = (o->map & NGC_D) != 0 ? ngc_word (o, 'D') : 0 /* current */;

	switch (o->g[NGC_G7]) {
	case NGC_G0400:
		return ngc_device_cutter (dev, NGC_CUTTER_C, -1);  /* off */

	case NGC_G0410:
		return ngc_device_cutter (dev, NGC_CUTTER_L, slot);

	case NGC_G0420:
		return ngc_device_cutter (dev, NGC_CUTTER_R, slot);
	}

	return 1;
}

/*
 * 14. cutter length compensation on or off (G43, G49)
 */
static int ngc_exec_conf_cutter_length_comp (struct ngc_state *o, struct ngc_device *dev)
{
	int slot = (o->map & NGC_H) != 0 ? ngc_word (o, 'H') : 0 /* current */;

	/*
	 * NOTE: Incompatibility with NGC3 for H0 meaning in line with EMC2
	 */

	switch (o->g[NGC_G8]) {
	case NGC_G0430:
		return ngc_device_tool (dev, NGC_TOOL_COMP, slot);

	case NGC_G0490:
		return ngc_device_tool (dev, NGC_TOOL_COMP, -1);  /* off */
	}

	return 1;
}

/*
 * 15. coordinate system selection (G54, G55, G56, G57, G58, G59, G59.1,
 *     G59.2, G59.3)
 */
static int ngc_exec_offset (struct ngc_state *o, struct ngc_device *dev)
{
	double vec[6];
	int cs = o->var[NGC_CS], i;

	for (i = 0; i < 6; ++i)
		vec[i] = o->var[NGC_CS1_X + cs * 20 + i];

	if (o->var[NGC_OFFSET_ON])
		for (i = 0; i < 6; ++i)
			vec[i] += o->var[NGC_OFFSET_X + i];

	return ngc_device_offset (dev, vec);
}

static
int ngc_exec_select_coord_system (struct ngc_state *o, struct ngc_device *dev)
{
	int cs;

	switch (o->g[NGC_G12]) {
	case NGC_G0540:		cs = 1; break;
	case NGC_G0550:		cs = 2; break;
	case NGC_G0560:		cs = 3; break;
	case NGC_G0570:		cs = 4; break;
	case NGC_G0580:		cs = 5; break;
	case NGC_G0590:		cs = 6; break;
	case NGC_G0591:		cs = 7; break;
	case NGC_G0592:		cs = 8; break;
	case NGC_G0593:		cs = 9; break;
	default:		return 1;
	}

	o->var[NGC_CS] = cs;
	return ngc_exec_offset (o, dev);
}

/*
 * 16. set path control mode (G61, G61.1, G64)
 */
static int ngc_exec_set_path_mode (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_G13]) {
	case NGC_G0610:
		return ngc_device_mode (dev, NGC_MODE_PATH, NGC_PATH_EXACT);

	case NGC_G0611:
		return ngc_device_mode (dev, NGC_MODE_PATH, NGC_PATH_STOP);

	case NGC_G0640:
		return ngc_device_mode (dev, NGC_MODE_PATH, NGC_PATH_CONT);
	}

	return 1;
}

/*
 * 17. set distance mode (G90, G91)
 */
static
int ngc_exec_set_distance_mode (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_G3]) {
	case NGC_G0900:
		o->var[NGC_REL] = 0;
		return ngc_device_opt (dev, NGC_OPT_RELATIVE, 0);

	case NGC_G0910:
		o->var[NGC_REL] = 1;
		return ngc_device_opt (dev, NGC_OPT_RELATIVE, 1);
	}

	return 1;
}

/*
 * 18. set retract mode (G98, G99)
 */
static
int ngc_exec_set_retract_mode (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_G10]) {
	case NGC_G0980:
		return ngc_device_opt (dev, NGC_OPT_RETRACT_BACK, 1);

	case NGC_G0990:
		return ngc_device_opt (dev, NGC_OPT_RETRACT_BACK, 0);
	}

	return 1;
}

/*
 * Axis helpers
 */
static void ngc_axis_zero (double *v)
{
	int i;

	for (i = 0; i < 6; ++i)
		v[i] = 0;
}

static void ngc_axis_copy (struct ngc_state *o, double *v)
{
	if ((o->map & NGC_X) != 0)	v[0] = ngc_word (o, 'X');
	if ((o->map & NGC_Y) != 0)	v[1] = ngc_word (o, 'Y');
	if ((o->map & NGC_Z) != 0)	v[2] = ngc_word (o, 'Z');
	if ((o->map & NGC_A) != 0)	v[3] = ngc_word (o, 'A');
	if ((o->map & NGC_B) != 0)	v[4] = ngc_word (o, 'B');
	if ((o->map & NGC_C) != 0)	v[5] = ngc_word (o, 'C');
}

static void ngc_axis_prepare (struct ngc_state *o)
{
	static const double zero[6];
	const double *axis = o->var[NGC_REL] ? zero : o->prev->axis;

	o->axis[0] = (o->map & NGC_X) != 0 ? ngc_word (o, 'X') : axis[0];
	o->axis[1] = (o->map & NGC_Y) != 0 ? ngc_word (o, 'Y') : axis[1];
	o->axis[2] = (o->map & NGC_Z) != 0 ? ngc_word (o, 'Z') : axis[2];
	o->axis[3] = (o->map & NGC_A) != 0 ? ngc_word (o, 'A') : axis[3];
	o->axis[4] = (o->map & NGC_B) != 0 ? ngc_word (o, 'B') : axis[4];
	o->axis[5] = (o->map & NGC_C) != 0 ? ngc_word (o, 'C') : axis[5];
}

/*
 * 19. home (G28, G30) or
 *     change coordinate system data (G10) or
 *     set axis offsets (G92, G92.1, G92.2, G92.3)
 */
static int ngc_exec_shift (struct ngc_state *o, struct ngc_device *dev)
{
	int i;

	if (!o->var[NGC_OFFSET_ON])
		ngc_axis_zero (o->var + NGC_OFFSET_X);

	for (i = 0; i < 6; ++i)
		o->var[NGC_OFFSET_X + i] += o->var[NGC_REL] ?
			o->axis[i] :
			o->axis[i] - o->prev->axis[i];

	o->var[NGC_OFFSET_ON] = 1;
	return ngc_exec_offset (o, dev);
}

static int ngc_exec_conf_offset (struct ngc_state *o, struct ngc_device *dev)
{
	int cs;

	ngc_axis_prepare (o);

	switch (o->g[NGC_G0]) {
	case NGC_G0100:
		if (ngc_word (o, 'L') == 2) {
			cs = ngc_word (o, 'P');
			ngc_axis_copy (o, o->var + NGC_CS1_X + (cs - 1) * 20);
		}

		return ngc_exec_offset (o, dev);

	case NGC_G0280:
		return ngc_device_move (dev, 0, o->axis) &&
		       ngc_device_home (dev, 0);

	case NGC_G0300:
		return ngc_device_move (dev, 0, o->axis) &&
		       ngc_device_home (dev, 1);

	case NGC_G0920:
		return ngc_exec_shift (o, dev);

	case NGC_G0921:
		ngc_axis_zero (o->var + NGC_OFFSET_X);
		/* passthrough */

	case NGC_G0922:
		o->var[NGC_OFFSET_ON] = 0;
		return ngc_exec_offset (o, dev);

	case NGC_G0923:
		o->var[NGC_OFFSET_ON] = 1;
		return ngc_exec_offset (o, dev);
	}

	return 1;
}

/*
 * 20. perform motion (G0 to G3, G80 to G89), as modified (possibly) by G53
 */
static int ngc_exec_arc (struct ngc_state *o, struct ngc_device *dev, int cw)
{
	double r, offs[3];

	if ((o->map & NGC_R) != 0) {
		r = ngc_word (o, 'R');
		return ngc_device_rarc (dev, o->axis, r, cw);
	}

	offs[0] = (o->map & NGC_I) != 0 ? ngc_word (o, 'I') : 0;
	offs[1] = (o->map & NGC_J) != 0 ? ngc_word (o, 'J') : 0;
	offs[2] = (o->map & NGC_K) != 0 ? ngc_word (o, 'K') : 0;

	return ngc_device_carc (dev, o->axis, offs, cw);
}

static int ngc_exec_perform_motion (struct ngc_state *o, struct ngc_device *dev)
{
	int abs = o->g[NGC_G0] == NGC_G0530;

	switch (o->g[NGC_G0]) {
	case NGC_G0100: case NGC_G0280: case NGC_G0300: case NGC_G0920:
		return 1;
	}

	if (o->g[NGC_G1] == 0)
		o->g[NGC_G1] = o->prev->g[NGC_G1];

	switch (o->g[NGC_G1]) {
	case NGC_G0000:
		return ngc_device_move (dev, abs, o->axis);

	case NGC_G0010:
		return ngc_device_line (dev, abs, o->axis);

	case NGC_G0020:
		return ngc_exec_arc (o, dev, 1);

	case NGC_G0030:
		return ngc_exec_arc (o, dev, 0);

	case NGC_G0382:
		return ngc_device_probe (dev, o->axis);
	}

	return 1;
}

/*
 * 21. stop (M0, M1, M2, M30, M60)
 */
static int ngc_exec_stop (struct ngc_state *o, struct ngc_device *dev)
{
	switch (o->g[NGC_M4]) {
	case NGC_M0000:
		return ngc_device_stop (dev, 0);

	case NGC_M0010:
		return ngc_device_stop (dev, 1);

	case NGC_M0020:
		return ngc_device_reset (dev) &&
		       ngc_state_end (o);

	case NGC_M0300:
		return ngc_device_reset (dev) &&
		       ngc_device_pallet_shuttle (dev) &&
		       ngc_state_reset (o);

	case NGC_M0600:
		return ngc_device_stop (dev, 0) &&
		       ngc_device_pallet_shuttle (dev);
	}

	return 1;
}

int ngc_exec (struct ngc_state *o, struct ngc_device *dev)
{
	return	ngc_exec_comment			(o, dev) &&
		ngc_exec_set_feed_rate_mode		(o, dev) &&
		ngc_exec_set_feed_rate			(o, dev) &&
		ngc_exec_set_spindle_speed		(o, dev) &&
		ngc_exec_change_tool			(o, dev) &&
		ngc_exec_conf_spindle			(o, dev) &&
		ngc_exec_conf_coolant			(o, dev) &&
		ngc_exec_conf_overrides			(o, dev) &&
		ngc_exec_dwell				(o, dev) &&
		ngc_exec_set_active_plane		(o, dev) &&
		ngc_exec_set_units			(o, dev) &&
		ngc_exec_conf_cutter_radius_comp	(o, dev) &&
		ngc_exec_conf_cutter_length_comp	(o, dev) &&
		ngc_exec_select_coord_system		(o, dev) &&
		ngc_exec_set_path_mode			(o, dev) &&
		ngc_exec_set_distance_mode		(o, dev) &&
		ngc_exec_set_retract_mode		(o, dev) &&
		ngc_exec_conf_offset			(o, dev) &&
		ngc_exec_perform_motion			(o, dev) &&
		ngc_exec_stop				(o, dev);
}
