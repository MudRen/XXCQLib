// Npc: /d/shaolin/npc/shaofan-seng.c
// Date: YZC 96/01/19

inherit NPC;
int ask_job();

void create()
{
	set_name("烧饭僧", ({"shaofan seng","shaofan",	"seng",}));
	set("long",
		"这是位胖胖的中年僧人，大概是因为长年烧饭作菜的缘故，才如此发福的吧。\n");

	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("age", 44);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 400);
	set("max_jingli", 200);
	set("neili", 100);
	set("max_neili", 100);
	set("jiali", 10);
	set("combat_exp", 2000);
	set("score", 100);

	set_skill("force", 12);
	set_skill("dodge", 12);
	set_skill("strike", 12);
	set_skill("cuff", 12);
	set_skill("parry", 12);

	create_family("少林派", 39, "弟子");

        set("inquiry", ([
                "job" : (: ask_job :),
        ]) );

	setup();
}

int ask_job()
{
	object me, ob;
	mapping myfam;

	me = this_player();
	myfam = me->query("family");

	if ( !myfam || myfam["family_name"] != "少林派" )
	{
		command("say 施主不是我少林的弟子，我怎敢劳驾？");
		return 1;
	}

	else if ((int)me->query("combat_exp")>20000)
	{
		command("shake " + me->query("id"));
		command("say "+RANK_D->query_respect(me)+"现在武功已有根底，应该加紧练功才对。");
		return 1;
	}

	else if ((me->query_temp("job")==1))
	{
		command("hmm");
		command("say 不快去打水还在这里做什么？");
		return 1;
	}

	else if (me->query_temp("job")==3)
	{
		command("say 桶丢了就算了吧，下次注意。");
		me->delete_temp("job");
		return 1;
	}

	else if (me->query_temp("job")==2)
	{
		command("say 不用跟我说，把水倒在缸里好了。");
		return 1;
	}

	me->set_temp("job", 1);
	ob = new("/d/shaolin/npc/obj/tong");
	ob->move(me);
	command("say 去山涧小溪打一桶水来，桶拿好别丢了。");
	me->set_temp("job",1);
	return 1;
}
