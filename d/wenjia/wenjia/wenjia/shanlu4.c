// Room: shanlu4.c
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
一条人由人踩出来的山路，这里已经可以遥遥的看见北面温家的大牌
坊。“已经到温家了”你心里这样想着。路过的温家弟子从身边的时候，
他们都会回头看看你，似乎觉得你很怪。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("objects", ([
                __DIR__"npc/wenjiadizi" : 1,
        ]));

        set("exits", ([
                "eastdown" : __DIR__"banshan",
                "north" : __DIR__"paifang",
        ]));
        setup();
        replace_program(ROOM);
}
