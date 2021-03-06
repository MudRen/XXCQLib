// NPC: zhangfangxs.c
// Created by Atlus 1999.7.23
// Modified by atlus 1999.10.15

#include <ansi.h>

inherit NPC;

void greeting(object);
void create()
{
        set_name("帐房先生", ({ "xiansheng", "sir"}) );
        set("gender", "男性" );
        set("age", 50+random(10));
        set("long",
                "帐房先生已经五十多岁了，据说是前科进士，在飞鱼山庄管帐已经二十多年了，几乎没有出过什么差错。\n");
        set("combat_exp", 30000);
        set("attitude", "friendly");
        set("rank_info/respect", "老师");

        set("qi", 500);
        set("max_qi", 500);
        set("jingli", 500);
        set("max_jingli", 500);

	create_family("飞鱼塘",3 , "弟子");

        set_skill("literate", 200);

        setup();
}



void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say("帐房先生正埋头打着算盘，发现有人进来，抬起头说到：“这位" + RANK_D->query_respect(ob)
             + "请问有什么事吗?”\n");
}

