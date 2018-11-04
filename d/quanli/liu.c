// quhanshan.c
// by mulan

#include <ansi.h>
inherit NPC;
int ask_rank();

void create()
{
        set_name("柳随风", ({"liu suifeng", "liu"}));
        set("gender", "男性");
        set("age", 56);
        set("nickname",HIW"袖里日月"NOR);
        set("long",
        "柳随风！ 这一声犹如晴天霹雳，炸响在每个人耳里！ 柳大总管：李沉舟的唯一亲信！\n");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 30);
        set("dex", 999);

        set("title","“权力帮__军师”");

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 100);

        set("combat_exp", 500000);
        set("score", 300000);

        set_skill("force", 200);
        set_skill("sword", 200);
        set_skill("liuxu-shenfa",220);  
        set_skill("dodge", 220);
        set_skill("parry", 200);
        set_skill("literate",180);

        map_skill("dodge", "liuxu-shenfa");
        
        set("inquiry", ([
            "rank" : (: ask_rank :),
            "级别" : (: ask_rank :),            
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
//	carry_object(__DIR__"obj/grayrobe")->wear();

}

int ask_rank()
{
	object me;
	int v_task;
	string v_rank;
	string *title1 = ({
"三绝","铁骑","百毒","神拳","铁腕","无影","无名","一洞","长刀","绝灭",
"瘟疫","血影","独脚","千手","快刀","飞腿","暗杀","佛口","飞刀",
});
	me = this_player();
	v_task = (int)me->query("party/tasks");
	
	if(me->query("party/party_name")!="权力帮")
	{
		command("say 你不是权力帮的人，我不能帮你!\n");
		return 1;
	}
	
	if(me->query_temp("rank") == 1)
	{
		command("say 你今天不是才问了吗？\n");
		return 1;
	}
	
	if(v_task > 10000)
	v_rank = HIY"总坛护法";
	else if(v_task > 5000)
	v_rank = HIW"柳随风之亲信";
	else if(v_task > 2000)
	v_rank = HIB""+title1[random(sizeof(title1))]+"分舵"+HIM"舵主"NOR;
	else if(v_task > 1000)
	v_rank = RED""+title1[random(sizeof(title1))]+"神君"+HIM"麾下"NOR;
	else
	command("say 你对本帮的忠诚度还不够！多做实事吧!\n");
	command("chat* gongxi "+me->query("id"));
	command("chat "+me->query("name")+"在权力帮任"+v_rank+"一职。\n");
	me->set_temp("rank",1);
// 	me->set("party/",v_rank);
	return 1;
}
#include "/kungfu/class/quanli/quanli.h"
