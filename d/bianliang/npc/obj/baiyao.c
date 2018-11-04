// jinchuang.c 金创药

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_fu", "fu");
}

void create()
{
	set_name(HIW"云南白药"NOR, ({"yunnan baiyao", "yao", "baiyao", "yunnan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "瓶");
		set("long", "这是一瓶被奉为疗伤圣品的云南白药，是用来敷(fu)在伤口上的。\n");
		set("value", 10000);
	}
	setup();
}

int do_fu(string arg)
{
	if (!id(arg))
		return notify_fail("你要敷什么药？\n");
	if ((int)this_player()->query("eff_qi") == 
	    (int)this_player()->query("max_qi"))
		return notify_fail("你现在不需要用云南白药。\n");
	else {
		this_player()->receive_curing("qi", 100+random(50));
		message_vision("$N小心翼翼的将云南白药倒在各处伤口上，伤口几乎是奇迹般的好转了。\n", this_player());
		destruct(this_object());
		return 1;
	}
}