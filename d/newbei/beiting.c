//By 山猫adx by snow 99-12-5

#include <ansi.h>
inherit ROOM;

void create()
{
    set("short",WHT"神雪北侧厅"NOR);
    set("long",
"你走进一间不大的房间这里是神雪山的北侧厅，你可以在这里向神雪山\n"
"山主打听任务去做"+HIC"(ask motobaby about job)。\n"NOR
    );
        set("exits", ([
                "south":__DIR__"dating",
        ]));
        set("objects",([
                __DIR__"npc/moto":1,
                ]));
        set("no_fight", 1);
	setup();
        replace_program(ROOM);
}
