// menwei

inherit NPC;

void create()
{
	set_name("门卫", ({ "men wei", "wei"}));
	set("long", 
"门卫xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx。\n");
	set("gender", "男性");
	set("age", 35);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 18);
	set("int", 25);
	set("con", 24);
	set("dex", 28);

	set("combat_exp", 100000);

	set_skill("force", 30);
	set_skill("dodge", 60);
	set_skill("parry", 40);
	set_skill("sword", 50);
	set_skill("blade", 40);
	set_skill("strike", 50);

	create_family("四川唐门", 10, "家丁");

	setup();
	carry_object("/clone/misc/cloth")->wear();
}