//By adx by snow 99-12-5

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", WHT"练功房"NOR);
	set("long",
"这里是武馆的练功房，大块的青砖铺地，空荡荡的一个大房间里\n"
"除了几个武馆的陪练弟子在练功外没有其他的东西，你可以和陪练弟子\n"
"比武"+HIC"(finger peilian)"NOR+"也可以直接攻击"+
HIC"(hit peilian)"NOR+"如果你打陪练弟子\n"
"不能增加潜能和战斗经验，就换一个房间试试。\n"
	);
	set("exits", ([
		"northeast" : __DIR__"houyuan",
	]));
        set("objects",([
                __DIR__"npc/peilian4":3,
                ]));
	setup();
	replace_program(ROOM);
}
