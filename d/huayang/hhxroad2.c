//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "浣花溪畔");
        set ("long", @LONG
从浣花桥向南走过这里就可以到浣花码头了，但其实只有浣花弟子在
这个码头上船，路东溪畔几个孩子在浅水处玩耍打闹，好不热闹偶尔也有
剑庐的丫鬟在这里洗衣服。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"north" : __DIR__"hhxroad1",
		"south" : __DIR__"hhmatou",
        ]));

	set("hhjob", 1);
        set("outdoors", "xiao");
        setup();
}