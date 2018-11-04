// bingying2.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "兵营大门");
	set("long", @LONG
这是汴梁城守城驻军的主帅营地，大批的军队则驻扎在城外四周。这
支部队表面上是御林军的一支，实际上却是相爷的亲兵。这里不可久留，
还是离开为妙。驻军管带鲜于仇就在兵营里面。
LONG);	
	set("valid_startroom",1);

	set("exits", ([
		"west" : __DIR__"huangshanjie4",
		"east" : __DIR__"bingying22",
	]));

	set("objects", ([
		__DIR__"npc/bing1" : 1,
		__DIR__"npc/bing2" : 1,
	]));

	set("outdoors", "bianliang");
	set("area", "汴梁");

	setup();
}

int valid_leave(object me, string dir)
{
	me = this_player();

	if (dir == "east" ) 
	{
		if(objectp(present("shi bing", environment(me))))
			return notify_fail("士兵横枪拦住你斥道：不要命啦，将军营帐你也敢闯？？？\n");
	}

	return ::valid_leave(me, dir);
}