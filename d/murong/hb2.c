// hb2.c

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short",GRN"湖边"NOR);
         set("long",
"俗话说："+BLINK HIC+"上有天堂, 下有苏杭"+NOR+"。这里正是大大有名的"+BLINK HIM+"太湖"+NOR+"。湖面绿波上\n"
"漂着一叶叶的"+BLINK HIW+"小舟"+NOR+", 一阵阵悦耳的小曲儿随着湖上的轻风不时漂入你的耳中。\n"
);
         set("outdoors","姑苏慕容");
         set("exits", ([
             "west" : __DIR__"hb1",
             "southeast" : __DIR__"sq",
]));
         setup();
}
void init()
{
	object me = this_player();
	object weapon;
	if( me->query_temp("is_suiciding") 
      	&& me->query("combat_exp") > 300000
	&& me->query("family/generation") == 3
       	&& me->query("family/family_name") == "姑苏慕容" 
        && me->query("jifen")
     	&& me->query("ketou")
	&& !me->query("marry")
        && !me->query("meet_mrb")
        && objectp(weapon=me->query_temp("weapon") )
        && weapon)
        {                        
        message_vision("突然破空声大作，一件暗器从十余丈外飞来，撞上$N手中"+weapon->query("name")+"。
铮的一声响，$N手中"+weapon->query("name")+"脱手而出，手掌中满是鲜血，虎口已然震裂。\n", me);
	weapon->move(environment(me));
	remove_call_out("meet_bo");
	call_out("meet_bo", 2, me);       
	return;
	}            
	call_out("check", 1, me);
}
void check()
{
	object me = this_player();
	if( me->query_temp("is_suiciding"))
	{
		me->move(__FILE__);
		remove_call_out("check");
	}
	else call_out("check", 1, me);
	return;
}	
	
void meet_bo()
{
	object me = this_player();
	tell_object(me, "你只觉得脚下一空，被一蒙面灰衣老僧凌空抓起。\n");
	message("vision", me->name()+"只觉得脚下一空，被一灰衣老僧凌空抓起，老僧跨出数丈，一溜烟不见了。\n", environment(me), ({me}));
	me->set_temp("mrb_see", 1);
	me->move(__DIR__"liulin1");
	return;
}

/*void init()
{
	 object me = this_player();
	 int luck = (int)me->query_temp("mrb_meet");
	 me->add("jingli", -10);
	 if( (int)me->query("mrb_fail", 1) < 5 ) 
	 {
         	if( me->query("combat_exp") > 300000
	         && me->query("family/generation") == 3
        	 && me->query("family/family_name") == "姑苏慕容" 
	         && me->query("jifen")
        	 && me->query("ketou")
	         && !me->query("marry")
        	 && luck < 1
	         && !me->query("meet_mrb")
        	 && random(5) < 2)
	         {
        	 	write("你突然觉得好象有人在你身后，转过头来却发现什么也没有。\n");
         		me->set_temp("mrb_meet", 1);
	         }   
         
        	 if (luck >= 1) 
	         {
        		  write("你突然觉得好象有人在你身后，转过头来却发现什么也没有。\n"); 
	        	  me->add_temp("mrb_meet", 1); 
                 }
	        
        	 if (luck >= 10) 
        	 {
          	 	  write("忽听背後一人嘿嘿冷笑了几声。\n");
          		  message_vision("\n$N被突如其来的笑声一惊，回头便发足狂奔。\n",me);         
          		  me->delete_temp("mrb_meet");
          		  me->set_temp("mrb_meet1", 1); 
          		  call_out("wait", 10, me);         
        	 }                                        
	}
}

void wait()
{
        object me;
        int total, try;
        me = this_player();
        total = (int)me->query("int")+(int)me->query("kar");
        try = me->query("mrb_fail");
        if(total > 40)
        {
        	message_vision("$N吓的浑身只打哆嗦，只得发足狂奔。\n",me);
	        me->set_temp("mrb_see", 1); 
        	me->delete_temp("mrb_meet1");
	        me->move(__DIR__"liulin1");
        	return;
        }
        else 
        {
        	if(!try) 
        	{
                	me->set("mrb_fail", 1);    
	                message_vision(HIR"$N脚下突然一软，骨碌碌地滚出了数十丈！\n"NOR,me);
        	        me->delete_temp("mrb_meet1");     
                	me->move(__DIR__"hb");
	                me->receive_wound("qi", 100);
        	        tell_room(environment(me), HIR + me->name()+"骨碌碌地滚了过来，躺在地上半天爬不起来！\n" NOR,({ me }));    
	                return;
                }
        	else 
        	{
                	me->add("mrb_fail", 1);    
	                message_vision(HIR"$N脚下突然一软，骨碌碌地滚出了数十丈！\n"NOR,me);
        	        me->delete_temp("mrb_meet1");     
                	me->move(__DIR__"hb");
	                me->receive_wound("qi", 100);
        	        tell_room(environment(me), HIR + me->name()+"骨碌碌地滚了过来，躺在地上半天爬不起来！\n" NOR,({ me }));        
	                return;
                }     
        }
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("mrb_meet1") && dir == "west")
                return notify_fail("忽听呼的一声响，一个人影从你头顶跃过，落在你身前。\n");
        return ::valid_leave(me, dir);
}
*/