// Item card.c
// Created by Zeus 1999.3.28
// Modified by Zeus 1999.3.28
// 
// 

inherit ITEM;

void create()
{
        set_name("温家总令牌", ({"wenjiacard"}));
             if( clonep() ) set_default_object(__FILE__);
        else {
        set("long",
               "这是“老字号温家”发给外姓熟人的令牌，有了此牌可以在温家总堂任意通行。\n");
        set("unit", "块");
        set("weight", 10);
        }
}
