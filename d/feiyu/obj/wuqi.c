// longsword.c 长剑

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
	set_name(WHT"武器"NOR, ({ "wuqi", }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是一柄五尺长的武器，由于刚刚打好,所以还没打磨。\n");
		set("value", 1500);
		set("material", "iron");
		set("distance", 3);
		
	}
       init_sword(1);
	setup();
}
