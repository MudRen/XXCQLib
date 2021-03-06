// heal.c

#include <ansi.h>

int exert(object me, object target)
{
	if( me->is_fighting() )
		return notify_fail("你正在战斗，不能运功疗伤！\n");

	if (me->is_busy())
		return notify_fail("你正忙着其他事，怎么疗伤？\n");

	if ((int)me->query_skill("tianlongforce", 1) < 30)
		return notify_fail("你的金刚天龙功修为还不够，还不会自己来疗伤。\n");
	if( (int)me->query("neili") < 50 ) 
		return notify_fail("你的真气不够。\n");
	if ((int)me->query("eff_qi") > ((int)me->query("max_qi")-1))
		return notify_fail("你不需要疗伤。\n");

	if( (int)me->query("eff_qi") < (int)me->query("max_qi") / 3 )
		return notify_fail("你受伤太重，无法自己引导真气运行全身来疗伤！\n");

	write( HIW "你气沉丹田，抱一归元，运“金刚天龙神功”渐渐控制了全身的真气，\n" NOR);
	message("vision",
		HIY + me->name() + "盘膝而坐，默运神功，突然狂啸一声，冲天拔起，脸色看起来似乎好了许多。\n" NOR,
		environment(me), me);

	me->receive_curing("qi", 20 + (int)me->query_skill("force")/5 );
	me->add("neili", -50);
	me->set("jiali", 0);

	return 1;
}
