/* See LICENSE file for copyright and license details. */

/* Helper macros for spawning commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }

/**** APPEARANCE ****/
static const unsigned int borderpx       = 5;   /* border pixel of windows */
static const int corner_radius           = 10;
static const unsigned int snap           = 16;  /* snap pixel */
static const int swallowfloating         = 1;   /* 1 means swallow floating windows by default */
static const unsigned int gappih         = 15;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 15;  /* vert inner gap between windows */
static const unsigned int gappoh         = 15;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 15;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 20;   /* 0 means derive from font, >= 1 explicit height */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_BOTTOM_BAR_SLIM;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_BOTTOM_BAR;
static int fakefsindicatortype           = INDICATOR_PLUS;
static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE;
static const char *fonts[]               = { "JetBrainsMono Nerd Font:size=10" };

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#cad3f5";
static char normbgcolor[]                = "#24273a";
static char normbordercolor[]            = "#c6a0f6";
static char normfloatcolor[]             = "#b7bdf8";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#005577";
static char selbordercolor[]             = "#005577";
static char selfloatcolor[]              = "#005577";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#444444";
static char titlenormfloatcolor[]        = "#db8fd9";

static char titleselfgcolor[]            = "#eeeeee";
static char titleselbgcolor[]            = "#005577";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#222222";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#db8fd9";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#005577";
static char tagsselbordercolor[]         = "#005577";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
	/*                    fg      bg        border     */
	[SchemeNorm]      = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]       = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeTitleSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]   = { OPAQUE, baralpha, borderalpha },
	[SchemeHidNorm]   = { OPAQUE, baralpha, borderalpha },
	[SchemeHidSel]    = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]       = { OPAQUE, baralpha, borderalpha },
};

static char *colors[][ColCount] = {
	/*                    fg                bg                border                float */
	[SchemeNorm]      = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]       = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm] = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]  = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]  = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]   = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]   = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]    = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]       = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

static const char *const autostart[] = {
	"kitty", NULL,
	NULL /* terminate */
};

static char *tagicons[][NUMTAGS] = {
	[DEFAULT_TAGS]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

/**** RULES ****/
static const Rule rules[] = {
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "Firefox", .tags = 1 << 7)
};

static const BarRule barrules[] = {
	/* monitor    bar   alignment         widthfunc         drawfunc        clickfunc         hoverfunc     name */
	{ -1,         0,    BAR_ALIGN_LEFT,   width_tags,       draw_tags,      click_tags,       hover_tags,   "tags" },
	{  0,         0,    BAR_ALIGN_RIGHT,  width_systray,    draw_systray,   click_systray,    NULL,         "systray" },
	{ -1,         0,    BAR_ALIGN_LEFT,   width_ltsymbol,   draw_ltsymbol,  click_ltsymbol,   NULL,         "layout" },
	{ statusmon,  0,    BAR_ALIGN_RIGHT,  width_status,     draw_status,    click_statuscmd,  NULL,         "status" },
};

/* layout(s) */
static const float mfact                = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster                = 1;    /* number of clients in master area */
static const int nstack                 = 0;    /* number of clients in primary stack area */
static const int resizehints            = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen         = 1;    /* 1 will force focus on the fullscreen window */
static const int refreshrate            = 120;  /* refresh rate (per second) for client move/resize */
static const int refreshrate_placemouse = 60;   /* refresh rate (per second) for placemouse */
static const int decorhints             = 1;    /* 1 means respect decoration hints */

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */
/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	  0 },
	{ -scrollsensetivity,	  0 },
	{ 0,                    +scrollsensetivity },
	{ 0,                    -scrollsensetivity },
};

static const Layout layouts[] = {
	/* symbol   arrange function, { nmaster, nstack, layout, master axis, stack axis, secondary stack axis, symbol func } */
	{ "[]=",    flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL } }, // default tile layout
 	{ "><>",    NULL,             {0} },    /* no layout function means floating behavior */
	{ "[M]",    flextile,         { -1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL } }, // monocle
	{ "[D]",    flextile,         { -1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL } }, // deck
	{ "TTT",    flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // bstack
	{ "[T]",    flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TATAMI, 0, NULL } }, // tatami mats
	{ "[\\]",   flextile,         { -1, -1, NO_SPLIT, DWINDLE, DWINDLE, 0, NULL } }, // fibonacci dwindle
	{ "(@)",    flextile,         { -1, -1, NO_SPLIT, SPIRAL, SPIRAL, 0, NULL } }, // fibonacci spiral
	{ "|||",    flextile,         { -1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // columns (col) layout
	{ ">M>",    flextile,         { -1, -1, FLOATING_MASTER, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL } }, // floating master
	{ "===",    flextile,         { -1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL } }, // bstackhoriz
	{ "|M|",    flextile,         { -1, -1, SPLIT_CENTERED_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, TOP_TO_BOTTOM, NULL } }, // centeredmaster
	{ "-M-",    flextile,         { -1, -1, SPLIT_CENTERED_HORIZONTAL, TOP_TO_BOTTOM, LEFT_TO_RIGHT, LEFT_TO_RIGHT, NULL } }, // centeredmaster horiz
	{ ":::",    flextile,         { -1, -1, NO_SPLIT, GAPPLESSGRID, GAPPLESSGRID, 0, NULL } }, // gappless grid
};

/* key definitions */
#define MODKEY Mod4Mask
#define METAKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                               KEY,  view,               {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,                   KEY,  toggleview,         {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,                     KEY,  tag,                {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,         KEY,  toggletag,          {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY,                       KEY,  setlayout,          {.v = &layouts[TAG]} }, \
	{ MODKEY|METAKEY|ControlMask,           KEY,  rotatelayoutaxis,   {.i = +TAG } },\
	{ MODKEY|METAKEY|ControlMask|ShiftMask, KEY,  rotatelayoutaxis,   {.i = -TAG } },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };
/***** PROGRAMS ***************/
static const char *kittycmd[]   = { "kitty", NULL };
static const char *roficombi[]  = { "rofi", "-show", "combi", NULL };
static const char *rofidrun[]   = { "rofi", "-show", "drun", NULL };
static const char *rofipower[]  = { "rofi", "-show", "power-menu", "-modi", "power-menu:rofi-power-menu", NULL };
static const char *yazifile[]   = { "kitty", "-e", "yazi", NULL };
static const char *nvimstart[]  = { "kitty", "nvim", NULL };
static const char *flamegui[]   = { "flameshot", "gui", NULL };
static const char *flamescreen[] = { "flameshot", "screen", NULL };

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
	{ "notify-send Volume$BUTTON", 1 },
	{ "notify-send CPU$BUTTON", 2 },
	{ "notify-send Battery$BUTTON", 3 },
};
/* test the above with: xsetroot -name "$(printf '\x01Volume |\x02 CPU |\x03 Battery')" */
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

static const Key keys[] = {
	/* modifier                     key             function                argument */
	{ MODKEY,                       XK_Escape,      setkeymode,             {.ui = COMMANDMODE} },
	{ MODKEY,                       XK_n,           spawn,                  {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_n,           spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_b,           togglebar,              {0} },
	{ MODKEY,                       XK_space,       zoom,                   {0} },
	{ MODKEY,                       XK_Tab,         view,                   {0} },
	{ MODKEY,                       XK_0,           view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,           tag,                    {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_q,           killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_Escape,      quit,                   {0} },
  /**** STACK ****/
  { MODKEY,                       XK_grave,       focusmaster,            {0} },
	{ MODKEY,                       XK_h,           focusdir,               {.i = 0 } }, // left
	{ MODKEY,                       XK_l,           focusdir,               {.i = 1 } }, // right
	{ MODKEY,                       XK_k,           focusdir,               {.i = 2 } }, // up
	{ MODKEY,                       XK_j,           focusdir,               {.i = 3 } }, // down
	{ MODKEY|ShiftMask,             XK_h,           placedir,               {.i = 0 } }, // left
	{ MODKEY|ShiftMask,             XK_l,           placedir,               {.i = 1 } }, // right
	{ MODKEY|ShiftMask,             XK_k,           placedir,               {.i = 2 } }, // up
	{ MODKEY|ShiftMask,             XK_j,           placedir,               {.i = 3 } }, // down
	{ MODKEY,                       XK_i,           setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_o,           setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_i,           setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,           setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_p,           setcfact,               {0} },
	{ MODKEY|ControlMask,           XK_i,           incnmaster,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_o,           incnmaster,             {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_i,           incnstack,              {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_o,           incnstack,              {.i = +1 } },
	{ MODKEY,                       XK_equal,       rotatestack,            {.i = +1 } },
	{ MODKEY,                       XK_minus,       rotatestack,            {.i = -1 } },
	{ MODKEY,                       XK_Right,       focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_Left,        focusstack,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,       movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,        movestack,              {.i = -1 } },
  /**** LAYOUTS ****/
	{ MODKEY|METAKEY,               XK_p,           setlayout,              {0} },
	{ MODKEY|METAKEY|ControlMask,   XK_p,           mirrorlayout,           {0} },
	{ MODKEY|METAKEY,               XK_minus,       cyclelayout,            {.i = -1 } },
	{ MODKEY|METAKEY,               XK_equal,       cyclelayout,            {.i = +1 } },
	{ MODKEY|METAKEY,               XK_space,       togglefloating,         {0} },
	{ MODKEY|METAKEY,               XK_f,           togglefullscreen,       {0} },
	{ MODKEY|METAKEY|ShiftMask,     XK_f,           togglefakefullscreen,   {0} },
	{ MODKEY|METAKEY|ControlMask,   XK_f,           fullscreen,             {0} },
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	TAGKEYS(                        XK_8,                                   7)
	TAGKEYS(                        XK_9,                                   8)
  /**** GAPS ****/
  { MODKEY|METAKEY,               XK_u,           incrgaps,               {.i = +1 } },
  { MODKEY|METAKEY|ShiftMask,     XK_u,           incrgaps,               {.i = -1 } },
  { MODKEY|METAKEY,               XK_i,           incrigaps,              {.i = +1 } },
  { MODKEY|METAKEY|ShiftMask,     XK_i,           incrigaps,              {.i = -1 } },
  { MODKEY|METAKEY,               XK_o,           incrogaps,              {.i = +1 } },
  { MODKEY|METAKEY|ShiftMask,     XK_o,           incrogaps,              {.i = -1 } },
  { MODKEY|METAKEY,               XK_h,           incrihgaps,             {.i = +1 } },
  { MODKEY|METAKEY|ShiftMask,     XK_h,           incrihgaps,             {.i = -1 } },
  { MODKEY|METAKEY,               XK_j,           incrivgaps,             {.i = +1 } },
  { MODKEY|METAKEY|ShiftMask,     XK_j,           incrivgaps,             {.i = -1 } },
  { MODKEY|METAKEY,               XK_l,           incrohgaps,             {.i = +1 } },
  { MODKEY|METAKEY|ShiftMask,     XK_l,           incrohgaps,             {.i = -1 } },
  { MODKEY|METAKEY,               XK_k,           incrovgaps,             {.i = +1 } },
  { MODKEY|METAKEY|ShiftMask,     XK_k,           incrovgaps,             {.i = -1 } },
	{ MODKEY|METAKEY,               XK_p,           togglegaps,             {0} },
	{ MODKEY|METAKEY|ShiftMask,     XK_p,           defaultgaps,            {0} },
  /**** MONITOR ****/
	{ MODKEY|ControlMask,           XK_comma,       focusmon,               {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,      focusmon,               {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_comma,       tagmon,                 {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_period,      tagmon,                 {.i = +1 } },
  /**** PROGRAMS AND SERVICES ****/
  { MODKEY|ShiftMask,             XK_Return,      spawn,                  {.v = kittycmd  } },
  { MODKEY,                       XK_r,           spawn,                  {.v = roficombi } },
  { MODKEY,                       XK_e,           spawn,                  {.v = rofidrun  } },
  { MODKEY,                       XK_Delete,      spawn,                  {.v = rofipower } },
  { MODKEY,                       XK_Return,      spawn,                  {.v = { "kitty", "-e", "yazi", NULL }} },
  { MODKEY,                       XK_v,           spawn,                  {.v = { "kitty", "nvim", NULL }} },
  { MODKEY,                       XK_Print,       spawn,                  {.v = flamescreen } },
  { MODKEY|METAKEY,               XK_Print,       spawn,                  {.v = flamegui  } },
};

static const Key cmdkeys[] = {
	/* modifier                    keys                     function         argument */
	{ 0,                           XK_Escape,               clearcmd,        {0} },
	{ ControlMask,                 XK_c,                    clearcmd,        {0} },
	{ 0,                           XK_i,                    setkeymode,      {.ui = INSERTMODE} },
};

static const Command commands[] = {
	/* modifier (4 keys)                          keysyms (4 keys)                                function         argument */
	{ {ControlMask, ShiftMask,  0,         0},    {XK_w,      XK_h,     0,         0},            setlayout,       {.v = &layouts[0]} },
	{ {ControlMask, 0,          0,         0},    {XK_w,      XK_o,     0,         0},            setlayout,       {.v = &layouts[2]} },
	{ {ControlMask, ShiftMask,  0,         0},    {XK_w,      XK_o,     0,         0},            onlyclient,      {0} },
	{ {ControlMask, 0,          0,         0},    {XK_w,      XK_v,     0,         0},            setlayout,       {.v = &layouts[0]} },
	{ {ControlMask, 0,          0,         0},    {XK_w,      XK_less,  0,         0},            setmfact,        {.f = -0.05} },
	{ {ControlMask, ShiftMask,  0,         0},    {XK_w,      XK_less,  0,         0},            setmfact,        {.f = +0.05} },
	{ {ControlMask, ShiftMask,  0,         0},    {XK_w,      XK_0,     0,         0},            setmfact,        {.f = +1.50} },
	{ {ShiftMask,   0,          0,         0},    {XK_period, XK_e,     0,         0},            spawn,           {.v = dmenucmd} },
	{ {ShiftMask,   0,          0,         0},    {XK_period, XK_o,     0,         0},            spawn,           {.v = dmenucmd} },
	{ {ShiftMask,   0,          0,         0},    {XK_period, XK_q,     XK_Return, 0},            quit,            {0} },
	{ {ShiftMask,   0,          0,         0},    {XK_period, XK_b,     XK_d,      XK_Return},    killclient,      {0} },
	{ {ShiftMask,   0,          0,         0},    {XK_period, XK_b,     XK_n,      XK_Return},    focusstack,      {.i = +1} },
	{ {ShiftMask,   0,          ShiftMask, 0},    {XK_period, XK_b,     XK_n,      XK_Return},    focusstack,      {.i = -1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button2,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,                   Button3,        spawn,          {.v = statuscmd } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizeorfacts,  {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,              Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,              Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,              Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,              Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};

