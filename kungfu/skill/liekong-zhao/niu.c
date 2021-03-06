// fenfei.c 冲拳
// By Load
 
#include <ansi.h>
 
inherit F_SSERVER;

int perform(object me)
{
	string msg;
	object weapon, target;
	object ob;
	int skill, skill2, ap, dp, qi_wound;

	me->clean_up_enemy();
	target = me->select_opponent();

	skill = (int)me->query_skill("claw");
	skill2 = (int)me->query_skill("force");

	if( !me->is_fighting()|| !living(me) || !(string)me->query_temp("qin_3")
	    || !objectp(ob = present((string)me->query_temp("qin_3"), environment(me)))
	    || !ob->is_fighting() || !living(ob)
	    || ob->query_temp("qin")!=1 ||ob->query_temp("qin_2")!=me->query("id"))
	    	return notify_fail("「扭」只能在战斗中对擒住的对手使用。\n");

	if( (int)me->query("max_neili") < 400 )
		return notify_fail("你的内力修为还不够高！\n");

	if( (int)me->query("neili") < 300 )
		return notify_fail("你现在的内力不足！\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("拿着武器怎么使「扭」？\n");

	if(skill < 135 )
		return notify_fail("你的爪法还不到家，无法使用「扭」！\n");

	if(skill2 < 120 )
		return notify_fail("你内功的修为不够，不能使用「扭」! \n");

	if( me->query_skill_mapped("claw") != "liekong-zhao") 
		return notify_fail("你没有使用裂空爪，无法使用「扭」！\n");
 
	ap = ((me->query("combat_exp"))*(me->query_str()));
	dp = ((target->query("combat_exp"))*(target->query_str()))/2;
	if( dp < 1 )
		dp = 1;
	if( random(ap) > dp )
	{
		qi_wound = skill*2 + random(skill*2);

		if(qi_wound > target->query("qi"))
		{
			msg = HIY "$N抓住$n左腕的突然一松，闪电般的放到$n的头顶，掌心一股吸力令$n的头无法随意转动，然后便是轻轻的一扭……\n\n"NOR;
			msg += HIM "清脆的一声“咔嚓”，$n的双眼就可以看到自己身后的东西了……\n\n"NOR;
			msg += HIR "这就是$n一生看到的最后的世界……\n\n"NOR;
			message_vision(msg, me, target);
			me->start_busy(2 + random(2));
			target->die();
		}
		else
		{
			msg = HIY "$N抓住$n双腕的双爪突然发力，猛然向内侧急转一周，$n惨叫一声，双臂已经不大听使唤了。\n\n"NOR;
			msg += HIR "$N猛地一甩，将$n凌空摔了出去，$n臂痛难当，无法运气，重重的摔在了地上。\n\n"NOR;
			message_vision(msg, me, target);
			target->add("qi", -(qi_wound/2));
			COMBAT_D->report_status(target, 0);
			target->delete_temp("qin",1);
			target->interrupt_me();
			target->delete_temp("qin_2");
			me->delete_temp("qin_3");
			me->interrupt_me();
			me->start_busy(2);
		}

		me->add("neili",-300);
	}
	else
	{
		msg = HIY "$N抓住$n双腕的双爪突然发力，猛然向内侧扭去，$n哪敢怠慢，顺势一拧，双臂如蛇一样脱开了$N的束缚。\n\n"NOR;
		msg += HIG "$N怕$n趁势反击，双爪护身一个筋斗翻了出去。\n\n"NOR;
		message_vision(msg, me, target);
		me->add("neili",-200);
		me->interrupt_me();
		me->start_busy(3);
		target->delete_temp("qin",1);
		target->interrupt_me();
		target->delete_temp("qin_2");
		me->delete_temp("qin_3");
	}

	return 1;
}
