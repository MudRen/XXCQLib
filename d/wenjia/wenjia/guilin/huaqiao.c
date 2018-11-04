// Room: huaqiao.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "花桥");
        set ("long", @LONG
一座桥跨过漓江上游的水路，连接了桂林镇与壮族居住地。这座桥叫
做“花桥”，桥是用石头做成，桥有房顶，可以用来避雨。从西北方上去
就是桂林镇中心。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("objects", ([
                __DIR__"npc/zzwoman" : 1,
        ]));

        set("exits", ([
                "northwest" : __DIR__"zhongxin",
                "southeast" : __DIR__"jiangdi1",
        ]));
        setup();
        replace_program(ROOM);
}

