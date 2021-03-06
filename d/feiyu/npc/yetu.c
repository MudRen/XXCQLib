// NPC: yetu.c
// Created by Zeus 1999.4.10
// Modified by M.A.D. 1999.7.21
// 
// 

inherit NPC;

void create()
{
        set_name("野兔", ({ "ye tu", "ye", "hare" }) );
        set("race", "野兽");
        set("age", 5);
        set("long", "一只好可爱的小野兔。\n");
        set("attitude", "peaceful");
	
        set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 500);
	
        set_temp("apply/attack", 2);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 2);
        set_temp("apply/armor", 1);

        setup();
}

void die()
{
        object ob;
        message_vision("$N凄惨的嚎了几声，死了。\n", this_object());
        ob = new("/d/feiyu/obj/turou");
        ob->move(environment(this_object()));
        destruct(this_object());
}
	
