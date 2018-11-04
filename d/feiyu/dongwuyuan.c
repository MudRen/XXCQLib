// Room: dongwuyuan.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "东武院");
        set ("long", @LONG
这里是飞鱼男弟子集中练习的地方。只见到几个人围在一起谈论着。
其余的都在各自练习着，西南方的路是通往东偏厅的，通过西面的门就到
内堂了。
LONG);
        set("area"," 飞鱼");
        set("valid_startroom", 1);

        set("objects", ([
                      "/kungfu/class/feiyu/yemengshen" : 1,
                       "/d/feiyu/npc/feiyudizi" : 2,
        ]));


        set("exits", ([
                "southwest" : __DIR__"dongpianting",
                "west" : __DIR__"neitang",   
        ]));

        setup();
        replace_program(ROOM);
}
