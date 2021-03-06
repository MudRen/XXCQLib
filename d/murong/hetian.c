// hetian.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", GRN"荷田"NOR);
	set("long",
"圆圆的一个大湖泊, 看得见湖中央有几个"GRN"小岛"NOR"。小岛上似乎有些小
黑点在移动。不知道是什么水鸟儿，野鸭? 湖边的浅滩上有棵"HIM"毛桃树"NOR"(tree), 浅滩的
不远处就是一大片绿油油的"GRN"荷田"NOR".你真想撑船过去瞧一瞧。\n"
);
	set("no_clean_up", 0);
	set("item_desc", ([
"tree" :("一棵碗口粗的桃树, 树上有好多的毛桃(tao), 你试试看能不能爬(climb)上去。\n"),
"boat":("一只在水边摇摇晃晃的船儿，你有点想跳(jump)上去。\n"),
"tao":(HIM"已经熟透了的桃儿，就快从树上落下来了。\n"NOR),
]));

	setup();
}

void init()
{
	add_action("do_climb", "climb");
	add_action("do_jump","jump");
}       

int do_jump(string arg)
{
	if(!arg||arg!="boat")
		return notify_fail("别瞎跳，小心掉进水里了。\n");
	message_vision("$N轻轻的解开绳子，一纵身往船头跳去。\n", this_player());
	this_player()->move(__DIR__"boat1");
	message_vision(BLU"$N费了好大劲才稳住身子. 你吓得赶紧蹲了下来.\n"NOR, this_player());
	return 1;
}

int do_climb(string arg)
{
	object ob, me;
	me = this_player();
	if (!arg|| arg!="tree")
		return notify_fail("你要往哪里爬?\n");

	switch(random(6))
	{
		case 0: 
		case 1:
		case 2:
		message_vision(HIR"$N一下用力过猛, 啪的一声一根树枝断了, 你从树上跌了下来.\n"NOR,me);
		break;
		case 3:
		case 4:
		message_vision(HIR"$N一不小心把手挂破了皮, 赶紧跳了下来.\n"NOR,me);
		break;
		case 5:
		message_vision(HIG"$N费了九牛二虎之力终于摘到了一颗"HIM"红红润润的毛桃.\n"NOR,me);
                ob=new("/u/ievolo/food/maotao");
		ob->move(this_player());
		break;
}
return 1;
}
