// NPC: chuwangong.c 叶梦色，中级师父  
// Created by Atlus 1999.7.24
// Modified by Atlus 1999.7.24
// 
// 原著人物!  特殊武功--飞鱼剑法

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void recover_ob();

void create()
{
        set_name("叶梦色", ({ "ye mengse","ye"}) );
        set("gender", "女性" );
        set("age", 22);
        set("per", 40);
        set("long",
                "叶梦色是“飞鱼塘”飞鱼山庄庄中最重要的“老秀”之一，她精通飞鱼剑法。\n她看上去大约二十岁，极为白皙,以至在暮色昏冥中,宛如一朵幽幽的白花,柔美清绝。\n");
        set("attitude", "friendly");

        set("qi", 1500);
        set("max_qi", 1500);
        set("jingli", 1200);
        set("max_jingli", 1200);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 500000);

        
        set_skill("force", 120);         //基本内功
        set_skill("dodge", 110);         //基本轻功
        set_skill("parry", 120);         //基本招架
        set_skill("literate", 100);      //读书写字
        set_skill("sword", 150);         //基本剑术
        set_skill("feiyu-jian", 150);    //飞鱼剑法
        set_skill("youyu-quan", 90);     //游鱼拳
        set_skill("fish-steps", 110);    //鱼形步法
        set_skill("tianlongforce", 110); //天龙功
        set_skill("cuff", 120);          //基本拳法
        set_skill("tao",150);            //道学心法

        map_skill("cuff", "youyu-quan");
		map_skill("force", "tianlongforce");
		map_skill("sword", "feiyu-jian");
		map_skill("dodge", "fish-steps");

		prepare_skill("sword", "feiyu-jian");

		create_family("飞鱼塘", 4, "弟子");

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
        if ((string)me->query("family/family_name") != "飞鱼塘") {
                command("say " + RANK_D->query_respect(me)+"既然已有名师指导，又何需拜我为师呢？");
                return;
         }

        if ( (int)me->query("combat_exp")<100000 ) {
                command("say " + RANK_D->query_respect(me)+"似乎火候未够，先去江湖上磨练磨练再来吧！");
                return;
        }
        if ((int)me->query_skill("sword", 1) < 100) {
                command("say 我的修为全在“剑”上，你的火候未够。"); 
                command("say " + RANK_D->query_respect(me) + 
                        "是否还应该在剑法上多下点功夫？");
                return;
         }
        if ((int)me->query("shen") < 30000) {
                command("say 飞鱼塘乃是堂堂名门正派，对弟子要求严格。");
                command("say 在德行方面，" + RANK_D->query_respect(me) +"是否还做得不够？");
                return;
        }


        command("say 好吧，我就收下你做徒弟吧。");
        command("say 剑法博大精深，你要好好的学呀!");
        command("recruit " + me->query("id"));
}

void recover_ob()
{
        command("yun recover");
        return;
}
