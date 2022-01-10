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
	NGC_PROBE_X	= 5061,	/* G38 X			*/
	NGC_PROBE_Y	= 5062,	/* G38 Y			*/
	NGC_PROBE_Z	= 5063,	/* G38 Z			*/
	NGC_PROBE_A	= 5064,	/* G38 A			*/
	NGC_PROBE_B	= 5065,	/* G38 B			*/
	NGC_PROBE_C	= 5066,	/* G38 C			*/
	NGC_PROBE_U	= 5067,	/* G38 U		(EMC2)	*/
	NGC_PROBE_V	= 5068,	/* G38 V		(EMC2)	*/
	NGC_PROBE_W	= 5069,	/* G38 W		(EMC2)	*/

	NGC_PROBE_OK	= 5070,	/* G38 Probe result	(EMC2)	*/

	NGC_HOME_X	= 5161,	/* G28 X			*/
	NGC_HOME_Y	= 5162,	/* G28 Y			*/
	NGC_HOME_Z	= 5163,	/* G28 Z			*/
	NGC_HOME_A	= 5164,	/* G28 A			*/
	NGC_HOME_B	= 5165,	/* G28 B			*/
	NGC_HOME_C	= 5166,	/* G28 C			*/
	NGC_HOME_U	= 5167,	/* G28 U		(EMC2)	*/
	NGC_HOME_V	= 5168,	/* G28 V		(EMC2)	*/
	NGC_HOME_W	= 5169,	/* G28 W		(EMC2)	*/

	NGC_WORK_X	= 5181,	/* G30 X			*/
	NGC_WORK_Y	= 5182,	/* G30 Y			*/
	NGC_WORK_Z	= 5183,	/* G30 Z			*/
	NGC_WORK_A	= 5184,	/* G30 A			*/
	NGC_WORK_B	= 5185,	/* G30 B			*/
	NGC_WORK_C	= 5186,	/* G30 C			*/
	NGC_WORK_U	= 5187,	/* G30 U		(EMC2)	*/
	NGC_WORK_V	= 5188,	/* G30 V		(EMC2)	*/
	NGC_WORK_W	= 5189,	/* G30 W		(EMC2)	*/

	NGC_OFFSET_ON	= 5210,	/* G92 offset enabled		*/

	NGC_OFFSET_X	= 5211,	/* G92 X offset			*/
	NGC_OFFSET_Y	= 5212,	/* G92 Y offset			*/
	NGC_OFFSET_Z	= 5213,	/* G92 Z offset			*/
	NGC_OFFSET_A	= 5214,	/* G92 A offset			*/
	NGC_OFFSET_B	= 5215,	/* G92 B offset			*/
	NGC_OFFSET_C	= 5216,	/* G92 C offset			*/
	NGC_OFFSET_U	= 5217,	/* G92 U offset		(EMC2)	*/
	NGC_OFFSET_V	= 5218,	/* G92 V offset		(EMC2)	*/
	NGC_OFFSET_W	= 5219,	/* G92 W offset		(EMC2)	*/

	NGC_CS		= 5220,	/* Coordinate System number	*/

	NGC_CS1_X	= 5221,	/* CS1 X			*/
	NGC_CS1_Y	= 5222,	/* CS1 Y			*/
	NGC_CS1_Z	= 5223,	/* CS1 Z			*/
	NGC_CS1_A	= 5224,	/* CS1 A			*/
	NGC_CS1_B	= 5225,	/* CS1 B			*/
	NGC_CS1_C	= 5226,	/* CS1 C			*/
	NGC_CS1_U	= 5227,	/* CS1 U		(EMC2)	*/
	NGC_CS1_V	= 5228,	/* CS1 V		(EMC2)	*/
	NGC_CS1_W	= 5229,	/* CS1 W		(EMC2)	*/
	NGC_CS1_R	= 5230,	/* CS1 R		(EMC2)	*/

	NGC_CS2_X	= 5241,	/* CS2 X			*/
	NGC_CS2_Y	= 5242,	/* CS2 Y			*/
	NGC_CS2_Z	= 5243,	/* CS2 Z			*/
	NGC_CS2_A	= 5244,	/* CS2 A			*/
	NGC_CS2_B	= 5245,	/* CS2 B			*/
	NGC_CS2_C	= 5246,	/* CS2 C			*/
	NGC_CS2_U	= 5247,	/* CS2 U		(EMC2)	*/
	NGC_CS2_V	= 5248,	/* CS2 V		(EMC2)	*/
	NGC_CS2_W	= 5249,	/* CS2 W		(EMC2)	*/
	NGC_CS2_R	= 5250,	/* CS2 R		(EMC2)	*/

	NGC_CS3_X	= 5261,	/* CS3 X			*/
	NGC_CS3_Y	= 5262,	/* CS3 Y			*/
	NGC_CS3_Z	= 5263,	/* CS3 Z			*/
	NGC_CS3_A	= 5264,	/* CS3 A			*/
	NGC_CS3_B	= 5265,	/* CS3 B			*/
	NGC_CS3_C	= 5266,	/* CS3 C			*/
	NGC_CS3_U	= 5267,	/* CS3 U		(EMC2)	*/
	NGC_CS3_V	= 5268,	/* CS3 V		(EMC2)	*/
	NGC_CS3_W	= 5269,	/* CS3 W		(EMC2)	*/
	NGC_CS3_R	= 5270,	/* CS3 R		(EMC2)	*/

	NGC_CS4_X	= 5281,	/* CS4 X			*/
	NGC_CS4_Y	= 5282,	/* CS4 Y			*/
	NGC_CS4_Z	= 5283,	/* CS4 Z			*/
	NGC_CS4_A	= 5284,	/* CS4 A			*/
	NGC_CS4_B	= 5285,	/* CS4 B			*/
	NGC_CS4_C	= 5286,	/* CS4 C			*/
	NGC_CS4_U	= 5287,	/* CS4 U		(EMC2)	*/
	NGC_CS4_V	= 5288,	/* CS4 V		(EMC2)	*/
	NGC_CS4_W	= 5289,	/* CS4 W		(EMC2)	*/
	NGC_CS4_R	= 5290,	/* CS4 R		(EMC2)	*/

	NGC_CS5_X	= 5301,	/* CS5 X			*/
	NGC_CS5_Y	= 5302,	/* CS5 Y			*/
	NGC_CS5_Z	= 5303,	/* CS5 Z			*/
	NGC_CS5_A	= 5304,	/* CS5 A			*/
	NGC_CS5_B	= 5305,	/* CS5 B			*/
	NGC_CS5_C	= 5306,	/* CS5 C			*/
	NGC_CS5_U	= 5307,	/* CS5 U		(EMC2)	*/
	NGC_CS5_V	= 5308,	/* CS5 V		(EMC2)	*/
	NGC_CS5_W	= 5309,	/* CS5 W		(EMC2)	*/
	NGC_CS5_R	= 5310,	/* CS5 R		(EMC2)	*/

	NGC_CS6_X	= 5321,	/* CS6 X			*/
	NGC_CS6_Y	= 5322,	/* CS6 Y			*/
	NGC_CS6_Z	= 5323,	/* CS6 Z			*/
	NGC_CS6_A	= 5324,	/* CS6 A			*/
	NGC_CS6_B	= 5325,	/* CS6 B			*/
	NGC_CS6_C	= 5326,	/* CS6 C			*/
	NGC_CS6_U	= 5327,	/* CS6 U		(EMC2)	*/
	NGC_CS6_V	= 5328,	/* CS6 V		(EMC2)	*/
	NGC_CS6_W	= 5329,	/* CS6 W		(EMC2)	*/
	NGC_CS6_R	= 5330,	/* CS6 R		(EMC2)	*/

	NGC_CS7_X	= 5341,	/* CS7 X			*/
	NGC_CS7_Y	= 5342,	/* CS7 Y			*/
	NGC_CS7_Z	= 5343,	/* CS7 Z			*/
	NGC_CS7_A	= 5344,	/* CS7 A			*/
	NGC_CS7_B	= 5345,	/* CS7 B			*/
	NGC_CS7_C	= 5346,	/* CS7 C			*/
	NGC_CS7_U	= 5347,	/* CS7 U		(EMC2)	*/
	NGC_CS7_V	= 5348,	/* CS7 V		(EMC2)	*/
	NGC_CS7_W	= 5349,	/* CS7 W		(EMC2)	*/
	NGC_CS7_R	= 5350,	/* CS7 R		(EMC2)	*/

	NGC_CS8_X	= 5361,	/* CS8 X			*/
	NGC_CS8_Y	= 5362,	/* CS8 Y			*/
	NGC_CS8_Z	= 5363,	/* CS8 Z			*/
	NGC_CS8_A	= 5364,	/* CS8 A			*/
	NGC_CS8_B	= 5365,	/* CS8 B			*/
	NGC_CS8_C	= 5366,	/* CS8 C			*/
	NGC_CS8_U	= 5367,	/* CS8 U		(EMC2)	*/
	NGC_CS8_V	= 5368,	/* CS8 V		(EMC2)	*/
	NGC_CS8_W	= 5369,	/* CS8 W		(EMC2)	*/
	NGC_CS8_R	= 5370,	/* CS8 R		(EMC2)	*/

	NGC_CS9_X	= 5381,	/* CS9 X			*/
	NGC_CS9_Y	= 5382,	/* CS9 Y			*/
	NGC_CS9_Z	= 5383,	/* CS9 Z			*/
	NGC_CS9_A	= 5384,	/* CS9 A			*/
	NGC_CS9_B	= 5385,	/* CS9 B			*/
	NGC_CS9_C	= 5386,	/* CS9 C			*/
	NGC_CS9_U	= 5387,	/* CS9 U		(EMC2)	*/
	NGC_CS9_V	= 5388,	/* CS9 V		(EMC2)	*/
	NGC_CS9_W	= 5389,	/* CS9 W		(EMC2)	*/
	NGC_CS9_R	= 5390,	/* CS9 R		(EMC2)	*/

	NGC_INPUT	= 5399,	/* Result of M66	(EMC2)	*/

	NGC_TOOL	= 5400,	/* Tool number		(EMC2)	*/

	NGC_TOOL_X	= 5401,	/* Tool X offset	(EMC2)	*/
	NGC_TOOL_Y	= 5402,	/* Tool Y offset	(EMC2)	*/
	NGC_TOOL_Z	= 5403,	/* Tool Z offset	(EMC2)	*/
	NGC_TOOL_A	= 5404,	/* Tool A offset	(EMC2)	*/
	NGC_TOOL_B	= 5405,	/* Tool B offset	(EMC2)	*/
	NGC_TOOL_C	= 5406,	/* Tool C offset	(EMC2)	*/
	NGC_TOOL_U	= 5407,	/* Tool U offset	(EMC2)	*/
	NGC_TOOL_V	= 5408,	/* Tool V offset	(EMC2)	*/
	NGC_TOOL_W	= 5409,	/* Tool W offset	(EMC2)	*/

	NGC_TOOL_D	= 5410,	/* Tool diameter	(EMC2)	*/
	NGC_TOOL_FA	= 5411,	/* Tool front angle	(EMC2)	*/
	NGC_TOOL_BA	= 5412,	/* Tool back angle	(EMC2)	*/
	NGC_TOOL_O	= 5413,	/* Tool orientation	(EMC2)	*/

	NGC_REL,
	NGC_INV,
	NGC_COMP,
	NGC_PLANE,

	NGC_VSIZE,
};

#endif  /* NGC_VARS_H */
