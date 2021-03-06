// Room: /city/zahuopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "河神庙");
	set("long", @LONG
长江边上每一个码头边几乎都有一间河神庙，虽然大多年久失修、破
烂不堪，但却香火旺盛，为了保佑长江不泛滥，渔民和江畔的居民都经常
到河神庙祭拜，这里没有和尚，只有一个半百的庙祝在这里主持。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"north" : __DIR__"jiangpan1",
	]));

	set("objects", ([
		__DIR__"npc/miaozhu": 1,
	]));

	setup();
	replace_program(ROOM);
}