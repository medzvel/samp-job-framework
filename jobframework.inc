/*
	JOB SYSTEM FRAMEWORK
	Last Update - 10/8/2018
	Include Version - 0.1A
	Created By: Amagida (2018)
*/
// custom include guard
#if defined _JF_included
	#endinput
#else
#define _JF_included

// checkout if a non-sampctl user has YSI library
#tryinclude <YSI_Coding\y_hooks> // in case a non-sampctl user has YSI 5.x, no warnings will be shown
#if defined _INC_y_hooks
	#define _JF_uses_YSI
#endif

#include "job_framework\main.inc"
#include "job_framework\player.inc"