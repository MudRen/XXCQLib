// luoyan.c 沉鱼落雁

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("[沉鱼落雁]只能对战斗中的对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能使用[沉鱼落雁]！\n");		
		
        if( (int)me->query_skill("youyu-quan", 1) < 100 )
		return notify_fail("你的游鱼拳法不够娴熟，不能使用「沉鱼落雁」。\n");
	                        
        if( (int)me->query("neili", 1) < 400 )
		return notify_fail("你现在内力太弱，不能使用「沉鱼落雁」。\n");
			
	msg = HIR "$N使出飞鱼拳法中的一式［沉鱼落雁］，双拳连环击出，顿时拳影密布，层层击向$n！" NOR;
	me->add("neili", -250);

        if( !target->is_killing(me) ) target->kill_ob(me);

	if (random(me->query_skill("cuff")) > target->query_skill("parry")/2 )
	{
		me->start_busy(2);
		target->start_busy(random(4));
		
		damage = (int)me->query_skill("youyu-quan", 1);
		
                damage = damage/2 + random(damage/2);
		
		target->receive_damage("qi", damage*2);
		target->receive_wound("qi", damage);
                
    if( damage < 20 ) msg += HIY"结果$n受到$N的内力反震，闷哼一声。\n"NOR;
        	else if( damage < 40 ) msg += HIY"结果$n被$N以内力反震，「嘿」地一声退了两步。\n"NOR;
        	else if( damage < 80 ) msg += RED"结果$n被$N以内力一震，胸口有如受到一记重锤，连退了五六步！\n"NOR;
                else msg += HIR"结果$n被$N的内力一震，眼前一黑，身子向后飞出丈许！！\n"NOR;
		
	} else 
	{
		me->start_busy(3);
		msg += CYN"可是$p看破了$P的企图，并没有上当。\n"NOR;
	}
	message_vision(msg, me, target);
	if(!target->is_fighting(me)) target->fight_ob(me);

	return 1;
}
