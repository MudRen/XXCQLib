// made by lks

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "/kungfu/class/xuehepai/xiao.h"
#include "/kungfu/class/xuehepai/cloth.h"
#include "/kungfu/class/xuehepai/caojob.h"
void heal_ob();
int ask_me();
void recover_ob();

void create()
{
        set_name("曹大悲",({"cao dabei","cao"}));
        set("nickname",RED"血雾纷飞"NOR);
	set("gender","男性");
       set("shen_type",-1);
	set("int",30);	
	set("con",30);
	set("str",30);
	set("dex",30);
	set("bac",40);
        set("book",1);
        set("age",30);
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
        set_skill("throwing",150);
        set_skill("huaxue-shenzhen",150);
        set_skill("tao",100);
        set_skill("feixue-quan",150);
        set_skill("huaxue-dafa",150);
        map_skill("force","huaxue-dafa");
        map_skill("dodge","youran-bu");
        map_skill("cuff","feixue-quan");
        map_skill("throwing","huaxue-shenzhen");
        map_skill("sword","xuehe-jian");
        prepare_skill("cuff","feixue-quan");
	
       create_family("血河派",13,"弟子");
	setup();
	carry_object("/clone/misc/cloth")->wear();
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
              "血河秘籍" : (: ask_me :),
              "秘籍" : (: ask_me :),
              "job" : (: ask_job :),
              "book" : (: ask_me :),
              "miji" : (: ask_me :),
       ]));
}

	
void heal_ob()
{
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
            if (!query("book"))
            {
                 command("say 秘籍已经被拿走了。");
                 return 1;
            }
                   if (me->query("combat_exp")>100000) {
                  ob=new("/d/longmen/xuehepai/obj/miji");
                  command("say 好吧，这几本书你拿去好好研究一下。");
        set("book",0);
                  ob->move(me);
                   }
              command("say 你的经验不够，要来也没有用!\n");
                  return 1;
}

