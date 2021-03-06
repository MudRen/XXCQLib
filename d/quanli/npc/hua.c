// huagufen.c 华孤坟	

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("华孤坟",({"hua gufen","hua"}));
	set("long",
	"很少有人能看见华孤坟的真实面容，此人阴毒无比，死在他手下的人\n"
	"从来就没有一个像人的。\n"
	"雪白的衣服，苍白的手，看似年轻的面容。\n");
	set("party/rank",HIC"百毒神魔"NOR);
	set("party/party_name","权力帮");
	set("age",35);
	set("gender","男性");
	set("autitude","friendly");
	set("str",22);
	set("con",24);
	set("dex",31);
	set("int",29);
	
	set("max_qi",3000);
	set("max_jing",2000);
	set("neili",3000);
	set("max_neili",3000);
	set("jiali",50);
	
	set("combat_exp",1500000);
	set("score",2000);
	
	set("inquiry",([
		"权力帮":"我愿为权力帮赴汤蹈火，尽忠尽力！",
		]));
			
    set_skill("dodge",150);
    set_skill("force",150);
    set_skill("poison",220);
	set_skill("force",180);
	set_skill("sword",200);
	set_skill("unarmed",120);
	
	setup();
	
    carry_object("/clone/misc/cloth")->wear();

	
}

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
        if( !arg || arg!="hua" )
                return 0;
        if(wizardp(ob))  return 0;
        if (ob->query("party/party_name") != "权力帮")
        {
                message_vision("$N摇了摇头。\n",this_object());
                command("tell "+ob->query("id")+" 不是权利帮的人不能察看。\n"); 
                return 1;
        }
    command("tell "+ob->query("id")+" 我所有的武功如下：\n"+
"华孤坟目前所学过的技能：    \n\n"+
"  基本轻功 (dodge)                         - 出神入化 150/    0     \n"+
"  基本内功 (force)                         - 一代宗师 180/    0   \n"+
"  基本剑法 (sword)                         - 深不可测 200/    0   \n"+
"  基本拳脚 (unarmed)                       - 神乎其技 120/    0  \n"+
"  基本毒技 (poison)                        - 半生不熟 220/    0       0/    0    \n");
"  基本轻功 (dodge)                         - 深不可测 200/    0        \n"+
"  基本内功 (force)                         - 深不可测 200/    0        \n"+
"  基本招架 (parry)                         - 深不可测 200/    0        \n"+
"  基本剑法 (sword)                         - 深不可测 220/    0        \n"+
"  读书写字 (literate)                      - 初窥门径 180/    0       0/    0  \n"+
"★无形之剑 (wuxing-jian)                   - 半生不熟 220/    0       0/    0  \n");
   return 1;
}
