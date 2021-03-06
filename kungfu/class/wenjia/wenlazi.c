// NPC: wenlazi.c
// Created by Zeus 1999.4.7
// Modified by Zeus 1999.4.7
// 
// 

inherit NPC;

void create()
{
        set_name("温辣子", ({ "wen lazi", "lazi"}) );
        set("gender", "男性" );
        set("age", 50);
        set("per", 10);
        set("long",
                "这个人是老字号中死字号的副首脑，他沉默寡言，\n"+
                "面色阴沉，双手一直藏在袖子里。\n");
        set("attitude", "friendly");

        set("qi", 1000);
        set("max_qi", 1000);
        set("jingli", 1000);
        set("max_jingli", 1000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 80000);

        set_skill("hand", 100);
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("literate", 60);

        add_money("silver", 10);

        setup();
}
