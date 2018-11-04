//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "土路");
        set ("long", @LONG
这是横穿小村庄的土路，土路边稀稀拉拉的有几家茅草房，偶尔有一
只鸡跑过，也是没精打采。路边晒着一些渔网，还有一些打上来的鱼，这
些就是渔民的粮食，路东则有一片难得一见的稻田。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"north" : __DIR__"tulu3",
		"southwest" : __DIR__"tulu5",
		"east" : __DIR__"maitian2",
		"west" : __DIR__"tulu8",
	]));

        set("outdoors", "zigui");
        setup();
}