// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

int ask_bao();

void create()
{
	set_name("天正大师", ({
		"tianzheng dashi",
		"tianzheng",
		"dashi",
	}));
	set("long",
		"他是一位白须白眉的老僧，身穿一袭金丝绣红袈裟。\n"
		"他身材略显佝偻，但却满面红光，目蕴慈笑，显得神完气足。\n"
	);


	set("title", "少林寺三十五代掌门");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
         set("max_qi", 3000);
         set("max_jing", 2000);
         set("neili", 4000);
         set("max_neili", 4000);
         set("jiali", 150);
         set("combat_exp", 2000000);
         set("score", 1000000);
     set_skill("force", 400);
     set_skill("banruo-changong", 400);
     set_skill("dodge", 400);
    set_skill("dashou-yin", 400);
      set_skill("club", 400);
      set_skill("sword", 400);
     set_skill("unarmed", 400);
       set_skill("wuxiang-shengong",400);
       set_skill("damo-jian",360);
       set_skill("huoyan-dao",360);
       set_skill("blade",360);
       set_skill("cuff",400);
       set_skill("shaolin-quan",400);
     set_skill("shaolin-shenfa", 400);
     set_skill("finger", 440);
     set_skill("strike", 360);
     set_skill("hand", 380);
     set_skill("claw", 360);
     set_skill("parry", 400);
     set_skill("nianhua-zhi", 440);
     set_skill("buddha", 440);
         set_skill("literate", 220);

    map_skill("force", "banruo-changong");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("parry", "nianhua-zhi");

	prepare_skill("finger", "nianhua-zhi");
	create_family("少林派", 35, "弟子");
        set("inquiry", ([
                "怀抱天下" : (: ask_bao :),
        ]) );

	setup();

        carry_object("/d/shaolin/npc/obj/jinjiasha")->wear();
        carry_object("/d/shaolin/npc/obj/sengxie")->wear();
}

void attempt_apprentice(object ob)
{
	object me; 
	mapping ob_fam, my_fam;
	string name, new_name;

	me = this_object();
	my_fam  = me->query("family");

	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派")
	{
		command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
		return;
	}

	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") 
	{
		command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
		return;
	}

	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
		return;
	}
        if (me->query_skill("banruo-changong",1)<160)
          {  command("say 你的般若禅功还要继续学习才行!\n");
          return;
          }
          if(me->query_skill("buddha",1)<150)
          {  command("say 你还没有理会到佛家的禅理!\n");
          return;
          }
          if(me->query_skill("finger",1)<150)
          { command("say 你的基本指法不够,学不到我的掌门绝技!\n");
           return;
          }
         if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "天")
      {
          new_name = "木" + name[2..3];
          ob->set("name", new_name);
          command("say 从今以后你的法名叫做" + new_name + "，恭喜你荣升为少林派木字辈弟子 !");
          command("recruit " + ob->query("id"));
          return;
        }

	else
	{
		command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
		return;
	}

	return;
}

int ask_bao()
{
command("say 好吧，我就带你去见五位长老，不过要小心!\n");
this_player()->move("/d/shaolin/zhulin17");
return 1;
}

