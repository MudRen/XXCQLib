// quhanshan.c
// by mulan

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int do_skills(string arg);

void create()
{
        set_name("屈寒山", ({"qu hanshan", "qu"}));
        set("gender", "男性");
        set("accept", 8000);
        set("age", 56);
        set("nickname",HIM"威震阳朔"NOR);
        set("long",
                "三络长须，仙风道骨，态度雍容，那人就是屈寒山，既是武林中的“威震阳朔”，也是“权力帮”中的“剑王”。\n");
        set("shen_type",1);
        set("shen",-100000);
        set("str", 52);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("title","“权力帮__剑王”");

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 100);

        set("combat_exp", 2000000);
        set("score", 300000);

        set_skill("force", 200);
        set_skill("sword", 220);
        set_skill("wuxing-jian",220);  
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set_skill("literate",180);

        map_skill("sword", "wuxing-jian");
        map_skill("parry", "wuxing-jian");

        setup();

        carry_object("/clone/weapon/changjian")->wield();
//        carry_object(__DIR__"obj/grayrobe")->wear();

}

/*
 int recognize_apprentice(object ob)
 {
     if (ob->query("party/party_name")!= "权力帮")
     {
     message_vision("$N摇了摇头。\n",this_object());
     command("say "+ob->query("id")+"不是权力帮的我不教。\n");
     return 0;
     }
        if(ob->query("party/tasks") < this_object()->query("accept"))
          {
          command("say 你对权利帮的贡献还不够,多去工作!\n");
          return 0;
          }
     return 1;
 }

*/
#include "quanli.h"
void init()
{
::init();
add_action("do_skills","skills");
add_action("do_skills","cha");
add_action("do_join","join");
}
int do_skills(string arg)
{
	object ob ;
	ob = this_player () ;
	if( !arg || arg!="qu" )
		return 0;
	if(wizardp(ob))  return 0;
	if (ob->query("party/party_name") != "权力帮")
	{
		message_vision("$N摇了摇头。\n",this_object());
		command("tell "+ob->query("id")+" 不是权利帮的人不能察看。\n"); 
		return 1;
	}
    command("tell "+ob->query("id")+" 我所有的武功如下：\n"+
"※屈寒山目前所学过的技能 	\n"+
"  基本轻功 (dodge)                         - 深不可测 200/    0	\n"+
"  基本内功 (force)                         - 深不可测 200/    0	\n"+
"  基本招架 (parry)                         - 深不可测 200/    0	\n"+
"  基本剑法 (sword)                         - 深不可测 220/    0	\n"+
"  读书写字 (literate)                      - 初窥门径 180/    0       0/    0	\n"+
"★无形之剑 (wuxing-jian)                   - 半生不熟 220/    0       0/    0	\n");
   return 1;
}
