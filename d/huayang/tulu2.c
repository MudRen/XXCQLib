//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "土路");
        set ("long", @LONG
这是一条被行人踩出来的土路，路上的行人很是不少，大多是来百花
潭的游人，也有一些是浣花弟子和来浣花拜师的人。路的两旁花草丛生，
路的西北就是百花潭，东面是一片树林，穿过树林就到了华阳小镇了。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"northeast" : __DIR__"baihuatan",
		"west" : __DIR__"treeroad3",
       ]));

        set("outdoors", "huayang");
        setup();
}