// hssg.c

#include <ansi.h>
inherit ROOM;
int start_douzhuan();
int halt_douzhuan(object me);
void create()
{
         set("short",MAG"还施水阁"NOR);
         set("long",
"这就是举世闻名的姑苏慕容的还施水阁，这里据说有很多武林人事向\n"
"往以久的武功。只见墙上有一个书架子(shujia)，上面摆满了各种武籍。\n"
);
         set("exits",([
             "south" : __DIR__"sf",
]));
         set("item_desc", ([
             "shujia" : "书架上各个门派的武功秘籍(miji)，你忍不住想拿起一本就翻看起来。\n",
]));
}

void init()
{
	add_action("douzhuan", "douzhuan");
}

int douzhuan(string arg)
{       
	object me = this_player();
	object where = environment(me);
	string skillname;
	int skill, skill_basic, time;
	seteuid(getuid());
	if( me->is_busy())
		return notify_fail("你正忙着呢。\n");
	if( me->is_fighting())
		return notify_fail("你正忙着呢。\n");        
	if( !stringp(skillname = me->query_skill_mapped(arg)) )
		return notify_fail("你只能练习用 enable 指定的特殊技能。\n");

	skill_basic = me->query_skill(arg, 1);
	skill = me->query_skill(skillname, 1);

	if( skill < 1 )
		return notify_fail("你好像还没有学过这项技能吧？最好先去请教别人。\n");
	if( skill_basic < 1 )
		return notify_fail("你对这方面的技能还是一窍不通，最好从先从基本学起。\n");
	if( skill_basic/2 <= skill/3 )
		return notify_fail("你的基本功没有练到家，必须先打好基础才能继续提高。\n");

	notify_fail("你现在不能练习这项技能。\n");
	if( !SKILL_D(skillname)->valid_learn(me) ) return 0;
	notify_fail("你试着练习" + to_chinese(skillname) + "，但是并没有任何进步。\n");
	if( SKILL_D(skillname)->practice_skill(me) )
	{
		message_vision( HIY"【练功】"NOR"$N摆开了练功的架式，准备开始练习"+to_chinese(skillname)+"。\n", me );
	    	time = (int)me->query_skill("douzhuan-xingyi", 1)/20;		
	    	me->set_temp("pending/douzhuan", 1);   
    		me->set_temp("douzhuan_times", time);
	    	me->set_temp("douzhuan/period", 1);    	
    		me->start_busy( (: start_douzhuan :), (: halt_douzhuan :) );	    	
		me->start_douzhuan(arg);
		printf("hehe\n");
		return 1;
	}
	return 0;		
} 

int start_douzhuan()
{                                                     
	string msg,skill, desc;
	object me, weapon, skill;
	mapping action;                                     
	me = this_object();   
	int jibie = me->query_skill(skill);
	int neili_cost = (int)me->query_skill("shenyuan-gong", 1)/4;                                    
        int time = (int)me->query_temp("douzhuan_times");
        int period = (int)me->query_temp("douzhuan/period");   
        me->receive_damage("neili", neili_cost);
       	if(period < time)
       	{            
		write("1.\n");
	}                                
	if( period == time)
        {
           	me->delete_temp("pending/douzhuan");
       	        message_vision(CYN"\n$N微微整开双眼，调整内息，站了起来。\n"NOR, me);
       	        return 0;
        }
        period++;                           
        me->set_temp("douzhuan/period", period);
        return 1;        
}           

int halt_douzhuan(object me)
{
        me->delete_temp("pending/douzhuan");    
        if(living(me))
        message_vision(CYN"\n$N微微整开双眼，调整内息，站了起来。\n"NOR, me);
        return 1;
}                          	