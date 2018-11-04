// Room: 药王谷
// By 山猫adx @ 宁波小雪 17:00 99-10-26

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "东厅");
	set("long", @LONG
这里是药王谷的东厅，北面是厨房，提供所有弟子的饮食。东面是一间休息室，
还有一间药房，这里放着一些基本的常用药。
LONG );
	set("area", "药王谷");
	set("areb", "东厅");
	set("no_fight", 1);
	set("exits", ([
		"north" : __DIR__"chufang",
		"west" : __DIR__"dating",
		"east" : __DIR__"xiuxi2",
		"northeast" : __DIR__"yaofang",
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);
	setup();
	replace_program(ROOM);
}
