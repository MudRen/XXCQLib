// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
void recover_ob();
int accept_object(object who, object ob);
int ask_job();
void create()
{
	set_name("李子木", ({"li zimu", "li", "zimu"}));
	set("nickname", HIR"虎组组长"NOR);
	set("gender", "男性");
	set("age", 26);
	set("long", 
		"他是一个非常精干的年轻人，作为虎组组长操劳着剑庐的里里外外。\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("int", 30);
	set("con", 20);
	set("dex", 15);
	set("bac", 15);

	set("qi", 700);
	set("max_qi", 700);
	set("jingli", 400);
	set("max_jingli", 400);
	set("neili", 500);
	set("max_neili", 500);
	
	set("combat_exp", 40000);
	set("score", 2000);
	
	set_skill("force", 40);
	set_skill("jiuqu-xinfa", 40); 
	set_skill("strike", 40);
	set_skill("feixu-zhang", 40);
	set_skill("dodge", 40); 
	set_skill("huanhua-shenfa", 40); 
	set_skill("sword", 40); 
	set_skill("parry", 40); 
	set_skill("literate", 40); 
	set_skill("confu", 40); 
	set_skill("huanhua-jian", 40); 
	
	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("parry", "huanhua-jian");
	map_skill("sword", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");
	
	create_family("浣花剑派", 5, "弟子");

        set("inquiry", ([
                "job" : (: ask_job :),
        ]) );

	setup();

	carry_object("/d/huanhua/npc/obj/jinpao")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	add_money("silver", 5+random(5));

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: recover_ob :)
	}) );
}

void recover_ob()
{
	command("yun recover");
	return;
}

void attempt_apprentice(object ob)
{
	object me;
	mapping my_fam, ob_fam;

	me = this_object();

	my_fam = ob->query("family");
	ob_fam = me->query("family");

	if (ob->query("killding"))
	{
		command("say 大胆狂徒，胆敢硬闯萧府，纳命来吧！");
		me->kill_ob(ob);
		ob->kill_ob(me);
		return;
	}

	if ((int)ob->query("shen") <= (-100))
	{
		if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
		{
			command("hmm");
			command("say 浣花萧家乃名门正派，岂能容纳邪魔外道，你还不快快滚出剑庐！！！");
			return;
		}
		else
		{
			command("say 你身为浣花弟子却不主张正义，甘入魔道，我浣花容不下你！");
			command("kaichu "+ob->query("id"));
			return;
		}
	}

	if ((!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派") && (int)ob->query("combat_exp")>20000)
	{
		command("say "+RANK_D->query_respect(ob)+"已是江湖成名之士，萧家哪敢相留。");
		command("say 对不起了，您请回吧。");
		return;
	}

	if ( my_fam )
	{
		if ( my_fam["family_name"] == "浣花剑派" )
		{
			if ( ob_fam["generation"] == my_fam["generation"] )
			{
				command("say 你我乃同辈弟子，切磋切磋倒是可以，拜师却是从何说起？");
				return;
			}
	
			if ( ob_fam["generation"] > my_fam["generation"] )
			{
				message_vision("$N一脸的诚惶诚恐道：究竟弟子犯了什么错，您要和弟子开这样的玩笑。\n", me);
				return;
			}
		}
	}

	command("say 好吧，" + RANK_D->query_respect(ob) +"既然拜我为师，还望努力练功，以期能为武林正义出一份力量。");
	command("recruit " + ob->query("id"));
	ob->set("title", "浣花剑派第六代弟子、"HIR"虎组组员"NOR);
	if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
		ob->set("pay_money", ob->query("age"));

	return;
}

int ask_job()
{
	mapping myfam, quest;
	object me, ob;
	string title;

	me = this_player();
	myfam = me->query("family");
	title = me->query("title");
	quest = "/d/huanhua/quest/liquest"->query_quest();

	if ( !myfam || myfam["family_name"] != "浣花剑派" )
	{
		command("ah "+me->query("id"));
		command("say 你不是我们浣花剑庐的人，我们怎么敢劳您的大驾呢？");
		return 1;
	}

	else if ( myfam["generation"] > 5 && myfam["master_name"]!="李子木" )
	{
		command("say 你不是我们虎组的组员，虎组的工作不用你来做。");
		return 1;
	}

	else if (me->query("combat_exp")<60000
        ||me->query_skill("sword")<20
        ||me->query_skill("parry")<20
        ||me->query_skill("dodge")<20)
	{
		command("shake");
		command("say 你的功夫太差，不适合外出，还是帮贾管家做一些事情吧。");
		return 1;
	}

	else if (me->query_temp("buygoods"))
	{
		command("hmm");
		command("say 有工作还来要，真是一个不安分的家伙。");
		return 1;
	}
         if (me->query("combat_exp")>300000)
         { 
             command("gongxi");
             command("say 你已经不用做这些杂活了,去保护剑庐吧");
             return 1;
          }

	command("say 你去" + quest["quest_1"] + "取一下我们" + quest["quest_2"] + "吧。");
	command("say " + quest["quest_3"] + "带好，到那给" + quest["quest_4"] + "就行了，别开小差。");
	command("say 权力帮埋伏在剑庐周围多日，你要早去早回，路上千万小心。");

	me->set_temp("buygoods", "begin");
	me->set_temp("goods", quest["quest_4"]);
	ob = new("/d/huanhua/npc/obj/dingdan");
	ob->set("name", quest["quest_3"]);
	ob->set("long", "这是一份用来在" + quest["quest_1"] + quest["quest_4"] + "处取货用的" + quest["quest_3"] + "。\n");
	ob->move(me);
	return 1;
}

int accept_object(object who, object ob)
{
	mapping myfam;

	if ((string)ob->query("id") == "huo") 
	{
		if ( !(	myfam = who->query("family")) || myfam["family_name"] != "浣花剑派" )
		{
			command("say 真是的，不知道又是谁丢的。");
			command("thank "+who->query("id"));
  			destruct(ob);
			return 1;
		}
		else if ((string)who->query_temp("buygoods") != "over")
		{
			command("say 居然敢拿别人的劳动来领功，真是不学好。");
  			destruct(ob);
			return 1;
		}
		else
		{
			message_vision("$N把货放下来让组长查验。\n", who);
			command("say 不错不错，干的确实不错，下去休息吧。");
			message_vision("李子木招呼了几个人出来将货物搬进了储藏室。\n", who);
			who->add("potential", 80+random(80));
			who->add("combat_exp", 100+random(100));
			who->add("succeed", 2);
			who->delete_temp("buygoods");
			who->delete_temp("goods");
  			destruct(ob);
			return 1;
		}
	}
	else
	{
		command("say 你给我这个干什么?");
		return 0;
	}
	
}
