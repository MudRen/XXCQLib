// made by lks

#include <ansi.h>

inherit F_SSERVER;
int exert(object me, object target)
{
        int damage;
        string msg;

        me->clean_up_enemy();
        target = me->select_opponent();

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「旋涡劲」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("force", 1) < 80 )
                return notify_fail("你的内功底子太薄，不能使用。\n");
                                
        if( (int)me->query_skill("longmen-shengong", 1) < 80 )
                return notify_fail("你的龙门神功不够熟练。\n");
                        
        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("你现在内力太弱，不能使用「旋涡劲」。\n");
                        
        msg = HIC "$N气贯丹田，双掌齐出，推出一股带着旋涡的气流。罩向$n。\n"NOR;

            if (wizardp(me)) {
                  msg += WHT"$n只觉人如舟子在掀天巨浪中颠簸起落，全不能自己！\n"NOR;
                  target->start_busy( (int)me->query_skill("force") / 40 + 1);
          message_vision(msg, me, target);
                  return 1;
               }
        if (random(me->query_skill("force")) > target->query_skill("force")/2 )
        {
                  target->start_busy( 4 + random(3));
                
                damage = (int)me->query_skill("force", 1);
                damage = damage +  (int)me->query("max_neili")/10;
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                me->add("neili", -300);
                msg += WHT"$n只觉人如舟子在掀天巨浪中颠簸起落，全不能自己！\n"NOR;
                me->start_busy(2);
        } else 
        {
                msg += YEL"可是$p向旁边侧身一闪,跳出了旋涡的攻击范围。\n"NOR;
                me->add("neili", -200);
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}

