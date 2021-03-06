// xiaoer2.c 酒店小二

inherit F_DEALER;

void create()
{
	set_name("店小二", ({ "xiao er", "xiao", "waiter" }) );
	set("gender", "男性" );
	set("age", 22);
	set("title", "叁合楼跑堂");
	set("long",
		"这位店小二正笑咪咪地忙著，已经累得满头大汗了。\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("no_get", "1");
	set("rank_info/respect", "小二哥");
	set("vendor_goods", ({
		__DIR__"obj/jitui",
		__DIR__"obj/jiudai",
		__DIR__"obj/baozi",
		__DIR__"obj/niurou",
	}));
	setup();
	carry_object(__DIR__"obj/cloth")->wear();
}

void init()
{	
	object ob; 

	ob = this_player();

	::init();
	remove_call_out("greeting");
	call_out("greeting", 1, ob);

	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
		case 0:
			say( "店小二笑咪咪地说道：这位" + RANK_D->query_respect(ob)
				+ "，进来吃点什么吧，我们这里的竹叶青很有名的。\n");
			break;
		case 1:
			say( "店小二用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
				+ "，快请进请进，里面坐。\n");
			break;
	}
}
