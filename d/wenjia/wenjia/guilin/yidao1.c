// Room: yidao1.c
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
两边种植了一些矮矮的小树，整个景色显得有些苍凉。道路向东延伸是桂
林的漓江边了。而西北边却是长长的驿道。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("exits", ([
                "east" : __DIR__"lijiangbian1",
                "northwest" : __DIR__"yidao2",
        ]));
        setup();
        replace_program(ROOM);
}

