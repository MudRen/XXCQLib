// xiting.c 西厅
// mlf设计,lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","西厅");
        set("long",
"这里是花府接待亲朋好友的地方，案头茶几上放着四时鲜果，精细茶
点，透者主人的细心周到。临近花首领的花甲大寿，这里更是装点的涣然
一新。仆人和丫鬟都在忙里忙外的四处奔走。\n"
	);
	set("valid_startroom",1);
	set("exits",([
		"east" : __DIR__"zoulang3",
		"north" : __DIR__"xixiangfang",
	]));
	setup();
	replace_program(ROOM);
}
