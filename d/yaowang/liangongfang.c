// Room: 药王谷
// By 山猫adx @ 宁波小雪 17:00 99-10-26

inherit ROOM;

void create()
{
	set("short", "练功房");
	set("long", @LONG
你走进一间挺宽敞的房间。这里青石铺地，墙边放着几个布娃娃，上面画着人身
上的经络和周身大穴，看来是药王谷弟子用来练习(lianxi)针灸的。
LONG );
	set("area", "药王谷");
	set("areb", "练功房");
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"xiting",
	]));
	set("objects", ([
		__DIR__"npc/buwawa" : 1,
	]));
	setup();
	replace_program(ROOM);
}
