// Room: huoroad5.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.4.16
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
这里是到“活字号”的山路，路旁种的都是一些奇异花草。
说不定这些花草是有毒的？还是快些离开这里吧。向西走是山
路，向南下去还是山路。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("exits", ([
                "west" : __DIR__"huoroad4",
                "southdown" : __DIR__"huoroad6",
        ]));
        setup();
        replace_program(ROOM);
}
