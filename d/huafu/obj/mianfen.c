// mianfen.c

inherit ITEM;

void create()
{
	set_name("面粉", ({"mianfen"}));
	set_weight(40);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一团白花花的面粉。\n");
		set("unit", "团");
		set("value", 40);
	}
}

void init()
{
         add_action("do_bann","ban");
}

int do_bann(string arg)
{
        object me;
        object ob;
        me=this_player();
        if ( (arg!="面粉") && (arg!="mianfen") )
                return 0;
        if ( !ob=present("mianfen",me) )
                return notify_fail("你要把高粱和哪种东西拌在一起？\n");
        if ( !me->query_temp("do-mo") )
                return notify_fail("你还没把高粱磨碎呢。\n");
        message_vision("$N将磨碎的高粱和面粉掺拌在一起，搅拌均匀。\n",me);
        ob=new("/d/huafu/obj/gaoliangfan");
        ob->move(me);
        me->delete_temp("do-mo");
                        me->add("jingli",-10);
        destruct(this_object());
        return 1;
}

