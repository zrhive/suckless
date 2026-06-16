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
static int tagindicatortype              = INDICATOR_NONE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_BOTTOM_BAR;
static int fakefsindicatortype           = INDICATOR_PLUS;
static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE;
static const char *fonts[]               = { "JetBrainsMono Nerd Font:size=10" };

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#a5adcb";
static char normbgcolor[]                = "#24273a";
static char normbordercolor[]            = "#6e738d";
static char normfloatcolor[]             = "#b7bdf8";

static char selfgcolor[]                 = "#cad3f5";
static char selbgcolor[]                 = "#24273a";
static char selbordercolor[]             = "#c6a0f6";
static char selfloatcolor[]              = "#f5bde6";

static char titlenormfgcolor[]           = "#a5adcb";
static char titlenormbgcolor[]           = "#24273a";
static char titlenormbordercolor[]       = "#24273a";
static char titlenormfloatcolor[]        = "#f5bde6";

static char titleselfgcolor[]            = "#f0c6c6";
static char titleselbgcolor[]            = "#24273a";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#a5adcb";
static char tagsnormbgcolor[]            = "#24273a";
static char tagsnormbordercolor[]        = "#24273a";
static char tagsnormfloatcolor[]         = "#f5bde6";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#24273a";
static char tagsselbordercolor[]         = "#f5bde6";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#a5adcb";
static char hidselfgcolor[]              = "#24273a";
static char hidnormbgcolor[]             = "#b7bdf8";
static char hidselbgcolor[]              = "#b7bdf8";

static char urgfgcolor[]                 = "#cad3f5";
static char urgbgcolor[]                 = "#24273a";
static char urgbordercolor[]             = "#ed8796";
static char urgfloatcolor[]              = "#f5bde6";

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
  "slstatus", NULL,
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
	RULE(.class = "Firefox", .tags = 1 << 7)
	RULE(.class = "st", .isfloating = 1)
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
static const int resizehints            = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen         = 1;    /* 1 will force focus on the fullscreen window */
static const int refreshrate            = 60;   /* refresh rate (per second) for client move/resize */
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
	/* symbol   arrange function */
	{ "[T]",      tile },     /* first entry is default */
	{ "[D]",      deck },     /* 2 */
	{ "[B]",      bstack },   /* 3 */
	{ "[M]",      monocle },  /* 4 */
	{ "[F]",      NULL },     /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define METAKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                         KEY,  view,             {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,             KEY,  toggleview,       {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,               KEY,  tag,              {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,   KEY,  toggletag,        {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY,                 KEY,  setlayout,        {.v = &layouts[TAG]} }, \
	{ MODKEY|METAKEY|ShiftMask,       KEY,  unfloatvisible,   {.v = &layouts[TAG]} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
	{ "notify-send Volume $BUTTON", 1 },
	{ "notify-send CPU $BUTTON", 2 },
	{ "notify-send Battery $BUTTON", 3 },
};
/* test the above with: xsetroot -name "$(printf '\x01Volume |\x02 CPU |\x03 Battery')" */
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

static const Key keys[] = {
	/* modifier                     key             function                argument */
	{ MODKEY,                       XK_Escape,      setkeymode,             {.ui = COMMANDMODE} },
	{ MODKEY,                       XK_n,           spawn,                  {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_n,           spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_b,           togglebar,              {0} },
	{ MODKEY|ShiftMask,             XK_q,           killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_Escape,      quit,                   {0} },
  /**** STACK ****/
  { MODKEY,                       XK_grave,       focusmaster,            {0} },
	{ MODKEY,                       XK_h,           focusdir,               {.i = 0 } },
	{ MODKEY,                       XK_l,           focusdir,               {.i = 1 } },
	{ MODKEY,                       XK_k,           focusdir,               {.i = 2 } },
	{ MODKEY,                       XK_j,           focusdir,               {.i = 3 } },
	{ MODKEY|ShiftMask,             XK_h,           placedir,               {.i = 0 } },
	{ MODKEY|ShiftMask,             XK_l,           placedir,               {.i = 1 } },
	{ MODKEY|ShiftMask,             XK_k,           placedir,               {.i = 2 } },
	{ MODKEY|ShiftMask,             XK_j,           placedir,               {.i = 3 } },
	{ MODKEY,                       XK_i,           setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_o,           setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_i,           setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,           setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_p,           setcfact,               {0} },
	{ MODKEY|ControlMask,           XK_i,           incnmaster,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_o,           incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_semicolon,   focusstack,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_semicolon,   focusstack,             {.i = -1 } },
  /**** LAYOUTS and TAGS ****/
	{ MODKEY|METAKEY,               XK_grave,       setlayout,              {0} },
	{ MODKEY|METAKEY,               XK_minus,       cyclelayout,            {.i = -1 } },
	{ MODKEY|METAKEY|ShiftMask,     XK_minus,       cyclelayout,            {.i = +1 } },
	{ MODKEY|METAKEY,               XK_0,           togglefloating,         {0} },
	{ MODKEY|METAKEY|ShiftMask,     XK_0,           unfloatvisible,         {0} },
	{ MODKEY|METAKEY,               XK_equal,       togglefullscreen,       {0} },
	{ MODKEY|METAKEY|ShiftMask,     XK_equal,       togglefakefullscreen,   {0} },
	{ MODKEY|METAKEY|ControlMask,   XK_equal,       fullscreen,             {0} },
	{ MODKEY|ShiftMask,             XK_grave,       zoom,                   {0} },
	{ MODKEY,                       XK_Tab,         view,                   {0} },
	{ MODKEY,                       XK_0,           view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,           tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_minus,       viewtoleft,             {0} },
	{ MODKEY,                       XK_equal,       viewtoright,            {0} },
	{ MODKEY|ShiftMask,             XK_minus,       tagtoleft,              {0} },
	{ MODKEY|ShiftMask,             XK_equal,       tagtoright,             {0} },
	{ MODKEY|ControlMask,           XK_minus,       tagandviewtoleft,       {0} },
	{ MODKEY|ControlMask,           XK_equal,       tagandviewtoright,      {0} },
  { MODKEY|LockMask,              XK_u,           incrgaps,               {.i = +1 } },
  { MODKEY|LockMask|ShiftMask,    XK_u,           incrgaps,               {.i = -1 } },
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	TAGKEYS(                        XK_8,                                   7)
	TAGKEYS(                        XK_9,                                   8)
  /**** MONITOR ****/
	{ MODKEY,                       XK_comma,       focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,                 {.i = +1 } },
  /**** PROGRAMS AND SERVICES ****/
  { MODKEY|ShiftMask,             XK_Return,      spawn,                  CMD("kitty") },
  { MODKEY,                       XK_r,           spawn,                  CMD("rofi", "-show", "combi") },
  { MODKEY,                       XK_e,           spawn,                  CMD("rofi", "-show", "drun") },
  { MODKEY,                       XK_Delete,      spawn,                  CMD("rofi", "-show", "power-menu", "-modi", "power-menu:rofi-power-menu") },
  { MODKEY,                       XK_Return,      spawn,                  CMD("kitty", "-e", "yazi") },
  { MODKEY,                       XK_v,           spawn,                  CMD("kitty", "-e", "nvim") },
  { MODKEY,                       XK_Print,       spawn,                  CMD("flameshot", "screen") },
  { MODKEY|METAKEY,               XK_Print,       spawn,                  CMD("flameshot", "gui") },
};

static const Key cmdkeys[] = {
	/* modifier                     keys            function                argument */
	{ 0,                            XK_Escape,      clearcmd,               {0} },
	{ MODKEY,                       XK_Escape,      setkeymode,             {.ui = INSERTMODE} },
  /**** GAPS ****/
  { ControlMask,                  XK_u,           incrgaps,               {.i = +1 } },
  { ControlMask|ShiftMask,        XK_u,           incrgaps,               {.i = -1 } },
  { ControlMask,                  XK_i,           incrigaps,              {.i = +1 } },
  { ControlMask|ShiftMask,        XK_i,           incrigaps,              {.i = -1 } },
  { ControlMask,                  XK_o,           incrogaps,              {.i = +1 } },
  { ControlMask|ShiftMask,        XK_o,           incrogaps,              {.i = -1 } },
  { ControlMask,                  XK_h,           incrihgaps,             {.i = +1 } },
  { ControlMask|ShiftMask,        XK_h,           incrihgaps,             {.i = -1 } },
  { ControlMask,                  XK_j,           incrivgaps,             {.i = +1 } },
  { ControlMask|ShiftMask,        XK_j,           incrivgaps,             {.i = -1 } },
  { ControlMask,                  XK_l,           incrohgaps,             {.i = +1 } },
  { ControlMask|ShiftMask,        XK_l,           incrohgaps,             {.i = -1 } },
  { ControlMask,                  XK_k,           incrovgaps,             {.i = +1 } },
  { ControlMask|ShiftMask,        XK_k,           incrovgaps,             {.i = -1 } },
	{ ControlMask,                  XK_p,           togglegaps,             {0} },
	{ ControlMask|ShiftMask,        XK_p,           defaultgaps,            {0} },
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

