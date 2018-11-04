// chanting.c 餐厅
// mlf设计,lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","餐厅");
        set("long",
"这里是花府的餐厅，由于花府的主人讲究饮食，所以弟子的伙食也不
错，一个胖厨师正在烧菜做饭，只要叫一声(chifan)佣人就会送上可口的
饭菜。\n"
	);
	set("valid_startroom",1);
	set("no_fight",1);
	set("exits",([
		"north" : __DIR__"liangong2",
		"east" : __DIR__"caifang",
	]));
	setup();
}

void init()
{
	add_action("do_chifan","chifan");
}

int do_chifan()
{
	object ob=this_player();
	int shiwu,yinshui;
	shiwu = ob->max_food_capacity();
        yinshui = ob->max_water_capacity();
        
        ob->set("food", shiwu);
        ob->set("water", yinshui);
        
        message_vision("$N拍了拍肚子，打了个饱嗝。\n",ob);
        return 1;
}
