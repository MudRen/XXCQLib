// Item chouduan.c 绸缎
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(CYN"绸缎"NOR, ({ "chouduan" }));
        set("long", "这是一件青色的" + CYN"绸缎"NOR + "，温家只有第三代弟子才能穿戴此服饰，是地位的象征。\n");
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 200);
                set("armor_prop/armor", 30);
        }
        setup();
}
