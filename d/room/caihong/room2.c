// room2.c 彩虹居房例之房间2
// Written by Doing Lu 1998/1/6

// 在生成房屋时：
// /**/开头的语句将被去掉
// //**开头的语句将被使用。

#include <room.h>
/**/inherit ROOM;
//**inherit PRIVATE_ROOM;

void create()
{
	set("short", "正房");
	set("long", @LONG
	这里是鲁班大师精心搭建的彩虹居的正房，屋子里很大，但是现在还是
空空的，什么也没有。
LONG
	);

	set("no_fight", 1);
//**	set("sleep_room", 1);

/**/	set("default_long", "这里就是正房，是主人休息的地方，右侧是一张大床，看上去睡着一定很舒服，" +
/**/			    "不远处放着一个衣柜。窗外可以眺望ROOM_POSITION的美景。" +
/**/			    "大厅就在东侧，那里是会见友人的地方。");
	set("key", "ROOM_KEY");
	set("owner", "ROOM_OWNER");

	set("exits", ([
		"east" : __DIR__"room1",
	]));

	create_door("east",  "室门", "west",  DOOR_CLOSED);

	setup();
}
