// longpao.c
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(WHT"织锦长衫"NOR, ({"zhijin changshan","changshan","shan","cloth"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
            set("long",
"一件银色的浣花织锦缝制的长衫，质地非常的不错，做工也很好。\n");
                set("value", 1000);
                set("material", "cloth");
                set("armor_type", "cloth");
                set("armor_prop/armor", 10);
             }
	setup();
}

