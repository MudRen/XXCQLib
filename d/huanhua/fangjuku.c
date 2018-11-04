// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "防具屋");
	set("long", @LONG
这里是剑庐的防具屋，墙上挂着几件练功用的衣物，在地上还扔着一
些防具，如指套、牛皮护腕等。你可以根据需要拿上几件。这些防具虽然
有用，但并不怎么值钱，如果你用不着还是不要多拿的好。
LONG
	);

	set("valid_startroom", 1);
	set("exits", ([
		"north" : __DIR__"wuchang3",
	]));
        set("objects", ([
		__DIR__"npc/obj/liangongfu" : 3,
		__DIR__"npc/obj/huwan" : 2,
		__DIR__"npc/obj/shoutao" : 2,
	]));

	setup();
	replace_program(ROOM);
}