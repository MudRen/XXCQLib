#include <armor.h>
#include <ansi.h>
inherit NECK;

void create()
{
        set_name(HIW"玉佩"NOR, ({"yu pei", "pei", "yu"}));
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
		set("value", 2000);
		set("long", "一枚玉佩，上面还刻着一些图案．\n");
		set("material", "steel");
		set("armor_prop/armor", 1);
		
        }
	setup();
}

