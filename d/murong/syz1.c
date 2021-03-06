// syz.c
#include <ansi.h>
inherit ROOM;
nosave int lianing;
nosave int tick;
// 要练习的武功
nosave string lian_skill;

// 练习的招数索引
nosave int zhao_index;
//判断是否在练功的函数
int is_lianing();
//开始练功
void do_lian();
void create()
{
	 lianing = 0;
         set("short",HIY"赏月斋"NOR);
         set("long",@long
赏月斋是为慕容家每到中秋之夜而建造的。里面富丽堂皇，瓜果应有尽
有，旁边有丫鬟伺候着，每到赏月之时，一家老小都在这里赏月，在赏月的
同时，也念念不忘复兴大燕的使命。
long);
         set("exits",([
		"west" : __DIR__"cl2",
	]));
	set("objects", ([
	__DIR__"obj/fruit" : 2,
]));
        setup();
}

void init()
{
	add_action("yanxi", "yanxi");
}

int is_lianing()
{
	return lianing;
}

void start_lian(string skill)
{
	object me = this_player();
	zhao_index = 0;
	lianing = 1;
	lian_skill = skill;
	me->start_busy( (: is_lianing :) );
}

void stop_lian()
{
	object me = this_player();
	lianing = 0;
	if ( me->is_busy() )
	{
		this_object()->interrupt_me();
	}
}

void do_lian()
{
	int jibie;
	int skill_basic,skill_int;
	string msg,skillname;
	object me, weapon, skill;
	mapping action;

	me = this_player();
	seteuid(getuid(me));

	me->set_heart_beat(1);
	tick = 5 + random(10);

	skillname = me->query_skill_mapped(lian_skill);
	skill_basic = me->query_skill(lian_skill, 1);
	skill_int = me->query_skill(lian_skill, 1);

	if( SKILL_D(skillname)->practice_skill(me) )
	{
			me->improve_skill(skillname, skill_basic/5 +1, skill_basic > skill_int? 0: 1);

			jibie = me->query_skill( lian_skill );
			action = SKILL_D(skillname)->query_action(jibie);
			if(action["lian"])
			{
				msg = HIY"【练功】"NOR+WHT+action[ "lian" ] + "\n"NOR;
				weapon = query_temp( "weapon" );
				if ( objectp( weapon ) )
				msg = replace_string( msg, "$w", weapon->name() );
				message_vision( msg, me );
				tell_object(me, HIC"【评论】"NOR+HIW+"你对这一招的练习还比较满意。\n"+NOR);
			}
			else{
				write( HIY "你正在练习" + to_chinese(skillname) + "\n" NOR);
			}
	}
	else{
		msg = sprintf( HIY"【练功】"NOR+"$N气收丹田, 练完了【%s】。\n", to_chinese( skillname) );
		message_vision( msg, me );
		lianing = 0;
		return;
	}
}

int yanxi(string arg)
{
	object me = this_player();
	object where = environment(me);
	string skillname;
	int skill, skill_basic;

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

	if( me->is_fighting() )
		return notify_fail("战斗中还想练习，你不想活啦。\n");

	if( !arg ) return (__DIR__"enable")->main(me, arg);

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
	        me->start_lian(arg);
		return 1;
	}
        return 1;
}
