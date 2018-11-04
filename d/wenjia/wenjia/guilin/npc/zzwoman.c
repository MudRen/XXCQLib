// NPC: zzwoman.c
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 

inherit NPC;

void create()
{
        set_name("壮族女青年", ({ "young woman"}) );
        set("gender", "女性" );
        set("age", 20+random(20));
        set("long",
                "这是一位壮族女青年，相貌较好，是家里的主力军。\n");
        set("attitude", "friendly");

        set("qi", 300);
        set("max_qi", 300);
        set("jingli", 600);
        set("max_jingli", 600);

        set_temp("apply/attack", 20);
        set_temp("apply/defense", 30);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 10);

        set("combat_exp", 3000);

        setup();
}
