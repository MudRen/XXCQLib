// pengjiu.c 彭九	

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("彭九",({"peng jiu","peng"}));
	set("long",
	"彭九早年闯荡江湖时被人砍去一脚，却为此苦练独脚，以钢杖替脚，\n"
	"反而有所成就。\n"
	"他面宽耳阔，两臂甚粗，唯有独脚使他格外显眼。\n");
	set("party/rank",HIC"独脚神魔"NOR);
	set("party/party_name","权力帮");
	set("nickname",HIG"独脚镇千山"NOR);
	set("age",44);
	set("gender","男性");
	set("autitude","friendly");
	set("str",25);
	set("con",26);
	set("dex",32);
	set("int",28);
	
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
    set_skill("staff",200);
    set_skill("leg",180);
	
	setup();
	
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangzhang")->wield();
	
}
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
        if( !arg || arg!="peng" )
                return 0;
        if(wizardp(ob))  return 0;
        if (ob->query("party/party_name") != "权力帮")
        {
                message_vision("$N摇了摇头。\n",this_object());
                command("tell "+ob->query("id")+" 不是权利帮的人不能察看。\n"); 
                return 1;
        }
    command("tell "+ob->query("id")+" 我所有的武功如下：\n"+
"※ 彭九目前所学过的技能：    \n"+
"\n  基本轻功 (dodge)                         - 出神入化 150/    0     \n"+
"  基本内功 (force)                         - 出神入化 150/    0    \n"+
"  基本杖法 (staff)                         - 深不可测 200/    0   \n"+
"  基本腿法 (leg)                           - 粗通皮毛 180/    0       0/    0    \n");
   return 1;
}
