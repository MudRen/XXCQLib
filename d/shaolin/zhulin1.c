// Room: /d/shaolin/zhulin1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "竹林小道");
	set("long", @LONG
这是一条卵石铺成的小道，曲曲折折地通向前方。两边是密密的竹林
。这里人迹罕至，惟闻足底叩击路面，有僧敲木鱼声；微风吹拂竹叶，又
如簌簌禅唱。令人尘心为之一涤，真是绝佳的禅修所在。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"north" : __DIR__"zhulin2",
		"south" : __DIR__"zoulang8",
	]));
	set("outdoors", "shaolin");
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

