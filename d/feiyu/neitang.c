// Room: neitang.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "内堂");
        set ("long", @LONG
这里是飞鱼塘主沈星南授徒的地方，所以很宽阔。东西两墙上挂着刀
和剑。正北的墙上是一幅巨大的山水画。东南方和西南方的两个门是很显
然是从前厅来这里的两个偏厅。向两边看去，可以看见弟子们在武院里练
功夫。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("objects", ([
                 "/kungfu/class/feiyu/shenxingnan" : 1,
        ]));

        set("exits", ([
                "southwest" : __DIR__"xipianting",
                "southeast" : __DIR__"dongpianting",
                "east" : __DIR__"dongwuyuan",
                "west" : __DIR__"xiwuyuan",
         ]));

        setup();
}

void init()
{
        object me = this_player();
        if (me->query_temp("feiyutask/given")) me->set_temp("di1mark", 1);
        return;
}
