// Room: shanlu3.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
脚下是一条小土路，盘旋上山，向北上一段路就是落神岭了，没有过
落神岭之前你看不到岭那边的任何东西。江湖白道领袖刀柄会六大支柱之
一的飞鱼堂据说就在岭的那边。
LONG);
        set("area","飞鱼");
        set("outdoors", "feiyu");

        set("exits", ([
                "northup" : __DIR__"luoshenling",
                "eastdown" : __DIR__"shanlu5",
        ]));
        setup();
        replace_program(ROOM);
}