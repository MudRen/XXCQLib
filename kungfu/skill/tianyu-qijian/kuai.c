// kuai.c 「闪电惊虹」
// Write by godzilla 1999.11.5

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	string msg;
	int i, num;

	if( !target ) target = offensive_target(me);
        if(!me->query("lingwu_perform"))
                return notify_fail("你还没有领悟其绝招。\n");
	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("「闪电惊虹」只能在战斗中使用。\n");
	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你现在内力不足，使不出「闪电惊虹」！\n");     	
    if( (int)me->query("int")<25)
	         return notify_fail("天羽奇剑关键在于一个“悟”，悟性不够无法用「闪电惊虹」。\n");	
        if( me->query_temp("tianyu_qijian") )
                return notify_fail("你刚使完「天羽奇剑」的绝招，目前气血翻涌，无法再次运用！\n");
                
    msg = HIY"剑飞，人随，犹如天空中的一道闪电，$N一连向$n刺出了"+HIM+chinese_number((int)me->query_int()/10)+HIY"剑。\n这就是天下第一的快招“"+BLINK+HIR+"闪电惊虹"+NOR+HIY+"”！！\n"NOR;

	if(random(me->query("combat_exp"))>(int)target->query("combat_exp")/20)
	{
		num = (int)me->query_int() / 10;
		msg += WHT"人未到，剑先到,$p被$P攻了个措手不及，连连后退不暇！\n" NOR;
		message_vision(msg, me, target);
		for(i = 0; i < num; i++)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                me->set_temp("tianyu_qijian",1);
		me->add("neili", -100);
		me->start_busy(1);
		call_out("remove_effect", (int)me->query_int()/2, me);
	}
	else
	{
		msg += WHT"剑虽快，可是$p料敌先机，抢先飞出丈外，使$P无法刺到。\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(2);
	}
	
	return 1;
}
void remove_effect(object me)
{
        if (!me)
        return;
        me->delete_temp("tianyu_qijian");
        tell_object(me, HIR"\n你经过一段时间调气养息，又可以使用「天羽奇剑」的绝招了。\n"NOR); 
}
