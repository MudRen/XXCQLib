inherit ITEM;

#include <ansi.h>

void init()
{
        add_action("do_drink", "drink");
        add_action("do_drink", "he");
}

void create()
{
	set_name(HIM"芙蓉花菇汤"NOR, ({"huagu tang", "huagu", "tang"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一盆汤稠汁浓，味滑爽口的芙蓉花菇汤。\n");
		set("unit", "盆");
		set("value", 1);
		set("drink_remaining", 4);
		set("drink_supply", 40);
	}
}

int do_drink(string arg)
{
	if ( !this_object()->id(arg) ) return 0;

	if ( this_player()->is_busy() )
		return notify_fail("你上一个动作还没有完成。\n");

	if ( (int)this_player()->query("water") >= (int)this_player()->max_water_capacity() )
		return notify_fail("你已经喝太多了，再也灌不下一滴水了。\n");

	this_player()->add("water", (int)query("drink_supply"));

	if ( this_player()->is_fighting() ) 
		this_player()->start_busy(2);

	add("drink_remaining", -1);

	if ( query("drink_remaining") )
	{
   		message_vision("$N捧起汤碗，美美的喝了一口芙蓉花菇汤。\n", this_player());
	}
	else 
	{ 
	   	message_vision("$N捧起汤碗，喝干了最后一滴芙蓉花菇汤。\n", this_player());
		destruct(this_object());
	}

	return 1;
}
