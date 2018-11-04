// qi.c 戚恋霞


inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void create()
{
    set_name("门卫", ({ "men wei", "wei" }));
    set("gender", "男性");
	set("age", 23);
        create_party(HIG"发梦二党"NOR,HIM"护院"NOR,2);
        set("rank","党羽");

	set("combat_exp", 60000);
        set_skill("tao",50);
        set_skill("parry",50);
        set_skill("cuff",50 );
        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("bairen-shengong",50);
        
        map_skill("force","bairen-shengong");
	
        create_family("发梦二党",4,"弟子");
	setup();
	carry_object("/clone/misc/cloth")->wear();
    carry_object("/clone/weapon/gangdao")->wield();
}

void die()
{
        message_vision("$N惨嚎一声，死了！\n", this_object());
        destruct(this_object());
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
/*
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
*/
                command("smile");
                command("handshake "+this_player()->query("id"));
                command("nodjoin "+this_player()->query("id"));
                command("tell "+this_player()->query("id")+" 大家从此就是一家人了。\n");
        return;
}

