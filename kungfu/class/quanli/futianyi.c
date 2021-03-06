inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void recover_ob();

void create()
{
	set_name("傅天义", ({"fu tianyi", "fu", "tianyi"}));
	set("gender", "男性");
	set("age", 53);
	set("nickname", WHT"铁腕神魔"NOR);
	set("long", 
		"他白眉白须，玄衣如铁，坐在江水飞浪、奔流怒潮的巨石临江，纹风不动。
他是权利帮十九神魔之一。\n");
	set("attitude", "peaceful");
	set("title", "权利帮金银分舵舵主");
	set("str", 26);
	set("int", 12);
	set("con", 24);
	set("dex", 18);
	set("bac", 20);

	set("qi", 1700);
	set("max_qi", 1700);
	set("jingli", 1100);
	set("max_jingli", 1100);
	set("neili", 1300);
	set("max_neili", 1300);
	set("jiali", 10);
	
	set("combat_exp", 200000);
	set("shen", 1000);
	
	set_skill("force", 100);
	set_skill("xuantian-xinfa", 100); 
	set_skill("claw", 110);
	set_skill("liekong-zhao", 110);
	set_skill("dodge", 120); 
	set_skill("pili-shenfa", 120); 
	set_skill("parry", 100); 
	set_skill("confu", 100); 
	set_skill("literate", 60); 
	
	map_skill("force", "xuantian-xinfa");
	map_skill("dodge", "pili-shenfa");
	map_skill("claw", "liekong-zhao");
	map_skill("parry", "liekong-zhao");

	prepare_skill("claw", "liekong-zhao");
	
	create_family("权利帮", 4, "弟子");
	create_party("权利帮","帮众",2);

	setup();

	carry_object("/d/quanli/npc/obj/tieyi")->wear();

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: perform_action, "claw.qin" :),
		(: perform_action, "claw.niu" :),
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
	if (ob->query("str")<25)
	{
		command("shake");
		command("say 你拜我为师？不配！");
		return;
	}
	else if (ob->query("shen")>(ob->query("combat_exp")/10))
	{
		command("say 我最瞧不起你们这种侠士了，快给我滚！");
		return;
	}

	command("haha "+ob->query("id"));
	command("say 好呀，老夫就收下你了！");
	command("recruit " + ob->query("id"));

	ob->set("title",WHT"铁腕神魔"NOR"傅天义亲传弟子");
	return;
}