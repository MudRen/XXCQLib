  //Update by godzilla 1999.12.8

#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        object ob;              // 对手的武器
        string msg;
        int i,m; 
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(HIY"「破空点」"+NOR+"只能在战斗中的使用。\n");
        if (objectp(weapon = me->query_temp("weapon")))
                        return notify_fail("你不能使用武器！\n");
        if( (int)me->query_skill("changkong-zhi", 1) < 200 )
               return notify_fail("你的长空指还不够熟练，不能使用「破空点」。\n");
        if( me->query("family/family_name")!="天羽派")
               return notify_fail("你不是天羽弟子，不能使用「破空点」\n"); 
        if( (int)me->query_skill("finger",1) < 200 )
                return notify_fail("你的基本指力不够，无法使用「破空点」。\n");    
        if ( me->query("max_neili") < 2000)
                return notify_fail("你的内力不够，无法使用「破空点」。\n");
        if ( me->query("neili") < 100)
                return notify_fail("你当前的内力不够，现在无法使用「破空点」。\n");       
        me->add("neili", -50);
        msg = HIY " $N深深吸了一口气，只见数股真气在指间流转，突然$N身法斗转,凌空点出几指,\n"
                  " 猛见数道真气向着$p激射过去。\n"NOR;
        ob = target->query_temp("weapon");
        if(  (int)me->query("combat_exp")  > random((int) target->query("combat_exp") ) )
        {
                me->start_busy(2);
                i=(int)me->query_skill("dodge",1);
                m=(int)me->query_skill("force",1);  
                if (! objectp(ob))
                {
                        int damage = 0;
                        if (target->query_skill("dodge") < i &&
 random(2) == 0)
                        {
                                switch (random(2))
                                {
                                case 0:
                                        msg += HIW " $p连续闪避，终于还是没能躲过，数道真气尽数"
                                                   "点在$p的丹田上，$p只觉得胸口气闷说不出的难受。\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIW " $p完全没有防备，听「噗」的一声，$p脸色煞白，已经摇摇欲坠了。\n";
                                        damage = 5;
                                        break;
                                }
                        }
                       else
                       if (target->query_skill("force") > m && random(2) == 0)
                       {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR " $p冷哼一声，自持内力高强，反手出招，「啵」"
                                                "的一声二指相交，$p身行微晃，脸如金纸。\n";
                                        damage = 3;
                                        break;
                                case 1:                                        msg += HIR " $p一声长啸，双手幻化出无数掌影，护住身前。"
                                                "只听「嗤」的一声，掌影顿消，$p已经变得脸色惨白。\n";
                                        damage = 4;
                                        break;
                                }
                        }
                        else
                         {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR " $p看到这招，竟然不知躲避，「嗤」的一声，$N"
                                                "这一指正点在$p的百汇穴。\n";
                                        damage = 5;
                                        break;
                                case 1:
                                        msg += HIR " $p正想躲避，可是真气来得太快,只听「嗤」的一声，已被$N点中檀"
                                                "中大穴。\n";
                                        target->unconcious();
                                        damage = 0;
                                        break;
                                }
                        }
                        if (damage > 0)
                        target->receive_damage("qi", target->query("max_qi") * damage / 12);
                        message_vision(msg + NOR, me, target);
                        return 1;
                }
                if (ob->query("nopawn"))
                {
                        switch(random(2))
                        {
                        case 0:
                        msg += HIR " $p忙用" + ob->query("name") + "招架，只觉得虎口剧震，所幸兵器完好无损。\n" NOR;
                        target->start_busy(2);
                        break;
                        case 1:
                        msg +=HIR "$p慌乱之中用"+ob->query("name")+"招架,只觉得虎口剧痛,手中"+ob->query("name")+"脱手而飞！\n"NOR;
                        ob->move(environment(target));
                        target->start_busy(2); 
                        break;
                        }         
                } 
                else
                {
                        msg += HIW " $p连忙招架，只听见「啪」地一声，$p手中的" + ob->name()
                                + "被真气打断，散落一地！\n";
                        ob->unequip();
                        ob->move(environment(target));
                        ob->set("name", "断掉的" + ob->query("name"));
                        ob->set("value", 0);
                        ob->set("weapon_prop", 0);
                }
                target->start_busy(2);
        }
 else
        {

                int busy = 0;
                if (target->query_skill("dodge") > i && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += WHT" $p一声轻笑，左闪右闪，巧妙的躲过了$N的进攻。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += WHT" $p突然向后飘去，疾若闪电，轻松的躲过了$N的比杀之计。\n";
                                busy = 1;
                                break;
                        }
                }
 else
                if (target->query_skill("force") > m && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += YEL" $p脸色凝重，忙运气与掌上，硬接下了$N的这招绝技。\n";
                                busy = 3;
                                break;
                        case 1:
                                msg += YEL" $p满脸不屑，掌风推出，只见把几道真气硬生生的反击回来，令$N大吃一惊。\n";
                                busy = 1;
                                break;
                        }
                }
 else                {
                        switch (random(3))
                        {
                        case 0:
                                msg += HIW" $p左摇右晃，看上去毫无章法，偏偏躲过了$N这一击。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += HIW" $p一指点出，看上去好象也是长空指法，$N一惊，攻势顿缓。\n";
                                busy = 2;
                                break;
                        case 2:
                                msg += HIW"$p摄住心神，真气贯注" + ob->query("name")
                                         + "，堪堪封住了$N的进攻。\n";
                                busy = 2;
                                break;
                  }
                }
                        
                
                target->start_busy(3);
                me->start_busy(2);
        
                }
        message_vision(msg + NOR, me, target);
        return 1;
}
