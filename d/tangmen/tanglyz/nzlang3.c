//nzlang3.c		四川唐门—走廊

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
			"south" : __DIR__"nzlang2",
			"north" : __DIR__"tangltt",
			"west" : __DIR__"tangshe",
			"east" : __DIR__"tangting",
	]));
	set("area", "蜀中");
	setup();
//	replace_program(ROOM);
}

int init()
{
	object me, roomt, rooms;

	me = this_player();

	if ( !( roomt = find_object(__DIR__"tangting")) )
		roomt = load_object(__DIR__"tangting");
	if ( !( rooms = find_object(__DIR__"tangshe")) )
		rooms = load_object(__DIR__"tangshe");

	if ( ( (string)me->query("family/family_name") != "四川唐门" ) && !wizardp(me) )
	{
		if ( objectp(present("tang ting", environment(me)) )
			|| ( objectp(roomt) && objectp(present("tang ting", roomt)) )
			|| ( objectp(present("tang she", environment(me)) ) )
			|| ( objectp(rooms) && objectp(present("tang she", rooms)) ) )
		me->set_temp("tangjindi",1);
		remove_call_out("do_kill");
		call_out("do_kill", 1);
	}
}

int do_kill()  
{
	object me, obj, roomt, rooms;

	me = this_player();

	me->delete_temp("tangjindi");

	if ( !( roomt = find_object(__DIR__"tangting")) )
		roomt = load_object(__DIR__"tangting");
	if ( !( rooms = find_object(__DIR__"tangshe")) )
		rooms = load_object(__DIR__"tangshe");

	if ( ( (string)me->query("family/family_name") != "四川唐门" ) && !wizardp(me) )
	{
		if ( objectp(present("tang ting", environment(me)) ) )
		{
			obj = present("tang ting", environment(me));
			message_vision("唐听对着$N大喝一声：“大胆！擅闯唐门禁地，我看你是不想活了！”\n",me);
			obj->kill_ob(me);
			me->fight_ob(obj);
			call_out("away", 20, obj);
		}
		else
		{
			if ( objectp(roomt) && objectp(present("tang ting", roomt)) )
			{
				obj = present("tang ting", roomt);
				tell_room(roomt, "唐听好象听到了什么声响，眉头一皱自语到：“是谁这么大胆，擅闯唐门禁地！我得去看看!”\n唐听快步向西走去。\n");
				tell_room(this_object(), "唐听快步从东边的屋中走出来。\n");
				obj->move(__DIR__"nzlang3");
				message_vision("唐听对着$N大喝一声：“大胆！擅闯唐门禁地，我看你是不想活了！”\n",me);
				obj->kill_ob(me);
				me->fight_ob(obj);
				call_out("away", 20, obj);
			}
		}

		if ( objectp(present("tang she", environment(me)) ) )
		{
			obj = present("tang she", environment(me));
			message_vision("唐舌对着$N大喝一声：“哼，哪里来的刺客，看剑!”\n",me);
			obj->kill_ob(me);
			me->fight_ob(obj);
			call_out("away", 20, obj);
		}
		else
		{
			if ( objectp(rooms) && objectp(present("tang she", rooms)) )
			{
				obj = present("tang she", rooms);
				tell_room(rooms, "唐舌好象听到了什么声响，眉头一皱自语到:“是谁这么大胆，擅闯唐门禁地！我得去看看!”\n唐舌快步向东走去。\n");
				tell_room(this_object(), "唐舌快步从西边的屋中走出来。\n");
				obj->move(__DIR__"nzlang3");
				message_vision("唐舌对着$N大喝一声：“哼，哪里来的刺客，看剑!”\n",me);
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
			if ( (string)obj->query("id") == "tang she" )
				obj->move(__DIR__ "tangshe");
			else
				if ( (string)obj->query("id") == "tang ting" )
					obj->move(__DIR__ "tangting");
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
	if ( obj = present("tang ting", environment(me) ) )
		msg = obj->query("name") + "说道：“哼！擅闯唐门禁地，还想走！先把我们撂倒再说！”\n";
	else
		if ( obj = present("tang she", environment(me) ) )
			msg = obj->query("name") + "说道：“哼！擅闯唐门禁地，还想走！先把我们撂倒再说！”\n";

	if ( me->query_temp("tangjindi") )
		return notify_fail("你感觉有高手就在身旁，不敢有所妄动！\n");

	if ( ( (dir == "north") || (dir == "west") || (dir == "east") || (dir == "south") ) && ( (string)me->query("family/family_name") != "四川唐门" ) && !wizardp(me) && obj)
		return notify_fail(msg);
	else
		return ::valid_leave(me, dir);
}

