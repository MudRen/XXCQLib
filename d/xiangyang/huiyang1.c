//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "惠阳街");
        set ("long", @LONG
惠阳街很短，几步就可以走到尽头，看到路西大大当字就知道西面是
一家当铺，看着匆匆走过的公差，大概可以猜到衙门就在街的南面。北面
就是秭归镇的中心了。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
         "east" : __DIR__"xyyizhan",
		"north" : __DIR__"zgcs",
		"south" : __DIR__"huiyang2",
	]));

        set("outdoors", "zigui");
        setup();
}
