//nzlang2.c		四川唐门—走廊

#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_kill();
void away(object obj);

void create()
{
	set("short", "走廊");
	set("long", @LONG
这里是莲云阁北侧的走廊。两旁是碧绿的湖水，无数荷花含苞欲
放，这美景让人留连忘返，止步不前。这里通向莲云阁后宅。
LONG);
	set("exits", ([
			"south" : __DIR__"houzhai",
			"north" : __DIR__"nzlang3",
			"west" : __DIR__"tangwen",
			"east" : __DIR__"tanggan",
	]));
	set("area", "蜀中");
	setup();
//	replace_program(ROOM);
}

int init()
{
	object me, roomg, roomw;

	me = this_player();

	if ( !( roomg = find_object(__DIR__"tanggan")) )
		roomg = load_object(__DIR__"tanggan");
	if ( !( roomw = find_object(__DIR__"tangwen")) )
		roomw = load_object(__DIR__"tangwen");

	if ( ( (string)me->query("family/family_name") != "四川唐门" ) && !wizardp(me) )
	{
		if ( objectp(present("tang gan", environment(me)) )
			|| ( objectp(roomg) && objectp(present("tang gan", roomg)) )
			|| ( objectp(present("tang wen", environment(me)) ) )
			|| ( objectp(roomw) && objectp(present("tang wen", roomw)) ) )
		me->set_temp("tangjindi",1);
		remove_call_out("do_kill");
		call_out("do_kill", 1);
	}
}

int do_kill()  
{
	object me, obj, roomg, roomw;

	me = this_player();

	me->delete_temp("tangjindi");

	if ( !( roomg = find_object(__DIR__"tanggan")) )
		roomg = load_object(__DIR__"tanggan");
	if ( !( roomw = find_object(__DIR__"tangwen")) )
		roomw = load_object(__DIR__"tangwen");

	if ( ( (string)me->query("family/family_name") != "四川唐门" ) && !wizardp(me) )
	{
		if ( objectp(present("tang gan", environment(me)) ) )
		{
			obj = present("tang gan", environment(me));
			message_vision("唐感对着$N大喝一声：“大胆！擅闯唐门禁地，我看你是不想活了！”\n",me);
			obj->kill_ob(me);
			me->fight_ob(obj);
			call_out("away", 20, obj);
		}
		else
		{
			if ( objectp(roomg) && objectp(present("tang gan", roomg)) )
			{
				obj = present("tang gan", roomg);
				tell_room(roomg, "唐感好象听到了什么声响，眉头一皱自语到：“是谁这么大胆，擅闯唐门禁地！我得去看看!”\n唐感快步向西走去。\n");
				tell_room(this_object(), "唐感快步从东边的屋中走出来。\n");
				obj->move(__DIR__"nzlang2");
				message_vision("唐感对着$N大喝一声：“大胆！擅闯唐门禁地，我看你是不想活了！”\n",me);
				obj->kill_ob(me);
				me->fight_ob(obj);
				call_out("away", 20, obj);
			}
		}

		if ( objectp(present("tang wen", environment(me)) ) )
		{
			obj = present("tang wen", environment(me));
			message_vision("唐闻对着$N大喝一声：“哼，哪里来的刺客，看剑!”\n",me);
			obj->kill_ob(me);
			me->fight_ob(obj);
			call_out("away", 20, obj);
		}
		else
		{
			if ( objectp(roomw) && objectp(present("tang wen", roomw)) )
			{
				obj = present("tang wen", roomw);
				tell_room(roomw, "唐闻好象听到了什么声响，眉头一皱自语到:“是谁这么大胆，擅闯唐门禁地！我得去看看!”\n唐闻快步向东走去。\n");
				tell_room(this_object(), "唐闻快步从西边的屋中走出来。\n");
				obj->move(__DIR__"nzlang2");
				message_vision("唐闻对着$N大喝一声：“哼，哪里来的刺客，看剑!”\n",me);
				obj->kill_ob(me);
				me->fight_ob(obj);
				call_out("away", 20, obj);
			}
		}
	}
	return 1;
}

void away(object obj)
{
	string name;
	if( living(obj) )
	{
		if (  !obj->busy() && !obj->is_fighting() )
		{
			message_vision("$N恨恨的说:“谁敢擅闯唐门禁地，我决不饶他。\n$N一转身走回了自己的屋中。\n", obj);
			if ( (string)obj->query("id") == "tang wen" )
				obj->move(__DIR__ "tangwen");
			else
				if ( (string)obj->query("id") == "tang gan" )
					obj->move(__DIR__ "tanggan");
		}
		else
			call_out("away", 20, obj);
	}
	return;
}

int valid_leave(object me, string dir)
{
	object obj;
	string msg;
	if ( obj = present("tang gan", environment(me) ) )
		msg = obj->query("name") + "说道：“哼！擅闯唐门禁地，还想走！先把我们撂倒再说！”\n";
	else
		if ( obj = present("tang wen", environment(me) ) )
			msg = obj->query("name") + "说道：“哼！擅闯唐门禁地，还想走！先把我们撂倒再说！”\n";

	if ( me->query_temp("tangjindi") )
		return notify_fail("你感觉有高手就在身旁，不敢有所妄动！\n");

	if ( ( (dir == "north") || (dir == "west") || (dir == "east") || (dir == "south") ) && ( (string)me->query("family/family_name") != "四川唐门" ) && !wizardp(me) && obj)
		return notify_fail(msg);
	else
		return ::valid_leave(me, dir);
}