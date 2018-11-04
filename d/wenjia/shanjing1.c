// Room: shanjing1.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.10
// 修改长描述。
// 

inherit ROOM;
void create ()
{
        set ("short", "山间小径");
        set ("long", @LONG
这里是一条弯弯曲曲的山间小径一直向西南方延伸着。小径
两边都是奇怪的岩石，周围没有一个人影。向西走就可以回到西
广场。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("exits", ([
                "east" : __DIR__"westsquare",
                "northwest" : __DIR__"shanjing2",
        ]));
        setup();
        replace_program(ROOM);
}
