// perform: feixing.c 飞行之毒
// Created by Zeus 1999.4.27
// Modified by Zeus 1999.6.8
// 
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
        int objxiandex,objdex,objdodge;
        int myxiancon,mycon,myforce;

        me->clean_up_enemy();
        target = me->select_opponent();

        if( !me->is_fighting() || !living(me) )
                return notify_fail("「飞行之毒」只能对战斗中的对手使用。\n");
 
        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("「飞行之毒」必须徒手使用。\n");

        if( me->query_skill("duzi-du") < 100)
                return notify_fail("你的「毒字毒」等级不够, 不能使用「飞行之毒」！\n");

        if( me->query("neili") < 200 )
                return notify_fail("你的内力不够，无法运用「飞行之毒」！\n");
 
        objxiandex=target->query("dex");
        objdex=target->query_dex();
        objdodge=target->query_skill("dodge",1);

        myxiancon=me->query("con");
        mycon=me->query_con();
        myforce=target->query_skill("force",1);

        msg = HIC "\n$N伸出右手食指在胸前写了一个大大的“毒”字，然后双手一扬，那“毒”字竟然向$p飞去。\n"NOR;
        message_vision(msg, me, target);

        if ( objxiandex <= 20 && me->query("neili")>50 ) { 
                msg = HIB "$n努力的向旁一闪，那“毒”字的一角还是碰到了$n，$n的脸色迅速变黑，\n"NOR;
                message_vision(msg, me, target);
                me->add("neili",-50);
                target->add("qi",-objxiandex*myxiancon);
                target->add("eff_qi",-objxiandex*myxiancon);
                target->apply_condition("feixing_poison", random(me->query_skill("duzi-du")/10) + 1 + me->query_condition("feixing_poison"));
                report_status(target);

                if ( objdex <=30 && me->query("neili")>50 ) {
                        msg = HIM "接着，$n奋力向后一跳，那“毒”字竟然朝着$n飞过来。整个毒字贴在胸前。\n"NOR;
                        message_vision(msg, me, target);
                        me->add("neili",-50);
                        target->add("qi",-objdex*mycon);
                        target->add("eff_qi",-objdex*mycon);
                        target->apply_condition("feixing_poison", random(me->query_skill("duzi-du")/10) + 1 + me->query_condition("feixing_poison"));
                        report_status(target);

                        if ( objdodge <= 150 && me->query("neili")>50 ) {
                                msg = RED "最后，$n努力的向旁一闪，那“毒”字竟然完全附在$n的脸上。\n"NOR;
                                message_vision(msg, me, target);
                                me->add("neili",-50);
                                target->add("qi",-objdodge*myforce/10);
                                target->add("eff_qi",-objdodge*myforce/10);
                                target->apply_condition("feixing_poison", random(me->query_skill("duzi-du")/10) + 1 + me->query_condition("feixing_poison"));
                                report_status(target);
                        }
                }
        }
        else {
                msg = GRN "$n轻轻一跃，跳过了那“毒”字的飞行路线，轻松的落在一旁。\n\n"NOR;
                message_vision(msg, me, target);
                me->start_busy(random(6));
                me->add("neili",-50);
        }

        return 1;

}
