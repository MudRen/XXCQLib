// fenfei.c 乱絮纷飞
 
#include <ansi.h>
 
inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target, ob;
        int i, num, skill, skill2, ap, dp,count;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = (int)me->query_skill("strike");
        skill2 = (int)me->query_skill("force");
        num = skill / 50;

        if( !me->is_fighting()|| !living(me) )
                return notify_fail("「乱絮纷飞」只能在战斗中使用。\n");

        if( (int)me->query("max_neili") < 600 )
                return notify_fail("你的内力修为还不够高！\n");

        if( (int)me->query("neili") < 400 )
                return notify_fail("你现在的内力不足！\n");

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("拿着武器怎么使「乱絮纷飞」？\n");

        if(skill < 120 )
                return notify_fail("你的掌法还不到家，无法使用「乱絮纷飞」！\n");

        if(skill2 < 90)
                return notify_fail("你内功的修为不够，不能使用「乱絮纷飞」! \n");

        if( me->query_skill_mapped("strike") != "feixu-zhang") 
                return notify_fail("你没有激发飞絮掌，无法使用「乱絮纷飞」！\n");
 
        msg = HIY "$N忽然身形一拧，越在半空，双臂急挥，双掌化十掌、百掌、千掌、万掌，如三月阳春，
「乱絮纷飞」，把$n完全罩在掌风之中。\n\n"NOR;

        message_vision(msg, me, target);
 
        ap = ((me->query("combat_exp"))*(me->query_dex()));
        dp = ((target->query("combat_exp"))*(target->query_dex()))/2;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp )
        {
                me->add("neili",-300);
                msg = HIR "突然$N的千万掌又合成一掌，欺近$n的身边，闪电般攻出数招，真是避无可避，退无可退！\n\n"NOR;
                message_vision(msg, me, target);
                count = me->query_dex();
                me->add_temp("dex", count * 2); 
                ob = me->select_opponent();
                for (i=0; i<num; i++)
                {
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                }
                me->add_temp("dex", (-1) * count * 2);  
                me->start_busy(random(4));
        }
        else if((random(me->query("combat_exp")))>(random(target->query("combat_exp"))))
        {
                me->add("neili",-300);
                msg = HIW "$n竭尽全力，竟然挡住了$N这虚虚实实、纷繁复杂的千万掌的攻势，可是却顾不上进招了！\n\n"NOR;
                message_vision(msg, me, target);
                target->start_busy(num/2+random(num));
        }
        else
        {
                msg = HIG "只见$n神色一凛，不敢硬接，一个翻身及时的退出战圈，躲开了$N凌厉的攻势！\n\n"NOR;
                message_vision(msg, me, target);
                me->add("neili",-100);
                me->start_busy(3);
        }

        return 1;
}
