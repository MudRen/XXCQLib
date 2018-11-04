// Room: 偏院
// Date: by godzilla 1999.11.18

inherit ROOM;

void create()
{
	set("short", "偏院");
	set("long", @LONG
这是靠西边的一个小院字。周围的围墙爬满了青藤，墙边的花坛
杂草丛生，几朵盛开的野花到也别致，时不时还引来蜂蝶，给这里带
来一片生机。南边是一间柴房。
LONG );
        set("outdoors", "tianyu");
	set("exits", ([
	        "east" : __DIR__"qianyuan", 
		"south"  : __DIR__"chaifang",
        "north"  : __DIR__"jijian",

		]));
	setup();
	replace_program(ROOM);
}
