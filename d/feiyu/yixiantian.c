// Room: yixiantian.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "一线天");
        set ("long", @LONG
这里往南就是飞鱼塘的天险之一“一线天”了。两旁高耸的峭壁间只
有一条窄窄的小路，刚好可以并肩过去两个人。一线天的出口是飞鱼塘守
卫最森严的地方。飞鱼塘建立一百七十年来，这里从来没有失守过。
LONG);
        set("area","飞鱼");
        set("outdoors", "feiyu");

        set("objects", ([
                __DIR__"npc/feiyudizi" : 2,
        ]));

        set("exits", ([
                "northwest" : __DIR__"shanlu1",
                "southdown" : __DIR__"yixiantiannei",
        ]));
        setup();
        replace_program(ROOM);
}
