// 蛇胆 药王庄做药的道具。
// By 山猫Adx 16:53 99-10-25

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name( HIG "蛇胆" NOR , ({"she dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个浓绿色的蛇胆。\n");
		set("unit", "个");
		set("yaowang", 1);
		set("value", 1000);
		set("weight", 1000);
	}
}
