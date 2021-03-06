// cycle.c

#include <skill.h>

inherit F_CLEAN_UP;

int exercising(object me);
int halt_exercise(object me);
int exercising2(object me);
int halt_exercise2(object me);

int main(object me, string arg)
{
	int neili_gain;
	int exercise_cost = (int)me->query("max_neili");//练习花费的时间因素！
	seteuid(getuid());
	if (me->is_busy() || me->query_temp("pending/zhoutian"))
		return notify_fail("你现在正忙着呢。\n");
	if (me->query_temp("mache")) return notify_fail("马车颠簸不能练功。\n");
	if (me->query_temp("chuan")) return notify_fail("船内颠簸不能练功。\n");
	if (me->is_fighting() )
		return notify_fail("战斗中不能练内功，会走火入魔。\n");
	if (!stringp(me->query_skill_mapped("force")) )
		return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");
	neili_gain = 1 + (((int)me->query_skill("force") / 5)*((int)me->query("qi")/(int)me->query("max_qi")));
	//预先估计一下耗费的时间，限制在4分钟内！
	if(( exercise_cost / neili_gain) > 2*60)
		return notify_fail("你现在基本内功不够娴熟，不足以控制气息，担心走火入魔哟！\n");
	if ((int)me->query("jingli") * 100 / (int)me->query("max_jingli") < 70 )
		return notify_fail("你现在精力不够，无法控制内息的流动！\n");
	if (!arg)
	{
		write("你盘膝跌坐，双目微合，一股内息自丹田达百会，开始沿大周天穴道开始在体内流动。\n");
		me->set_temp("pending/zhoutian", 1);
		me->set_temp("exercise_cost", exercise_cost);
		message("vision",
			me->query("name")+"盘膝坐下，双目微合，开始运息练功。\n",
			environment(me), ({me}) );
		me->start_busy((: exercising :), (:halt_exercise:));
		return 1;
	}
	else if ( arg == "-l")
	{
		write("你盘膝跌坐，双目微合，一股内息走少阴脉，开始沿小周天穴道开始在体内流动。\n");
		me->set_temp("pending/zhoutian", 1);
		me->set_temp("exercise_cost", exercise_cost);
		message("vision",
		me->query("name")+"盘膝坐下，双目微合，开始运息练功。\n",
		environment(me), ({me}) );
		me->start_busy((: exercising2 :), (:halt_exercise2:));
		return 1;
	}
	else write("参数错误。命令格式：zhoutian|cycle [-l]\n");
	return 1;
}
//在这个函数返回0的时候终止忙！
//而且这个函数将被2秒调用一次
int exercising(object me)
{
	int exercise_cost = (int)me->query_temp("exercise_cost");
	int neili_gain = 1 + (((int)me->query_skill("force") / 5)*((int)me->query("qi")/(int)me->query("max_qi")));
	int jingli_c;
	//判断此时气息不足
	if(( exercise_cost / neili_gain) > 2*60)
	{
		me->set_temp("pending/zhoutian",0);//这一句不可缺少，否则如果exercise_cost<1就不能再练了
		return notify_fail("你气息不足，被迫停止运行周天。\n");
	}
	if ((int)me->query("max_neili")<300)
	{
		jingli_c = 30;
	}
	else
	{
		jingli_c = ((int)me->query("max_neili")/10);
	}
	if (exercise_cost < neili_gain) neili_gain = exercise_cost;
	if (exercise_cost < 1)
	{
		me->set_temp("pending/zhoutian",0);//这一句不可缺少，否则如果exercise_cost<1就不能再练了
		return 0;
	}
	//这里实现每次增加一点已经使用了的精力（应该是及时体现才对！）
	me->set_temp("exercise_cost", exercise_cost -= neili_gain);
	if (exercise_cost > 0)
		return 1;
	me->set_temp("pending/zhoutian", 0);
	message_vision("$N运功完毕，深深吸了口气，站了起来。\n", me);
	if ((int)me->query("max_neili") > (int)me->query_skill("force",1) * (int)me->query("con") + 1) 
	{
		write("你的内力修为似乎已经达到了瓶颈。\n");
		me->set("neili", (int)me->query("max_neili"));
		me->add("jingli", -jingli_c);
		return 0;
	}
	else
	{
		me->add("max_neili", 1);
		me->add("jingli", -jingli_c);
		write("你一个周天运行完毕，将气息缓缓归入丹田。\n");
		write("你的内力增加了！！\n");
		return 0;
	}
}

int halt_exercise(object me)
{
	if (random(100)>50) 
	{
		message_vision("$N满头大汗，终于将内息归回了丹田，长吁一口气站了起来。\n", me);
		me->add("qi", -(int)me->query("qi")/2);
		me->add("neili", -(int)me->query("neili")/2);
	}
	else
	{
		message_vision("$N突然间气血逆流，“哇”的一声突出了一口鲜血，看来受了很重的内伤。\n", me);
		me->add("qi", -(int)me->query("qi")/2);
		me->set("neili", 0);
		me->add("eff_qi", -(int)me->query("eff_qi")/2);
	}
	me->set_temp("pending/zhoutian", 0);
	return 1;
}

int exercising2(object me)
{
	int exercise_cost = (int)me->query_temp("exercise_cost");
	int neili_gain = 1 + (((int)me->query_skill("force") / 2)*((int)me->query("qi")/(int)me->query("max_qi")));
	int jingli_c, zht_l;
	//判断此时气息不足
	 if(( exercise_cost / neili_gain) > 2*60)
	{
		me->set_temp("pending/zhoutian",0);//这一句不可缺少，否则如果exercise_cost<1就不能再练了
		return notify_fail("你气息不足，被迫停止运行周天。\n");
	}
	if ((int)me->query("max_neili")<300)
	{
		jingli_c = 15;
	}
	else
	{
		jingli_c = ((int)me->query("max_neili")/20);
	}
	if (exercise_cost < neili_gain) neili_gain = exercise_cost;
	if (exercise_cost < 1)
		return 0;
	me->set_temp("exercise_cost", exercise_cost -= neili_gain);
    if (exercise_cost > 0)
		return 1;
	me->set_temp("pending/zhoutian", 0);
	message_vision("$N运功完毕，深深吸了口气，站了起来。\n", me);
	zht_l = (int)me->query_temp("zht_l");
	zht_l++;
	if (zht_l < 3)
	{
		me->add("jingli", -jingli_c);
		write("你一个小周天运行完毕，将气息缓缓归入丹田。\n");
		me->set_temp("zht_l", zht_l);
		return 0;
	}
	else
	{
		if ((int)me->query("max_neili") > (int)me->query_skill("force",1) * (int)me->query("con") + 1)
		{
			write("你的内力修为似乎已经达到了瓶颈。\n");
			me->set("neili", (int)me->query("max_neili"));
			me->add("jingli", -jingli_c);
			me->set_temp("zht_l", 0);
			return 0;
		}
		else 
		{
			me->add("max_neili", 1);
			me->add("jingli", -jingli_c);
			write("你一个周天运行完毕，将气息缓缓归入丹田。\n");
			write("你的内力增加了！！\n");
			me->set_temp("zht_l", 0);
			return 0;
		}
	}
}

int halt_exercise2(object me)
{
	if (random(100)>50)
	{
		message_vision("$N满头大汗，终于将内息归回了丹田，长吁一口气站了起来。\n", me);
		me->add("qi", -(int)me->query("qi")/4);
		me->add("neili", -(int)me->query("neili")/4);
	}
	else 
	{
		message_vision("$N突然间气血逆流，“哇”的一声突出了一口鲜血，看来受了很重的内伤。\n", me);
		me->add("qi", -(int)me->query("qi")/4);
		me->set("neili", 0);
		me->add("eff_qi", -(int)me->query("eff_qi")/4);
	}
	me->set_temp("pending/zhoutian", 0);
	return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : exercise|dazuo [<耗费「气」的量> 必须多于 10]

运气练功，控制体内的气在各经脉间流动，藉以训练人体肌肉骨骼的耐
力、爆发力，并且用内力的形式将能量储备下来。

HELP
        );
        return 1;
}
