// sample master.c code
// xiake island master.c

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void away();

void create()
{
	set_name("蒙面人", ({"mengmian ren", "mengmian", "ren"}));
	set("gender", "男性");
	set("age", 26);
	set("long", 
		"一个蒙着面的黑衣人，一副鬼鬼祟祟的样子。\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("bac", 20);

	setup();

	set("chat_chance", 20);
	set("chat_msg", ({
		(: away :),
	}));
}

void away()
{
	if( living(this_object()) )
	{
		message_vision(HIW"蒙面人冷哼了一声道：堂堂少林不过如此。然后匆匆的离开了。\n"NOR, this_object());
		destruct(this_object());
	}
	return;
}

void unconcious()
{
	message_vision(HIC"\n蒙面人跃出战圈，一抱拳道：“少林功夫，名不虚传，再会。”说罢急急忙忙离开了。\n\n"NOR,this_object());
	destruct(this_object());
	return;
}