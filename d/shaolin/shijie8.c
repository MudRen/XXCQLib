// Room: /d/shaolin/shijie8.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "石阶");
	set("long", @LONG
这里看来是半山腰了。不远的前面有一座小石亭，几位游客在这里歇
息。山路到这里变得十分平坦，东边的山壁上提满了名人即兴题下的诗句
。远望山林间层峦迭嶂，满目滴翠。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"westdown" : __DIR__"shanmen",
		"northup" : __DIR__"shijie9",
	]));
	set("no_clean_up", 0);
	set("outdoors", "shaolin");
	setup();
}

int valid_leave(object me, string dir)
{
	me = this_player();

	if (( present("shui tong", this_player())) && dir == "northup")
	{
		if (me->query("jingli")<15)
			return notify_fail("提着大水桶，你已经累的走不动道了。\n");
		me->add("jingli",-10);
		me->improve_skill("dodge",10+random(5));
		me->start_busy(1);
	}

	return ::valid_leave(me, dir);
}
