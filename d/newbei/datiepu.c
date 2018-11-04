// Room: /welcome/datiepu.c
//By adx @ CuteRabbit 15:57 99-5-18

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",WHT"打铁铺"NOR);
	set("long", @LONG
这是一家简陋的打铁铺，中心摆着一个火炉，炉火把四周照得一片通红，
你一走进去就感到浑身火热。墙角堆满了已完工和未完工的菜刀、铁锤、铁
棍、匕首、盔甲等物。一位铁匠满头大汗挥舞着铁锤，专心致志地在打铁。
LONG );
	set("exits", ([
		"west" : __DIR__"nanlang2",
	]));
        set("objects", ([
		__DIR__"npc/smith": 1,
	]));
	set("no_fight", 1);
//	set("no_clean_up", 0);
	setup();
}

void init()
{
           add_action("do_job","da");
}
int do_job(string arg)
{
        object *inv;
        object me;
         int i, jingli;

	me = this_player();
	jingli = ( random(me->query("str"))/3 );
	inv = all_inventory(me);
	if (jingli <= 0)
		jingli = 5;

	if (me->query("jingli")<=10) {
	message_vision ("你没有气力了，先去休息室睡一下吧！"+HIC"(sleep)\n"NOR, me );
        return 1;
	}
	   //判断是否wield了工具
	if( (string)(inv[i]->query("id"))=="hammer" && 
		(int) inv[i]->query("equipped") ) 
	{
		if( !arg || arg!="铁" )
			{return notify_fail ("你要打什么？\n");
		}
		else {
			me->add_temp("wancheng", jingli);
			me->add("jingli", -jingli);
			me->add("combat_exp", jingli);
			me->add("potential", (jingli/2));
			message_vision ("$N抡起铁锤，用力锤着烧红的铁！\n", me );
			if (me->query_temp("wancheng") >= 100)
			{
				me->set_temp("renwu",100);   //设100表示完成任务
				return notify_fail (WHT"你可以回去复命了！(ask moto about ok)\n"NOR);
				}
			}
	}
	else {
		return notify_fail ("你空手怎么打铁？拿拳头锤吗！\n");
		}
        return 1;
}

int valid_leave(object me, string dir)
{
         if ( (dir == "west") &&
		(me->query("wancheng") >= 100) )
	{
		if ( !present("hammer", me) ) {return 1;}
			message_vision ("$N放下手中的铁锤。\n", me);
		destruct(present("hammer", me));
	}
	return ::valid_leave(me, dir);
}
