// Item lphandbook.c
// Created by Zeus 1999.7.1
// Modified by Zeus 1999.7.22
// 
// 

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( MAG"施毒手法（秘籍篇）"NOR,({ "lphand book"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",MAG"施毒手法（秘籍篇）。\n"NOR);
                set("value", 1500);
                set("material", "paper");
                set("skill", ([
                        "name": "lphand",           //name of the skill
                        "exp_required": 0 ,        //minimum combat experience required
                        "jingli_cost":  50,         // jingli cost every time study this
                        "difficulty":   15,        // the base int to learn this skill
                        "max_skill":    101        // the maximum level you can learn
                ]) );
        }
}
