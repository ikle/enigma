/*
 * NIST RS274/NGC Executer
 *
 * Copyright (c) 2021 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "ngc-state.h"

/*
 * 1. comment (includes message)
 */
static int ngc_exec_comment (struct ngc_state *o)
{
	return 1;
}

/*
 * 2. set feed rate mode (G93, G94 — inverse time or per minute)
 */
static int ngc_exec_set_feed_rate_mode (struct ngc_state *o)
{
	return 1;
}

/*
 * 3. set feed rate (F)
 */
static int ngc_exec_set_feed_rate (struct ngc_state *o)
{
	return 1;
}

/*
 * 4. set spindle speed (S)
 */
static int ngc_exec_set_spindle_speed (struct ngc_state *o)
{
	return 1;
}

/*
 * 5. select tool (T)
 */
static int ngc_exec_select_tool (struct ngc_state *o)
{
	return 1;
}

/*
 * 6. change tool (M6)
 */
static int ngc_exec_change_tool (struct ngc_state *o)
{
	return 1;
}

/*
 * 7. spindle on or off (M3, M4, M5)
 */
static int ngc_exec_conf_spindle (struct ngc_state *o)
{
	return 1;
}

/*
 * 8. coolant on or off (M7, M8, M9)
 */
static int ngc_exec_conf_coolant (struct ngc_state *o)
{
	return 1;
}

/*
 * 9. enable or disable overrides (M48, M49)
 */
static int ngc_exec_conf_overrides (struct ngc_state *o)
{
	return 1;
}

/*
 * 10. dwell (G4)
 */
static int ngc_exec_dwell (struct ngc_state *o)
{
	return 1;
}

/*
 * 11. set active plane (G17, G18, G19)
 */
static int ngc_exec_set_active_plane (struct ngc_state *o)
{
	return 1;
}

/*
 * 12. set length units (G20, G21)
 */
static int ngc_exec_set_units (struct ngc_state *o)
{
	return 1;
}

/*
 * 13. cutter radius compensation on or off (G40, G41, G42)
 */
static int ngc_exec_conf_cutter_radius_comp (struct ngc_state *o)
{
	return 1;
}

/*
 * 14. cutter length compensation on or off (G43, G49)
 */
static int ngc_exec_conf_cutter_length_comp (struct ngc_state *o)
{
	return 1;
}

/*
 * 15. coordinate system selection (G54, G55, G56, G57, G58, G59, G59.1,
 *     G59.2, G59.3)
 */
static int ngc_exec_select_coord_system (struct ngc_state *o)
{
	return 1;
}

/*
 * 16. set path control mode (G61, G61.1, G64)
 */
static int ngc_exec_set_path_mode (struct ngc_state *o)
{
	return 1;
}

/*
 * 17. set distance mode (G90, G91)
 */
static int ngc_exec_set_distance_mode (struct ngc_state *o)
{
	return 1;
}

/*
 * 18. set retract mode (G98, G99)
 */
static int ngc_exec_set_retract_mode (struct ngc_state *o)
{
	return 1;
}

/*
 * 19. home (G28, G30) or
 *     change coordinate system data (G10) or
 *     set axis offsets (G92, G92.1, G92.2, G94)
 */
static int ngc_exec_conf_offset (struct ngc_state *o)
{
	return 1;
}

/*
 * 20. perform motion (G0 to G3, G80 to G89), as modified (possibly) by G53
 */
static int ngc_exec_perform_motion (struct ngc_state *o)
{
	return 1;
}

/*
 * 21. stop (M0, M1, M2, M30, M60)
 */
static int ngc_exec_stop (struct ngc_state *o)
{
	return 1;
}

int ngc_exec (struct ngc_state *o)
{
	return	ngc_exec_comment			(o) &&
		ngc_exec_set_feed_rate_mode		(o) &&
		ngc_exec_set_feed_rate			(o) &&
		ngc_exec_set_spindle_speed		(o) &&
		ngc_exec_select_tool			(o) &&
		ngc_exec_change_tool			(o) &&
		ngc_exec_conf_spindle			(o) &&
		ngc_exec_conf_coolant			(o) &&
		ngc_exec_conf_overrides			(o) &&
		ngc_exec_dwell				(o) &&
		ngc_exec_set_active_plane		(o) &&
		ngc_exec_set_units			(o) &&
		ngc_exec_conf_cutter_radius_comp	(o) &&
		ngc_exec_conf_cutter_length_comp	(o) &&
		ngc_exec_select_coord_system		(o) &&
		ngc_exec_set_path_mode			(o) &&
		ngc_exec_set_distance_mode		(o) &&
		ngc_exec_set_retract_mode		(o) &&
		ngc_exec_conf_offset			(o) &&
		ngc_exec_perform_motion			(o) &&
		ngc_exec_stop				(o);
}
