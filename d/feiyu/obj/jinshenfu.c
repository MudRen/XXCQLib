// Item jinshenfu.c 紧身服
// Created by M.A.D. 1999.7.21
// Modified by M.A.D. 1999.7.21
// 
// 

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIR"紧身服"NOR, ({ "fu" }));
        set("long", "这是一件" + HIR"紧身服"NOR + "，这是飞鱼塘“中秀”的统一装束，有一定的防护力。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 200);
                set("armor_prop/armor", 10);
        }
        setup();
}
