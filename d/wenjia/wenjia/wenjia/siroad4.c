// Room: siroad4.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.6.10
// 
// 

#include <ansi.h>

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
这里是到“死字号”的山路，路旁种的都是一些奇异花草。说不定这
些花草是有毒的？还是快些离开这里吧。西南上去是山路，向东下去还是
山路。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

        set("exits", ([
                "eastdown" : __DIR__"siroad3",
                "southwest" : __DIR__"siroad5",
        ]));

        setup();
}

void init()
{
        object me = this_player();
	
        if( me->query_skill("dodge",1) < 80) 
        {
                me->receive_wound("qi",  100);
                message_vision(HIR"$N一不小心脚下踏了个空，……啊……！\n"NOR, me);
                me->move(__DIR__"eastsquare");
                tell_object(me, HIR"你沿着山路滚了下来，只觉得浑身无处不疼，还受了几处伤。\n"NOR);
                message("vision", HIR"只见" + me->query("name") + "从山上骨碌碌地滚了下来，躺在地上半天爬不起来！\n"NOR, environment(me), me);
        }
}
