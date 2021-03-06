// huangshanjie5.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "黄衫街");
	set("long", @LONG
站在这里，你的西面就传来了阵阵香气，原来叁合楼就坐落在街的西
面，这座古老的酒楼里人声鼎沸，不断有人进进出出。路的东面挂着一个
长长得蓝布幌子，上面书有一个大大的“当”字。路的北面传来了阵阵操
练声，南面则是京城广场。
LONG);	
	set("valid_startroom",1);
	set("exits", ([
		"north" : __DIR__"huangshanjie4",
		"south" : __DIR__"guangchang",
         "west" : "/d/bianliang/jiulou/sanhelou",
		"east" : __DIR__"huang_dangpu",
	]));

	set("outdoors", "bianliang");

	set("area", "汴梁");

	setup();

	replace_program(ROOM);
}
