#ifndef _GLOBALDEFINE_H_
#define _GLOBALDEFINE_H_

#define SAFE_DELETE(p)	{if(p){delete p;p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[] p;p = NULL;}}
#define SAFE_NEW(p, type)	{if(NULL == p){p = new type;}}

#define RECT_WIDTH(rc)	(rc.right - rc.left)
#define RECT_HEIGHT(rc) (rc.bottom - rc.top)

//  Network or standalone mode
//#define NETWORK_MODE
#define MAGIC_PLAY_OFTX		8
#define MAGIC_PLAY_OFTY		8

#define ARGB_WHITE	ARGB(255, 255, 255, 255)
#define ARGB_RED	ARGB(255, 255, 0, 0)
#define ARGB_GREEN	ARGB(255, 0, 255, 0)
#define ARGB_BLUE	ARGB(255, 0, 0, 255)
#define ARGB_YELLOW	ARGB(255, 255, 255, 0)
#define ARGB_BLACK	ARGB(255, 0, 0, 0)

#define COLOR_SYSTEM	0xffe53fc8
#define COLOR_PRIVATECHAT		0xff1E90FF

#define MOUSE_SEARCH_X			2
#define MOUSE_SEARCH_Y			2

#define FONT_WIDTH_WORD			12
#define FONT_HEIGHT_WORD		12
#define FONT_WIDTH_NUMBER		6
#define FONT_HEIGHT_NUMBER		6

#define VIEW_OFFSET				25
#define INVALID_ITEM_ID			-1

#define MAX_ATTACK_INTERVAL		140.0f
#define MAX_MOVE_INTERVAL		160.0f

#define _PI_					3.141592

//  Floor item drop offset
#define FLOOR_ITEM_OFFSET		4

//  HP display mode: NORMAL = direct, SPECL = based on difference 1:1
#define ADD_NORMAL				0
#define ADD_SPECL				1

//  Equipment description line count
#define BREAK_NUMBER			28

//  Running skill distance
#define RUN_HYPO_DISTANCE		120
//  Walking skill distance
#define WALK_HYPO_DISTANCE		0

//  Direction flags
#define DRT_UP					0x01
#define DRT_RIGHTUP				(DRT_RIGHT | DRT_UP)
#define DRT_RIGHT				0x02
#define DRT_RIGHTDOWN			(DRT_RIGHT | DRT_DOWN)
#define DRT_DOWN				0x04
#define DRT_LEFTDOWN			(DRT_LEFT | DRT_DOWN)
#define DRT_LEFT				0x08
#define DRT_LEFTUP				(DRT_LEFT | DRT_UP)

//  Max magic count
#define MAX_MGC_NUM				20

//  Max say text length
#define MAX_SAY_LENGTH			80

//  Player direction
enum PLAYER_DIRECTION
{
	PDT_UP = 0,
	PDT_RIGHTUP,
	PDT_RIGHT,
	PDT_RIGHTDOWN,
	PDT_DOWN,
	PDT_LEFTDOWN,
	PDT_LEFT,
	PDT_LEFTUP,
};

//  Player status
enum PLAYER_STATUS
{
	PST_NONE,
	PST_STAND,
	PST_WALK,
	PST_RUN,
	PST_ATTACKSTOP,
	PST_ATTACKNOWEAPON,
	PST_ATTACKWEAPON,
	PST_FORCEATTACK,
	PST_SK_LEIDIANSHU,
	PST_WAROU,
	PST_ATTACKED,
	PST_DEAD,
	PST_GROUND,
	PST_APPEAR,
	PST_SHOW,
	PST_SLEEP,
	PST_WAKE,
	PST_EXT1,
	PST_EXT2,
	PST_EXT3,
	PST_EXT4
};

//  Player sex
enum PLAYER_SEX
{
	PSX_NONE,
	PSX_MAN,
	PSX_WOMAN,
};

//  Object type
enum OBJECT_TYPE
{
	OBJ_NPC,
	OBJ_MONS,
	OBJ_PLAYER,
	OBJ_OTHERPLAYER,
	OBJ_SELF,
	OBJ_UNKNOW,
};

//  Job class
#define JOB_DC	0
#define JOB_MC	1
#define JOB_SC	2

//  Custom messages
#define WM_DLG_BRINGTOTOP	(0x0400 + 1)
//  Socket message
#define WM_SOCKMSG			(0x0400 + 2)
//  Scene switch progress
#define WM_SCENE_PROG		(0x0400 + 3)
//  Enter game scene
#define WM_ENTER_GAMESCENE	(0x0400 + 4)
//  Return to character select
#define WM_BACK_SELCHR		(0x0400 + 5)
//  Hide assist window
#define WM_HIDE_ASSITWND	(0x0400 + 6)

//  Timer IDs
#define TIMER_CONNECTSVR	(101)
#define TIMER_CONNTIMEOUT	(102)
#define TIMER_CLOSEGAME		(103)
#define TIMER_LOADDATA		(104)
#define TIMER_RUNGAME		(105)
#define TIMER_FTYPETIMEOUT	(106)
#define TIMER_STYPETIMEOUT	(107)
#define TIMER_VERIFYTIMEOUT	(108)
#define TIMER_SEND_LOGIN_HEARTBEAT	(109)

#define TIMER_PRECONN_UPDATE (100)

//  Scene IDs
#define SCENE_LOGIN		0
#define SCENE_SELCHR	1
#define SCENE_GAME		2

//  Extra-attribute display descriptors (indexed by extraAttrib.nAttribID).
//  Stub strings — real names are loaded from lua config in production builds.
extern const char* g_szExtraAttribDescriptor[];

//  Walking cost interval in ms (frame budget for walk action)
#ifndef NORMAL_WALK_COST_TIME
#define NORMAL_WALK_COST_TIME    300
#endif

//  Save-mask bit signaling that an EXP delta must NOT be persisted.
#ifndef EXPR_MASK_NOSAVE
#define EXPR_MASK_NOSAVE         0x80000000u
#endif

#endif
