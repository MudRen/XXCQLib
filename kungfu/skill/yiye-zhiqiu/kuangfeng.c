// kuangfeng.c  狂风扫落叶

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object ob;
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「狂风扫落叶」只能对战斗中的对手使用。\n");

	if ( !ob=present("bajiaoye",me) )
		return notify_fail("你身上好象缺一样东西，不能发挥这招的威力。\n");
	
         if ( (int)me->query("shen") < 5000 )
		return notify_fail("你的侠义正气不够，控制不了铁叶的飞行轨迹。\n");
		
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return 0;
		
	if( (int)me->query_skill("yiye-zhiqiu", 1) < 50 )
		return notify_fail("你的一叶知秋不够娴熟，不会使用。\n");
	                        
	if( (int)me->query_skill("bairen-shengong", 1) < 50 )
		return notify_fail("你的百忍不如一怒神功不够高。\n");
			
	if( (int)me->query("neili", 1) < 300 )
		return notify_fail("你现在内力太弱，不能使用「狂风扫落叶」。\n");
			
	msg = CYN "$N凝神息气，手腕疾抖，一道白光夹着拳劲飞向$n。\n"NOR;

	if( !target->is_killing(me) ) target->kill_ob(me);

	if (random(me->query_skill("force")) > target->query_skill("force")/2 )
	{
                target->start_busy( (int)me->query_skill("yiye-zhiqiu") / 20 + 1);
		
		damage = (int)me->query_skill("bairen-shengong", 1);
		damage = damage +  (int)me->query_skill("yiye-zhiqiu", 1);
		damage = damage +  (int)me->query_skill("cuff", 1);
		
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
                me->add("neili", -(damage/3));
		msg += HIR"只见白光聚为一线，穿向$n,\n$n只觉一股热流穿心而过，喉头一甜，鲜血狂喷而出！\n"NOR;
		me->start_busy(2);
	} else 
	{
		msg += CYN"可是$p猛地向前一跃,跳出了$P的攻击范围。\n"NOR;
		me->add("neili", -100);
		me->start_busy(4);
	}
	message_vision(msg, me, target);

	return 1;
}
