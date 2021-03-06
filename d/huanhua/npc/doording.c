// ding.c 家丁

inherit NPC;

int ask_baishi();

void create()
{
	set_name("家丁", ({ "jia ding", "ding" }));
	set("age", 25);
	set("gender", "男性");
	set("title","浣花剑派第六代弟子、"CYN"犬组组员"NOR);
	set("long", "他是一个精壮的青年男子，每日里就负责在门口戒备及接待来客。\n");
	set("attitude", "peaceful");

	set("str", 24);
	set("dex", 16);
	set("combat_exp", 20000);
	set("shen_type", 1);

	set_skill("force", 50);
	set_skill("jiuqu-xinfa", 50); 
	set_skill("strike", 50);
	set_skill("feixu-zhang", 50);
	set_skill("dodge", 50); 
	set_skill("huanhua-shenfa", 50); 
	set_skill("sword", 50); 
	set_skill("parry", 50); 
	set_skill("literate", 50); 
	set_skill("confu", 40); 
	set_skill("huanhua-jian", 50); 

	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("parry", "huanhua-jian");
	map_skill("sword", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");
	
	create_family("浣花剑派", 6, "弟子");

        set("inquiry", ([
                "拜师" : (: ask_baishi:),
		"baishi" : (: ask_baishi:),
        ]) );

	setup();

	carry_object(__DIR__"obj/jinpao")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}

int ask_baishi()
{
	object me,ob;
	me = this_player();
	ob = this_object();

	if ((me->query("combat_exp"))>20000)
	{
		command("say "+RANK_D->query_respect(me)+"已是江湖成名之士，我们萧家哪敢让您屈就？您还是请回吧。\n");
	}
	else if ((me->query("shen"))<0)
	{
		command("hmm");
		command("say 浣花不收邪魔外道之人，您还是请回吧，免得自讨没趣。\n");
	}
	else
	{
		command("say "+RANK_D->query_respect(me)+"既然有心拜师，就请跟我来吧。\n");
		me->move("/d/huanhua/qianroad1");
		command("enter");
		command("say "+RANK_D->query_respect(me)+"自己进去吧，不要随意乱跑呀。\n");
		command("out");
	}

	return 1;
}