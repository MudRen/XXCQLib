// NPC: wenxiaobian.c 温家第六代弟子、初级师父  温小便
// Created by Zeus 1999.5.28
// Modified by Zeus 1999.7.10
// 
// 原著人物!  特殊武功--袖手不旁观

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void recover_ob();

void create()
{
        set_name("温小便", ({ "wen xiaobian","wen"}) );
        set("nickname", MAG"袖手不旁观"NOR );
        set("gender", "男性" );
        set("age", 30);
        set("per", 10);
        set("long",
                "温小便是……………………………………\n");
        set("attitude", "friendly");

        set("qi", 1000);
        set("max_qi", 1000);
        set("jingli", 800);
        set("max_jingli", 800);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);

        set("combat_exp", 500000);

        set_skill("lphand", 80);    //施毒手法
        set_skill("force", 80);     //基本内功
        set_skill("dodge", 80);     //基本轻功
        set_skill("parry", 80);     //基本招架
        set_skill("poisonk", 60);   //毒药知识
        set_skill("zhixin", 80);    //温故知新
        set_skill("qianli", 80);    //毒行千里
        set_skill("bupangguan", 150); //袖手不旁观
        set_skill("literate", 60);  //读书写字

        map_skill("force", "zhixin");
        map_skill("dodge", "qianli");
        map_skill("lphand", "bupangguan");
        map_skill("parry", "bupangguan");

        prepare_skill("lphand", "bupangguan");

        create_family("老字号温家", 6, "弟子");

        setup();

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
		(: recover_ob :)
        }) );

        add_money("silver", 10);

        carry_object("/d/wenjia/obj/redduanda")->wear();
}

void attempt_apprentice(object me)
{
        if ( (int)me->query("combat_exp")>5000 && (string)me->query("family/family_name") != "老字号温家") {
                command("say " + RANK_D->query_respect(me)+"既然有名师指导，又何必来我温家。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 好好的学吧!");
        command("recruit " + me->query("id"));
}

void recover_ob()
{
        command("yun recover");
        return;
}
