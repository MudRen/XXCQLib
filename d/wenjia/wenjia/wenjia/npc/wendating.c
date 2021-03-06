// NPC: wendating.c
// Created by Zeus 1999.3.27
// Modified by Zeus 1999.7.9
// 修改技能
// 

inherit NPC;

void recover_ob();

void create()
{
        set_name("温大听", ({ "wen dating", "dating"}) );
        set("gender", "男性" );
        set("age", 20+random(10));
        set("long",
                "温大听和温小听是温家总堂二位守门神。\n"+
                "他们在广场上守卫，禁止不是温家得子弟进入。\n");
        set("attitude", "friendly");

        set("qi", 1000);
        set("max_qi", 1000);
        set("jingli", 1000);
        set("max_jingli", 1000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 800000);

        set_skill("lphand", 100);    //施毒手法
        set_skill("force", 100);     //基本内功
        set_skill("dodge", 100);     //基本轻功
        set_skill("parry", 100);     //基本招架
        set_skill("duzi-du", 100);   //惟毒独尊
        set_skill("zhixin", 100);    //温故知新
        set_skill("qianli", 100);    //毒行千里
        set_skill("literate", 60);   //读书写字

        map_skill("force", "zhixin");
        map_skill("dodge", "qianli");
        map_skill("lphand", "duzi-du");
        map_skill("parry", "duzi-du");

        prepare_skill("lphand", "duzi-du");

        create_family("老字号温家", 5, "弟子");

        setup();

        add_money("silver", 10);

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "lphand.feixing" :),
                (: recover_ob :)
        }) );

        carry_object("/d/wenjia/obj/grnduanda")->wear();
}


void recover_ob()
{
        command("yun recover");
        return;
}
