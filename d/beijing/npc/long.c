// longchuichui.c 

inherit NPC;

#include <ansi.h>

//string *query_killer() { return killer; }

void create()
{
	set_name("龙吹吹", ({ "long chuichui", "long" }));
	set("long", 
"龙吹吹腰佩钢刀，手持水火棍，顶插花翎，一副标\n"
"准官差打扮。他身形瘦小，但样子长得很精灵清俊。\n"
"他是小四大名捕之一，也是其中最年轻干练的一个。\n");
	set("gender", "男性");
	set("age", 20);
        set("title", BLU"巡捕"NOR);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 18);
	set("int", 25);
	set("con", 20);
	set("dex", 20);
	
	set("max_qi", 1200);
	set("max_jing", 1000);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 50);
	set("combat_exp", 100000);
	set("score", 8000);

	set_skill("force", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("club", 100);
	set_skill("strike", 100);
	set_skill("cuff", 100);

	set("chat_chance", 1);
	set("chat_msg", ({
		(: random_move :),
	}));

	setup();

	carry_object("d/beijing/npc/obj/yayifu")->wear();
	carry_object("/clone/weapon/gangdao");
	carry_object("d/beijing/npc/obj/shuihuo-gun")->wield();
}

void init()
{	
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}

//	add_action("do_fight", "fight");
//	add_action("do_kill","kill");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(3) ) {
		case 0:
			say( "龙吹吹大声喝道：“京城重地，禁止打架斗殴，都听到没有！！！”\n");
			break;
		case 1:
			say( "龙吹吹用冰冷冷的眼光注视着在场的每一个人。\n");
			break;
		case 2:
			say( "龙吹吹大声喊道：“让开，让开！！！”\n");
			break;
	}
}
/*
int do_fight()
{
	object ob,me;
	ob = this_player();
	me = this_object();
	message_vision("$N对著$n大喝一声：在我面前打架，你找死呀！\n", me, ob);
	message_vision("只见$N手握木棍向$n狠狠的一挥。\n", me, ob);
	ob->unconcious();
	ob->move("/u/exam/laofang");
	return 0;
}

int do_kill()
{
	object ob,me;
	ob = this_player();
	me = this_object();
	message_vision("$N对著$n大喝一声：在我面前行凶，你眼里还有王法吗！\n", me, ob);
	command("unwield gun");
	command("wield dao");
	me->kill_ob(ob);
	return 1;
}
*/