// hongbujie4.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "红布街");
	set("long", @LONG

 这里是全国闻名的大街，是一条宽阔的青石板街道。两边都是民宅。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("outdoors", "bianliang");
	set("exits", ([
		"north" : __DIR__"hongbujie3",
		"south" : __DIR__"hongbujie5",
		"west" : __DIR__"minzhai1",
		"east" : __DIR__"minzhai2",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
