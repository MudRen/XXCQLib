// Room: working.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "还未创造的空间入口");
        set ("long", @LONG
这里是一个还未创造的空间入口，只见一个人穿着太空服，坐在一部
流动工程平台上(SCV)，指挥着一群Zerging干着活。那个穿太空服的人应
该是温老幺吧?
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "northeast" : __DIR__"guishulin3",
        ]));
        setup();
        replace_program(ROOM);
}

