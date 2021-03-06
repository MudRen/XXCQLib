// poison_dust.c

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{

	set_name(WHT"软骨散"NOR, ({ "ruangu san", "san" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "这是一包白色的药粉。\n" );
		set("unit", "包");
		set("base_value", 700);
       set("base_unit", "包");
		set("base_weight", 30);
       set("yaowang", 1);
       set("nopawn", 1);
       set("no_pawn", 1);
       set("value", 0);
	}
	set_amount(1);
}

void init()
{
	object me, ob;
	int obj;

	me = this_player();
	ob = this_object();
	obj = (int)me->query_skill("healing");

	if( me->query_temp("liandan")==1
		&& ob->query("value")==0 )
	{
		if(obj<60) {
			ob->set("value", (random(2000)+2000)); }
		if(obj>=60 && obj<80) {
			ob->set("value", (random(4000)+4000)); }
		if(obj>=80 && obj<100) {
			ob->set("value", (random(8000)+7000)); }
		if(obj>=100 && obj<150) {
			ob->set("value", (random(15000)+15000)); }
		if(obj>=200) {
			ob->set("value", (random(20000)+30000));
			}
	}
	add_action("do_pour", "pour");
}

int do_pour(string arg)
{
	string me, what;
	object ob;
	function f;

	if( !arg
	||	sscanf(arg, "%s in %s", me, what)!=2
	||	!id(me) )
		return notify_fail("命令格式: pour <药> in <物品>。\n");

	ob = present(what, this_player());
	if( !ob )
		return notify_fail("你身上没有" + what + "这样东西。\n");
	if( !ob->query("liquid/remaining") )
		return notify_fail(ob->name() + "里什么也没有，先装些酒水才能溶化药粉\n");
	f = (: call_other, __FILE__, "drink_drug" :);
	ob->set("liquid/drink_func", bind(f, ob));
	ob->add("liquid/slumber_effect", 100);
	message_vision("$N将一些" + name() + "倒进" + ob->name() 
		+ "摇晃了几下。\n", this_player());
	add_amount(-1);
	return 1;
}

int drink_drug(object ob)
{
	this_player()->apply_condition("slumber_drug",
		(int)this_player()->query_condition("slumber_drug") 
		+ (int)ob->query("liquid/slumber_effect") );
	return 0;
}
