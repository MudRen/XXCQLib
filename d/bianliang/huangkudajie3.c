// huangkudajie3.c

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{	
	set("short", "黄裤大街");
	set("long", @LONG
从这里向南就到了温宅的大门，由于“温门十石”的影响，前来拜师
学艺的江湖新秀络绎不绝，由于这里是发梦二党的地盘，到处可见其党羽
来来往往穿梭其间，东边是一条小巷。
LONG);	
      set("valid_startroom",1);
      set("no_steal", "1");
      set("outdoors", "bianliang");
	set("exits", ([
//                "north" : __DIR__"mingliquan",
                "south" : "/d/wenzhai/damen",
//                "west" : __DIR__"huangkudajie2",
                "west" : __DIR__"xichengmen",
		"east" : __DIR__"hua_lukou",
	]));
//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));
	set("area", "汴梁");
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        mapping myfam,party;
        myfam=(mapping)me->query("family");
        party=(mapping)me->query("party");

        if( (party && party["party_name"]== HIG "发梦二党" NOR) || (myfam && myfam["family_name"]== "发梦二党")
                && (dir == "south") )
        return ::valid_leave(me, dir);
           if (!myfam && !party)
        return ::valid_leave(me, dir);
          if (dir=="south")
          {
                if(!objectp(present("men wei", environment(me))))              
                {
                        if (query("shibai"))
            {
                  me->set_temp("killwei",1);
                                return ::valid_leave(me,dir);
      }
                ob=new("/d/huafu/npc/menwei1");
                ob->move(environment(me));      
                message_vision("一个身影挡在$N的面前。\n",me);
                        set("shibai",1);
                }
                if(!objectp(present("bai tie",me)))
                      return notify_fail("门卫伸手拦住你谦声说道：发梦二党温宅不容外人擅自入内，\n若非拜师的话"
                                + RANK_D->query_respect(me) +"还是请回去吧，免得自讨没趣。\n");
                return notify_fail("门卫笑眯眯的对你说道：把拜帖给我吧。\n");
            }
       return ::valid_leave(me, dir);
}


