// Room: ziliaoshi1.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "资料室");
        set ("long", @LONG
这里是活字号的资料室，这里的资料与小字号的资料室的资料基本一
样。这里的资料是为研究解药而准备的。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("exits", ([
                "east" : __DIR__"yanjiushi",
        ]));

        setup();
        replace_program(ROOM);
}
