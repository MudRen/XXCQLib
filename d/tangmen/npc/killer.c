//killer.c	唐门死士

inherit NPC;
inherit F_MASTER;

void recover_ob();
void away();

void create()
{
	set_name("唐门死士", ({"killer"}));
	set("gender", "男性");
	set("age", 26);
	set("long", 
		"他看上去没有一丝表情，感情对他来说早已不存在了。\n");
	set("attitude", "peaceful");
	set("str", 30);
	set("int", 40);
	set("con", 30);
	set("dex", 40);

	set("qi", 1200);
	set("max_qi", 1200);
	set("jingli", 600);
	set("max_jingli", 600);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 50);
	
	set("combat_exp", 700000);
	set("score", 20000);
	
	set_skill("force", 140);
	set_skill("strike", 130);
	set_skill("cuff",120);
	set_skill("dodge", 150); 
	set_skill("sword", 150); 
	set_skill("parry", 130); 
	set_skill("literate", 120); 
	
	create_family("四川唐门", 10, "死士");

	setup();

	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	set("chat_chance", 5);
	set("chat_msg", ({
		(: away :),
	}));
}

void away()
{
	if( living(this_object()) )
	{
		message_vision("唐门弟子急急忙忙的走开了。\n", this_object());
		destruct(this_object());
	}
	return;
}