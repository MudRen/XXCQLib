// jieyinshi.c 接客童子
// netkill 1998/9/4

#include <ansi.h>
inherit NPC;
int panchan();

string ask_me(string name);

void create()
{
        set_name("接客童子", ({ "tong zi", "tong" }));
        set("long", "这是一位专门接待新玩家的童子\n");
        set("gender", "男性");
        set("age", 18);

        set("shen_type", 1);
         set("inquiry", ([
		"盘缠" :   (: panchan :),
		"食物" :   (: ask_me, "jitui" :),
		"水" :   (: ask_me, "jiudai" :),
        ]) );
        setup();

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
                say("童子说道：如果你没有盘缠的话，可以问我要"+HIW"(ask tong about 盘缠)"NOR+"。\n");
                say("           如果你没有吃的，可以问我要"+HIW"(ask tong about 食物)"NOR+"。\n");
                say("           如果你没有水，可以问我要"+HIW"(ask tong about 水)"NOR+"。\n");
}

int panchan()
{
	object ob,me=this_player();
        int i=me->query_temp("silver");
        if  ( i < 10 )
        {
        ob=new("/clone/money/silver");
        ob->move(me);
        message_vision("接客童子给$N一些白银。\n",me);
        i=i+1;
        me->set_temp("silver", i);
        }
        else return 0;
        return 1;
}

string ask_me(string name)
{
	object ob;

	if (  present(name, this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"你先把身上的吃了（chi jitui）再向我要。\n"+
		"你可以到有水的地方装水（zhuang jiudai）\n";

	ob = new(__DIR__"obj/" + name);
	ob->move(this_player());

	message_vision(YEL"接客童子给$N一个" + ob->query("name") + "。\n"NOR, this_player());

	return "给。";
}
