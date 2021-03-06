// huoji. 药铺伙计

inherit F_DEALER;

void create()
{
	set_name("伙计", ({ "huoji"}));
	set("str", 20);
	set("gender", "男性");
	set("title", "回春堂跑堂");
	set("age", 18);
	set("long", "他是上太师的学徒，平时就在店里当伙计。\n");
	set("combat_exp", 250);
	set("attitude", "friendly");
	set("vendor_goods", ({
		__DIR__"obj/jinchuang",
		__DIR__"obj/baiyao",
	}));

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
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "伙计迎上来道：这位" + RANK_D->query_respect(ob)
				+ "要买什么药，我们这里刚来了一批上好的云南白药。\n");
			break;
		case 1:
			say( "伙计用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
				+ "，进来看看，我们这里药最全了。\n");
			break;
	}
}
