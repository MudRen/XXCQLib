//zoulang1。c             血河派--走廊

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "走廊");
	set("long", @LONG
这里是血河派西侧的走廊。两边栽种着大片的竹林，清风徐徐，竹影
婆娑，着实令人惬意，还有不少边陲稀有的名花夹间其中，花香竹韵，让
人留恋忘返。这里通向西厢房。
LONG);
	set("valid_startroom",1);
	set("outdoors","龙门");
	set("valid_startroom",1);
	set("exits", ([
		"west" : __DIR__"liangongfang",
		"east" : __DIR__"qinghange",
		"north" : __DIR__"youmingge",
		"south" : __DIR__"xixiangfang",
	]));
	setup();
}

int valid_leave(object me,string dir)
{

        mapping myfam;
         me=this_player();
        myfam=(mapping)me->query("family");

       if (dir=="east")
       {
        if (!myfam || myfam["family_name"]!="血河派")
            return notify_fail("你不是血河派的弟子，不能进去。\n");

        if ( me->query("gender")!="女性")
            return notify_fail("那里是女弟子的休息室，你不能进去。\n");

       }
        return ::valid_leave(me, dir);

}
