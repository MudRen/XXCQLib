// Room: lingqu.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "灵渠");
        set ("long", @LONG
我国古代伟大的水利工程就呈现在你眼前，这伟大的工程表现了我国
人民的智慧和伟大。你无法不为这一伟大的工程以喝彩。沿灵渠往西南走
就是一片漓江的堤岸。东北方向是地势较高的漓江上游。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "northeast" : __DIR__"lijiangbian2",
                "southwest" : __DIR__"jiangdi",
        ]));
        setup();
        replace_program(ROOM);
}

