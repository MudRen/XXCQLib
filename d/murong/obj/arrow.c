// arrow.c 弓箭
#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(HIY"弓箭"NOR, ({ "gongjian" }));
        set_weight(2000);		                      	
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "张");
		set("long", HIY"这是一把传说中的大燕国皇上御用的弓箭。\n"NOR);
		set("value", 50000);
                set("material", "iron");            
	}
        setup();
}

void init()
{
	add_action("do_aim", "aim");
	add_action("do_shoot", "shoot");
}

int do_aim(string arg)
{                        
	int i;
	object me, ob, room, *obj;
	me = this_player();
	ob = this_object();
	room = find_object("/d/murong/boat1");
	obj = all_inventory(room);
	if(!living(me))
		return 0;
	if(!arg || arg == "" || arg != "boat")
		return notify_fail("你要瞄准什么？\n");
	if(!present(ob, me))
		return 0;                                      
	
	if( arg == "boat" )                
	{                                              
		if(!(room=find_object("/d/murong/boat1")))
		     room=load_object("/d/murong/boat1");
		if( room->query("busy"))
		{
			message_vision("$N鼓足力气，暗运内功，把箭拉了起来，对准了湖面上的小船。\n", me);
		}
		message_vision("$N鼓足力气，暗运内功，把箭拉了起来。\n", me);	
		me->set_temp("aim_target", 1);		
		return 1;		
	}
}		                                      

int do_shoot(string arg)
{                                 
	int i;
	object me, ob, room, *obj, obb;
	me = this_player();
	ob = this_object();
	room = find_object("/d/murong/boat1");
	obj = deep_inventory(room);         

	if(!living(me))
		return 0;
	if(!arg || arg == "" || arg != "boat")
		return notify_fail("你要向什么地方发射？\n");
	if(!present(ob, me))
		return 0;                                      
	if(!me->query_temp("aim_target"))
		return notify_fail("你还没有瞄准呢。\n");	
	if( arg == "boat" )
	{                	
		if(!(room=find_object("/d/murong/boat1")))
	     	     room=load_object("/d/murong/boat1");      
	     	if( room->query("busy"))
	     	{       
	     		if( objectp(obb=present("arrow", me)) && obb->query_amount()>0 )
	     		{
	        		for(i=0; i<sizeof(obj); i++)
                		{
	                		if(obj[i]->is_character() && living(obj[i]) && !wizardp(obj[i]))
		        		{        
		                		message_vision("$N从袋子中取出一支箭搭在弦上，突然一松手，一只离弦的箭朝着湖面上的小船飞去。\n", me);
		                		message_vision(HIY"HEHE"NOR, room);
		          		      	call_out("wait", 2, room);
		                		return 1;
		                	}
		                	else 
		                	{
		                		message_vision("$N从袋子中取出一支箭搭在弦上，突然一松手，一只离弦的箭朝着湖面上的小船飞去。\n", me);
		                		call_out("fail", 2, me);
		                		return 1;
		                	}
		                }	
		        }
		        else 
		        {
		        	write("你突然发现你身上已经没有箭了。\n");        
		        	return 1;
		        }
		 }
		 else
		 {
		 	write("你揉了揉眼睛，突然发现小船里并没有人。\n");
		 	return 1;
		 }
	}
}                