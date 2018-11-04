// dumpling.c 包子

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(YEL"包子"NOR, ({"baozi", "bao", "dumpling"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个香喷喷的猪肉馅包子。\n");
		set("unit", "个");
		set("value", 50);
		set("food_remaining", 3);
		set("food_supply", 20);
	}
}