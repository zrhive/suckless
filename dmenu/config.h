/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

/*******************************************************/
/* -b option; if 0, dmenu appears at bottom            */
/*******************************************************/
static int topbar = 1;

/*******************************************************/
/* -F option; if 0, dmenu doesn't use fuzzy matching   */
/*******************************************************/
static int fuzzy  = 1;

/*******************************************************/
/* -fn option overrides fonts[0]; default X11 font set */
/*******************************************************/
static const char *fonts[] = {
	"JetBrainsMono Nerd Font Mono:size=14"
};

/*******************************************************/
/* -p option; prompt to the left of input field        */
/*******************************************************/
static const char *prompt = NULL;

/*******************************************************/
/* COLORSCHEME                                         */
/*******************************************************/
static const char *colors[SchemeLast][2] = {
	/*                        foreground  background */
	[SchemeNorm]          = { "#a5adcb",  "#24273a" },
	[SchemeSel]           = { "#cad3f5",  "#363a4f" },
	[SchemeSelHighlight]  = { "#8aadf4",  "#363a4f" },
	[SchemeNormHighlight] = { "#8aadf4",  "#24273a" },
	[SchemeOut]           = { "#000000",  "#00ffff" },
};

/*******************************************************/
/* -l options; number of lines in grid if > 0          */
/*******************************************************/
static unsigned int lines   = 3;

/*******************************************************/
/* -g options; number of columns in grid if > 0        */
/*******************************************************/
static unsigned int columns = 4;

/*******************************************************/
/* Characters not considered part of a word            */
/* while deleting words. for example: " /?\"&[]"       */
/*******************************************************/
static const char worddelimiters[] = " ";
