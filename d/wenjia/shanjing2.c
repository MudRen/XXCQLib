// Room: shanjing2.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.4.17
// 修改长描述。增加摔交。
// 

#include <ansi.h>

inherit ROOM;
void create ()
{
        set ("short", "山间小径");
        set ("long", @LONG
这条小径两边都是陡峭的山壁，小径非常倾斜，一直向南面
延伸，通往一片树林。这里一不小心就会摔跤。向东南方走就会
回到那条平坦的小径。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("exits", ([
                "southeast" : __DIR__"shanjing1",
                "northdown" : __DIR__"shulin1",
        ]));
        setup();
}

void init()
{
        object me = this_player();
	
        if( random((int)me->query_skill("dodge")) <= 20) 
        {
                me->receive_damage("qi", 50);
                me->receive_wound("qi",  50);
                message_vision(HIR"$N一不小心脚下踏了个空，... 啊...！\n"NOR, me);
                me->move(__DIR__"shulin1");
                tell_object(me, HIR"你沿着小径滚了下来，只觉得浑身无处不疼，还受了几处伤。\n"NOR);
                message("vision", HIR"只见" + me->query("name") + "从山上骨碌碌地滚了下来，躺在地上半天爬不起来！\n"NOR, environment(me), me);
        }
}
		

