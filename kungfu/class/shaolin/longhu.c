// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

void recover_ob();

void create()
{
	set_name("龙虎大师", ({"longhu dashi", "longhu", "dashi",}));
	set("long",
		"他是一位天神一般的高僧，身穿一袭金丝绣红袈裟。\n"
		"他身材巨大忻长，满面红光，目蕴威严，显得神完气足。\n"
	);


	set("title", "少林寺戒律院掌刑");
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
	set("max_jingli", 1500);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 75);
	set("combat_exp", 1000000);
	set("score", 500000);
	set("banruo-changong", 2);

	set_skill("force", 170);
	set_skill("banruo-changong", 170);
	set_skill("dodge", 160);
	set_skill("shaolin-shenfa", 160);
	set_skill("cuff", 200);
	set_skill("parry", 160);
	set_skill("shaolin-quan", 200);
	set_skill("buddha", 150);
	set_skill("literate", 120);

	map_skill("force", "banruo-changong");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "shaolin-quan");
	map_skill("parry", "shaolin-quan");

	prepare_skill("cuff", "shaolin-quan");

	create_family("少林派", 35, "弟子");

	setup();

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: recover_ob :)
	}) );

        carry_object("/d/shaolin/npc/obj/jinjiasha")->wear();
        carry_object("/d/shaolin/npc/obj/sengxie")->wear();
}

void recover_ob()
{
	command("yun recover");
	return;
}