// lurou.c 什锦炒饭

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("什锦炒饭", ({"chao fan", "fan"}));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "这是一盘由米饭、鸡蛋、腊肉炒成的什锦炒饭，趁热吃吧。\n");
		set("unit", "盘");
		set("food_remaining", 5);
		set("food_supply", 30);
	}
}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "chi");
}

int do_eat(string arg)
{
	if ( !this_object()->id(arg) ) return 0;

	if ( this_player()->is_busy() )
		return notify_fail("你上一个动作还没有完成。\n");

	if ( (int)this_player()->query("food") >= (int)this_player()->max_food_capacity() )
		return notify_fail("你已经吃的太多了，再也吃不下了。\n");

	this_player()->add("food", (int)query("food_supply"));

	if ( this_player()->is_fighting() ) 
		this_player()->start_busy(2);

	add("food_remaining", -1);

	if ( query("food_remaining") )
	{
   		message_vision("$N捧起盘子，狼吞虎咽的吃了起来。\n", this_player());
	}
	else 
	{ 
	   	message_vision("$N捧起盘子，吃完最后一口饭，舔舔嘴，一副意尤未尽的样子。\n", this_player());
		destruct(this_object());
	}

	return 1;
}
