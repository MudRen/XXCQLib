// huoji. 药铺伙计

inherit NPC;

void kai(object me, int a, int b, int c, int vager, object mtype);

void create()
{
	set_name("司徒通", ({ "situ tong", "situ", "tong"}));
	set("str", 35);
	set("gender", "男性");
	set("title", "得意赌坊老板");
	set("age", 35);
	set("long", "他是一个满脸大胡子的中年男子，虽然现在是满脸笑容，但你欠他钱的时候……。\n");
	set("combat_exp", 250);
	set("attitude", "friendly");

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

        add_action("do_gamble", "gamble");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	say( "司徒通满脸堆笑的对你说：这位" + RANK_D->query_respect(ob)
				+ "来玩两把吧，包赢！\n");
}

int do_gamble(string arg)
{
	int a,b,c;
	int wager;
	string wtype2, wtype0, sb;
	object mtype, me;
	int min, max;
	min = 100;
	max = 100000;

	me = this_player();

	if (!arg || sscanf(arg, "%s %d %s", wtype0, wager, wtype2) !=3)
		return notify_fail("赌博的命令格式是：gamble big|small <amount> <type>\n"
		"比如：押十两银子“大”的命令格式为　gamble big 10 silver。\n");

	mtype = present(wtype2 + "_money", me);

	if (this_object()->query("doing"))
		return notify_fail("你没看到他们正赌着呢嘛！\n");

	if (!mtype)
		return notify_fail("你身上没有这种货币。\n");

	if ((int)mtype->query_amount() < wager)
		return notify_fail("司徒通瞪了你一眼道：没这么多"
		+ mtype->query("name") + "也敢押，怎么，想诈赌？\n");

	if( wager*(mtype->query("base_value")) < min ||	wager*(mtype->query("base_value")) > max )
		return notify_fail("司徒通抱歉的笑了笑：小坊只能押一两银子到十两金子，您多多包涵。\n");

	if ( (wtype0 != "big") && (wtype0 != "small") )
		return notify_fail("你要赌大还是赌小?\n");

	a = random(6) + 1;
	b = random(6) + 1;
	c = random(6) + 1;

        if ( ( (a == b) && (b == c) ) ||
             ( (a+b+c) > 10 && (wtype0 == "small") ) ||
             ( (a+b+c) < 11 && (wtype0 == "big") ) )
		me->set_temp("status", 1);

	if (wtype0=="small") sb = "小";
	else sb = "大";

	message_vision("“好！”见到有人在桌上押了钱，司徒通突然叫到，“" + me->query("name")
		+ chinese_number(wager) + mtype->query("base_unit") + mtype->query("name")
		+ "押" + sb + "！！！\n", me);
	message_vision("司徒通将手中摇晃的骰筒突然的往桌子上一扣，“啪”！\n", me);
	message_vision("全场都摒住了呼吸，唯一听到的是三粒骰子在骰筒中来回的撞击声。\n", me);
	this_object()->set("doing",1);
	call_out("kai", 5, me, a, b, c, wager, mtype);
        return 1;
}

void kai(object me, int a, int b, int c, int wager, object mtype)
{
	string str;

	message_vision("\n等骰筒内渐渐没了声音，司徒通长长的一声：“开～～～！”，将骰筒提了起来。\n", me);

	if ((a == b) && (b == c)) str = "大小通杀";
	else if ((a+b+c) > 10 ) str = "吃小赔大";
	else if ((a+b+c) < 11 ) str = "吃大赔小";

	message_vision("扫一眼骰子，司徒通即道：“开" + chinese_number(a) + "、" + chinese_number(b) + "、" + chinese_number(c) + "，" + str + "！”\n", me);

        if ( me->query_temp("status"))
	{
        	message_vision("司徒通拍了拍你的肩膀道：“输了" + chinese_number(wager) +
			mtype->query("base_unit") + mtype->query("name") + "没关系，下次一定会赢！”\n\n", me);
                mtype->set_amount((int)mtype->query_amount() - wager);
                mtype->move(me);
	}
	else
	{
		message_vision("司徒通朝$N一拱手道：“恭喜恭喜，赢了" + chinese_number(wager) +
			mtype->query("base_unit") + mtype->query("name") + "，还不乘胜追击？”\n\n", me);
		mtype->set_amount((int)mtype->query_amount() + wager);
		mtype->move(me);
	}
	me->delete_temp("status");
	this_object()->delete("doing");
	return;
}