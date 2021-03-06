// tongzhi.c 铜智
// by Load

#include "/kungfu/class/shaolin/tong.h"
inherit NPC;

void create()
{

	set_name("铜智", ({"tong zhi","tong","zhi",}));
	set("long",
		"他是一位身穿黄布袈裟的青年僧人。脸上稚气未脱，身手却已相\n"
		"当矫捷，看来似乎学过一点武功。\n"
	);

	set("nickname", "守门僧");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 20);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 35);
	set("dex", 20);
	set("bac", 22);
	set("max_qi", 400);
	set("qi", 400);
	set("max_jingli", 300);
	set("jingli", 300);
	set("neili", 200);
	set("max_neili", 200);
	set("jiali", 10);
	set("combat_exp", 20000);
	
	set_skill("force", 40);
    set_skill("wuxiang-shengong", 40);
	set_skill("dodge", 40);
	set_skill("shaolin-shenfa", 40);
	set_skill("cuff", 40);
	set_skill("luohan-quan", 40);
	set_skill("parry", 40);
	set_skill("club", 40);
	set_skill("zui-gun", 40);
	set_skill("buddha", 40);

    map_skill("force", "wuxiang-shengong");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "luohan-quan");
	map_skill("parry", "zui-gun");
	map_skill("club", "zui-gun");

	prepare_skill("cuff", "luohan-quan");

	create_family("少林派", 38, "弟子");

	setup();

        carry_object("/d/shaolin/npc/obj/huangjiasha")->wear();
        carry_object("/d/shaolin/npc/obj/sengxie")->wear();
        carry_object("/d/shaolin/npc/obj/qimeigun")->wield();
}

void check(object me)
{
	object ob;
	mapping my_fam;

	ob = this_object();

	my_fam = me->query("family");

	if ( my_fam && my_fam["master_id"] == ob->query("id")
        && me->query_skill("wuxiang-shengong",1) > 30
		&& me->query_skill("buddha",1) > 30
		&& !me->query("bai_tie")
		&& environment(me)==environment(ob))
	{
		command("pat " + me->query("id"));
		command("say 你勤奋用功，学有所成，为师能教你的已经不多了。");
		command("say 你去试着拜其他师叔伯，或者看看哪位铁字辈的师祖愿意收你吧。");
		command("say 以后不要忘了为师的教诲：诸事无常，胜极必衰。去吧。");
		me->set("bai_tie", 1);
	}
}
