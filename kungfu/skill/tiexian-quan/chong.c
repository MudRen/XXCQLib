// fenfei.c 冲拳
// By Load
 
#include <ansi.h>
 
inherit F_SSERVER;

int perform(object me)
{
	string msg;
	object weapon, target;
	object ob;
	int skill, skill2, ap, dp,qi_wound;

	me->clean_up_enemy();
	target = me->select_opponent();

	skill = (int)me->query_skill("cuff");
	skill2 = (int)me->query_skill("force");

	if( !me->is_fighting() || !living(me) )
	    	return notify_fail("「冲拳」只能在战斗中使用。\n");

	if( (int)me->query("max_neili") < 800 )
		return notify_fail("你的内力修为还不够高！\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("拿着武器怎么使「冲拳」？\n");

	if( (int)me->query("neili") < 400 )
		return notify_fail("你现在的内力不足！\n");

	if( skill < 135 )
		return notify_fail("你的拳法还不到家，无法使用「冲拳」！\n");

	if( skill2 < 120)
		return notify_fail("你内功的修为不够，不能使用「冲拳」! \n");

	if( me->query_skill_mapped("cuff") != "tiexian-quan") 
		return notify_fail("你没有激发铁线拳，无法使用「冲拳」！\n");
 
	msg = HIY "$N突然向前迈上三大步，气沉丹田，一声闷喝，右拳一记「冲拳」自腰间猛然挥出，
势若奔雷、快若闪电却又简简单单、全无花巧，直奔$n而去！！！\n\n"NOR;
	message_vision(msg, me, target);
 
	ap = ((me->query("combat_exp"))*(me->query_str()));
	dp = ((target->query("combat_exp"))*(target->query_dex()))/2;
	if( dp < 1 )
		dp = 1;
	if( random(ap) > dp )
	{
		if(userp(me))
			me->add("neili",-500);

		msg = HIR "$n躲闪不及，被$N雷霆一拳正中前心，“嘭”一声闷响，前胸已然塌了下去，
$n的脸色变得煞白，一口鲜血自$n口中狂喷而出。\n\n"NOR;
		message_vision(msg, me, target);
		qi_wound = skill*2 + random(skill*2);

		if(qi_wound > target->query("qi"))
			qi_wound = (target->query("qi") + 1);

		target->add("qi", -qi_wound);
		COMBAT_D->report_status(target, 0);
		me->start_busy(2 + random(3));
	}
	else if( ob = target->query_temp("weapon")
	&& (random(me->query("combat_exp")))>(random(target->query("combat_exp"))))
	{
		if(userp(me))
		{
			ob = target->query_temp("weapon");
			me->add("neili",-400);
			message_vision(HIW "忙乱间$N用手中" + ob->name() +
				"去挡来拳,却只听见「啪」地一声，$N手中的" + ob->name() +
				"已经断为两截！\n" NOR, target );
			ob->unequip();
			ob->move(environment(target));
			ob->set("name", "断掉的" + ob->query("name"));
			ob->set("value", 0);
			ob->set("weapon_prop", 0);
			target->reset_action();
			me->start_busy(random(3));
		}
	}
	else
	{
		msg = HIG "只见$n神色一凛，不敢硬接，一个翻身及时的退出战圈，躲开了$N凌厉的攻势！\n\n"NOR;
		message_vision(msg, me, target);
		if(userp(me))
			me->add("neili",-200);
		me->start_busy(3);
	}

	return 1;
}
