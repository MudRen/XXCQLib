 //驱毒
//Write by phoenix 1999.12.5

int overqudu(object me);

#include <ansi.h>
string *qudu_msg = ({
        CYN"\n额头上已经盛出了汗水，全身散发着热气，毒已经慢慢的逼出了丹田。\n\n"NOR,
        CYN"内息越转越快，骨骼啪啪做响，两只手掌已经乌黑了。\n\n"NOR,
        CYN"手掌心已经约见红色，十指尖上一滴一滴的盛出了黑色的毒液。\n\n"NOR,
 
});
int exert(object me)
{
    int stage;  
    if( me->is_fighting() )
        return notify_fail("战斗中运功驱毒？找死吗？\n");
    if ((int)me->query_skill("tianyu-qigong", 1) < 100)
        return notify_fail("你的天羽奇功修为还不够，强行驱毒可能反受其害。\n");
    if( (int)me->query("neili") < 500 )
        return notify_fail("你的\内力不够，不能驱毒。\n");
    if (me->is_busy() || me->query_temp("qu_du"))
                return notify_fail("你现在正忙着呢。\n");
        if(me->query("family/family_name")!="天羽派")
        return notify_fail("你现在不能驱毒。\n");
    if ((int)me->query_condition("xisui_du") > 0
          || me->query_condition("yangdu_poison") > 0
          || me->query_condition("yao1_poison") > 0 
          || me->query_condition("yao2_poison") > 0
          || me->query_condition("xie_poison") > 0
          || me->query_condition("xiangshi_poison") > 0
          || me->query_condition("sworm_poison") > 0
          || me->query_condition("snake_poison") > 0
          || me->query_condition("shengdu_poison") > 0
          || me->query_condition("hx_poison") > 0
          || me->query_condition("feixing_poison") > 0
          || me->query_condition("duzun_poison") > 0  
           )  
          {
                message_vision(HIW"$N潜心静坐，一股内气从丹田逆行而上，准备强行逼出体内毒素。\n"NOR,me);
                me->set_temp("qu_du",20);
                me->start_busy((: overqudu :));
                remove_call_out("guocheng_qudu");
                call_out("guocheng_qudu",9,me,stage);
                return 1;
           }
    else
    return notify_fail("你好象没有中毒的迹象。\n");
}
int overqudu(object me)
{
        int num=me->query_temp("qu_du");
        int stage; 
        if (num < 1)
        return 0; 
        me->set_temp("qu_du", num-=1);   
        if (num > 1)
        return 1;
        me->set_temp("qu_du", 0);
        me->add("neili",-500);
        message_vision(HIW"$N驱毒完毕，深深吸了口气，站了起来。\n"NOR, me);
        me->apply_condition("xisui_du",0);
        me->apply_condition("yangdu_poison",0);
        me->apply_condition("yao1_poison",0);
        me->apply_condition("yao2_poison",0);
        me->apply_condition("xie_poison",0); 
        me->apply_condition("xiangshi_poison",0);
        me->apply_condition("sworm_poison",0);
        me->apply_condition("snake_poison",0);
        me->apply_condition("shengdu_poison",0);
        me->apply_condition("hx_poison",0);
        me->apply_condition("feixing_poison",0);
        me->apply_condition("duzun_poison",0);    
}               
int guocheng_qudu(object me,int stage)
{
        tell_object(me, qudu_msg[stage]);
        if(++stage < sizeof(qudu_msg) )
        {
                call_out("guocheng_qudu",9,me,stage);
                return 1;
        }
}        
        
 
