// woshi.c 卧室
// mlf 设计,lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","卧室");
        set("long",
"这里是花枯发的卧室，奇怪的是卧室的摆设十分简单，只有一张桌子
，两把椅子和一张床，床上的"HIY"被子"NOR"也没叠，就放在那里。虽然看上去很寒
酸，但是很干净。\n"
	);
	set("valid_startroom",1);
	set("item_desc",([
		"床" : "床上除了被子就剩一对"HIW"枕头"NOR"了。\n",
	]));
	setup();
}

void init()
{
	add_action("do_pull","pull");
	add_action("do_zhuan","zhuan");
	add_action("do_open","open");
	add_action("do_enter","enter");
}

int do_pull(string arg)
{
	object me=this_player();
          if (arg!="beizi") return 0;
	if (me->query_temp("marks/pull"))
                return notify_fail("被子已经被你翻的乱七八糟。\n");
	me->set_temp("marks/pull", 1);
        message_vision("被子被$N拿了起来,$N什么也没发现。\n",me);
	return 1;
}

int do_zhuan(string arg)
{
     object me=this_player();
          if (arg!="zhentou") return 0;
	if( !me->query_temp("marks/pull") )
                return notify_fail("你想干啥？\n");
	message_vision("$N突然听到一阵响声,墙上出现了一道门(enter)。\n",me);
	set("zhuan",1);
	return 1;
}

int do_enter(object me)
{
	object room;
	object where;
        me=this_player();
	where=environment(me);
	if(!where->query("zhuan"))
          return notify_fail("你要进哪去？\n");
	if(!( room = find_object(__DIR__"mishi")) )
          room = load_object(__DIR__"mishi");
	message_vision("$N钻进了一道暗门。\n",me);
        me->move(room);
	set("zhuan",0);
        return 1;
}

int do_open(string arg)
{
	object room;

	if (query("exits/west"))
		return notify_fail("卧室门已经是开着了。\n");

	if (!arg || (arg != "door" && arg != "west"))
		return notify_fail("你要开什么？\n");

	if(!( room = find_object(__DIR__"neitang")) )
		room = load_object(__DIR__"neitang");
	if(objectp(room))
	{
		set("exits/west", __DIR__"neitang");
		message_vision("$N使劲把卧室门打了开来。\n",this_player());
		room->set("exits/east", __FILE__);
		message("vision","里面有人把卧室门打开了。\n",room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}
	return 1;
}

void close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"neitang")) )
		room = load_object(__DIR__"neitang");
	if(objectp(room))
	{
		delete("exits/west");
		message("vision","只听乒地一声，卧室门自动关了起来。\n",this_object());
                message("vision","坏了！出不去了！\n" ,
			this_object());
		room->delete("exits/east");
		message("vision","只听乒地一声，卧室门自动关了起来。\n",room);
                message("vision","哎哟！又进不去了！\n" ,
			room );
	}
}
