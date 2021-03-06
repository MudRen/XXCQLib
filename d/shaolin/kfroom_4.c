// Room: /d/shaolin/qfdian.c
// Date: YZC 96/01/19

#include <room.h>
#include <ansi.h>
inherit ROOM;
int consider_lv(object ob,int a);

void create()
{
	set("short", "精武房");
	set("long", @LONG
精武房是少林功夫房之一，内有精妙机关，置身其内可以很快的提升
武功，是武林人士梦寐以求的地方，你环顾四周，发现这里大概两丈见方
，四壁均有一些一尺宽、两尺高的木窗，窗内隐隐可以看到雕得栩栩如生
的木人。
LONG );
	set("valid_startroom", 1);

	set("exits", ([
		"west" : __DIR__"luohan",
	]));

	setup();
}

void init()
{
	object me;
	int x;
	x = 11;
	me = this_player();

	if (userp(me) && me->query_temp("kfroom_4"))
		call_out("combat_go", 1, me, x);
	return;
}

int combat_go(object me, int x)
{
	object ob;

	if ( x > 1 && userp(me))
	{
		if (x==11)
			message_vision(WHT"\n一走进精武房,四周的十数个木窗中便响起了卡卡的声音,似乎有机关开动了。\n"NOR, me);
		ob = new(__DIR__"npc/muren");
		ob->set("combat_exp",me->query("combat_exp"));
		ob->set("max_qi",me->query("max_qi"));
		ob->set("eff_qi",me->query("max_qi"));
		ob->set("qi",me->query("max_qi"));
		ob->set("max_jingli",me->query("max_jingli"));
		ob->set("eff_jingli",me->query("max_jingli"));
		ob->set("jingli",me->query("max_jingli"));
		ob->set("max_neili",me->query("max_neili"));
		ob->set("neili",me->query("max_neili"));
		ob->set_skill("weituo-gun", consider_lv(ob, 8));
		ob->set_skill("force", consider_lv(ob, 8));
		ob->set_skill("shaolin-shenfa", consider_lv(ob, 8)); 
		ob->set_skill("banruo-changong", consider_lv(ob, 8)); 
		ob->set_skill("dodge", consider_lv(ob, 8)); 
		ob->set_skill("club", consider_lv(ob, 8));
		ob->set_skill("parry", consider_lv(ob, 8)); 
		ob->map_skill("force", "banruo-changong");
		ob->map_skill("dodge", "shaolin-shenfa");
		ob->map_skill("club", "weituo-gun");
		ob->map_skill("parry", "weituo-gun");
		ob->move("/d/shaolin/kfroom_4");

		if (!objectp(present(me->query("id"), environment(ob))))
		{
			destruct(ob);
			return 0;
		}
		
		COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 0);
		me->add("combat_exp", 25+random(25));
		me->add("potential", 12+random(12));
		destruct(ob);

		call_out("combat_go", 5, me, x -= 1);

		return 1;
	}
	else
	{
		message_vision(HIW"\n卡卡的机关声渐渐小了下来，看来这次训练结束了。\n"NOR, me);
		message_vision(HIW"\n突然两边闪出两个木人，将你架出精武房。\n"NOR, me);
		me->move(__DIR__"luohan");
		me->delete_temp("kfroom_4");
		environment(me)->delete_temp("kfroom_4");
		me->apply_condition("kf_job",17);
	}
	return 1;
}

int consider_lv(object ob,int a)
{
	int level; 
	float exper;

	exper = to_float(ob->query("combat_exp"));
	level = ceil( pow( exper*10.0, 0.333333) );

	level = level * a / 10;

	return level;
}

int valid_leave(object me, string dir)
{
	if( me->query_temp("kfroom_4") && dir == "west")
	{
		me->apply_condition("kf_job",17);
	}
	return ::valid_leave(me, dir);
}