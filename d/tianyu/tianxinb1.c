// Room: 天心壁
// Date: by godzilla 1999.11.18

#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "天心壁");
	set("long", @LONG
不只觉中来到一峭壁前，俯望壁底，只见云雾缭绕，不知道到底
有多深，偶尔从谷底飘来一阵阵紫气，嗅一嗅顿觉心旷神怡，使人有
种向下跳的感觉。
LONG );
        set("outdoors", "tianyu");
        set("exits", ([
        "north"  : __DIR__"xiaojing1",
        ])); 
	setup();
	
}
void init()
{
	add_action("do_jump","jump");
}
int do_jump(string arg)
{
	
	object me=this_player();
        int i=(int)me->query_skill("dodge");
	if(!arg||arg=="")
	return notify_fail("你要往哪儿跳。\n");
	if(arg=="down")
	message_vision(HIR"$N纵身跳下山壁。\n"NOR, me);
	if(i<60+random(50))
	{
		me->move(__DIR__"yuduan");
		call_out("do_wait", 2, me);
		return 1;
	}
	else
	{
		me->move(__DIR__"yuduan");
		call_out("do_wait1",2,me);
		return 1;
	}
}
void do_wait(object me)
{
	write(HIR"你只觉得耳边呼呼风声作响，身体越坠越快....\n"NOR, me);
	write(HIW"你只觉得死神在向你召唤........\n"NOR, me);
	me->move(__DIR__"tianxinb");
	tell_room(environment(me),me->name()+"从山上跳了下来。\n");
	me->set_temp("last_damage_from","摔下山崖跌");
	me->unconcious();
	me->die();
}
void do_wait1(object me)
{
	tell_object(me,HIR"你只觉得耳边呼呼风声作响，身体越坠越快....\n"NOR);
//    tell_object(me,HIW"不知过了多久,你只觉脚下一沉就失去了只觉........\n"NOR, me);  ^M
	me->move(__DIR__"tianxinb");
	tell_room(environment(me),me->name()+"从山上跳了下来。\n");
//    me->unconcious();
}	
			
		      	 
