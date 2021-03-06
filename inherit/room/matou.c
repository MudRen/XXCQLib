// bank.c

inherit ROOM;

void init()
{
	add_action("do_gu", "gu");
	add_action("do_qu", "qu");
}

void check_trigger(object me)
{
	object room;
	if( !(room = find_object("/clone/room/chuan")) )
		room = load_object("/clone/room/chuan");
	if( room = find_object("/clone/room/chuan") )
	{
		if((int)room->query("chuan_trigger")==0 )
		{
			message_vision("一个中年汉子从船篷里钻了出了，上上下下打量着$N。\n", me);
			message_vision("汉子道：“客官去哪呀(type qu XX)？我们可只能去浣花(hh)和秭归(zg)两个码头。”\n\n", me);
			me->set_temp("guchuan", 1);
		}
		else
		message_vision("可是敲了半天却没有人出来，看来主人是出去了。\n", me);
        }
        else
            message("vision", "ERROR: chuan not found\n", this_object() );
}

int do_gu(string arg)
{
	object me;
	me = this_player();

	if(!arg || arg != "chuan")
		return notify_fail("你要雇什么？这里只有乌篷船(chuan)可以雇。\n");
	
	message_vision("$N敲了敲一艘停在码头的乌篷船的篷子，喊道：“有人吗？雇船！”\n", me);
        check_trigger(me);
        return 1;
}

int do_qu(string arg, int num)
{
	object room, me;
	me = this_player();

	if (!me->query_temp("guchuan"))
		return notify_fail("根本没有人理你，你觉得自己真傻。\n");

	if (!arg)
		return notify_fail("你倒是说去哪呀！\n");

	if( !(room = find_object("/clone/room/chuan")) )
		room = load_object("/clone/room/chuan");
	if( room = find_object("/clone/room/chuan") )
	{
		if ( arg == "huanhua" || arg == "hh" )
		{
			message_vision("汉子让$N上了船，高喊一声：“坐好，开船去浣花罗！”\n\n", me);
			me->set_temp("chuan", "huanhua");
		}
		else if ( arg == "zigui" || arg == "zg" )
		{
			message_vision("汉子让$N上了船，高喊一声：“坐好，开船去秭归罗！”\n\n", me);
			me->set_temp("chuan", "zigui");
		}
		else
		{
			message_vision("大汉抱歉的笑了笑道：现在水路只通浣花(hh)和秭归(zg)，真抱歉。\n", me);
			return 1;
		}
		message_vision("不一会，船就摇啊摇的划了起来。\n\n", me);
		call_out("arrived", 25, me);
		me->move("/clone/room/chuan");
		room->set("chuan_trigger", 1);
		return 1;
	}
}

int arrived(object me)
{
	object room;
	if( room = find_object("/clone/room/chuan") )
	{
		if (me->query_temp("chuan") == "huanhua")
		{
			me->move("/d/huayang/hhmatou");
		}
		else if (me->query_temp("chuan") == "zigui")
		{
			me->move("/d/xiangyang/zgmatou");
		}
		me->delete_temp("chuan");
		me->delete_temp("guchuan");
		message_vision("\n乌篷船渐渐停了下来，船夫高叫一声：到了！\n\n", me);
		message_vision("船慢慢的靠岸，$N从上面走了下来。\n\n", me);
	        room->delete("chuan_trigger"); 
		return 1;
	}
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object("/clone/room/chuan") )
        room->delete("chuan_trigger"); 
}
