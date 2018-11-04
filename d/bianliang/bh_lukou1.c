// bh_lukou1.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "路口");
	set("long", @LONG
这里是个丁字路口，北边是小戒桥，人来人往，十分热闹，
南边就是瓦子巷。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
		"north" : __DIR__"xiaojieqiao",
		"south" : __DIR__"wazixiang1",
		"east" : __DIR__"tianshuixiang1",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
