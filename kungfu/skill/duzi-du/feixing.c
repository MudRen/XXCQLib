// perform: feixing.c 
// Created by Zeus 1999.4.27
// Modified by Zeus 1999.4.30
// Big Modified
// 
 
#include <ansi.h>
 
inherit F_SSERVER;

string status_msg(int ratio)
{
	if( ratio==100 ) return HIG "看起来充满活力，一点也不累。" NOR;
	if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
	if( ratio > 90 ) return HIY "看起来可能有些累了。" NOR;
	if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
	if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
	if( ratio > 40 ) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
	if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑著不倒下去。" NOR;
	if( ratio > 20 ) return HIR "看起来已经力不从心了。" NOR;
	if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
	return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}

varargs void report_status(object ob)
{
	message_vision( "( $N" + status_msg(
		(int)ob->query("qi") * 100 / (int)ob->query("max_qi") ) 
		+ " )\n", ob);
}

int perform(object me)
{
        string msg;
	object weapon, target;
	object ob;
	int skill, skill2, ap, dp, neili_wound, qi_wound;

	me->clean_up_enemy();
	target = me->select_opponent();

        skill = (me->query_skill("duzi-du",1)+(me->query_skill("lphand",1))/2);
	skill2 = (me->query_skill("zhixin",1)+(me->query_skill("force",1))/2);

        if( !me->is_fighting() || !living(me) )
                return notify_fail("「飞行之毒」只能对战斗中的对手使用。\n");
 
        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("「飞行之毒」必须徒手使用。\n");

        if( skill < 100)
                return notify_fail("你的「毒字毒」等级不够, 不能使用「飞行之毒」！\n");

        if( me->query("neili") < 200 )
                return notify_fail("你的内力不够，无法运用「飞行之毒」！\n");
 
        msg = HIC "$N伸出右手食指在胸前写了一个大大的“毒”字，然后双手一扬，那“毒”字竟然向$p飞去。\n"NOR;
        message_vision(msg, me, target);

	ap = ((me->query("combat_exp"))*(me->query_dex()));
	dp = ((target->query("combat_exp"))*(target->query_dex()))/2;
	if( dp < 1 )
		dp = 1;
	if( random(ap)*2 > dp && (random(100)<10))
	{
		if(userp(me))
			me->add("neili",-100);

                msg = HIR "$n一个躲闪不及，"+HIR"那“毒”字竟然完全附在$n的胸前，$n的身体颤抖了一下，肤色迅速变黑，看来$n已经死了。\n\n"NOR;
		message_vision(msg, me, target);
                target->die();
		me->start_busy(random(6));
	}
	else if( random(ap) > dp )
	{
		if(userp(me))
			me->add("neili",-100);

		msg = HIR "$n努力的向旁一闪，"+HIR"那“毒”字的一角还是碰到了$n，$n的脸色迅速变黑，显然中了不小的毒，$n咬了咬牙，已然痛苦得汗如雨下了。\n\n"NOR;
		message_vision(msg, me, target);
		qi_wound = skill + random(skill*2);

		if(qi_wound > target->query("qi"))
			qi_wound = (target->query("qi") + 1);

		target->add("qi", -qi_wound);
		target->add("eff_qi", -(qi_wound/4));
                target->apply_condition("feixing_poison", random(me->query_skill("duzi-du")/10) + 1 + me->query_condition("feixing_poison"));
		report_status(target);
		me->start_busy(random(6));
	}
	else
	{
		msg = HIG "只见$n不敢怠慢，身轻如燕，"+HIG"一下子漂过了那“毒”字的飞行路线，好险哪！\n\n"NOR;
		message_vision(msg, me, target);
		if(userp(me))
			me->add("neili",-100);
		me->start_busy(3);
	}

	return 1;

}
