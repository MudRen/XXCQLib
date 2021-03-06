// fenfei.c 满天花雨
 
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

        skill = me->query_skill("sword");
        skill2 = me->query_skill("force");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("笨蛋，不使剑怎么能使「满天花雨」？\n");

        if((string)weapon->query("name") == "剑鞘")
                return notify_fail("傻瓜，剑鞘怎么逼的碎？\n");

        if( !me->is_fighting()|| !living(me) )
                return notify_fail("「满天花雨」只能在战斗中使用。\n");

        if( (int)me->query("max_neili") < 600 )
                return notify_fail("你的内力修为还不够高！\n");

        if( (int)me->query("neili") < 300 )
                return notify_fail("你现在的内力不足！\n");

        if( skill < 120)
                return notify_fail("你浣花剑法的修为不够，不能使用「满天花雨」! \n");

        if( skill2 < 90)
                return notify_fail("你九曲心法的修为不够，不能使用「满天花雨」! \n");

        if( me->query_skill_mapped("sword") != "huanhua-jian") 
                return notify_fail("你没有激发浣花剑法，无法使用「满天花雨」！\n");
 
        if (skill<270 || weapon->query("endure")<130)
        {
                msg = HIY "$N忽然向后疾退两步，气沉丹田，力贯剑身，霎时剑身碎裂，犹如「满天花雨」，无数剑片向$n飞射而去。\n\n"NOR;
                message_vision(msg, me, target);
                ob = me->query_temp("weapon");
        if( (string)weapon->query("id")!="changge")
                destruct(ob);
 
                ap = ((me->query("combat_exp"))*(me->query_dex()));
                dp = ((target->query("combat_exp"))*(target->query_dex()))/2;

                if( dp < 1 )
                        dp = 1;
                if( random(ap) > dp )
                {
                        msg = HIR "$n一个躲闪不及，无数剑片已然嵌在了$n的身上，$n惨叫一声，脸上露出极为痛苦的表情。\n\n"NOR;
                        message_vision(msg, me, target);
                        qi_wound = 100 + skill + random(skill*2);

                        if(qi_wound > target->query("qi")) qi_wound = (target->query("qi") + 1);
                        target->add("qi", -qi_wound);
                        target->add("eff_qi", -(qi_wound/4));
                        COMBAT_D->report_status(target, 0);
                        me->start_busy(1+random(2));
                        me->add("neili",-250);
                }
                else
                {
                        msg = HIG "只见$n不敢怠慢，脚一点地疾飞冲天，堪堪躲过了这满天的剑片。\n\n"NOR;
                        message_vision(msg, me, target);
                        me->start_busy(3);
                        me->add("neili",-100);
                }

                call_out("perform_qiao", 10, me);
                return 1;
        }
        else if(skill<270 && weapon->query("endure")>=130)
        {
                msg = HIW "$N忽然向后疾退两步，手腕一振就要施展浣花剑法三绝技之一的“满天花雨”，却不料功力不
足，居然没有震碎手中$w。\n" NOR;
                msg += HIR "$n刚要躲闪，突然发现机会难得，立时又扑了上来。\n\n";
                message_vision(msg, me, target);
                me->add("neili",-50);
                me->start_busy(1+random(2));
        }
        else
        {
                msg = WHT "$N突然向后疾退两步，力惯"+weapon->query("name")+WHT"，三寸剑芒吞吐，手腕一振，竟然使出了浣花三绝
技之“满天花雨”，万点剑芒罩向$n。\n\n" NOR;
                message_vision(msg, me, target);

                ap = ((me->query("combat_exp"))*(me->query_dex()));
                dp = ((target->query("combat_exp"))*(target->query_dex()))/2;

                if( dp < 1 )
                        dp = 1;
                if( random(ap) > dp )
                {
                        msg = HIR "$n一个躲闪不及，万道剑芒恰如无数剑片打在了$n的身上，$n惨叫一声，脸
上露出极为痛苦的表情。\n\n"NOR;
                        message_vision(msg, me, target);
                        qi_wound = 100 + skill + random(skill*2);

                        if(qi_wound > target->query("qi")) qi_wound = (target->query("qi") + 1);
                        target->add("qi", -qi_wound);
                        target->add("eff_qi", -(qi_wound/4));
                        COMBAT_D->report_status(target, 0);
                        me->start_busy(1 + random(2));
                        me->add("neili",-200);
                }
                else
                {
                        msg = HIG "只见$n不敢怠慢，脚一点地疾飞冲天，堪堪躲过了这满天的剑芒。\n\n"NOR;
                        message_vision(msg, me, target);
                        me->start_busy(2);
                        me->add("neili",-100);
                }

                return 1;
        }

        return 1;
}
int perform_qiao(object me)
{
        object weapon, target;
        target = me->select_opponent();
        if(me->is_fighting() && living(target) && living(me) && (!objectp(weapon = me->query_temp("weapon"))))
        {
                object qiao;
                string msg;
                int count;
                qiao = new("/d/huanhua/npc/obj/qiao");
                qiao->move(me);
                qiao->wield();
                count = me->query_dex();
                me->add_temp("dex", count * 3); 
                count = me->query_str();
                me->add_temp("str", count * 2); 
                msg = HIY "\n$N突然从腰畔将剑鞘拿到手中，招式突然加速，闪电般攻出三招，这突然的变化令$n目瞪口呆！\n\n"NOR;
                message_vision(msg, me, target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                me->delete_temp("dex", count * 3);
                me->delete_temp("str", count * 2);
        }
        return 1;
}
