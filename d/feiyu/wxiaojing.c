// Room: wxiaojing.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create ()
{
        set ("short", "小径");
		set ("long", @LONG
这是一条青石铺成的小径，不知不觉已经走到了小径尽头。从这里再
向北走几步就到了飞鱼塘男休息室门前了。这条路上不时的有劲装打扮的
飞鱼弟子走过，看来飞鱼塘的弟子个个身怀绝技。南面隐约看得见一条小
路。
LONG);
        set("valid_startroom", 1);
        set("exits", 
            ([
		        "north" : __DIR__"nanxiuxishi",
		        "south" : __DIR__"xiyuan",
            ]));
        set("outdoors", "feiyu");
		setup();
}

int valid_leave(object me, string dir)
{
       me = this_player();

       if (  (dir == "north" )&& (me->query("gender") == "女性" )) 
	{
	 message_vision("$N一个姑娘家，要到男弟子寝室去做什么？", me);
	 return notify_fail("\n");
	}

	return ::valid_leave(me, dir);
}
