// Room: xiaochi.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "小吃店");
        set ("long", @LONG
这里是桂林镇上的唯一的小吃店，许多壮族人都要来这里吃东西。这
里的饭菜比许多本地人做的都好吃。在这里可以买到一些桂林名菜和风味
小吃。这里也是桂林镇唯一不是壮族人开的店铺。
LONG);
        set("area","桂林");
	set("valid_startroom", 1);

        set("objects", ([
                __DIR__"npc/afa" : 1,
        ]));

        set("exits", ([
                "east" : __DIR__"zhongxin",
        ]));
        setup();
        replace_program(ROOM);
}

