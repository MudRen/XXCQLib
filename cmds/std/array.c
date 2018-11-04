//天羽剑法
//Write by phoenix 1999.12.29

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int main(object me, string arg)
{
        string *style = ({
"$N脚踏-"HIR"火"HIW"-行位，拿起手中之剑，随着剑气，刺向$n的要害！",
"$N脚踩-"HIG"水"HIW"-行位，反手刺向$n，瞬时就将$n团团围住！",
"$N飞踏-"HIY"金"HIW"-行位，跟着$N向前一纵，手中之剑向$n猛刺过去！",
"$N纵向-"HIC"土"HIW"-行位，欺身急进，手中之剑上下连点，分刺$n的两处要害！",
"$N跃入-"HIM"木"HIW"-行位，身形纵起，手中之剑自下而上，迅猛无比，刺砸向$n的要害！"
});
        object ob,ob1,*obs;
        string who1,msg;
        int exp,i;
        me=this_player();
        if( environment(me)->query("no_fight") )
                return notify_fail("这里禁止战斗。\n");
        if( me != this_player() )
        return 0;
        if( !arg || sscanf(arg, "to %s", who1) != 1 )
                return notify_fail("指令格式: array to <某人>\n");
        if( !objectp(ob1 = present(who1, environment(me))))
                return notify_fail("找不到" + who1 + "。\n");
        if( !living(ob1) )
                return notify_fail("这不能对这个物件使用阵法。\n");
        if(!pointerp(obs=me->query_team()))
        return notify_fail("必须组队才可以发动此式！\n");
        if(sizeof(obs)>=5)
        return notify_fail("队伍最多五个人！！\n");
        if(!pointerp(obs=me->query_team())
        ||!me->is_team_leader())
        return notify_fail("只有队伍领袖才可以发动此式！\n");
        if(me->query_temp("start_zhenfa"))
        return notify_fail("天羽阵法已经在进行中！\n");
        for(i=0;i<sizeof(obs);i++)
        {
                if(!obs[i])
                return notify_fail("你需要从新组合队伍。\n");
                if(environment(obs[i])!= environment(me))
                return notify_fail("你组阵成员好象不全在你身边。\n");
                if(!obs[i]->query_skill("tianyu-zhenfa"))
                return notify_fail("你队伍中有人并不会使用天羽阵法。\n");
                if(obs[i]->query_skill("tianyu-zhenfa")<60)
                return notify_fail("你队伍中有人天羽阵法还不够娴熟。\n");
                if(!objectp(ob=obs[i]->query_temp("weapon")))
                return notify_fail("你的队伍中有人没有兵器！\n");
                if(ob->query("skill_type") != "sword")
                return notify_fail("你的队伍中有人没有用剑！\n");
        }
        
        message_vision(HIY"\n\n$N高喝一声："HIR"布天羽剑阵!!!，\n"HIY"忽见天羽门人一字排开，分踏五行八卦，天羽阵法徐徐滚动，
        阵中五行环环相生，环环相克，一下子把$n困在了阵中。 \n\n"NOR,me,ob1);
        for(i=0;i<sizeof(obs);i++)
        {
                
                ob=obs[i]->query_temp("weapon");
                exp=200/5*sizeof(obs);
                obs[i]->add_temp("apply/attack", exp);
                obs[i]->add_temp("apply/parry", exp);
                obs[i]->add_temp("apply/dodge", exp);
                msg = HIW +  style[i] + NOR;
                message_vision(msg,obs[i],ob1); 
                COMBAT_D->do_attack(obs[i],ob1,ob,0);
                obs[i]->fight_ob(ob1); 
                if(!ob1->is_killing(me))
                ob1->kill_ob(obs[i]);
                        
       }
       me->set_temp("start_zhenfa",1);
       call_out("start_array",5,me);
       return 1;
}

int start_array(object me,object *obs)
{
        int i,exp;
        obs=me->query_team();
          
        for(i=0;i<sizeof(obs);i++)
        {
                
                if(obs[i]->is_fighting())
                {
                        tell_object(environment(obs[i]),HIW"天羽剑阵急速地旋转着，阵中之人越转快、一层层地向内收紧！\n" NOR);
                        call_out("start_array",5,obs[i]);
                        return 1;
                }
                else
                {
                        exp=200/5*sizeof(obs);
                        me->set_temp("start_zhenfa",0);
                        tell_object(environment(obs[i]),HIW"天羽剑阵已经完毕，各自收阵回位！\n" NOR);
                        obs[0]->add_temp("apply/dodge",-exp);
                        obs[0]->add_temp("apply/parry",-exp);
                        obs[0]->add_temp("apply/attack",-exp);
                        obs[1]->add_temp("apply/dodge",-exp);
                        obs[1]->add_temp("apply/attack",-exp);
                        obs[1]->add_temp("apply/parry",-exp);
                        obs[2]->add_temp("apply/attack",-exp);
                        obs[2]->add_temp("apply/dodge",-exp);
                        obs[2]->add_temp("apply/parry",-exp);
                        obs[3]->add_temp("apply/attack",-exp);
                        obs[3]->add_temp("apply/dodge",-exp);
                        obs[3]->add_temp("apply/parry",-exp);
                        obs[4]->add_temp("apply/parry",-exp);
                        obs[4]->add_temp("apply/attack",-exp);
                        obs[4]->add_temp("apply/dodge",-exp);
                        return 1;
                }
        }
}                               
