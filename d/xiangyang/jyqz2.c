//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "金银钱庄后厅");
        set ("long", @LONG
走进金银钱庄后厅，就看到一个金衣金服，硕大无朋的大汉做在那里
，身旁放着一根金刚杵，看到你近来，牛眼一瞪，吓得你达了一个冷战。
他就是钱庄总管管八方了。东面有一间偏房是睡房。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"south" : __DIR__"jyqz",
		"east" : __DIR__"sleep",
	]));

	set("objects", ([
//		__DIR__"npc/cheng": 1,
	]));

        setup();
}