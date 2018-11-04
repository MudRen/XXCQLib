//changan city

inherit ROOM;
int do_da(string);

void create ()
{
        set ("short", "练武场");
        set ("long", @LONG
这是一个极宽敞的练武场，练武场上有许多人在汗流浃背的练着功。
在场子中分布着十余个木桩，弟子们不停的用掌打着木桩(da zhuang )。
在练武场的南面有一间小屋，那是剑庐的防具屋，你也可以进去拿一件适
合的防具。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"east" : __DIR__"wuchang1",
		"south" : __DIR__"fangjuku",
	]));

        set("outdoors", "xiao");

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

	if ( !arg || ( arg != "zhuang" ) )
                return notify_fail("你想打什么？要打就打眼前的这个木桩子(zhuang)吧。\n");

	a = random(20)+20;
	b = random(20)+20;

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

        message_vision("$N马步蹲裆，吐气开声，一掌拍在木桩子上。\n", me);

        if ( (int)me->query_skill("strike", 1) < 101)
        {
                me->improve_skill("strike", ((me->query("int"))+ random(me->query("int"))));
                tell_object(me, "你觉得你的手掌打的生疼！\n你的掌法进步了！\n");
        }
        else
        { 
                tell_object(me, "你一掌险些将木桩子打倒了，看来再也不能通过打木桩练掌法了。\n");
        }
        return 1;
}