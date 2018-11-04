// jiaxin-biji.c 夹心荸荠
// by Load

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(WHT"夹心荸荠"NOR, ({"jiaxin biji", "biji", "jiaxin"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一盆形态精巧别致，外脆里嫩，而又别有风味的夹心荸荠。\n");
		set("unit", "盘");
		set("value", 1);
		set("food_remaining", 4);
		set("food_supply", 40);
	}
}
