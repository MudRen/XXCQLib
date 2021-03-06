// heal.c

#include <ansi.h>

int exert(object me, object target)
{
	if( me->is_fighting() )
		return notify_fail("战斗中运功疗伤？找死吗？\n");

	if (me->is_busy())
		return notify_fail("你正忙着其他事，怎么疗伤？\n");

	if ((int)me->query_skill("banruo-changong", 1) < 20)
		return notify_fail("你的般若禅功修为还不够。\n");
	if( (int)me->query("neili") < 50 ) 
		return notify_fail("你的真气不够。\n");
	if( (int)me->query("jingli") < (10 + (int)me->query_skill("force")/3)/3 ) 
		return notify_fail("你的真气不够。\n");
	if ((int)me->query("eff_qi") > ((int)me->query("max_qi")-1))
		return notify_fail("你不需要疗伤。\n");

	if( (int)me->query("eff_qi") < (int)me->query("max_qi") *2/ 5 )
		return notify_fail("你的经脉受损，根本无法引导真气运行周身！\n");

	write( HIC "你面向北方，盘膝而坐，运一股丹田气护住心脉，另外一股至刚内息则运转周身。\n" NOR);
	write( HIW "片刻过去，内息已经畅快了不少，伤势见轻，但精神有些疲惫。\n" NOR);
	message("vision",
		HIM + me->name() + "面北而坐，双手合十，双目微闭，潜运内功，片刻脸上已经红润了不少，但神色有些疲惫。\n" NOR,
		environment(me), me);

	me->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
	me->add("neili", -50);
	me->add("jingli", -((10 + (int)me->query_skill("force")/3)/2));
	me->set("jiali", 0);

	return 1;
}
