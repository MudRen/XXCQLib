// hongbujie5.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "红布街");
	set("long", @LONG
这里是全国闻名的大街，东边是一座高大的院子，半月形的大门上方写着
“紫旗磨房”四个大字，西边是个民宅。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("outdoors", "bianliang");
	set("exits", ([
		"north" : __DIR__"hongbujie4",
		"south" : __DIR__"hongbujie6",
		"west" : __DIR__"minzhai3",
		"east" : __DIR__"ziqimofang",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
