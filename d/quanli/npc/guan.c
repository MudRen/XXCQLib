// guhuanqing.c 顾环青	

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("顾环青",({"gu huanqing","gu"}));
	set("long",
	"顾环青是权力帮十九人魔之一，以腿功擅长，后死于萧易人剑下。\n"
	"他貌似年轻，上身瘦小，但双腿却非常发达。\n");
	set("party/rank",HIC"飞腿天魔"NOR);
	set("party/party_name","权力帮");
	set("age",37);
	set("gender","男性");
	set("autitude","friendly");
	set("str",24);
	set("con",28);
	set("dex",31);
	set("int",26);
	
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
			
	set_skill("dodge",180);
	set_skill("force",180);
    set_skill("leg",180);
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
        if( !arg || arg!="gu" )
                return 0;
        if(wizardp(ob))  return 0;
        if (ob->query("party/party_name") != "权力帮")
        {
                message_vision("$N摇了摇头。\n",this_object());
                command("tell "+ob->query("id")+" 不是权利帮的人不能察看。\n"); 
                return 1;
        }
    command("tell "+ob->query("id")+" 我所有的武功如下：\n"+
"顾环青目前所学过的技能：   \n\n"+
"  基本轻功 (dodge)                         - 一代宗师 180/    0     \n"+
"  基本内功 (force)                         - 一代宗师 180/    0    \n"+
"  基本拳脚 (unarmed)                       - 神乎其技 120/    0   \n"+
"  基本腿法 (leg)                           - 粗通皮毛 180/    0       0/    0       \n");
   return 1;
}
