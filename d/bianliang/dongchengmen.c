// dongchengmen.c  by winder

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "东城门");
	set("long", @LONG
 这是东城门，城门正上方刻着“东门”两个楷书大字。

LONG);	
//	set("valid_startroom",1);
//	set("no_steal", "1");
//	set("no_fight", "1");
//	set("sleep_room",1);
	set("exits", ([
		"west" : __DIR__"huangkudajie10",
        "east" : __DIR__"guandao3",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
	replace_program(ROOM);
}
