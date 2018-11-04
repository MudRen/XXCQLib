// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "九曲廊");
	set("long", @LONG
或许因为湖南岸的长廊比湖北岸的长廊更曲折的原因吧，名字也由七
曲变成了九曲，走在九曲廊感到格外的舒畅，因为南面的湖面开满了美丽
的荷花。长廊南面的建筑就是观鱼阁，萧家大小姐最爱在二层阁楼上看美
丽的湖光了。
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"east" : __DIR__"jqlang_1",
		"northwest" : __DIR__"jqlang_3",
		"south" : __DIR__"guanyu",
	]));

        set("objects", ([
	]));

	setup();
	replace_program(ROOM);
}