
#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        int neili_limit;
        
        neili_limit=(int)me->query_skill("force",1)*(int)me->query("con")+1;
        
        if ((int)me->query("max_neili")>neili_limit)
        {
                me->set("max_neili",neili_limit);
                tell_object(me, "你的内力修为已经达到了瓶颈！\n" NOR );              
        }
        else {
                me->set("max_neili",(int)me->query("max_neili")+(int)me->query_temp("neili_save")); 
                tell_object(me, "你觉得内息又比以前有了进步。但是全身疼痛难忍！\n" NOR );
        }
        message("vision", me->name() + "脸色阴晴不定，象是得了什么疾病。\n",environment(me), me);

        me->apply_condition("bairi_du", duration - 1);
        
        if( duration == 1 )
        {
                tell_object(me, HIB "毒药在体内爆发了，你已经毒气攻心！\n" NOR );
              me->set("max_neili",(int)me->query_temp("neili_save"));
                me->die();
        }
       if (!duration) return 0;
       return 1;
}

