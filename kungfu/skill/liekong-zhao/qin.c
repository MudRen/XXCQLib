// qin.c 擒
 
#include <ansi.h>
 
inherit F_SSERVER;

int perform(object me)
{
	string msg;
	object weapon, target;
	int num, skill, skill2, ap, dp,damage;

	me->clean_up_enemy();
	target = me->select_opponent();

	skill = (int)me->query_skill("claw");
	skill2 = (int)me->query_skill("force");
	num = skill / 50;

	if( !me->is_fighting()|| !living(me) )
	    	return notify_fail("「擒」只能在战斗中使用。\n");

	if( (int)me->query("max_neili") < 300 )
		return notify_fail("你的内力修为还不够高！\n");

	if( (int)me->query("neili") < 200 )
		return notify_fail("你现在的内力不足！\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("拿着武器怎么使「擒」？\n");

	if(skill < 100 )
		return notify_fail("你的爪法还不到家，无法使用「擒」！\n");

	if(skill2 < 90)
		return notify_fail("你内功的修为不够，不能使用「擒」! \n");

	if( me->query_skill_mapped("claw") != "liekong-zhao") 
		return notify_fail("你没有使用裂空爪，无法使用「擒」！\n");
 
	msg = HIW "$N虚幌一爪，突然欺上三步，双爪贯足真力以迅雷不及掩耳之势扣向$n的双腕。\n\n"NOR;

	message_vision(msg, me, target);
 
	ap = ((me->query("combat_exp"))*(me->query_dex()));
	dp = ((target->query("combat_exp"))*(target->query_dex()))/3;
	if( dp < 1 )
		dp = 1;
	if( random(ap) > dp )
	{
		if (random(me->query("max_neili")*me->query_str())>random((target->query("max_neili")*target->query_str())/2))
		{
			me->add("neili",-200);
			msg = HIY "$n一个躲闪不及，双腕已被$N扣个正着，$N顺势一扭，已经将$n的双臂扭在了身后，$n一下子便动弹不得了！\n\n"NOR;
			message_vision(msg, me, target);
			me->start_busy(6);
			target->start_busy(6);
			target->set_temp("qin",1);
			target->set_temp("qin_2",me->query("id"));
			me->set_temp("qin_3",target->query("id"));
			call_out("check", 6, me, target);
		}
		else
		{
			damage = skill + random(skill);
			target->add("neili",100);
			me->add("neili",-200);
			msg = HIR "$n没有躲闪，待$N双爪一扣$n的双腕，突运内力，立时一股大力向$N反冲而去，$N感到喉口一甜，一口鲜血便喷了出来！\n\n"NOR;
			message_vision(msg, me, target);
			target->receive_damage("qi", damage);
			target->receive_wound("qi", damage/3);
			COMBAT_D->report_status(me, 0);
		}
	}
	else
	{
		msg = HIG "只见$n双臂疾缩，一个翻身落在七尺开外，躲开了$N凌厉的一扣！\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-100);
		me->start_busy(3);
	}

	return 1;
}

int check(object me,object target)
{
	object weapon;
	string msg;

 	if(me->is_fighting() && living(target) && living(me) && (!objectp(weapon = me->query_temp("weapon")))
		&& target->query_temp("qin"))
	{
		int a,b;
		a=(me->query("max_neili"))*(me->query_str());
		b=(target->query("max_neili"))*(target->query_str());
		if ((random(a)>random(b))&& me->query("neili")>200)
		{
			msg = HIY "\n$n用力挣扎，无奈$N双手如铁钳一般纹丝不动，实在挣脱不开！\n\n"NOR;
			message_vision(msg, me, target);
			me->add("neili",-100);
			if (target->query("neili")>50) target->add("neili",-50);
			me->start_busy(6);
			target->start_busy(6);
			target->set_temp("qin",1);
			target->set_temp("qin_2",me->query("id"));
			me->set_temp("qin_3",target->query("id"));
			call_out("check", 6, me, target);
		}
		else
		{
			msg = HIC "\n$n觉得$N似乎体力消耗过大，双爪渐松，忙趁机运全身力气拼命一挣，竟然挣脱开了$N的束缚！\n\n"NOR;
			message_vision(msg, me, target);
			target->delete_temp("qin",1);
			target->interrupt_me();
			target->delete_temp("qin_2");
			me->delete_temp("qin_3");
			me->interrupt_me();
			me->start_busy(2);
		}
	}
	return 1;
}
