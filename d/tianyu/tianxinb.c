// Room: 天心壁
// Date: by godzilla 1999.11.18

#include <ansi.h>
inherit ROOM;
int exercising();
int exercising1();

void create()
{
	set("short", "天心壁");
	set("long", @LONG
一走进来就感觉到真气舒畅，天心壁四面环山，地理位置正处于
气流交接之处，空气清新，这是天羽前辈们所找到的最好练功场所。
LONG );
	setup();
	
}
void init()
{
	add_action("do_look","look");
        add_action("do_halt","halt");
	add_action("do_mianbi","lianqi");
	add_action("do_climb","climb");
}
int do_halt()
{
       tell_object(this_player(),"天心壁,天造之所,不能终止任何行动！\n");
       return 1;
}
int do_look()
{
	object ob;
	mixed *local;
	local = localtime(time() * 60);
		
	if(local[2]>=4 && local[2]<8)
	{
		write(HIW"山壁四周的雾气渐渐浓起来，空气凉丝丝的透着一股凉意，微风习习，
		\n犹如母亲亲吻孩子般的拂在脸上，令人心旷神怡，大有飘飘欲仙之感。\n"NOR,ob);
        }
        if(local[2]>=8 && local[2]<22)
        {
        	write(MAG"雾已经散了，阳光透过山壁照了进来，四周山壁在阳光的映照下，既然
        	          \n奇迹般的发出阵阵紫气，一会功夫整个山谷都已经被紫气所包围了。\n"NOR,ob);
        }	 
        if(local[2]>=22 || local[2]<2)
        {
        	write(HIB"天地间渐渐暗了下来。四周的山壁一下子安静下来，紫气也慢慢的消失了......\n"NOR,ob);
        }
        if(local[2]>=2 && local[2]<4)
        {
            write(WHT"天气剧冷，四周山壁在冷空气的刺激下，散发出白色的气体。\n");
        }	
}

int do_mianbi()
{
        object me = this_player();
	mixed *local;
        local = localtime(time() * 60);
	if (me->is_busy()||me->query_temp("pending/exercising"))
	return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() )
	return notify_fail("战斗中不能练气，这是很危险的。\n");
	if( !stringp(me->query_skill_mapped("force")) )
	return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");
	if(me->query("jingli")<100)
	return notify_fail("你现在精力不够，无法练气。\n");
	if(me->query("neili")<me->query("max_neili")/2)
	return notify_fail("你现在内力不够，无法练气。\n");
	if(local[2]>=4 && local[2]<8)
	{
		write("你坐下来运气用功，一股内息开始在体内流动。\n");
		me->set_temp("pending/exercise", 1);
		me->set_temp("exercise_cost", 70-me->query("con"));
		message_vision("$N盘膝坐下，开始修炼内力。\n", me);
		me->start_busy((: exercising :));
            	return 1;
        }
        if(local[2]>=8 && local[2]<22)
        {
        	write(MAG"你静心静神，双膝盘座练气行功，只见一股紫气在你四周环绕，大地精华尽其所用。\n"NOR);
        	me->set_temp("pending/exercise",1);
        	me->set_temp("exercise_cost", 40-me->query("con"));
            	message_vision(MAG"$N紫气缓吸，开始修炼内力。\n"NOR, me);
            	me->start_busy((: exercising1 :));
            	return 1;
        }
        if(local[2]>=22 || local[2]<2)
        {
            	write("你坐下来运气用功，一股内息开始在体内流动。\n");
		me->set_temp("pending/exercise", 1);
		me->set_temp("exercise_cost", 70-me->query("con"));
		message_vision("$N盘膝坐下，开始修炼内力。\n", me);
		me->start_busy((: exercising :));
            	return 1;
        }
        if(local[2]>=2 && local[2]<4)
        {
        	write(HIB"你深吸一口气，突然觉得胸口郁闷，气息不畅，全身麻木不能动弹。"NOR);
        me->add("max_neili",-3);
        	me->unconcious();
        }	
        
}
int exercising()
{
	object me =this_player();
	int i = me->query_temp("exercise_cost");
	me->set_temp("exercise_cost", i -=1);
	if (i > 0)
	return 1;
	if (i <= 1)
	{
		me->set_temp("pending/exercise", 0);
		me->interrupt_me();
		me->add("max_neili", 1);
	        me->add("neili", -100);
	        me->add("jingli",-100);
	        message_vision("$N运功完毕，深深吸了口气，站了起来。\n", me);
	        return 0;
	}        
     if ((int)me->query("max_neili") < (int)me->query_skill("force") * 5)
	{
		return 0;
	}	
	else
	{
		write("你的内力修为似乎已经达到了瓶颈。\n");
		return 0;
	}
}
int exercising1()
{
	object me =this_player();
	int i = me->query_temp("exercise_cost");
	me->set_temp("exercise_cost", i-=1);
	if (i > 0)
	return 1;
	if (i <1)
	{
		me->set_temp("pending/exercise", 0);
		me->interrupt_me();
		me->add("max_neili", 1+random(2));
	        me->add("jingli",-50);
		message_vision(MAG"$N一周天行功完毕，缓缓站了起来，只觉全身气流翻滚，内功修为又增加一分。\n"NOR, me);
		return 0;
	}	
	if ((int)me->query("max_neili") < (int)me->query_skill("force") * 10)
	{
		return 0;
	}	
	else
	{
		write("你的内力修为似乎已经达到了瓶颈。\n");
		return 0;
	}
}
int do_climb(string arg)
{
	object me=this_player();
	if(!arg||arg=="")
	return notify_fail("你要往哪儿爬。\n");
	if(me->is_busy())
	return notify_fail("你现在正忙着呢。\n");
	if(arg=="up")
	message_vision("$N抓住壁缝，慢慢的往上爬.....\n",me);
	if(me->query("jingli")<200)
	{
		tell_object(me,"你只觉得越来越力不从心，一个失手又掉了下来。\n");
		tell_room(environment(me),"只见"+me->name()+"从半山上又掉了下来。\n");
		me->move(__DIR__"tianxinb");
		me->unconcious();
		return 1;
	}
	else
	{
		tell_object(me,"你不一会就爬上了山壁。\n");
		me->move(__DIR__"tianxinb1");
		return 1;
	}
}	
			
			
	
	     	 
