// Room: luoshenling.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21 
// 

inherit ROOM;
void create ()
{
        set ("short", "落神岭");
        set ("long", @LONG
这里就是飞鱼塘的天险之一“落神岭”了。两旁高耸的山峰间只有一
条山道，“落神岭”是飞鱼塘的对外总隘口，一直因为飞鱼塘的实力与出
产，所以一直都很旺盛。但因为在“人止关”之前，所以对飞鱼塘的位置
环境完全观望不到。
LONG);
        set("area","飞鱼");
        set("outdoors", "feiyu");

        set("objects", ([
		__DIR__"npc/feiyudizi" : 2,
        ]));

        set("exits", ([
		"northdown" : __DIR__"shanlu3",
		"southdown" : __DIR__"shanlu4",
	]));
        setup();
}

void init()
{
        object me = this_player();
        if (me->query_temp("feiyutask/given")) me->set_temp("di4mark", 1);
        return;
}