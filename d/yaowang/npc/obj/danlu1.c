// Room: 汴梁药局
// By 山猫adx @ 宁波小雪 17:00 99-10-26

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(CYN"炼丹炉"NOR, ({ "liandan lu", "liandan", "lu" }) );
        set_weight(300000);
        set_max_encumbrance(50000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是一个青铜铸成的炼丹炉。\n");
                set("value", 1000);
                set("no_get",1);
                set("amount",10);
		set("container",1);
        }
        setup();
}

void init()
{
       add_action("do_fang", "fang");
	add_action("do_lian", "liandan");
	add_action("do_ran", "ran");
}

int do_fang(string arg)
{
	object me, ob;
	me = this_player();

	if(me->query("party/party_name")!=HIB"药王谷"NOR
		&& (int)me->query_skill("healing",1)<60 ) {
		return notify_fail("你还不能在这里炼丹！\n");
	}

	if(me->query("shen")<0) {
		return notify_fail("你应当到东边的炼丹房去炼丹！\n");
	}

	if(!arg || !ob=present(arg, me))
		return notify_fail("你要把什么放进炼丹炉中\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        message_vision(YEL"\n$N把一"+ob->query("unit")+ob->query("name")
		+"放进炼丹炉中\n\n"NOR, me);

	destruct(ob);
	ob->move(this_object());
	return 1;
}

int do_lian(string arg)
{
        object ob1, ob2, ob3, ob4, ob5;
	object me, ob, obj;
	me=this_player();
	ob=this_object();

	if(me->query("party/party_name")!=HIB"药王谷"NOR
		&& me->query("party/level")<4 ) {
		return notify_fail("你还不能在这里炼丹！\n");
	}

	if(me->query("shen")<0) {
		return notify_fail("你应当到东边的炼丹房去炼丹！\n");
	}

        if( !arg && ((arg!="bigu wan") || (arg!="zaohua dan")) )
		return notify_fail("指令格式：liandan <丹药ID> \n"
		"        可以练的丹药有： 碧谷丸(bigu wan)\n"
		"                         造化丹(zaohua dan)\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if( !me->query_temp("liandan") )
                return notify_fail("丹炉还没有点燃，怎么炼丹！\n");

	if( objectp(ob1=present("lu xue",ob))
		&& objectp(ob2=present("lu rong",ob))
		&& objectp(ob3=present("xiong dan",ob))
		&& objectp(ob4=present("xiong zhang",ob))
		&& objectp(ob5=present("she dan",ob)) ) {
                        destruct(ob1);
                        destruct(ob2);
                        destruct(ob3);
                        destruct(ob4);
                        destruct(ob5);
		if(arg=="bigu wan") { obj=new(__DIR__"biguwan"); }
		if(arg=="zaohua dan") { obj=new(__DIR__"zaohuadan"); }
	message_vision(HIR"$N关上丹炉的炉门，催动火力开始炼丹。\n\n"NOR, me);
	message_vision(HIR"一会儿炉膛内的火焰渐渐熄灭。\n\n"NOR, me);
	message_vision(HIR"丹药练成了。\n"NOR, me);
	message_vision(HIR"炉火渐渐熄灭了！\n"NOR, me);
	me->improve_skill("healing", ((int)me->query_skill("healing",1)/2));
		obj->move(ob);
		me->delete_temp("liandan");
		return 1;
                }
	else
	return notify_fail("可是药材还没准备齐呀！\n");
}

int do_ran(string arg)
{
	object me;
	me=this_player();

	if(me->query("party/party_name")!=HIB"药王谷"NOR
		|| me->query("party/level")<4
		|| me->query("shen")<0 ) {
		return notify_fail("不许乱碰这里的东西！\n");
	}

        if( me->query_temp("liandan") )
                return notify_fail("丹炉的火已经很旺了，快开始炼丹吧！\n");

	me->set_temp("liandan",1);
	message_vision(HIR"$N拿起火折塞进炉膛，把丹炉点燃。\n"NOR, this_player());
	return 1;
}
