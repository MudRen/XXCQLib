//changan city

inherit ROOM;

void create ()
{
        set ("short", "落花湖畔");
        set ("long", @LONG
沿长廊走到落花湖的湖边，落花湖因其沿岸的百余株桃树而名，每到
落花季节，湖面都要落满了美丽的桃花，整个湖面也被花香而弥漫着。一
道长廊绕湖而建，从这里向南可以到达练武场和观鱼阁。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"southwest" : __DIR__"jqlang_1",
		"north" : __DIR__"hupan_n",
		"east" : __DIR__"southlang_2",
	]));

        set("objects", ([
                 __DIR__"npc/haishen": 1,
	]));

        set("outdoors", "xiao");
        setup();
}

int valid_leave(object me, string dir)
{
	mapping myfam;

	myfam = (mapping)me->query("family");

	if ((!myfam || myfam["family_name"] != "浣花剑派" ) && dir == "southwest" )
	{
        	if(objectp(present("hai shen", environment(me))))
        		return notify_fail("海神伸手拦住你谦声说道：再往里不方便进入，这位"+ RANK_D->query_respect(me) +"请回吧。\n");
	}

	return ::valid_leave(me, dir);
}