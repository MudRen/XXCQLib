// NPC: zzold.c
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 

inherit NPC;

void create()
{
        set_name("壮族老伯", ({ "old man"}) );
        set("gender", "男性" );
        set("age", 50+random(10));
        set("long",
                "这是一位壮族老伯，头发微白，脸上皱纹颇多，经验很丰富的样子。\n");
        set("attitude", "friendly");

        set("qi", 500);
        set("max_qi", 500);
        set("jingli", 600);
        set("max_jingli", 600);

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 15);

        set("combat_exp", 3500);

        setup();
}

int accept_object(object who, object ob)
{
	
        if (ob->query("money_id") && ob->value() >= 100) 
        {
                tell_object(who, "壮族老伯笑了笑说：多谢了，有什么服务不周处，请提出。\n");

                who->set_temp("rent_paid",1);

                return 1;
        }

        return 0;
}
