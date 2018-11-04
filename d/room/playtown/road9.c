// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit ROOM;

void create()
{
	set("short","青砖路");
	set("long",@LONG
这是一条非常平整的青砖铺成的路，北面是一个非常别致的小花
园，东南面是一个三岔口。
LONG );
	set("recordable_room",1);
	set("outdoors","playertown");	
	set("exits",([
		"northeast" : __DIR__"huayuan1",
		"west" : __DIR__"road11",
		"southeast" : __DIR__"road8",
	]));
	setup();
	replace_program(ROOM);
}
