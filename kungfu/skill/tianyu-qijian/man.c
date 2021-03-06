// man.c
// 老牛破车

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「老牛破车」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("你使用的武器不对。\n");
        if( target->is_busy() )
                return notify_fail(target->name() + "的动作已经慢了下来。\n");
                
        if( (int)me->query_skill("tianyu-qijian", 1) < 100 )
                return notify_fail("你的天羽奇剑不够娴熟，不会使用「老牛破车」。\n");
      if((int)me->query("int")<25)
          return notify_fail("天羽奇剑关键在于一个“悟字”,你悟性不够无法使用「老牛破车」!\n");

        if(!me->query("lingwu_perform"))
                return notify_fail("你还没有领悟其绝招。\n");

        msg = CYN "\n四周的空气似乎已经慢慢凝固，眼前的一切已经慢了下来，$N缓缓使出了\n天下第一慢招"+BLINK+WHT+"「老牛破车」\n"NOR;

        if(me->query("combat_exp") > random(target->query("combat_exp")))
        {
                msg += RED"结果$p完全被$P的招式所控制，招式跟着慢了下来。\n" NOR;
                target->start_busy(3+random(3));
                
        } 
        else 
        {
                msg += WHT"$p不被你招式所动，仍然应对自如。\n" NOR;
                me->start_busy(random(2));
        }
        message_vision(msg, me, target);
        if(!target->is_fighting(me))
        target->fight_ob(me);
        return 1;
}

