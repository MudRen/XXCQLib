// matou.c

inherit ROOM;
#include <ansi.h>  

void create()
{
        set("short", "码头");
	set("long",@LONG
这是一个出入太湖的水上码头，只见人们来来往往，好不热闹。一个个
风尘仆仆，码头边的老船夫见到你走过来，马上笑呵呵的迎了上去。
LONG 
);
	set("outdoors","姑苏慕容");
	set("objects",([
	__DIR__"npc/laoda" : 1,
]));
	set("exits",([
	 "north" : __DIR__"sq",
]));
	setup();
	replace_program(ROOM);
}                                                           



