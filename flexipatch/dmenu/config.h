/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;        /* -b  option; if 0, dmenu appears at bottom */
static int fuzzy = 1;         /* -F  option; if 0, dmenu doesn't use fuzzy matching */
static int center = 1;        /* -c  option; if 0, dmenu won't be centered on the screen */
static int min_width = 800;   /* minimum width when centered */
static int quiet = 1;         /* -q  option; if 1, dmenu will not show any items if the search string is empty */

/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"JetBrainsMono Nerd Font Mono:size=14"
};

/* -p  option; prompt to the left of input field */
static const char *prompt = "";

static const char *colors[][2] = {
	/*               fg         bg       */
	[SchemeNorm] = { "#bbbbbb", "#222222" },
	[SchemeSel]  = { "#eeeeee", "#005577" },
	[SchemeOut]  = { "#000000", "#00ffff" },
	[SchemeBorder] = { "#000000", "#005577" },
	[SchemeSelHighlight]  = { "#ffc978", "#005577" },
	[SchemeNormHighlight] = { "#ffc978", "#222222" },
	[SchemeHp]   = { "#bbbbbb", "#333333" },
	[SchemeCursor] = { "#222222", "#bbbbbb" },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 20;
static unsigned int maxhist    = 15;
static int histnodup           = 1;	/* if 0, record repeated histories */

/* Characters not considered part of a word while deleting words
 * for example: " /?\"&[]" */
static const char worddelimiters[] = " ";

/* vi option; if nonzero, vi mode is always enabled and can be
 * accessed with the global_esc keysym + mod mask */
static unsigned int vi_mode = 1;
static unsigned int start_mode = 0;			/* mode to use when -vi is passed. 0 = insert mode, 1 = normal mode */
static Key global_esc = { XK_n, Mod1Mask };	/* escape key when vi mode is not enabled explicitly */
static Key quit_keys[] = {
	/* keysym	modifier */
	{ XK_q,		0 }
};

/* Size of the window border */
static unsigned int border_width = 2;
