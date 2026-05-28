/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

/* -b  option; if 0, dmenu appears at bottom */
static int topbar = 1;

/* -F  option; if 0, dmenu doesn't use fuzzy matching */
static int fuzzy  = 1;

/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"JetBrainsMono Nerd Font Mono:size=12"
};

/* -p  option; prompt to the left of input field */
static const char *prompt = NULL;

static const char *colors[SchemeLast][2] = {
	/*                        foreground  background */
	[SchemeNorm]          = { "#bbbbbb",  "#222222" },
	[SchemeSel]           = { "#eeeeee",  "#005577" },
	[SchemeSelHighlight]  = { "#ffc978",  "#005577" },
	[SchemeNormHighlight] = { "#ffc978",  "#222222" },
	[SchemeOut]           = { "#000000",  "#00ffff" },
};

/* -l and -g options; controls number of lines and columns in grid if > 0 */
static unsigned int lines   = 0;
static unsigned int columns = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
