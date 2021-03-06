// globals.h
// this file will be automatically included by the driver
// for XKX mudlib, by Xiang

#ifndef __SENSIBLE_MODIFIERS__
#define protected static
#define nosave static
#endif
//added by DayDream
#define SAVE_EXTENSION __SAVE_EXTENSION__
//Solove the problem of MudOS version
#define NO_MUDLIST 0
// Add by Find for maze.
#define VRM_SERVER		"/adm/daemons/vrm_server"

//added for SNOW
#define YIZHAN	"/clone/room/mache.h"
#define MATOU		"/inherit/room/matou"

//added by Doing @ CCTX
#define PRIVATE_ROOM	"/inherit/private_room.c"
#define RECORDABLE_ROOM	"/inherit/recordable_room.c"
#define ROOM_D		"/adm/daemons/roomd.c"

// 增加帮会的函数调用 adx @ CCTX
#define BANGHUI_D       "/adm/daemons/banghuid" //帮会
#define F_BUKUAI        "/feature/bukuai"       //捕快

//added by JackyBoy @ CCTX
#define USERS   "/adm/etc/users"
#define IDUSER  "/adm/etc/iduser"
#define REGROOM "/inherit/room/regroom"
#define EMAIL_D "/adm/daemons/emaild"
#define BACKUP_D        "/adm/daemons/backupd"
#define NCLOTH "/clone/misc/cloth"
#define BID_ROOM	"/inherit/Save/bidroom"
#define SR_DEALER	"/inherit/Save/dealer"
#define SR_BANK "/inherit/Save/bank.c"
#define SR_DANGPU	"/inherit/Save/dangpu"
#define F_VI		"/feature/vi"
#define F_PAWN	"/feature/pawn"
#define PAWN		"/feature/pawn"
#define F_BANKER		"/feature/banker"
#define QUEST_OB		"/feature/quest_list"
#define EXPLIST		"/clone/quest/explist"
//added by JackyBoy @ CCTX for TOPTEN
#define TOPTEN_RICH 	"/topten/rich.txt"
#define TOPTEN_PKER	"/topten/pker.txt"
#define TOPTEN_EXP	"/topten/exp.txt"
#define TOPTEN_SHEN1	"/topten/shen1.txt"
#define TOPTEN_SHEN2	"/topten/shen2.txt"
#define TOPTEN_NEILI	"/topten/neili.txt"
#define RICH_B 		"《小雪初晴》TOP TEN十大富人排行榜"
#define PKER_B 		"《小雪初晴》TOP TEN十大杀人狂排行榜"
#define EXP_B  		"《小雪初晴》TOP TEN十大EXP高手排行榜"
#define SHEN1_B		"《小雪初晴》TOP TEN十大侠客排行榜"
#define SHEN2_B		"《小雪初晴》TOP TEN十大魔头排行榜"
#define NEILI_B		"《小雪初晴》TOP TEN十内力高手排行榜"

#define TOPTEN_D		"/adm/daemons/toptend"

// Important directories
#define INC_DIR		"/include/"
#define COMMAND_DIR	"/cmds/"
#define CONFIG_DIR	"/adm/etc/"
#define DATA_DIR		"/data/"
#define HELP_DIR		"/help/"
#define LOG_DIR		"/log/"
#define BACKUP_DIR      "/backup/"
#define DUMP_DIR        "/dump/"
#define TEMP_DIR        "/temp/"
#define STORY_DIR       "/adm/daemons/story/"

// Daemons
#define CONVERT_D		"/adm/daemons/languaged"
//本来应该是convertd.c，但是现在将两者合二为一
#define LANGUAGE_D		"/adm/daemons/languaged"
#define ALIAS_D		"/adm/daemons/aliasd"
#define BAN_D		"/adm/daemons/band"
#define CHANNEL_D		"/adm/daemons/channeld"
#define CHAR_D		"/adm/daemons/chard"
#define CHINESE_D		"/adm/daemons/chinesed"
#define COMBAT_D		"/adm/daemons/combatd"
#define COMMAND_D		"/adm/daemons/commandd"
#define EMOTE_D		"/adm/daemons/emoted"
#define FINGER_D		"/adm/daemons/fingerd"
#define FTP_D		"/adm/daemons/ftpd"
#define INQUIRY_D		"/adm/daemons/inquiryd"
#define LOGIN_D		"/adm/daemons/logind"
#define MONEY_D		"/adm/daemons/moneyd"
#define NATURE_D		"/adm/daemons/natured"
#define PIG_D		"/adm/daemons/pigd"
#define PROFILE_D		"/adm/daemons/profiled"
#define RANK_D		"/adm/daemons/rankd"
#define SECURITY_D "/adm/daemons/securityd"
#define UPDATE_D		"/adm/daemons/updated"
#define VIRTUAL_D		"/adm/daemons/virtuald"
#define WEAPON_D		"/adm/daemons/weapond"
#define COMPETE_D       "/adm/daemons/competed"


// End of appendence
#define CLASS_D(x)	("/kungfu/class/" + x)
#define SKILL_D(x)	("/kungfu/skill/" + x)
#define CONDITION_D(x)	("/kungfu/condition/" + x)

// Clonable/Non-inheritable Standard Objects
#define COIN_OB		"/clone/money/coin"
#define CORPSE_OB		"/clone/misc/corpse"
#define GOLD_OB		"/clone/money/gold"
#define LOGIN_OB		"/clone/user/login"
#define MASTER_OB		"/adm/obj/master"
#define MAILBOX_OB	"/clone/misc/mailbox"
#define SILVER_OB		"/clone/money/silver"
#define SIMUL_EFUN_OB	"/adm/obj/simul_efun"
#define USER_OB		"/clone/user/user"
#define VOID_OB		"/clone/misc/void"

// Inheritable Standard Objects
#define BANK		"/inherit/room/bank"
#define BULLETIN_BOARD	"/inherit/misc/bboard"
#define W_BOARD                  "/inherit/misc/wboard"
#define CHARACTER		"/inherit/char/char"
#define COMBINED_ITEM	"/inherit/item/combined"
#define EQUIP		"/inherit/misc/equip"
#define FORCE		"/inherit/skill/force"
#define HOCKSHOP		"/inherit/room/hockshop"
#define ITEM		"/inherit/item/item"
#define LIQUID		"/inherit/food/liquid"
#define MONEY		"/inherit/item/money"
#define NPC			"/inherit/char/npc"
#define PILL		"/inherit/medicine/pill"
#define POWDER		"/inherit/medicine/powder"
#define ROOM		"/inherit/room/room"
#define SKILL		"/inherit/skill/skill"

// User IDs

#define ROOT_UID		"Root"
#define BACKBONE_UID	"Backbone"

// Features
#define F_ENCODING			"/feature/encoding.c"
#define F_ACTION			"/feature/action.c"
#define F_ONEOWNER		"/feature/oneowner.c"
#define F_ALIAS			"/feature/alias.c"
#define F_APPRENTICE		"/feature/apprentice.c"
#define F_ATTACK			"/feature/attack.c"
#define F_ATTRIBUTE		"/feature/attribute.c"
#define F_AUTOLOAD		"/feature/autoload.c"
#define F_CLEAN_UP		"/feature/clean_up.c"
#define F_COMMAND			"/feature/command.c"
#define F_CONDITION		"/feature/condition.c"
#define F_DAMAGE			"/feature/damage.c"
#define F_DBASE			"/feature/dbase.c"
#define F_DEALER			"/feature/dealer.c"
#define F_EDIT			"/feature/edit.c"
#define F_EQUIP			"/feature/equip.c"
#define F_FINANCE			"/feature/finance.c"
#define F_FOOD			"/feature/food.c"
#define F_PILL			"/feature/pill.c"
#define F_LIQUID			"/feature/liquid.c"
#define F_MASTER			"/inherit/char/master.c"
#define F_MESSAGE			"/feature/message.c"
#define F_MORE			"/feature/more.c"
#define F_MOVE			"/feature/move.c"
#define F_NAME			"/feature/name.c"
#define F_SAVE			"/feature/save.c"
#define F_SKILL			"/feature/skill.c"
#define F_TEAM			"/feature/team.c"
#define F_TREEMAP			"/feature/treemap.c"
#define F_VENDOR			"/feature/dealer.c"
#define F_SSERVER			"/feature/sserver.c"
#define F_UNIQUE			"/feature/unique.c"
#define F_COMPETE		"/feature/compete.c"
// Profiling switches
//
// If you changed any of these defines, you'll need reboot to make it
// in effect.

#undef PROFILE_COMMANDS
