//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "浣花溪畔");
        set ("long", @LONG
这是一条小土路，沿浣花溪向两边延伸，路的东侧是满坡的野山花，
煞是好看，路西侧可以看到清澈的溪水，鱼游其中，好不畅快。这条路向
南延伸通向远近闻名的杜甫草堂，许多孩子也匆匆的走在这条路上。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"south" : __DIR__"fhroad1",
		"north" : __DIR__"fhroad3",
       ]));

        set("outdoors", "xiao");
        setup();
}