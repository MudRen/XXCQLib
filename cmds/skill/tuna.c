// Create By Lanny

#include <skill.h>

inherit F_CLEAN_UP;

private int respirate_cost;
private int respirating(object me);
private int halt_respirate(object me);

int main(object me, string arg)
{

        seteuid(getuid());
        
        if (me->is_busy()) 
                return notify_fail("你现在正忙着呢！\n");

        if (me->query_temp("xuet"))
                return notify_fail("你还是专心读书吧。\n");

        if (me->query_temp("mache")) return notify_fail("马车颠簸不能练功。\n");
        if (me->query_temp("chuan")) return notify_fail("船内颠簸不能练功。\n");

        if( me->is_fighting() )
                return notify_fail("战斗中吐纳，好象只有神仙才能做到。\n");

        if( !arg || !sscanf(arg, "%d", respirate_cost))
                return notify_fail("你要花多少气息修行？\n");

        if (respirate_cost <= 9)
                return notify_fail("你不是神仙！\n");

        if( (int)me->query("qi") < respirate_cost )
                return notify_fail("你现在气息不足，无法修行精力！\n");

        write("你闭上眼睛开始吐纳炼精。\n");
        me->set_temp("pending/exercise", 1);
        me->set_temp("respirate_cost", respirate_cost);
        message_vision("$N盘膝坐下，开始吐纳炼精。\n", me);
        me->start_busy((: respirating :), (: halt_respirate :));
        return 1;
}

int respirating(object me)
{
        
        
        int respirate_cost = (int)me->query_temp("respirate_cost");
        int jingli_gain = 1 + (int)me->query_skill("force") / 10;


        if (respirate_cost < 1)
                return 0;

//      me->set_temp("respirate_cost", respirate_cost = respirate_cost - jingli_gain);
        
        if ( me->query("qi") >= jingli_gain )
        {
                me->add("jingli", jingli_gain);
                me->set_temp("respirate_cost", respirate_cost-= jingli_gain);
                me->add("qi", -jingli_gain);
        }
        else
        {
                me->add("jingli", me->query("qi"));
                respirate_cost -= me->query("qi");
                me->set_temp("respirate_cost", respirate_cost-= me->query("qi"));
                me->set("qi", 0);
        }
                

        if (respirate_cost > 0)
                return 1;


        me->delete_temp("pending/exercise");
        respirate_cost = 0;
        
        message_vision("$N吐纳完毕，睁开双眼，站了起来。\n", me);
        
       if((int)me->query("jingli") < (int)me->query("max_jingli") * 2)
                return 0;
        else {
                if ((int)me->query("max_jingli") > (int)me->query_skill("force") * 10)
                {
                        write("你的精力修为似乎已经达到了瓶颈。\n");
                        me->set("jingli", (int)me->query("max_jingli"));
                        return 0;
                }
                else
                {
                        me->add("max_jingli", 1);
                        me->set("eff_jingli", (int)me->query("max_jingli"));
                        me->set("jingli", (int)me->query("max_jingli"));
                        write("你的精力增加了！！\n");
                        return 0;
                }
        }
}

int halt_respirate(object me)
{
        respirate_cost = 0;
        if ((int)me->query("jingli") > (int)me->query("max_jingli") * 2)
                me->set("jingli", (int)me->query("max_jingli") * 2);        
        me->delete_temp("pending/exercise");
        return 1;
        
        
}

int help(object me)
{
        write(@HELP
指令格式 : respirate|tuna [<耗费「气息」的量>]
 
打坐修行，利用「炼精化气，炼气化神，炼神还虚」的方法将你的精
转变成精力。

See also: exercise
HELP
        );
        return 1;
}
