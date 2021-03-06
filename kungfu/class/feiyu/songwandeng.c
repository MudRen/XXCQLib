// NPC: songwandeng.c 飞鱼四小之一、初级师父 宋晚灯
// Created by M.A.D. 1999.7.21
// Modified by M.A.D. 1999.7.21
// 
// 原著人物!  特殊武功--游鱼拳法，飞鱼剑法

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void recover_ob();

void create()
{
        set_name("宋晚灯", ({ "song wandeng","song"}) );
        set("nickname", MAG"沈星南首徒"NOR );
        set("gender", "男性" );
        set("age", 20);
        set("per", 20);
        set("long",
                "宋晚灯是“飞鱼塘”飞鱼山庄庄主沈星南的大徒弟.\n他看上去大约二十岁，高达六尺,轩昂之躯,甚见气势。\n");
        set("attitude", "friendly");

        set("qi", 1000);
        set("max_qi", 1000);
        set("jingli", 800);
        set("max_jingli", 800);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 50);

        set("combat_exp", 300000);

        set_skill("cuff", 100);          //基本拳法
        set_skill("force", 100);         //基本内功
        set_skill("dodge", 100);         //基本轻功
        set_skill("parry", 100);         //基本招架
        set_skill("feiyu-jian", 100);    //飞鱼剑法
        set_skill("youyu-quan", 100);    //游鱼拳
        set_skill("fish-steps", 100);    //鱼形步法
        set_skill("tianlongforce", 100); //天龙功
         set_skill("sword", 100);         //基本剑法
        set_skill("tao",100);            //道学心法
         
		map_skill("cuff", "youyu-quan");
		map_skill("force", "tianlongforce");
		map_skill("sword", "feiyu-jian");
		map_skill("dodge", "fish-steps");

        prepare_skill("sword", "feiyu-jian");

		create_family("飞鱼塘", 5, "弟子");

        setup();

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
		(: recover_ob :)
        }) );

        add_money("silver", 10);

        carry_object("/d/feiyu/obj/jinshenfu")->wear();
        carry_object("/d/feiyu/obj/changjian")->wield();
}

void attempt_apprentice(object me)
{
        if ( (int)me->query("combat_exp")>10000 && (string)me->query("family/family_name") != "飞鱼塘") {
                command("say " + RANK_D->query_respect(me)+"既然已有名师指导，又何需拜我为师呢？");
                return;
        }

        command("say 好吧，我就收下你做徒弟吧。");
        command("say 飞鱼塘武功博大精深，你要好好的学呀!");
        command("recruit " + me->query("id"));
}

void recover_ob()
{
        command("yun recover");
        return;
}
