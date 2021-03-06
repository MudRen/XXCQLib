// huakufa.c 花枯发
// made by lks

#include <ansi.h>
int ask_ye();
#include "/d/huafu/npc/cam.h"

inherit NPC;
inherit F_MASTER;
#include "/kungfu/class/fameng/yidai.h"
void heal_ob();
void recover_ob();

void create()
{
        set_name("花枯发",({"hua kufa","hua"}));
        set("nickname",HIG"花府"HIW"---"HIR"大当家"NOR);
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
	"他就是花府大首领---花枯发。\n虽然他和温梦成常闹别扭，可是一旦发生什么事，他们还是一致对外的。"
	);
	set("neili",2000);
	set("jingli",1000);
	set("max_neili",2000);
	set("max_jingli",1000);
           set_skill("literate",280);
           set_skill("cuff",350);
           set_skill("dodge",350);
           set_skill("force",250);
           set_skill("bairen-shengong",250);
           set_skill("tao",350);
         set_skill("fengye-xiangsi",350);
           set_skill("parry",350);
           set_skill("throwing",350);
        set_skill("yiye-zhiqiu",250);
             map_skill("force","bairen-shengong");
             map_skill("dodge","fengye-xiangsi");
	map_skill("cuff","yiye-zhiqiu");
        prepare_skill("cuff","yiye-zhiqiu");
	
       create_family("发梦二党",1,"开山祖师");
	setup();
	carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/huafu/npc/obj/yeziye");
        carry_object("/d/huafu/npc/obj/bajiaoye");
         set("chat_chance", 1);
	set("chat_msg", ({
		"花枯发焦急地看了看天色：卧室的钥匙不知道掉哪去了？\n",
		"花枯发一脸的哭丧相：今天我可到哪去睡觉啊。\n",
		(: heal_ob :),
	}));
                set("inquiry",([
                        "暗器" : (: ask_ye :),
                        "yezi" : (: ask_ye :),
                ]));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
                (: perform_action, "cuff.kuangfeng" :),
                (: recover_ob :),
	}) );
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

int ask_ye()
{
        object ob,me;
        mapping fam;
        
        me=this_player();
        fam=(mapping)me->query("family");
        
        if (!fam || (fam["family_name"]!="发梦二党"))
        {
                command("say 你不是本党嫡系弟子，要来做啥？");
                return 1;
        }

        if (query("gived"))
        {
              command("say 叶子已经送人了。");
              return 1;
        }

         if (fam && (fam["generation"]>3))
        {
                command("say 这么重要的东西我只能给我相信的弟子,你的辈分还不够。");
                return 1;
        }
        
        if (me->query("shen")< 1000)
        {
                command("shake");
                command("say 你的正气太低了，我不放心交给你。");
                return 1;
        }                
        command("smile "+me->query("id"));
        command("say 好吧，我把为一叶知秋特制的叶子给你，\n它将会大大增强一叶知秋的杀伤力。");
        ob=new("/d/huafu/npc/obj/bajiaoye");
        ob->move(me);
        ob=new("/d/huafu/npc/obj/yeziye");
        ob->move(me);
           set("gived",1);
        return 1;
}

