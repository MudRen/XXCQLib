// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "虎啸堂");
	set("long", @LONG
这是一间偏厢房，正堂悬有一面红匾，上书行龙走凤的“虎啸堂”三
个大字，堂正中一张硬木红案，一个年轻人做在后面翻看着几本账簿，许
多浣花弟子不停的进进出出，那个年轻人则有条不紊的分派着各项工作。
LONG
	);

	set("exits", ([
		"west" : __DIR__"southyuan",
	]));

        set("objects", ([
        __DIR__"npc/li" : 1,
		__DIR__"npc/zuyuan_h" : 1,
	]));

      set("no_fight",1);
	setup();
	replace_program(ROOM);
}
