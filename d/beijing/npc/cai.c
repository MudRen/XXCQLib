// cai.c 蔡老板 

inherit F_DEALER;

void create()
{
	set_name("蔡玉丹", ({ "cai yudan", "cai" }));
	set("title", "绸缎行老板");
	set("shen_type", 1);
        set("nickname","缠丝大侠");
	set("gender", "男性");
	set("age", 45);
	set("long",
		"他就是有名的缠丝大侠蔡玉丹，他不但生意做的大，名声好，而且\n"
		"功夫也好，常常打抱不平，据说他和“幽明山庄”的庄主石幽明是\n"
		"好朋友。\n");
	set_skill("strike", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 40000);
	set("attitude", "friendly");

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
	object obj, sil;
	obj = this_object();

	if ((string)ob->query("id") == "dan") 
	{
		if ((string)who->query_temp("goods") != obj->query("name"))
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("? "+who->query("id"));
			command("say 这份"+ob->query("name")+"不是我们这里的呀！");
			command("say 你还是到别的地方去找找吧。");
			command("give dan to "+who->query("id"));
			return 1;
		}
		else if (!(string)who->query_temp("buygoods") || (string)who->query_temp("buygoods") != "begin")
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("? "+who->query("id"));
			command("say 这虽然是我们这里的，但是……，大概不是您的吧。");
			command("say 这张单子我们先留下了，省得顾客受损失，谢谢您了。");
  			destruct(ob);
			return 1;
		}
		else
		{
			message_vision("$N把单子递给"+obj->query("name")+"查验。\n", who);
			command("say 太好了，太好了，您终于来了！");
			message_vision(obj->query("name")+"拿过一根笔在账单上划了两下，然后收了起来。\n", who);
			message_vision(obj->query("name")+"转了进去，一会带着一个伙计扛出来一个大包裹。\n", who);
			message_vision(obj->query("name")+"笑了笑说：这就是您们剑庐的货，您收好。\n", who);
			sil = new("/d/huanhua/npc/obj/huo");
			sil->set("name", "布匹");
			sil->set("long", "这是从家和绸缎庄取来的布匹。");
			sil->move(who);
			who->set_temp("buygoods", "over");
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
