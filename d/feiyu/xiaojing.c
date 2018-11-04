// Room: xiaojing.c
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
向北走几步就到了飞鱼塘女休息室门前了。这条路上不时的有劲装打扮的
女子来来往往，看来飞鱼的女弟子毫不逊色于男弟子。南面隐约看得见一
座拱门。
LONG);
	    set("valid_startroom", 1);
        set("exits", 
	        ([
				"north" : __DIR__"girlroom",
				"south" : __DIR__"dongyuan",
			]));
	    set("outdoors", "feiyu");
        setup();
}

int valid_leave(object me, string dir)
{
       me = this_player();

       if (  (dir == "north" )&& (me->query("gender") == "男性" )) 
	{
	 message_vision("$N一个大男人，要到女弟子寝室去，有何企图？", me);
	 return notify_fail("\n");
	}

	return ::valid_leave(me, dir);
}
