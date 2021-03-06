// Room: /d/shaolin/banruo1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "般若堂偏殿");
	set("long", @LONG
这是般若堂北偏殿，是一间极为简陋的禅房。环视四周，除了几幅佛
竭外，室内空荡荡地别无他物。西面是少林功夫房之一的始武房，地上摆
放着一个破烂且发黑的黄布蒲团，一位须发花白的老僧正在坐在上面闭目
入定，他就是负责看管始武房的天鹏。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"south" : __DIR__"banruo",
		"west" : __DIR__"kfroom_1",
	]));

	set("objects",([
		"/kungfu/class/shaolin/tianpeng" : 1,
	]));

	setup();

}

void init()
{
	object me = this_player();

	if (me->query_temp("kfroom_1"))
	{
		me->delete_temp("kfroom_1");
		environment(me)->delete_temp("kfroom_1");
	}
}

int valid_leave(object me, string dir)
{
	if( !me->query_temp("kfroom_1"))
	{
		if (dir == "west")
		{
			return notify_fail("始武房机关重重，没有天鹏的允许谁也进不去。\n");
		}
	}
	return ::valid_leave(me, dir);
}