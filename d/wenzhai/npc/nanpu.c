// nanpu.c

inherit NPC;
#include <ansi.h>

int serve_me(object who);
void create()
{
        set_name("男仆", ({ "nan pu", "pu" }));
        set("gender", "男性");
        set("age", 25);

        set("combat_exp", 4000);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_temp("apply/attack",  10);
        set_temp("apply/defense", 10);
         set("food",5);
        setup();

        set("inquiry", ([
                "吃饭" : (: serve_me :),
                "用餐" : (: serve_me :),
	]) );
        add_money("silver",3);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
        object ob;

        ::init();
	
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

	say("男仆笑眯眯的说道：“这位" + RANK_D->query_respect(ob)
	     + "想要吃点什么东西，就知会我一声。”\n");
}


int serve_me(object who)
{
        object ob;
        object room;

        if( !who || environment(who) != environment() ) return 0;

        if( !objectp(room = environment()) ) return 0;

          if (query("food")>0) {
        ob = new("/d/wenzhai/obj/longjing");
        ob->move(room);
        message_vision("男仆端来一壶龙井茶。\n",who);

        ob = new("/d/wenzhai/obj/niqiu");
        ob->move(room);
        message_vision("男仆将一碟刚出锅的干鞭泥鳅放在桌上。\n", who);
       add("food",-1);
       }
       else
		message_vision("男仆在内厅歉声应道: 嗨，吃的喝的都没了。\n",who);
		
        return 1;
}
