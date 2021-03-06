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
 * 4.3.10 Program Functions
 */

int ngc_device_reset	(struct ngc_device *o);

/*
 * 4.3.3  Representation
 * 4.3.5  Machining Attributes
 */

enum ngc_mode {
	NGC_MODE_UNITS,
	NGC_MODE_PLANE,
	NGC_MODE_PATH,		/* Path control mode			*/
	NGC_MODE_RATE,		/* Feed rate mode			*/
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

enum ngc_path {
	NGC_PATH_EXACT = 0,	/* Exact path mode		*/
	NGC_PATH_STOP,		/* Exact stop mode		*/
	NGC_PATH_CONT,		/* Continuous path mode		*/
};

enum ngc_rate {
	NGC_RATE_UPM,		/* Units per minute			*/
	NGC_RATE_CPM,		/* Commands per minute (inverse time)	*/
};

enum ngc_conf {
	NGC_CONF_RATE,
	NGC_CONF_SPEED,
	NGC_CONF_MAX_RATE,	/* Maximum traverse rate		*/
	NGC_CONF_MAX_FORCE,	/* Spindle maximum force		*/
	NGC_CONF_MAX_TORQUE,	/* Spindle maximim torque		*/
};

int ngc_device_mode	(struct ngc_device *o, int opt, int value);
int ngc_device_conf	(struct ngc_device *o, int opt, double value);
int ngc_device_offset	(struct ngc_device *o, double *vec);

/*
 * 4.3.4 Free Space Motion
 */

int ngc_device_home	(struct ngc_device *o, int index);
int ngc_device_move	(struct ngc_device *o, int abs, double *end);

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

enum ngc_spindle {
	NGC_SPINDLE_STOP,	/* Stop spindle				*/
	NGC_SPINDLE_CW,		/* Run spindle clockwise		*/
	NGC_SPINDLE_CCW,	/* Run spindle counterclockwise		*/
	NGC_SPINDLE_ORIENT,	/* Orient spindle			*/
};

int ngc_device_spindle	(struct ngc_device *o, int op, double arg);

/*
 * 4.3.8 Tool Functions
 */

enum ngc_tool {
	NGC_TOOL_SELECT,
	NGC_TOOL_CHANGE,
	NGC_TOOL_COMP,		/* Enable tool length compensation	*/
};

int ngc_device_tool	(struct ngc_device *o, int op, int slot);

/*
 * 4.3.11 Cutter Radius Compensation
 */

enum ngc_cutter {
	NGC_CUTTER_C,		/* Cutter at center, no compensation	*/
	NGC_CUTTER_L,		/* Cutter at left with compensation	*/
	NGC_CUTTER_R,		/* Cutter at right with compensation	*/
};

int ngc_device_cutter	(struct ngc_device *o, int op, int slot);

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

#endif  /* NGC_DEVICE_H */
