// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
void recover_ob();

void create()
{
	set_name("阮行月", ({"ruan xingyue", "ruan", "xingyue"}));
	set("nickname", CYN"犬组组长"NOR);
	set("gender", "男性");
	set("age", 26);
	set("long", 
		"他是一个精明的年轻人，眼牟里闪烁着警惕的神情，犬组在剑庐肩负着守卫的重任。\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("bac", 20);

	set("qi", 1200);
	set("max_qi", 1200);
	set("jingli", 700);
	set("max_jingli", 700);
	set("neili", 800);
	set("max_neili", 800);
	
	set("combat_exp", 80000);
	set("score", 5000);
	
	set_skill("force", 70);
	set_skill("jiuqu-xinfa", 70); 
	set_skill("strike", 70);
	set_skill("feixu-zhang", 70);
	set_skill("dodge", 70); 
	set_skill("huanhua-shenfa", 70); 
	set_skill("sword", 70); 
	set_skill("parry", 70); 
	set_skill("literate", 70); 
	set_skill("confu", 60); 
	set_skill("huanhua-jian", 70); 

	map_skill("force", "jiuqu-xinfa");
	map_skill("dodge", "huanhua-shenfa");
	map_skill("strike", "feixu-zhang");
	map_skill("parry", "huanhua-jian");
	map_skill("sword", "huanhua-jian");

	prepare_skill("strike", "feixu-zhang");
	
	create_family("浣花剑派", 5, "弟子");

	setup();

	carry_object("/d/huanhua/npc/obj/jinpao")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: recover_ob :)
	}) );
	set("add_title","浣花剑庐犬组组员");
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

	if (ob->query("combat_exp")<10000
		|| ob->query_skill("huanhua-shenfa",1)<40
		|| ob->query_skill("dodge",1)<40)
	{
		command("say 不行不行，你功夫太差，杀不了敌人反倒被敌人杀了怎么办？");
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

	command("say 好吧，" + RANK_D->query_respect(ob) +"入我犬组，就好好为剑庐出力吧。");
	command("recruit " + ob->query("id"));
	ob->set("title", "浣花剑派第六代弟子、"CYN"犬组组员"NOR);
	if (!(my_fam = ob->query("family")) || my_fam["family_name"] != "浣花剑派")
		ob->set("pay_money", ob->query("age"));

	return;
}