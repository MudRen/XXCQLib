//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "草丛");
        set ("long", @LONG
沿着浣花溪向北走到这里土路已经渐渐的不见了，你的周围已是杂草
丛生，许多野花开得分外的茂盛，你穷目向北望了望，却什么也看不到，
还是返回去吧。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"south" : __DIR__"hhxroad3",
		"north" : __DIR__"hhxroad4",
        ]));

	set("hhjob", 1);
        set("outdoors", "xiao");
        setup();
}