// Room: /welcome/npc/qian.c
//By adx @ CuteRabbit 15:57 99-5-18

inherit F_BANKER;

void create()
{
        set_name("钱眼开", ({"qian yankai", "qian", "yankai"}));
        set("title", "钱庄老板");
        set("nickname", "铁公鸡");
        set("gender", "男性");
        set("age", 34);
        set("str", 22);
        set("int", 24);
        set("dex", 18);
        set("con", 18);
        set("qi", 500);
        set("max_qi", 500);
        set("jing", 100);
        set("max_jing", 100);
        set("shen", 0);

        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 2);
        set("chat_msg", ({
        "钱眼开骄傲的说道：本银号已经有上百年的历史，在江南可以说是第一家。\n",
        "钱眼开笑着说道：在本店存钱无利息，取钱收十分之一手续费，客官您看着办吧。\n"
        }));
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);
        setup();
        carry_object("/clone/misc/cloth")->wear();
	add_money("silver",5);
}