// wenmengcheng.c 温梦成
// made by lks

#include <ansi.h>
#include "/d/huafu/npc/cam.h"

inherit NPC;
#include "/kungfu/class/fameng/yidai.h"
inherit F_MASTER;

void create()
{
        set_name("温梦成",({"wen mengcheng","wen"}));
	set("nickname",HIR"温府"HIW"---"HIG"大首领"NOR);
	set("gender","男性");
	set("int",30);	
	set("con",30);
	set("str",30);
	set("dex",30);
	set("bac",40);
	set("age",40);
	set("attitude","friendly");
	set("shen_type",1);
	set("combat_exp",800000);
	set("score",1000);
	set("long",
	"他出身于温家，由于不满当今朝廷奸臣当道，于是\n建立了温宅，与花枯发一起组建了发梦二党，吸纳有志之士。\n"
	"可是由于与花枯发的关系一直不好，两派势力不能联合。\n所以，发梦二党在京城名气不大。\n"
	);
	set("neili",2000);
	set("jingli",1000);
	set("max_neili",2000);
	set("max_jingli",1000);
         set_skill("literate",180);
        set_skill("cuff",250);
          set_skill("parry",250);
         set_skill("dodge",250);
             set_skill("force",350);
             set_skill("bairen-shengong",350);
             set_skill("tao",350);
             set_skill("yiye-zhiqiu",250);
             set_skill("fengye-xiangsi",250);
	map_skill("force","bairen-shengong");
        map_skill("cuff","yiye-zhiqiu");
        map_skill("parry","yiye-zhiqiu");
        map_skill("dodge","fengye-xiangsi");
        prepare_skill("cuff","yiye-zhiqiu");

        create_family("发梦二党",1,"梦党首领");
	setup();
	carry_object("/clone/misc/cloth")->wear();
        set("chat_chance", 4);
	set("chat_msg", ({
		(: exert_function, "recover" :),
		(: exert_function, "heal" :),
	}));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}) );
}

