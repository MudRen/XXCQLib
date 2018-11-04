// jinjia.c 金甲

#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name(HIB"寒铁甲"NOR, ({"hantie jia","jia", "armor"}));
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else
	{
                set("unit", "件");
		set("long", "一件上好寒铁打造的铠甲，隐隐发着蓝光．\n");
                set("material", "steel");
                set("value", 50000);
		set("wear_msg","寒光一闪，$N已将"HIB"寒铁甲"NOR"披挂在身，平添一分威武！\n");
                set("armor_prop/armor", 30);
		set("armor_prop/dodge", -5);
        }
        setup();
}


