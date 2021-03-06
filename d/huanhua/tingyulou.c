// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "听雨楼");
	set("long", @LONG
走进听雨楼，立即感受到了浣花萧家的一份儒雅之气，在正厅高悬着
一面“浣花洗剑”的匾额，低处则挂着一副李太白手书的“长恨歌”，四
周摆设的家具古玩格调也颇为高雅。厅里并没有人，只有一名家丁在这里
侍茶。厅的左侧有楼梯通向听雨楼的二层。
LONG
	);

	set("valid_startroom", 1);
	set("exits", ([
		"out" : __DIR__"tingyudoor",
		"up" : __DIR__"tingyulou2",
	]));

        set("objects", ([
		__DIR__"npc/zuyuan_q" : 1,
	]));

	setup();
	replace_program(ROOM);
}