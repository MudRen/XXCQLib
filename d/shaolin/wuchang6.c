// Room: /d/shaolin/wuchang3.c
// Date: YZC 96/01/19

inherit ROOM;
int do_da(string);

void create()
{
	set("short", "练武场");
	set("long", @LONG
这里是少林寺的西练武场。由无数块巨大的花岗岩石板铺就。上千年的
踩踏已使得这些石板如同镜子般平整光滑。练武场中间竖立着不少木桩，桩
上钉着一些千层纸,十来个僧人正打纸(da zhi )练习拳法。西面就是出了无
数武林高手的般若堂。南北是两道走廊。
LONG
	);
	set("valid_startroom", 1);
	set("exits", ([
		"west" :__DIR__"banruo",
		"south" : __DIR__"zoulang1",
		"east" : __DIR__"wuchang1",
		"north" : __DIR__"zoulang5",
	]));

	set("outdoors", "shaolin");

	set("objects",([
		"/kungfu/class/shaolin/tianheng" : 1,
        "/kungfu/class/shaolin/tiancheng" : 1,
	]));

	setup();
}

void init()
{
	add_action("do_da", "da");
}

int do_da(string arg)
{
	object me;
	int a, b;

	me = this_player();

	if ( !arg || ( arg != "zhi" ) )
                return notify_fail("你想打什么？要打就打千层纸(zhi)吧。\n");

	a = random(20)+25;
	b = random(20)+25;

        if((int)me->query("jingli") < a)
	{
                return notify_fail("你现在精神无法集中，别再练功了吧！\n");
                return 1;
	}
        if((int)me->query("qi") < b)
	{
                return notify_fail("你都快累死了，快歇歇吧！\n");
                return 1;
	}

        me->add("jingli", -a);
        me->add("qi", -b);

        message_vision("$N清喝一声，摆好架势，一拳打在千层纸上。\n", me);

        if ( (int)me->query_skill("cuff", 1) < 101)
        {
                me->improve_skill("cuff", ((me->query("int"))+ random(me->query("int"))));
                tell_object(me, "你的手震的有些酸疼！你的基本拳法有了一些进步！\n");
        }
        else
        { 
                tell_object(me, "你一拳差不多把千层纸打烂了，看来这样练功对你没什么帮助了。\n");
        }
        return 1;
}
