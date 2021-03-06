// Room: /d/shaolin/qfdian.c
// Date: YZC 96/01/19

#include <room.h>
#include <ansi.h>
inherit ROOM;
int consider_lv(object ob,int a);

void create()
{
	set("short", "穷武房");
	set("long", @LONG
穷武房是少林功夫房之一，内有精妙机关，置身其内可以很快的提升
武功，是武林人士梦寐以求的地方，你环顾四周，发现这里大概两丈见方
，四壁均有一些一尺宽、两尺高的木窗，窗内隐隐可以看到雕得栩栩如生
的木人。
LONG );
	set("valid_startroom", 1);

	set("exits", ([
		"east" : __DIR__"banruo_s",
	]));

	setup();
}

void init()
{
	object me;
	int x;
	x = 11;
	me = this_player();

	if (userp(me))
		call_out("combat_go", 1, me, x);
	return;
}

int combat_go(object me, int x)
{
	object ob;

	if ( x > 1 && userp(me))
	{
		if (x==11)
			message_vision(WHT"\n一走进始武房,四周的十数个木窗中便响起了卡卡的声音,似乎有机关开动了。\n"NOR, me);
		ob = new(__DIR__"npc/muren");
		if (me->query("combat_exp")>100)
		{
			ob->set("combat_exp",me->query("combat_exp") * 4 / 5);
			ob->set("max_qi",me->query("max_qi"));
			ob->set("eff_qi",me->query("max_qi"));
			ob->set("qi",me->query("max_qi"));
			ob->set("max_jingli",me->query("max_jingli"));
			ob->set("eff_jingli",me->query("max_jingli"));
			ob->set("jingli",me->query("max_jingli"));
			ob->set("max_neili",me->query("max_neili"));
			ob->set("neili",me->query("max_neili"));
			ob->set_skill("force", consider_lv(ob, 7));
			ob->set_skill("dodge", consider_lv(ob, 7)); 
			ob->set_skill("club", consider_lv(ob, 7));
			ob->set_skill("parry", consider_lv(ob, 7)); 
		}
        ob->move("/d/shaolin/kfroom_5");

		if (!objectp(present(me->query("id"), environment(ob))))
		{
			destruct(ob);
			return 0;
		}
		
		COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 0);
		me->add("combat_exp", 10+random(10));
		me->add("potential", 6+random(6));
		destruct(ob);

		call_out("combat_go", 5, me, x -= 1);

		return 1;
	}
	else
        {
		message_vision(HIW"\n卡卡的机关声渐渐小了下来，看来这次训练结束了。\n"NOR, me);
         message_vision(HIW"\n突然两边闪出两个木人，将你架出始武房。\n"NOR, me);
                me->move(__DIR__"banruo_s");
                me->delete_temp("kfroom_5");
                environment(me)->delete_temp("kfroom_5");
                me->apply_condition("kf_job",10);
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
