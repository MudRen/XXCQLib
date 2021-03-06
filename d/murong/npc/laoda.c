// laoda.c

inherit NPC;
#include <ansi.h>
int ask_price();        
int ask_hire();
void create()
{
	set_name("船老大", ({ "laoda" , "chuanlaoda" }) );
	set("long", "他正等着跟你商量雇船的事情。\n");
	set("gender", "男性" );
	set("age", 42);
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "老大");
	set("inquiry", ([
		"name": "我是这里的船老大，客官们想游太湖都是老大我伺候着。",
		"rumors": "这太湖里可是藏龙卧虎之地，大名鼎鼎的姑苏慕容和归云庄都在太湖里面。",
		"here": "这里是附近唯一的码头了。",
		"雇船": (: ask_hire :),
		"价钱" : (: ask_price :),
	]) );
	setup();
}                                      

int ask_hire()
{
	command("say 客官您要去哪里啊？不瞒您说，太湖里的水陆就是我最熟悉。您要是真想去，"+BLINK HIW+"价钱"+CYN+"好商量。");
	return 1;
}
int ask_price()
{
	object ob=this_player();
	int money = 5000;

	if (ob->query("age") < 16)
		money = (ob->query("age") - 13) * 500;
	if ((ob->query("family/family_name") == "姑苏慕容" 
	||  ob->query("family/family_name") == "桃花岛")) 
	{
		say ("船老大说道：算我交个朋友，这次分文不取，客官您上船吧。\n");
		command("say 好了您哪。\n");                                
		message_vision("船老大叫过来一个艄公，带着$N一同上了小舟。\n", ob);		
		ob->move("/d/murong/xiaozhou1");                  
	}
		 
	else 
	{
		say("船老大似笑非笑地说道：我看客官面善，就收您" + MONEY_D->price_str(money) + "吧。\n" );
		command("hehe laoda");
		ob->set_temp("ask_price", 1);
	}
	return 1;
}
int accept_object(object who, object ob)
{
	int money = 5000;

	if (who->query("age") < 16)
		money = (who->query("age") - 13) * 500;
	if ( !who->query_temp("ask_price") 
	&& (who->query("family/family_name") != "姑苏慕容"
	||  who->query("family/family_name") != "桃花岛" )) 
	{
		command("say 船老大乐了，说道：您老是有钱没处花么？\n");
		return 1;
	}		
	if (!ob->query("money_id") || ob->value() < money)  
	{
		command("say 就给这么点钱，喝西北风都不够。\n");
		return 1;
	}
	command("say 船老大说道：好了您哪。\n"); 
	message_vision("船老大叫过来一个艄公，带着$N一同上了小舟。\n", who);
	who->delete_temp("ask_price");
	who->move("/d/murong/xiaozhou1");                  
	return 1;
}