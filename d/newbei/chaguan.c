// Room: /welcome/chaguan.c
//By adx @ CuteRabbit 15:57 99-5-18

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", WHT"神雪茶馆"NOR);
	set("long",
"你一走进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八仙桌一字\n"
"排开，坐满了客人，或高声谈笑，或交头接耳。你要想打听江湖掌故和谣言，\n"
"这里是个好所在。墙上贴着一张广告"+HIC"(guanggao)\n"NOR
 );
	set("item_desc", ([
		"guanggao" : "你可以用"+HIC"list"NOR+"查看本店出售的物品"+
			     "用"+HIC"buy"NOR+"买物品。\n"+
			     "另外本店急需帮工，请向山主打听。\n\n",
	]));
	set("no_fight", 1);
	set("resource/water", 1);
	set("exits", ([
		"east" : __DIR__"beilang1",
	]));
	set("objects", ([
		__DIR__"npc/aqingsao" : 1,
	]));
	setup();
}

void init()
{
           add_action("do_job","shao");
}
int do_job(string arg)
{
        object *inv;
        object me;
         int i, jing;

	me = this_player();
	jing = ( random(me->query("dex"))/3 );
	inv = all_inventory(me);
	if (jing <= 0)
		jing = 5;

	if (me->query("jingli")<=10) {
	message_vision ("你没有气力了，先去休息室睡一下吧！"+HIC"(sleep)\n"NOR, me );
        return 1;
	}
	   //判断是否wield了工具
     if( (string)(inv[i]->query("id"))=="shanzi" && 
		(int) inv[i]->query("equipped") ) 
	{
		if( !arg || arg!="水" )
			{return notify_fail ("你要砍什么？\n");
		}
		else {
			me->add_temp("wancheng", jing);
			me->add("jingli", -jing);
			me->add("combat_exp", jing);
			me->add("potential", (jing/3));
			message_vision ("$N拿起扇子，在炉灶边轻轻扇，烧着水！\n", me );
			if (me->query_temp("wancheng") >= 100)
			{
				me->set_temp("renwu",100);   //设100表示完成任务
				return notify_fail (WHT"水烧开了，你可以回去复命了！(ask moto about ok)\n"NOR);
				}
			}
	}
	else {
		return notify_fail ("你空手怎么扇火？用嘴吹吗！\n");
}
         return 1;
 }

 int valid_leave(object me, string dir)
 {
         if ( (dir == "east") &&
                 (me->query("wancheng") >= 100) )
         {
                 if ( !present("shanzi", me) ) {return 1;}
                         message_vision ("$N放下手中的扇子。\n", me);
                         destruct(present("shanzi", me));
         }
         return ::valid_leave(me, dir);
 }

