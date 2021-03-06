// tang.c 唐一独

#include <ansi.h>
inherit NPC;
#include "/d/huafu/npc/cam.h"

int ask_job();
void create()
{
	set_name("唐一独", ({ "tang yidu", "tang" }));
        set("nickname",HIY"独来独往"NOR);
	set("gender", "男性");
         set("rank","党羽");
	set("age", 45);

	set("combat_exp", 60000);
        set_skill("cuff",50 );
        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("bairen-shengong",50);
        
        map_skill("force","bairen-shengong");
       create_party(HIG"发梦二党"NOR,HIC"管事"NOR,3);
	
	setup();
	set("inquiry",([
		"job" : (: ask_job :),
	]));
	carry_object("/clone/misc/cloth")->wear();
}

int ask_job()
{
	object me;
	mapping party;
	mapping myfam;
        int i;
        object money;
	me=this_player();
        party=(mapping)me->query("party");
        myfam=(mapping)me->query("family");
	
	if( (!party || party["party_name"] != HIG "发梦二党" NOR) && ( !myfam || myfam["family_name"] != "发梦二党") )
	{
		command("say "+RANK_D->query_respect(me)+"不是我发梦二党的兄弟，我们又怎敢劳烦您呢？");
		return 1;
	}
        if ( (me->query("combat_exp")>40000 ) && myfam )
	{
                command("say "+RANK_D->query_respect(me)+"你做的不错，现在不需要你帮忙了。\n");
		return 1;
	}
         if ( party && !myfam) {
                command("say 您现在是发梦二党的兄弟了，去清谋石那看看有什么事做吧。");
		return 1;
        }
          if ( me->query_temp("fmjob_ok") )
	{
          if ( me->query_temp("fmjob_start") )
		{
			command("say 多谢，多谢，辛苦了，你去休息休息吧。");
                        me->add("potential", 50+random(50));
                        me->add("combat_exp", 75+random(75));
                        for (i=1;i<5;i++)
                        {
                               money=new("/clone/money/silver");
                               money->move(me);
                        }
                          me->delete_temp("fmjob_start");
                          me->delete_temp("fmjob_ok");
			return 1;
		}
		command("say 我没教你去做，你却去帮忙。现在象你这样的好人不多啊。");
		me->add("potential", 1+random(10));
		me->add("combat_exp", 3+random(10));
                  me->delete_temp("fmjob_ok");
		return 1;
	}
	message_vision("好吧,$N你去到糟坊帮忙吧！\n",me);
	message_vision("造酒的原料嘛，先到粮仓去看看吧！\n",me);
          me->set_temp("fmjob_start",1);
	return 1;
}

void attempt_join()
{
        object ob;
        object mee;
        
        ob = this_player () ;
        mee=this_object();
        if ((int)ob->query("shen") < 0)
        {
        message_vision(HIC "$n对$N大怒道：一看你就不是好人!\n" NOR,ob,mee);
//      set_leader(this_player());
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, this_player()); 
        return;
        }
        if ((int)ob->query("shen") < 1000)
        {
        message_vision(HIC "$N摇摇头道：你还不够侠义!\n" NOR,mee);
        return;
        }
        if (ob->query("combat_exp")<10000)
        {
        message_vision(HIC "$n对$N摇头道：你的实战经验太低。\n" NOR,ob,mee);
        return;
        }
                command("smile");
                command("handshake "+this_player()->query("id"));
                command("nodjoin "+this_player()->query("id"));
                command("tell "+this_player()->query("id")+" 大家从此就是一家人了。\n");
        return;
}


