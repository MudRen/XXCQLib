// Room: /city/kefang.c
// YZC 1995/12/04 
#define TIME1 10
#define TIME2 15

inherit ROOM;

void create()
{
	set("short", "马车内");
	set("long", @LONG
你现在在一辆乌蓬马车内，车内铺有一层厚厚的被子，路途还很遥远，
你可以休息一会。车角挂的铃铛被风儿吹得“叮叮”的响着... ...
LONG
	);
	setup();
}

void init()
{
	if(!query("back_flag"))
	{
		call_out("do_go_back",TIME1+TIME2+5);
		set("back_flag",1);
	}
	add_action("do_quit", "quit");
	add_action("do_lian", "dazuo");
	add_action("do_lian", "exercise");
	add_action("do_lian", "tuna");
	add_action("do_lian", "zhoutian");
	add_action("do_lian", "du");
	add_action("do_lian", "learn");
	add_action("do_lian", "xue");
	add_action("do_fight", "fight");
	add_action("do_fight", "kill");
	add_action("do_steal", "steal");
}

int do_go_back()
{
	int i;
	object *inv;
	inv=all_inventory(this_object());
	if(!query("back_flag"))
		return 0;
	message("vision","你往车外一看，咦？！！不是你要去的地方呀！\n"+
		"马夫一脸愧色地说：“你要去的地方去不了，我只有把你送回这儿来了。”\n\n",this_object());
	for(i=0;i<sizeof(inv);i++)
	{
		if(inv[i]->is_character())
		{
			if(!inv[i]->move(inv[i]->query_temp("mache_start")))
				inv[i]->move(inv[i]->query("startroom"));
		}
	}
	this_object()->delete("back_flag");
	return 1;
}
			
int do_quit()
{
	object me;
	me = this_player();
	message("vision", "你在车里,现在不能退出!请稍候.\n", me );
	return 1;
}

int do_lian()
{
	object me;
	me = this_player();
	message("vision", "马车颠簸,练功恐怕会岔了内息,小心走火入魔!\n", me );
	return 1;
}

int do_fight()
{
	object me;
	me = this_player();
	message("vision", "马车里打架?小心摔下去!\n", me );
	return 1;
}

int do_steal()
{
	object me;
	me = this_player();
	message("vision", "马车里行窃?不好吧?\n", me );
	return 1;
}
