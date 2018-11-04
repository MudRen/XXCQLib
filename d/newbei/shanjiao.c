// 山猫ADX by snow 99-12-4

#include <ansi.h>
inherit ROOM;

void create ()
{
	set("short",  "神雪山脚");
	set("long",
"这里是神雪山的山脚，一条用长条石铺成的抬价拾级而上。可以隐约\n"
"看到山腰有一座山庄大红色的屋顶掩映在绿树丛中。\n"
"抬头就可以看到高高的神雪峰: \n"
);
	set("exits",  ([
		"westup"  :  __DIR__"shanyao",
		"eastdown"  :  __DIR__"road8",
	]));
	set("outdoors",  1);
	setup();
	replace_program(ROOM);
}
