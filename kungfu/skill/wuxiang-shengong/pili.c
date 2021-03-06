// heal.c

#include <ansi.h>

int exert(object me, object target)
{
	int skill, count, d_count;

	count = me->query_str();
	d_count = me->query_dex();

	skill=me->query_skill("wuxiang-shengong",1);

	if ((int)me->query_skill("wuxiang-shengong", 1) < 120)
		return notify_fail("你的无相神功修为还不够。\n");

	if ((int)me->query("neili") < 500 || (int)me->query("max_neili") < 1000 )
		return notify_fail("你的真气不够。\n");

	if (me->query_temp("leiting"))
		return notify_fail("你已经在运「雷霆霹雳」了\n");

	message_vision(HIW"\n$N深吸一口气，默运「雷霆霹雳」，全身的骨节“啪啪”爆响，僧衣好似大海般的滚腾，翻跃、伏踞、冲折、起落。\n"NOR, me);
	message_vision(HIY"顿时$N的身形灵动了不少，攻势更是威猛了许多，让人有些无力招架。\n"NOR, me);

	me->add_temp("str", count * 3);	
	me->add_temp("dex", d_count);
	me->add("neili", -500);
	me->set_temp("leiting",1);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, count*3, d_count :), skill/6);

	return 1;
}

void remove_effect(object me, int aamount, int damount)
{
	if ( (int)me->query_temp("leiting") ) 
	{
		me->add_temp("str", -aamount);
		me->add_temp("dex", -damount);
		me->delete_temp("leiting");
		tell_object(me, HIY "你的「雷霆霹雳」运行完毕，将内力收回丹田。\n" NOR);
		me->start_busy(random(4));
	}
}
