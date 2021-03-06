// luo.c 洛五霞
#include <ansi.h>
#include "/d/huafu/npc/cam.h"
inherit NPC;
inherit F_MASTER;
#include "/d/huafu/npc/luo.h"
int ask_kungfu();

void create()
{
	set_name("洛五霞", ({ "luo wuxia", "luo" }));
	set("nickname",HIY"丈八剑"NOR);
         set("rank","党羽");
	set("gender", "男性");
	set("age", 33);

	set("combat_exp", 1200000);
        set("max_neili",4000);
        set("neili",4000);
        set("max_qi",4000);
        set("eff_qi",4000);
        set("qi",4000);
        set("max_jingli",4000);
        set("eff_jingli",4000);
        set("jingli",4000);

        set_skill("cuff",100 );
        set_skill("confu",200);
        set_skill("force", 180);
        set_skill("dodge", 200);
                 set_skill("chixin-jian",350);
                 set_skill("sword",350);
        set_skill("bairen-shengong",180);

        map_skill("force","bairen-shengong");
	map_skill("sword","chixin-jian");
       create_party(HIG"发梦二党"NOR,HIW"护法"NOR,6);
	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
            set("inquiry",([
                    "痴心情长剑" : (: ask_kungfu :),
                    "学艺" : (: ask_kungfu1 :),
                    "sword" : (: ask_kungfu2 :),
                    "剑法" : (: ask_kungfu2 :),
                    "绝招" : (: ask_kungfu :),
            ]));
          set("chat_chance",2);
          set("chat_msg",({
              (: exert_function,"heal" :),
              (: exert_function,"heal" :),
          }));
          set("chat_chance_combat",30);
          set("chat_msg_combat",({
              (: perform_action,"sword.kuhai" :),
              (: exert_function,"recover" :),
          }));

          carry_object("/clone/misc/cloth")->wear();
          carry_object("/clone/weapon/changjian")->wield();
}

void attempt_join()
{
        object ob;
        object mee;
        
        ob = this_player () ;
        mee=this_object();
        if ((int)ob->query("shen") < 0)
        {
        message_vision(HIC "$n对$N大怒道：一看你就不是好人!\n" NOR,ob,mee);
//      set_leader(this_player());
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, this_player()); 
        return;
        }
        if ((int)ob->query("shen") < 1000)
        {
        message_vision(HIC "$N摇摇头道：你还不够侠义!\n" NOR,mee);
        return;
        }
        if (ob->query("combat_exp")<10000)
        {
        message_vision(HIC "$n对$N摇头道：你的实战经验太低。\n" NOR,ob,mee);
        return;
        }
                command("smile");
                command("handshake "+this_player()->query("id"));
                command("nodjoin "+this_player()->query("id"));
                command("tell "+this_player()->query("id")+" 大家从此就是一家人了。\n");
        return;
}

