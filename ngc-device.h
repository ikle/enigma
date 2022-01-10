/*
 * NIST RS274/NGC Device
 *
 * Copyright (c) 2021 Alexei A. Smekalkine
 *
 * Standard: NIST IR 6556
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NGC_DEVICE_H
#define NGC_DEVICE_H  1

/*
 * 4.3.2 Initialization and Termination
 */

struct ngc_device *ngc_device_alloc (const char *name);
void ngc_device_free (struct ngc_device *o);

/*
 * 4.3.3 Representation
 * 4.3.5 Machining Attributes
 */

enum ngc_conf {
	NGC_CONF_UNITS,
	NGC_CONF_PLANE,
	NGC_CONF_MODE,		/* Feed mode	*/
};

enum ngc_units {
	NGC_UNITS_MM = 0,
	NGC_UNITS_INCHES,
};

enum ngc_plane {
	NGC_PLANE_XY = 0,
	NGC_PLANE_XZ,
	NGC_PLANE_YZ,
};

enum ngc_mode {
	NGC_MODE_EXACT_PATH = 0,
	NGC_MODE_EXACT_STOP,
	NGC_MODE_CONTINUOUS,
};

int ngc_device_conf		(struct ngc_device *o, int opt, int value);
int ngc_device_offset		(struct ngc_device *o, double *vec);

/*
 * 4.3.4 Free Space Motion
 */

//int ngc_device_traverse_rate	(struct ngc_device *o, double rate);
int ngc_device_home		(struct ngc_device *o);
int ngc_device_move		(struct ngc_device *o, int abs, double *end);

/*
 * 4.3.5 Machining Attributes
 */

int ngc_device_feed_rate	(struct ngc_device *o, double rate, int inv);

/*
 * 4.3.6 Machining Functions
 */

int ngc_device_line	(struct ngc_device *o, int abs, double *end);
int ngc_device_carc	(struct ngc_device *o, double *end, double *c, int cw);
int ngc_device_rarc	(struct ngc_device *o, double *end, double r,  int cw);
int ngc_device_dwell	(struct ngc_device *o, double delay);
int ngc_device_probe	(struct ngc_device *o, double *end);
int ngc_device_stop	(struct ngc_device *o, int opt);

/*
 * 4.3.7 Spindle Functions
 */

enum ngc_dir {
	NGC_DIR_STOPPED = 0,	/* Spindle stopped		*/
	NGC_DIR_CW,		/* Clockwise direction		*/
	NGC_DIR_CCW,		/* Counterclockwise direction 	*/
};

enum ngc_limit {
	NGC_LIMIT_FORCE = 0,
	NGC_LIMIT_TORQUE,
};

int ngc_device_spindle_speed	(struct ngc_device *o, double speed);
int ngc_device_spindle_run	(struct ngc_device *o, int dir);

//int ngc_device_spindle_limit	(struct ngc_device *o, double limit, int type);
//int ngc_device_spindle_orient	(struct ngc_device *o, double angle);

/*
 * 4.3.8 Tool Functions
 */

int ngc_device_tool_change	(struct ngc_device *o, int slot);
int ngc_device_tool_offset	(struct ngc_device *o, double tool);

/*
 * 4.3.9 Miscellaneous Functions
 */

enum ngc_opt {
	NGC_OPT_RELATIVE	= 1 << 0,
	NGC_OPT_OVERRIDE_FEED	= 1 << 2,
	NGC_OPT_OVERRIDE_SPEED	= 1 << 3,
	NGC_OPT_RETRACT_BACK	= 1 << 4,
	NGC_OPT_FEED_SYNC	= 1 << 5,
};

enum ngc_coolant {
	NGC_COOLANT_FLOOD	= 1 << 0,
	NGC_COOLANT_MIST	= 1 << 1,
	NGC_COOLANT_TROUGH_TOOL	= 1 << 2,
};

int ngc_device_comment		(struct ngc_device *o, const char *s);
int ngc_device_message		(struct ngc_device *o, const char *s);

int ngc_device_opt		(struct ngc_device *o, int mask, int on);
int ngc_device_coolant		(struct ngc_device *o, int mask, int on);

int ngc_device_pallet_shuttle	(struct ngc_device *o);

/*
 * 4.3.10 Program Functions
 */

int ngc_device_reset	(struct ngc_device *o);

/*
 * 4.3.11 Cutter Radius Compensation
 */

enum ngc_cutter {
	NGC_CUTTER_CENTER,
	NGC_CUTTER_LEFT,
	NGC_CUTTER_RIGHT,
};

int ngc_device_cutter_comp	(struct ngc_device *o, int pos, double r);

#endif  /* NGC_DEVICE_H */
