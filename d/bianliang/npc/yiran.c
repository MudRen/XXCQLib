// huoji. 药铺伙计

inherit NPC;
#include "/d/bianliang/npc/hhjob.h"

void create()
{
	set_name("冉毅然", ({ "ran yiran", "ran", "yiran"}));
	set("str", 20);
	set("gender", "男性");
	set("title", "黑衣染坊第四代传人");
	set("age", 45);
	set("long", "他是一个又瘦又矮的中年男子，是冉黑衣的重孙子，也有一手的染布技术。\n");
	set("combat_exp", 250);
	set("attitude", "friendly");

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	say( "冉毅然在围裙上擦了擦手道：这位" + RANK_D->query_respect(ob)
				+ "今天来是要染布吗？\n");
}
