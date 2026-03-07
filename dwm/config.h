/* See LICENSE file for copyright and license details. */

/*****************************************/
/*              APPEARANCE               */
/*****************************************/
static const unsigned int borderpx  = 0;  /* border pixel of windows */
static const unsigned int snap      = 16; /* snap pixel */
static const unsigned int gappih    = 20; /* horiz inner gap between windows */
static const unsigned int gappiv    = 20; /* vert inner gap between windows */
static const unsigned int gappoh    = 20; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20; /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;  /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;  /* 0 means no bar */
static const int topbar             = 1;  /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=12" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=10";
static const char col_rose[]        = "#f4dbd6";
static const char col_pink[]        = "#f5bde6";
static const char col_base[]        = "#24273a";
static const char col_surface[]     = "#363a4f";
static const char col_overlay[]     = "#6e738d";
static const char col_lavender[]    = "#b7bdf8";
static const char *colors[][3]      = {
  /*               foreground   background    border   */
  [SchemeNorm] = { col_rose,    col_base,     col_overlay },
  [SchemeSel]  = { col_pink,    col_base,  col_lavender  },
};

/*****************************************/
/*                TAGGING                */
/*****************************************/
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
  /*  xprop(1):
   *	  WM_CLASS(STRING) = instance, class
   *	  WM_NAME(STRING) = title
   */
  /* class          instance    title     tags mask   isfloating   monitor */
  { "st",           NULL,       NULL,     0,          1,           -1 },
  { "blueman",      NULL,       NULL,     0,          1,           -1 },
  { "Firefox",      NULL,       NULL,     1 << 1,     0,           -1 },
};

/*****************************************/
/*               LAYOUT(S)               */
/*****************************************/
static const float mfact          = 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster          = 1;    /* number of clients in master area */
static const int resizehints      = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen   = 1;    /* 1 will force focus on the fullscreen window */
static const int refreshrate      = 60;   /* refresh rate (per second) for client move/resize */
static const int attachdirection  = 2;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
#define FORCE_VSPLIT 1      /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },     /* first entry is default */
  { "[M]",      monocle },
  { "H[]",      deck },
  { "TTT",      bstack },
  { "[\\]",     dwindle },
  { "|M|",      centeredmaster },
  { "><>",      NULL },     /* no layout function means floating behavior */
  { "[@]",      spiral },
  { "###",      nrowgrid },
  { "---",      horizgrid },
  { ":::",      gaplessgrid },
  { "===",      bstackhoriz },
  { "HHH",      grid },
  { ">M>",      centeredfloatingmaster },
  { NULL,       NULL },
};

/*****************************************/
/*            KEY DEFINITIONS            */
/*****************************************/
#include <X11/XF86keysym.h>
#include "unfloat.c"
#include "movestack.c"
#define MODKEY Mod4Mask
#define METAKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,  view,         {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,  toggleview,   {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,  tag,          {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,  toggletag,    {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/***** COMMANDS DEFAULT ********/
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
/***** AUDIO AND BACKLIGHT ****/
static const char *volup[]    = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@",   "5%+", "-l", "1.0", NULL };
static const char *voldown[]  = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@",   "5%-", NULL };
static const char *volmute[]  = { "wpctl", "set-mute",   "@DEFAULT_AUDIO_SINK@",   "toggle", NULL };
static const char *micmute[]  = { "wpctl", "set-mute",   "@DEFAULT_AUDIO_SOURCE@", "toggle", NULL };
static const char *litup[]    = { "light", "-A", "5", NULL };
static const char *litdown[]  = { "light", "-U", "5", NULL };
/***** PROGRAMS ***************/
static const char *kittycmd[]   = { "kitty", NULL };
static const char *roficombi[]  = { "rofi", "-show", "combi", NULL };
static const char *rofidrun[]   = { "rofi", "-show", "drun", NULL };
static const char *yazifile[]   = { "kitty", "-e", "yazi", NULL };
static const char *nvimstart[]  = { "kitty", "-e", "nvim", NULL };

static const Key keys[] = {
  /* modifier                       key           function          argument */
  { MODKEY,                         XK_n,	        spawn,            {.v = dmenucmd } },
  { MODKEY|ShiftMask,               XK_n,	        spawn,            {.v = termcmd } },
  { MODKEY,                         XK_b,        	togglebar,        {0} },
  /******* STACK ***************************************************/
  { MODKEY,                         XK_j,        	focusstack,       {.i = +1 } },
  { MODKEY,                         XK_k,        	focusstack,       {.i = -1 } },
  { MODKEY|ShiftMask,               XK_j,        	movestack,        {.i = +1 } },
  { MODKEY|ShiftMask,               XK_k,        	movestack,        {.i = -1 } },
  { MODKEY,                         XK_i,        	incnmaster,       {.i = +1 } },
  { MODKEY|ShiftMask,               XK_i,        	incnmaster,       {.i = -1 } },
  { MODKEY,                         XK_h,        	setmfact,         {.f = -0.05} },
  { MODKEY,                         XK_l,        	setmfact,         {.f = +0.05} },
  { MODKEY|ShiftMask,               XK_h,        	setcfact,         {.f = +0.25} },
  { MODKEY|ShiftMask,               XK_l,        	setcfact,         {.f = -0.25} },
  { MODKEY,                         XK_p,        	setcfact,         {.f =  0.00} },
  { MODKEY,                         XK_o,         zoom,             {0} },
  { MODKEY,                         XK_q,         killclient,       {0} },
  /******* GAPS ****************************************************/
  { MODKEY|ControlMask,             XK_u,        	incrgaps,         {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask,   XK_u,        	incrgaps,         {.i = -1 } },
  { MODKEY|ControlMask,             XK_i,        	incrigaps,        {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask,   XK_i,        	incrigaps,        {.i = -1 } },
  { MODKEY|ControlMask,             XK_o,        	incrogaps,        {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask,   XK_o,        	incrogaps,        {.i = -1 } },
  { MODKEY|ControlMask,             XK_h,        	incrihgaps,       {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask,   XK_h,        	incrihgaps,       {.i = -1 } },
  { MODKEY|ControlMask,             XK_j,        	incrivgaps,       {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask,   XK_j,        	incrivgaps,       {.i = -1 } },
  { MODKEY|ControlMask,             XK_l,        	incrohgaps,       {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask,   XK_l,        	incrohgaps,       {.i = -1 } },
  { MODKEY|ControlMask,             XK_k,        	incrovgaps,       {.i = +1 } },
  { MODKEY|ControlMask|ShiftMask,   XK_k,        	incrovgaps,       {.i = -1 } },
  { MODKEY|ControlMask,             XK_p,         togglegaps,       {0} },
  { MODKEY|ControlMask|ShiftMask,   XK_p,         defaultgaps,      {0} },
  /******* LAYOUTS *************************************************/
  { MODKEY|METAKEY,                 XK_1,         setlayout,        {.v = &layouts[0]} },
  { MODKEY|METAKEY,                 XK_2,         setlayout,        {.v = &layouts[1]} },
  { MODKEY|METAKEY,                 XK_3,         setlayout,        {.v = &layouts[2]} },
  { MODKEY|METAKEY,                 XK_4,         setlayout,        {.v = &layouts[3]} },
  { MODKEY|METAKEY,                 XK_5,         setlayout,        {.v = &layouts[4]} },
  { MODKEY|METAKEY,                 XK_6,         setlayout,        {.v = &layouts[5]} },
  { MODKEY|METAKEY,                 XK_7,         setlayout,        {.v = &layouts[6]} },
  { MODKEY|METAKEY,                 XK_8,         setlayout,        {.v = &layouts[7]} },
  { MODKEY|METAKEY,                 XK_9,         setlayout,        {.v = &layouts[8]} },
  { MODKEY|METAKEY,                 XK_o,         setlayout,        {0} },
  { MODKEY|METAKEY,                 XK_p,         togglefloating,   {0} },
  { MODKEY|METAKEY|ShiftMask,       XK_p,         unfloatvisible,   {0} },
  { MODKEY|METAKEY|ShiftMask,       XK_1,         unfloatvisible,   {.v = &layouts[0]} },
  { MODKEY|METAKEY|ShiftMask,       XK_2,         unfloatvisible,   {.v = &layouts[1]} },
  { MODKEY|METAKEY|ShiftMask,       XK_3,         unfloatvisible,   {.v = &layouts[2]} },
  { MODKEY|METAKEY|ShiftMask,       XK_4,         unfloatvisible,   {.v = &layouts[3]} },
  { MODKEY|METAKEY|ShiftMask,       XK_5,         unfloatvisible,   {.v = &layouts[4]} },
  { MODKEY|METAKEY|ShiftMask,       XK_6,         unfloatvisible,   {.v = &layouts[5]} },
  { MODKEY|METAKEY|ShiftMask,       XK_7,         unfloatvisible,   {.v = &layouts[6]} },
  { MODKEY|METAKEY|ShiftMask,       XK_8,         unfloatvisible,   {.v = &layouts[7]} },
  { MODKEY|METAKEY|ShiftMask,       XK_9,         unfloatvisible,   {.v = &layouts[8]} },
  { MODKEY|METAKEY,					XK_i,		  fullscreen,		{0} },
  { MODKEY|METAKEY,				    XK_u,         togglefullscreen, {0} },
  /******* MONITOR *************************************************/
  { MODKEY,                         XK_comma,     focusmon,         {.i = -1 } },
  { MODKEY,                         XK_period,    focusmon,         {.i = +1 } },
  { MODKEY|ShiftMask,               XK_comma,     tagmon,           {.i = -1 } },
  { MODKEY|ShiftMask,               XK_period,    tagmon,           {.i = +1 } },
  /******* TAGS ****************************************************/
  { MODKEY,                         XK_0,         view,             {.ui = ~0 } },
  { MODKEY|ShiftMask,               XK_0,         tag,              {.ui = ~0 } },
  { MODKEY,                         XK_Tab,       view,             {0} },
  { MODKEY,                         XK_Right,     viewnext,         {0} },
  { MODKEY,                         XK_Left,      viewprev,         {0} },
  { MODKEY|ShiftMask,               XK_Right,     tagtonext,        {0} },
  { MODKEY|ShiftMask,               XK_Left,      tagtoprev,        {0} },
  TAGKEYS(                          XK_1,                           0)
  TAGKEYS(                          XK_2,                           1)
  TAGKEYS(                          XK_3,                           2)
  TAGKEYS(                          XK_4,                           3)
  TAGKEYS(                          XK_5,                           4)
  TAGKEYS(                          XK_6,                           5)
  TAGKEYS(                          XK_7,                           6)
  TAGKEYS(                          XK_8,                           7)
  TAGKEYS(                          XK_9,                           8)
  { MODKEY|ShiftMask,               XK_Escape,    quit,             {0} },
  /******* AUDIO AND BACKLIGHT CONTROL *******************/
  { 0,                XF86XK_AudioRaiseVolume,    spawn,  {.v = volup } },
  { 0,                XF86XK_AudioLowerVolume,    spawn,  {.v = voldown } },
  { 0,                XF86XK_AudioMute,           spawn,  {.v = volmute } },
  { 0,                XF86XK_AudioMicMute,        spawn,  {.v = micmute } },
  { 0,                XF86XK_MonBrightnessUp,     spawn,  {.v = litup } },
  { 0,                XF86XK_MonBrightnessDown,   spawn,  {.v = litdown } },
  /******* PROGRAMS AND SERVICES *************************/
  { MODKEY,           XK_t,         spawn,  {.v = kittycmd  } },
  { MODKEY,           XK_r,         spawn,  {.v = roficombi } },
  { MODKEY,           XK_e,         spawn,  {.v = rofidrun  } },
  { MODKEY,           XK_y,         spawn,  {.v = yazifile  } },
  { MODKEY,           XK_v,         spawn,  {.v = nvimstart } },
};

/*****************************************/
/*          BUTTON DEFINITIONS           */
/*****************************************/
// #include "buttons/buttons.h"
//#define STATUSBAR "slstatus" /* for statuscmd signal patch */
/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
  /* function     identifier */
	{ "hello",    5 },
	// { backlight,    2 },
	// { batt_cap,     3 },
	// { datetime,     4 },
	// { network,      4 },
	// { cpu_perc,     4 },
	// { ram_perc,     4 },
	// { loadavg,      4 },
	// { net_tx,       4 },
	// { net_rx,       4 },
};
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };
// static const char *open[]  = { "kitty", "-e", "", NULL };

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click            event mask    button      function          argument */
  { ClkLtSymbol,      0,            Button1,    setlayout,        {0} },
  { ClkLtSymbol,      0,            Button3,    setlayout,        {.v = &layouts[2]} },
  { ClkWinTitle,      0,            Button2,    zoom,             {0} },
  { ClkStatusText,    0,            Button1,    spawn,            {.v = statuscmd } },
  { ClkStatusText,    0,            Button2,    spawn,            {.v = statuscmd } },
  { ClkStatusText,    0,            Button3,    spawn,            {.v = statuscmd } },
  { ClkClientWin,     MODKEY,       Button1,    movemouse,        {0} },
  { ClkClientWin,     MODKEY,       Button2,    togglefloating,   {0} },
  { ClkClientWin,     MODKEY,       Button3,    resizemouse,      {0} },
  { ClkTagBar,        0,            Button1,    view,             {0} },
  { ClkTagBar,        0,            Button3,    toggleview,       {0} },
  { ClkTagBar,        MODKEY,       Button1,    tag,              {0} },
  { ClkTagBar,        MODKEY,       Button3,    toggletag,        {0} },
};

