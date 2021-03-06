// lifeheal.c

#include <ansi.h>

int exert(object me, object target)
{
	if ((!target)||target->query("id")==me->query("id"))
		return notify_fail("请用yun heal为自己疗伤。\n");

	if (me->query_skill("banruo-changong",1) < 60)
		return notify_fail("你没有达到小般若神功的境界，无法给别人疗伤。\n");

	if( me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功疗伤！\n");


	if( (int)me->query("max_neili") < 300 )
		return notify_fail("你的内力修为不够。\n");

	if( (int)me->query("neili") < 150 )
		return notify_fail("你的真气不够。\n");

	if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 5 )
		return notify_fail( target->name() +
			"已经受伤过重，经受不起你的真气震荡！\n");

	message_vision(
		HIY "$N盘膝坐在$n身后一掌贴其后心运内力护其心脉，另一掌运足真力拍了下去……\n"NOR + 
		HIC"$n身子猛地一震，一口"NOR+RED"暗红色淤血"NOR+HIC"喷出，脸色看起来红润了许多。\n\n" NOR,
		me, target );

	target->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
	target->add("qi", 10 + (int)me->query_skill("force")/5 );
	if( (int)target->query("qi") > (int)target->query("eff_qi") ) target->set("qi", (int)target->query("eff_qi"));

	me->add("neili", -150);
	me->set("jiali", 0);
	return 1;
}