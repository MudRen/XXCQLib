//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "长江江畔");
        set ("long", @LONG
走在长江江畔，俯瞰着滚滚长江，甚是壮观。这段长江流得甚是平缓
，许多龙舟和彩船充斥江面，看来比赛快开始了。你的东面就是秭归镇码
头，西面则是漫漫长江江畔了。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"west" : __DIR__"jiangpan4",
		"east" : __DIR__"zgmatou",
       ]));

        set("outdoors", "zigui");
        setup();
}