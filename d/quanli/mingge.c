//mingge。c  by god

#include <room.h>
#include <skill.h>

inherit ROOM;

void create()
{	
	set("short", "权力殿");
	set("long", @LONG
这里是权力帮的大殿.

LONG);	
	set("valid_startroom",1);
	set("objects",([
	]));
	set("exits",([
		"east" : __DIR__"huozoulang",
		"south" : __DIR__"dati",
	]));

        set("area", "权力帮");
        set("objects",([
           __DIR__"npc/liu" : 1,
        ]));
        setup();
            replace_program(ROOM);
}
