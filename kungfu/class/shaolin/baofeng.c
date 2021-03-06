// bao.c

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("抱风", ({ "bao feng", "feng" }) );
	set("title", "少林长老");
	set("gender", "男性");
	set("age", 90);
	set("long",
		"这是一个面颊深陷，瘦骨零丁的老僧，他脸色枯黄，如同一段枯木。\n");

	set("attitude", "peaceful");
	set("class", "bonze");
	set("combat_exp", 1500000);
	set("score", 200000);

	set("str", 30);
	set("int", 30);
	set("cor", 30);
	set("cps", 30);
	set("con", 30);

	set("qi", 4000);
	set("max_qi", 2000);
	set("neili", 4000);
	set("max_neili", 2000);
	set("jiali", 90);

	create_family("少林派", 35, "弟子");

	set_skill("force", 220);
	set_skill("parry", 220);
	set_skill("dodge", 220);
	set_skill("unarmed", 220);

  set_skill("banruo-changong", 220);
	set_skill("shaolin-shenfa", 220);
	set_skill("huaibao-tianxia", 220);
	
	map_skill("force", "banruo-changong");
	map_skill("unarmed", "huaibao-tianxia");
	map_skill("dodge", "shaolin-shenfa");

	setup();
}

void init()
{

        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
        if(this_player()->query("title")=="少林长老")
          return;
	  call_out("do_test",5,this_player());
}

void greeting(object ob)
{
	object me;
	me = this_object();
	
	if(ob->query("shen") < -10000) {
	  command("say 大胆邪派狗贼！擅闯少林重地，送死啊!\n");
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
	}
	else 
		{
		}
}

int do_test()
{
	object me,ob;
	mapping fam;
	me = this_object();
	ob = this_player();
	fam = ob->query("family");

    if(!(fam = ob->query("family")) || fam["family_name"] != "少林派")
	{
	 return 1;
	}

  if(fam["master_name"] != "天正大师")
  {
  return 1;
}
	COMBAT_D->do_attack(me, ob, query_temp("weapon") );
	if (ob->query("qi") < ob->query("max_qi")/4)
	  {
	     return 1;
	  }
             call_out("do_test2",5,this_player());

	return 1;
}

int do_test2()
{
	object me,ob;
	me = this_object();
	ob = this_player();

	COMBAT_D->do_attack(me, ob, query_temp("weapon") );
	if (ob->query("qi") < ob->query("max_qi")/4)
	  {
	     return 1;
	  }
             call_out("do_test3",5,this_player());

	return 1;
}

int do_test3()
{
	object me,ob;
	me = this_object();
	ob = this_player();

	COMBAT_D->do_attack(me, ob, query_temp("weapon") );
	if (ob->query("qi") < ob->query("max_qi")/4)
	  {
	     return 1;
	  }
             call_out("halt",5);

	return 1;
}

void halt()
{
	string name,new_name;
	object ob,me;
	ob = this_player();
	me = this_object();
	command("halt");
	if(!interactive(ob)) command("sigh "+ob->query("id"));

	message_vision(HIB"只见"+me->query("name")+"的双掌一推，一股真气在你体内运行!\n",ob);
	message_vision(CYN"一会儿工夫，"+me->query("name")+"将手一挥，满意的点了点头。\n"NOR,ob);
	ob->set_skill("huaibao-tianxia",30);
	name = ob->query("name");
	new_name = "抱" + name[2..3];
	ob->set("name", new_name);
}

