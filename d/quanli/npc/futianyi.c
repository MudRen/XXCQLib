// futianyi.c 傅天义	

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("傅天义",({"fu tianyi","fu"}));
	set("long",
	"傅天义常年隐居在秭归古城，只有当权力帮要他卖命时他才出山。\n"
	"他身材瘦高，唯有两臂非常粗壮，白须在风中微微颤动。\n");
	set("party/rank",HIC"铁腕神魔"NOR);
	set("party/party_name","权力帮");
	set("age",62);
	set("gender","男性");
	set("autitude","friendly");
	set("str",33);
	set("con",28);
	set("dex",30);
	set("int",25);
	
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
    set_skill("strike",200);
    set_skill("unarmed",200);
	
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
        if( !arg || arg!="fu" )
                return 0;
        if(wizardp(ob))  return 0;
        if (ob->query("party/party_name") != "权力帮")
        {
                message_vision("$N摇了摇头。\n",this_object());
                command("tell "+ob->query("id")+" 不是权利帮的人不能察看。\n"); 
                return 1;
        }
    command("tell "+ob->query("id")+" 我所有的武功如下：\n"+
"傅天义目前所学过的技能：     \n"+
"  基本轻功 (dodge)                         - 出神入化 150/    0    \n"+
"  基本内功 (force)                         - 出神入化 150/    0      \n"+
"  基本掌法 (strike)                        - 深不可测 200/    0      \n"+
"  基本拳脚 (unarmed)                       - 深不可测 200/    0     \n");
   return 1;
}
