// dating.c 大厅
// mlf设计，lks编程

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short","大厅");
        set("long",
"这里就是花府大厅，气势威严，进来一眼就可以看到墙上有一幅字画
，正是李白的<<侠客行>>，气派非凡。但到了某些喜庆的日子，这里就会
张灯接彩，大摆宴席。\n"
	);
        set("class","发梦二党");
	set("valid_startroom",1);
	set("exits",([
		"south" : __DIR__"huayuan",
		"west"  : __DIR__"zoulang3",
		"east"  : __DIR__"zoulang4",
		"northeast" : __DIR__"zoulang2",
	]));
	set("objects",([
		__DIR__"npc/zhang" : 1,
	]));
	setup();
          "/clone/board/huafu_b"->foo();
}

/*
void init()
{
        object ob;
      int i;
        object *obb;
        object me=this_player();
        mapping fam;
        mapping party;
        
        if (interactive(me))
        {
                if (me->query_temp("compaign_start"))
                {
                        if (query("send"))      return;
                        if (!objectp(ob=present("hua kufa",environment(me)))) 
                        {
                                ob=new("/d/huafu/npc/huakufa");
                               ob->move(environment(me));
                                message_vision("花枯发走了过来。\n",me);
                        }
                        if (!objectp(ob=present("wen mengcheng",environment(me))))           
                        {
                                ob=new("/d/wenzhai/npc/wenmengcheng");
                               ob->move(environment(me));
                                message_vision("温梦成走了过来。\n",me);                                
                        }
                        message_vision("花枯发和温梦成交谈了一会，对$N说道：“你来得最快，这个令牌给你发号施令吧！”\n",me);
                        ob=new("/d/huafu/obj/ling");
                        ob->move(me);
                        me->set_temp("shouling",1);
                        set("send",1);
                }
                if (me->query_temp("killwei"))
                {
                        obb=all_inventory(environment(me));
                        for(i=0; i<sizeof(obb); i++) {
				if (obb[i]->is_character() )
				{
                                fam=(mapping)obb[i]->query("family");
                                party=(mapping)obb[i]->query("party");
//                                if (fam["family_name"]==me->query_temp("oponent") || party["party_name"]==me->query_temp("oponent") )
                                if ( !fam && !party ) return;
                                if ((fam && fam["family_name"]!="发梦二党") || (party && party["party_name"]!=HIG"发梦二党"NOR ))
					return;
                                        obb[i]->kill_ob(me);
                                        me->kill_ob(obb[i]);
                        }
                 return;
               }
                }
                return;
        }
}


int valid_leave(object me, string dir)
{
        object ob;
        mapping myfam,party;
        myfam=(mapping)me->query("family");
        party=(mapping)me->query("party");
        if ( !party && !myfam ) return ::valid_leave(me,dir);
        if( (!party || party["party_name"] != HIG "发梦二党" NOR) && ( !myfam || myfam["family_name"] != "发梦二党"))
                return ::valid_leave(me,dir);
               if (!(me->query_temp("buzhile")) && me->query_temp("compaign_start"))
                      return notify_fail(
                      WHT"还没有分配给你防守区域，不能离开。\n"NOR);
        me->delete_temp("compaign_start");
        me->set_temp("zhangang",1);
        return ::valid_leave(me,dir);
}


*/
