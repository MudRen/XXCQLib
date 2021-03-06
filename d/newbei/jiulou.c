// Room: /welcome/jiulou.c
//By adx @ CuteRabbit 15:57 99-5-18

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",WHT"醉仙楼"NOR);
	set("long",
"方圆数百里内提起醉仙楼可以说是无人不知，无人不晓。当年苏学士云\n"
"游到此，对醉仙楼的花雕酒赞不绝口，欣然为其题匾，流下一段传遍海内的\n"
"佳话，从此醉仙楼名声大震。楼下布置简易，顾客多是匆匆的行人，买点包\n"
"子、鸡腿、米酒就赶路去了。楼上是雅座。墙上贴着一张广告"+HIM"(guanggao)\n"NOR
 );
	set("item_desc", ([
		"guanggao" : "你可以用"+HIC"list"NOR+"查看本店出售的物品"+
			     "用"+HIC"buy"NOR+"买物品。\n"+
			     "另外本店急需帮工，请向山主打听。\n\n",
	]));
	set("exits", ([
		"east" : __DIR__"nanlang1",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer" : 1,
	]));
	set("no_fight", 1);
//	set("no_clean_up", 0);
	setup();
}

void init()
{
           add_action("do_job","qie");
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
	if( (string)(inv[i]->query("id"))=="caidao" && 
		(int) inv[i]->query("equipped") ) 
	{
		if( !arg || arg!="菜" )
			{return notify_fail ("你要切什么？\n");
		}
		else {
			me->add_temp("wancheng", jingli);
			me->add("jingli", -jingli);
			me->add("combat_exp", jingli);
			me->add("potential", (jingli/2));
			message_vision ("$N拿起菜刀，在案板上切着菜！\n", me );
			if (me->query_temp("wancheng") >= 100)
			{
				me->set_temp("renwu",100);   //设100表示完成任务
				return notify_fail (WHT"你可以回去复命了！(ask moto about ok)\n"NOR);
				}
			}
	}
	else {
		return notify_fail ("你空手怎么切菜？拿手砍吗！\n");
		}
        return 1;
}

int valid_leave(object me, string dir)
{
         if ( (dir == "east") &&
		(me->query("wancheng") >= 100) )
	{
		if ( !present("caidao", me) ) {return 1;}
			message_vision ("$N放下手中的菜刀。\n", me);
			destruct(present("caidao", me));
	}
	return ::valid_leave(me, dir);
}
