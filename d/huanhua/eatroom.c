// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "剑庐饭厅");
	set("long", @LONG
这是剑庐的饭厅，厅内的摆设非常简单，只是四张大大的圆桌和围在
周围的几十把木椅。由于剑庐并没有固定的开饭时间，所以几乎随时都有
人在在吃饭，饭厅的左侧有一个木门，里面就是厨房了。在这里的家丁急
匆匆的进进出出，为吃饭的人端来米饭炒菜，如果你饿了不妨让他们也给
你端上来一些(serve)。
LONG
	);

	set("no_fight", 1);

	set("valid_startroom", 1);

	set("exits", ([
		"east" : __DIR__"southyuan",
        "south" : __DIR__"churoom",
	]));

        set("objects", ([
                 __DIR__"npc/eatding": 1,]));

	setup();
}

int valid_leave(object me, string dir)
{
	me = this_player();

	if (  (dir == "east")
	   && ( present("tang", this_player())
	        || present("chao fan", this_player()) ) 
	   && objectp(present("jia ding", environment(me))) )
	{
	 message_vision("家丁对$N一拱手道：庄主吩咐，饮食不得带出饭厅。", me);
	 return notify_fail("\n");
	}

	return ::valid_leave(me, dir);
}
