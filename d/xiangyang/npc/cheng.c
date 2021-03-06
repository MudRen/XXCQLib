// ding.c 家丁

inherit NPC;
#include <ansi.h>
int accept_object(object who, object ob);
int ask_job();
int ask_enter();

void create()
{
	set_name("程老板", ({ "cheng laoban", "cheng", "laoban" }));
	set("age", 25);
	set("gender", "男性");
	set("nickname", HIY"称千金"NOR);
	set("title","金银钱庄掌柜");
	set("long", "他是一个精明的中年人，眼神中流露的却不仅仅是狡猾，而是歹毒。\n");
	set("attitude", "peaceful");
	set("combat_exp", 20000);
	set("shen", -5000);

	set("str", 20);
	set("int", 12);
	set("con", 24);
	set("dex", 24);
	set("bac", 20);

	set("qi", 900);
	set("max_qi", 900);
	set("jingli", 600);
	set("max_jingli", 600);
	set("neili", 500);
	set("max_neili", 500);
	set("rank", "帮众");

	set_skill("force", 60);
	set_skill("parry", 60);
	set_skill("dodge", 60); 
	set_skill("parry", 60); 
	set_skill("stick", 60); 
	set_skill("confu", 30); 
	set_skill("literate", 90); 

    create_party("权力帮","帮众",1);

//	carry_object("/clone/misc/cloth")->wear();
//	carry_object(__DIR__"obj/tiecheng")->wield();

        set("inquiry", ([
                "job" : (: ask_job :),
        ]) );

        set("inquiry", ([
                "enter" : (: ask_enter :),
                "job" : (: ask_job :),
                "进帮" : (: ask_enter :),
        ]) );
	setup();
}

void attempt_join(object ob)
{
	if (ob->query("family")&&ob->query("family/family_name")=="浣花剑派")
	{
		command("say 呵呵，来了个自投罗网的，真是找死！");
		this_object()->kill_ob(ob);
		ob->kill_ob(this_object());
		return;
	}
	if (ob->query("shen")>0)
	{
		command("hmm");
		command("say 你们这种自命侠士会想参加本帮，莫不是来做卧低的吧？");
		return;
	}
	else if (ob->query("combat_exp")<10000)
	{
		command("shake");
		command("say 你功夫这么差，怎么为本帮效力?还是算了吧。");
		return;
	}
        else if (ob->query("party"))
        {
            command("say 你已经有帮派了，我怎敢收你啊!\n");
            return;
        }
    else if (ob->query("kill")< 0)
	{
		command("say 你斯斯文文，怎么能做打打杀杀的勾当？还是算了吧。");
		return;
	}

	command("say 好吧，" + RANK_D->query_respect(ob) +"既然愿意，我就替本帮收下你了。");
	command("nodjoin " + ob->query("id"));

	return;
}

int ask_job()
{
    mapping quest;
	object me, ob;

	me = this_player();
	quest = __DIR__"quest/jyquest"->query_quest();

    if ( !((mapping)me->query("party")) || (string)me->query("party/party_name") != "权力帮" )
	{
		command("look "+me->query("id"));
		command("say 你什么意思？你是不是想到我们这来捣乱？");
		return 1;
	}

	else if (me->query_temp("qljob") && me->query_temp("qljob") == 1)
	{
		command("hmm");
		command("say 是不是对帮派给你的工作不满意？哼！");
		return 1;
	}

	else if (me->query_temp("qljob") && me->query_temp("qljob") == 4)
	{
		command("jump");
		command("say 干的好，长了我们钱庄的威风，下去歇歇吧！");
		me->add("potential", 50+random(80));
		me->add("combat_exp", 80+random(100));
		me->add("party/tasks", 2);
		me->delete_temp("qljob");
		me->delete_temp("subject");
		me->delete_temp("money");
		return 1;
	}

	else if ( me->query_condition("jyfail") )
	{
		command("say 让你要个帐都要不来，又不敢杀人，我还怎么让你做事！");
		command("say 你还下去吧，省得我们金银山庄的脸都被你丢光了！");
		me->delete_temp("qljob");
		me->delete_temp("subject");
		me->delete_temp("money");
		return 1;
	}
	else if ( me->query_temp("qljob"))
	{
		command("say 收完帐不交钱，是不是想吞了呀？");
		return 1;
	}

	command("say " + quest["quest_1"] + "欠我们钱庄" + chinese_number(quest["quest_2"]) + "两银子，你去要回来吧。");
	command("say 这张欠单带好，到那甭废话，直接收帐(shouzhang)。");
	command("say 如果" + quest["quest_1"] + "赖着不还，就杀了他，显显我们钱庄的威风。");

	me->set_temp("qljob", 1);
	me->set_temp("subject", quest["quest_3"]);
	me->set_temp("money", quest["quest_2"]);
	ob = new("/d/quanli/npc/obj/qiandan");
	ob->set("long", "
	欠单
" + quest["quest_1"] + "欠金银山庄" + chinese_number(quest["quest_2"]) + "两纹银，
口说无凭，立此为证。

	黑老汉、金银山庄\n");
	ob->move(me);
	return 1;
}

int accept_object(object who, object ob)
{

	if (ob->query("money_id")) 
	{
		if (who->query_temp("qljob") && (who->query_temp("qljob") == 1))
		{
			command("say 这点钱我就收下了，可是你的活却没有做完！");
			command("say 还不快去做！");
			destruct(ob);
			return 1;
		}
		else if (who->query_temp("qljob") && (who->query_temp("qljob") == 2 ||who->query_temp("qljob") == 5))
		{
			command("say 自己收不到帐还想瞒我？你当我是谁？");
			command("say 这点钱就算你孝敬我的，我有事做再叫你。");
			destruct(ob);
			who->delete_temp("qljob");
			who->delete_temp("subject");
			who->delete_temp("money");
			return 1;
		}
		else if (who->query_temp("qljob") && who->query_temp("qljob") == 3 && ob->value() >= (100 * who->query_temp("money")))
		{
			command("say 不错不错，干的确实不错，下去休息吧。");
			message_vision("程老板在帐单上记上一笔，然后把钱放进了钱柜。\n", who);
			who->add("potential", 60+random(60));
			who->add("combat_exp", 80+random(80));
			who->add("party/tasks", 1);
			who->delete_temp("qljob");
			who->delete_temp("subject");
			who->delete_temp("money");
  			destruct(ob);
			return 1;
		}
		else if (who->query_temp("qljob") && who->query_temp("qljob") == 3 && ob->value() < (100 * who->query_temp("money")))
		{
			command("say 就收了这么一点钱，恐怕是你把钱扣下了吧！");
			command("say 看来你是活的不耐烦了。");
			return 1;
		}
		else return notify_fail("出现了巫师没有想到的情况，快通知巫师吧。\n");
	}
	else
	{
		return notify_fail("你给我这个干什么?\n");
	}
}
int ask_enter()
{
object me = this_player();
if(me->query("party/party_name") == "权力帮")
{
    command("say 既然是本帮的人请进吧!\n");
    me->move("/d/quanli/damen");
  return 1;
}
      if(present("mi han",me))
         {
           command("say 原来是给我派送信,好吧你就进去吧!\n");
            me->move("/d/quanli/damen");
          return 1;
         }
command("say 你不是本帮的人就不能进去!\n");
command("heng");
return 1;
}
