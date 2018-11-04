// Room: xiwuyuan.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "西武院");
        set ("long", @LONG
这里是飞鱼女弟子集中练习的地方。可以见到几个人两两对练着。
西南方的路是通往西偏厅的，通过西面的门就到内堂了。
LONG);
        set("area"," 飞鱼");
        set("valid_startroom", 1);

        set("objects", ([
                      "/kungfu/class/feiyu/yemengse" : 1,
                       "/d/feiyu/npc/feiyudizi" : 2,
        ]));
		set("exits", ([
                "southeast" : __DIR__"xipianting",
                "east" : __DIR__"neitang",   
        ]));

        setup();
        replace_program(ROOM);
}
