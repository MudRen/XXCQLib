// made by lks

#include <ansi.h>
#include "/kungfu/class/xuehepai/xiaojob.h"

inherit NPC;
inherit F_MASTER;
int ask_me();
int ask_me1();
int ask_job();
#include "/kungfu/class/xuehepai/xiao.h"
#include "/kungfu/class/xuehepai/cloth.h"
void heal_ob();
void recover_ob();

void create()
{
        set_name("萧萧天",({"xiao xiaotian","xiao"}));
        set("nickname",HIR"幽冥血奴"NOR);
	set("gender","男性");
	set("int",30);	
	set("con",30);
	set("str",30);
	set("dex",30);
	set("bac",40);
	set("age",40);
	set("attitude","friendly");
        set("combat_exp",500000);
        set("kill",1000);
	set("long",
"英俊潇洒,但始终看不破一个情字，最后也殉情了。\n"
	);
        set("neili",2000);
        set("jingli",1800);
        set("max_neili",2000);
        set("max_jingli",1800);
        set_skill("literate",100);
        set_skill("cuff",150);
        set_skill("parry",150);
        set_skill("dodge",150);
        set_skill("youran-bu",150);
        set_skill("xuehe-jian",150);
        set_skill("sword",150);
        set_skill("force",150);
        set_skill("tao",100);
        set_skill("feixue-quan",150);
        set_skill("throwing",150);
        set_skill("huaxue-shenzhen",150);
        set_skill("huaxue-dafa",150);
        map_skill("force","huaxue-dafa");
        map_skill("dodge","youran-bu");
        map_skill("cuff","feixue-quan");
        map_skill("sword","xuehe-jian");
        map_skill("throwing","huaxue-shenzhen");
        prepare_skill("cuff","feixue-quan");
	
       create_family("血河派",13,"弟子");
	setup();
	carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/longmen/xuehepai/obj/zhen")->wield();
        set("chat_chance", 2);
	set("chat_msg", ({
		(: heal_ob :),
	}));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
                (: exert_function, "xisui" :),
                (: exert_function, "xuewu" :),
                (: recover_ob :),
	}) );
       set("inquiry",([
              "血翼" : (: ask_me :),
              "job" : (: ask_job :),
              "xueyi" : (: ask_me :),
              "cancel" : (: ask_me1 :),
       ]));
}


	
void heal_ob()
{
	command("yun heal");
	command("yun heal");
	command("yun heal");
	command("yun recover");
	return;
}

void recover_ob()
{
	command("yun recover");
	return;
}

int ask_me()
{
           object ob;
           mapping fam;

           object me=this_player();

           fam=(mapping)me->query("family");

           if (!fam || fam["family_name"]!="血河派")
           {
                  command("say 你与本派并无瓜葛，此话从何说起？");
                  return 1;
           }
           if (me->query("combat_exp")<300000)
           {
                  command("say 你的实战经验太低了。");
                  return 1;
           }
             if (me->query("max_neili")<300)
           {
                  command("say 你的内力修为太低了。");
                  return 1;
           }
           if (query("yi"))
           {
                 command("say 血翼已经被拿走了。");
                 return 1;
            }
                  command("say 好吧，我把血翼交给你。");
                    set("yi",1);
                  ob=new("/d/longmen/xuehepai/obj/xueyi");
                  ob->move(me);
                  return 1;
}

int ask_job()
{
        object me;
        object ob;
        mapping myfam;
        me=this_player();

        myfam=me->query("family");
        
        if ( !myfam || myfam["family_name"] != "血河派" )
        {
                command("say "+RANK_D->query_respect(me)+"不是我血河派的弟子，我们又怎敢劳烦您呢？");
                return 1;
        }
        
        if (me->query_temp("job_start"))
        {
                command("say 你已经有工作了，还不快去！");
                return 1;
        }
        
          if (me->query("combat_exp")>40000)
        {
                command("say "+RANK_D->query_respect(me)+"你是时候练武功了，这些小事就不用麻烦你了。");
                return 1;
        }
        
        tell_object(me,"好吧,听说后山山道上的石头材质不错！\n");
        tell_object(me,"你去搬一块回来，我要做一些东西！\n");
         if (!(ob=present("hammer",me)))
         {
         ob=new("/kungfu/class/xuehepai/obj/hammer");
         ob->move(me);
           }
        me->set_temp("job_start",1);
        return 1;
}


int ask_me1()
{
                object me;
                mapping family;

                me=this_player();
                family=(mapping)me->query("family");

                if ( !family || family["family_name"]!="血河派")      return 0;
            if (me->query_temp("job_start"))  {
                      command("poor "+me->query("id"));
                           command("say 好吧！ 再给"+me->query("name")+"你一次机会吧。");
                           me->add("combat_exp",-(me->query("combat_exp")/1000));
                           me->add("potential",-(me->query("potential")/1000));
                           me->delete_temp("find");
                      return 1;
           }
           return 0;
}


