// 扫把 回春堂做任务的道具。
// By 山猫Adx 16:53 99-10-25

#include <weapon.h>
inherit HAMMER;

void create()
{
	set_name("扫把", ({ "saoba" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "根");
		set("long", "这是一根竹制的扫把。\n");
                set("value", 1);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，拿在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
	}
        init_hammer(5);
	setup();
}

void init()
{
           add_action("do_job","dasao");
}

int do_job(string arg)
{
        object *inv;
        object me;
         int i, jing;

	me = this_player();
	jing = ( random(me->query("str"))/3 );
	inv = all_inventory(me);
	if (jing <= 0)
		jing = 5;

	if (me->query("jingli")<=jing) {
		message_vision ("$N太累了，得先休息一下，才能继续完成任务！\n", me );
        	return 1;
	}

	if (!me->query_temp("renwu_name")) {
		message_vision ("$N拿起扫把，狂舞了一阵便觉无趣！\n", me);
        	return 1;
	}

	if (me->query_temp("renwu_wancheng") >= 100)
	{
		me->set_temp("renwu_wancheng",100);   //表示完成任务
		return notify_fail ("你完成了任务，回去复命吧！\n");
	}

	if(environment(me)->query("short")!=me->query_temp("renwu_name"))
		return notify_fail ("不是让你在这里打扫啊！\n");

	//判断是否wield了工具
	if( (string)(inv[i]->query("id"))=="saoba" && 
		(int) inv[i]->query("equipped") ) {

		me->add_temp("renwu_wancheng",jing);
		me->add("jingli", -jing);
		me->improve_skill("healing", (jing/3));
		message_vision ("$N拿起扫把，一边扫着地板，一边留意医师在给人把脉！\n", me);
	}
	else {
		return notify_fail ("你空手怎么扫地？拿手抓吗！\n");
		}
        return 1;
}
