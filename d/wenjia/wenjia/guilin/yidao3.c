// Room: yidao3.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "驿道");
        set ("long", @LONG
朝廷传送公文的驿道，不时有马骑从身边经过。驿道上尘土飞扬，而
两边种植了一些矮矮的小树，整个景色显得有些苍凉。这里已经是四川境
内了。北边的道路一直向西北边延伸着。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "south" : __DIR__"yidao2",
                "northwest" : __DIR__"yidao4",
        ]));
        setup();
        replace_program(ROOM);
}

