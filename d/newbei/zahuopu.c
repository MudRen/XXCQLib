// Room: /welcome/zahuopu.c
//By adx @ CuteRabbit 15:57 99-5-18

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", WHT"杂货铺"NOR);
	set("long",
"这是一家小小的杂货铺，大箱小箱堆满了一地，都是一些日常用品。杨\n"
"掌柜懒洋洋地躺在一只躺椅上，招呼着过往行人。据说私底下他也卖一些贵\n"
"重的东西。墙上贴着一张广告"+HIM"（guanggao）"NOR+"你首先应当看看。\n"
 );
	set("item_desc", ([
		"guanggao" : "你可以用"+HIC"list"NOR+"查看本店出售的物品品"+
			     "用"+HIC"buy"NOR+"买物品。\n"+
			     "另外本店急需帮工，请向山主打听。\n\n",
	]));
	set("exits", ([
		"west" : __DIR__"beilang2",
	]));
	set("objects", ([
		__DIR__"npc/yang": 1,
	]));
	set("no_fight", 1);
//	set("no_clean_up", 0);
	setup();
}

void init()
{
           add_action("do_job","kan");
}
int do_job(string arg)
{
        object *inv;
        object me;
         int i, jingli;

	me = this_player();
	jingli = ( random(me->query("dex"))/3 );
	inv = all_inventory(me);
	if (jingli <= 0)
		jingli = 5;

	if (me->query("jingli")<=10) {
	message_vision ("你没有气力了，先去休息室睡一下吧！"+HIC"(sleep)\n"NOR, me );
        return 1;
	}
	   //判断是否wield了工具
	if( (string)(inv[i]->query("id"))=="chaidao" && 
		(int) inv[i]->query("equipped") ) 
	{
		if( !arg || arg!="柴" )
			{return notify_fail ("你要砍什么？\n");
		}
		else {
			me->add_temp("wancheng", jingli);
			me->add("jingli", -jingli);
			me->add("combat_exp", jingli);
			me->add("potential", (jingli/2));
			message_vision ("$N拿起柴刀，把木头劈开！\n", me );
			if (me->query_temp("wancheng") >= 100)
			{
				me->set_temp("renwu",100);   //设100表示完成任务
				return notify_fail (WHT"你可以回去复命了！(ask moto about ok)\n"NOR);
				}
			}
	}
	else {
		return notify_fail ("你空手怎么砍柴？拿手劈吗！\n");
		}
        return 1;
}

int valid_leave(object me, string dir)
{
         if ( (dir == "west") &&
		(me->query("wancheng") >= 100) )
	{
		if ( !present("chaidao", me) ) {return 1;}
			message_vision ("$N放下手中的柴刀。\n", me);
		destruct(present("chaidao", me));
	}
	return ::valid_leave(me, dir);
}
