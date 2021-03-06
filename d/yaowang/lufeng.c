// NPC 掌柜
// By 山猫Adx 16:53 99-10-25

#include <ansi.h>
inherit NPC;

int ask_me();
int ask_ok();

void create()
{
	set_name("陆风", ({ "lu feng", "lu", "feng" }) );
	set("title", HIB"药王谷"NOR+WHT"管事"NOR);
	set("long", "他在药王谷负责掌管打理药田。\n" );
	set("gender", "男性" );
	set("age", 52);
	set("combat_exp", 100);
	set("attitude", "friendly");

        set("inquiry", ([
		"job" : (: ask_me :),
		"ok" : (: ask_ok :),
        ]));

	setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
	object ob = this_player();

	::init();
	if( interactive(ob) && !is_fighting() )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

int greeting(object ob)
{
	int i=(ob->query("eff_qi")*100)/ob->query("max_qi");
	if((string)ob->query("party/party_name")==HIB"药王谷"NOR) {
		command("say 这位兄弟辛苦了，快请进！\n");
		return 1;}

	if (i<=90) {
		command("wa "+ob->query("id"));
		command("say "+RANK_D->query_respect(ob)
			+"，你受了重伤啊！快去回春堂让医师给你看看吧！\n");
		return 1;}
	else {
	switch( random(4) ) {
		case 0:
			command("bow "+ob->query("id"));
			break;
		case 1:
			command("nod "+ob->query("id"));
			break;
		case 2:
			command("hi "+ob->query("id"));
			break;
		case 3:
			command("welcome "+ob->query("id"));
			break;
		}
	}
}

int ask_me()
{
	object ob, me;
	me = this_player();

	if( me->query("party/party_name")!=HIB"药王谷"NOR ) {
		command("say 你不是这里的伙计，这种活怎么能让你干呢？\n");
		return 1; }

	if( (int)me->query_skill("healing",1)<20 ) {
		command("say 你还不能在这里干活！\n");
		return 1; }

	if( (int)me->query_skill("healing",1)>=40 ) {
		command("say 你不需要干这种活的！\n");
		return 1; }

	if ( !me->query_temp("renwu_name1") ) {
		ob = new(__DIR__"obj/tong");
		ob->move(me);
		me->set_temp("renwu_name1",1);
		message_vision(YEL"陆风给了$N一个水桶。\n"NOR, me);
		command("say 你打桶水把药田都浇好！\n");
		return 1;
	}
	else {
		command("say 你先把活干完吧！\n");
		return 1;
	}
}

int ask_ok()
{
	object money, me;
	int amount,i;
	i=random(3);
	me = this_player();
	amount = random(30);
	if ( me->query_temp("renwu_wancheng")==100 ) {
		me->delete_temp("renwu_wancheng");
		me->delete_temp("renwu_name1");
		if ( present("tong", me) ) {
			message_vision ("$N放下手中的水桶。\n", me);
			destruct(present("tong", me));
        	        money = new ("/clone/money/silver");
                	money->move(me);
			money->set_amount(amount);
			command("say 好！干得不错，这是赏你的！\n");
			if(i=1) {me->add("max_jingli",1);}
		} else { 
			command("hmm "+me->query("id"));
			command("say 真没用，让你干活，你把工具都丢了！\n");
			}
	} else {
		command("say 你赶快去把活干完啊！\n");
		}
        return 1;
}
