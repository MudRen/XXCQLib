// NPC 伙计
// By 山猫Adx 16:53 99-10-25

#include <ansi.h>
//inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("伙计", ({ "huo ji", "huo", "ji" }) );
	set("title", HIB"药王谷"NOR+YEL"跑堂"NOR);
	set("gender", "男性" );
	set("age", 22);
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("vendor_goods", ({
		"/d/bianliang/obj/jinchuang",
		"/d/bianliang/obj/baiyao",
	}));

	setup();
        add_money("silver", 5);
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
	object ob = this_player();

	::init();
	if( interactive(ob) && !is_fighting() )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

int greeting(object ob)
{
	if((string)ob->query("party/party_name")==HIB"药王谷"NOR) {
		command("say 这位兄弟请了！\n");
		return 1;}
	else {
	switch( random(4) ) {
		case 0:
			command("bow "+ob->query("id"));
			command("say "+RANK_D->query_respect(ob)
		+"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
			break;
		case 1:
			command("nod "+ob->query("id"));
			command("say "+RANK_D->query_respect(ob)
		+"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
			break;
		case 2:
			command("hi "+ob->query("id"));
			command("say "+RANK_D->query_respect(ob)
		+"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
			break;
		case 3:
			command("welcome "+ob->query("id"));
			command("say "+RANK_D->query_respect(ob)
		+"，你要买些药吗？常用药这里出售，特殊药请到内屋选购！\n");
			break;
		}
	}
}

