// xian. 冼老板

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("胡老板", ({ "hu laoban", "hu" }));
	set("title", "叁合楼老板");
	set("shen_type", 1);

	set("str", 20);
	set("gender", "男性");
	set("age", 45);
	set("long", "胡老板是个懂得和气生财得中年人，经营叁合楼已有二十余年。\n");
	set("combat_exp", 50000);
        set("qi", 300);
        set("max_qi", 300);
	set("attitude", "friendly");
	set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
	setup();
        add_money("gold", 1);
	carry_object("clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_invite", "yaoqing");
        add_action("do_jieshu", "jieshu");
        add_action("do_answer", "answer");
}

int do_invite(string arg)
{
	object me, ob;
	me = this_player();

        if( !me->query_temp("marks/主人") ) return 0;

	if( !arg ) return notify_fail("指令格式：yaoqing <ID> \n");

	if( !ob ) ob = find_living(arg);

	if (!ob) return notify_fail("现在没这个人。\n");

	if (ob==me) return notify_fail("邀请自己，不用吧？\n");

	if(ob->query_temp("marks/赴宴"))
		return notify_fail("他已经被邀请了！\n");

	ob->set_temp("marks/赴宴",1);
	write(HIG "你邀请"+ob->name(1)+"参加你在汴梁叁合楼的宴会。\n"NOR);
	tell_object(ob, sprintf(BLINK HIG"%s邀请你参加在汴梁叁合楼的庆贺"+
		me->query_temp("marks/内容")+"宴会。\n"NOR, me->name(1)));
	return 1;
}

int do_answer()
{
	object me,item;
	string msg;
        me = this_player();
	msg = me->query("name")+"在汴梁叁合楼举办庆贺"+me->query_temp("marks/内容")+"宴会开始了！\n";

        if(me->query_temp("marks/主人")) {
		if( present("table", (environment(me))) ) {
			command("say 现在酒席正在进行中你稍等一下！");
			return 1; }
        message("channel:chat",BLINK HIG+"【通告】"+msg+NOR, users() );
        command("say 好吧，现在开席，祝大家吃个饱吃个好，一醉方休才得归！");
        command("haha ");
        command("say 小二，上菜！");
        message_vision("店小二不一会儿就端着热气腾腾的山珍海味上到了诺大的圆桌(table)上。\n",me);
	me->set_temp("marks/开始",1);
	item = new(__DIR__"table");
        item->move(environment(me));
        return 1;
	}
        else return 0;
}       

int do_jieshu()
{
	object me;
	string msg;
	me = this_player();
	msg = me->query("name")+"在汴梁叁合楼举办庆贺"+me->query_temp("marks/内容")+"宴会结束了！\n";

	if(!me->query_temp("marks/开始")) return 0;

        if(me->query_temp("marks/主人")) {
	message("channel:chat",BLINK HIG+"【通告】"+msg+NOR, users() );
		command("say 好吧，宴会结束，欢迎下次再来光顾！");
		command("ok ");
		command("say 小二，收拾一下！");
		message_vision("店小二跑了过来把酒席收拾了。\n",me);
		me->delete_temp("marks/主人");
		me->delete_temp("marks/坐");
		me->delete_temp("marks/赴宴");
		me->delete_temp("marks/内容");
		me->delete_temp("marks/开始");
		destruct( present("table", (environment(me))) );
		return 1;
	}
        else return 0;
}       
