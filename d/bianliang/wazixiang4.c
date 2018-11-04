// wazixiang4.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "瓦子巷");
	set("long", @LONG
这里是汴梁城的瓦子巷,不过是一条小胡同而已。路上有十几个人影了。
在西边是纱行，在东边是果子行。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
		"north" : __DIR__"wazixiang3",
		"south" : __DIR__"wazixiang5",
		"west" : __DIR__"shahang",
		"east" : __DIR__"guozihang",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
