// bh_lukou4.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "路口");
	set("long", @LONG
这是个丁字路口，往西是半夜街，往东是苦水铺。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
//		"north" : __DIR__"bayezhuang",
		"south" : __DIR__"heibujie3",
		"west" : __DIR__"banyejie2",
		"east" : __DIR__"kushuipu1",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
