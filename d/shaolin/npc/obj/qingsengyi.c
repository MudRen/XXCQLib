// qingsengyi.c 青布僧衣
// by Load

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(CYN"青布僧衣"NOR, ({ "seng yi", "yi", "cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
		set("long", "一件青色粗布缝制的僧衣，是少林小沙弥穿的僧衣。\n");
		set("value", 0);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}

