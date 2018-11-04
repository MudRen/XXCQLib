// Room: 药王谷
// By 山猫adx @ 宁波小雪 17:00 99-10-26

inherit ROOM;

void create()
{
	set("short", "后院");
	set("long", @LONG
这里是药王谷山庄的后院。院子种着几株小树，还有一口水井，
一条鹅卵石铺成的小路通过一个拱门。
LONG );
	set("area", "药王谷");
	set("areb", "后院");
	set("no_fight", 1);
	set("resource/water", 1);
	set("exits", ([
		"north" : __DIR__"xiaolu1",
		"south" : __DIR__"dating",
	]));

	setup();
	replace_program(ROOM);
}
