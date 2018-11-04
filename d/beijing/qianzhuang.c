// Room: /city/qianzhuang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "大徐银庄");
	set("long", @LONG
	这是一家老字号的银庄，老板是京城著名的商人高鸡血高老板，因为高老
板雄厚的实力和他那不为人知的后台，没人会怀疑钱庄的信誉，所以这里的生意总
是很好，但由于高老板不收手续费，所以在这里不能存太多的钱，大概每人在这里
只能存二百两黄金左右。(取钱=qu,存钱=cun,查帐=chazhang,兑换=duihuan)
LONG
	);
	set("valid_startroom", 1);

	set("exits", ([
		"south" : __DIR__"shalan-e1",
	]));

	set("objects", ([
		__DIR__"npc/gao" : 1
	]));

	setup();
	replace_program(ROOM);
}

