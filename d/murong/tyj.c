// tingyuju.c

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short",BLU"听雨居"NOR);
         set("long",
"「"WHT"听雨居"NOR"」三面环水, 从窗中望出去, 湖上烟波尽收眼底。屋正中摆着\n"
"一张大圆桌, 上面摆满了蔬果点心, 每一样都十分精致。 圆桌四周放了数\n"
"把椅子。墙边的小柜上放着一把「"BLINK HIB"琴"NOR"」。\n"
);        
         set("item_desc",([
             "floor" : "古琴旁边的地面不是十分平整。\n",
             "qin" : "这是一把古琴，弹一曲会使人心旷神怡。\n",
]));
         set("exits",([
		"east" : __DIR__"xs",
])); 
	 setup();
}                

void init()
{
	add_action("do_tan", "play");
	add_action("do_tan", "press");
        add_action("do_tan", "tan");
}

int do_tan(string arg)
{
	int i, j;
        object me, boat;
     	me = this_player();
     	boat = find_object(__DIR__"boat");
        i = 20+random(20);
        j = 20+random(20);
        if (!living(me))  return 0;
        if (arg !="qin" || !arg || arg == "") 
		return notify_fail("你要弹什么？\n");


        if( arg=="qin")
        {
	        if(!(boat=find_object(__DIR__"boat")))
	             boat=load_object(__DIR__"boat");
	        if(boat->query_temp("busy"))
	        {
	             	write("你弹了一下琴，发出了悦耳的音律。\n");
	             	if(random(5) <2)
	             	tell_object(boat, "远处的湖面上传来了悦耳的音律。\n");
	             	return 1;
	        }
	        else 
	        {	
         	write("你弹了一下琴，突然脚下一空，掉了下去。\n");
             	message("vision", me->name() + "弹了一下琴，突然脚下一空，掉了下去。\n", environment(me), ({me}) );
             	me->move(__DIR__"boat");
             	message("vision", me->name() + "从上面的隔板中掉了下来,落到一条小舟上。\n", environment(me), ({me}) );
             	me->delete("mr/x");
             	me->delete("mr/y");
             	me->set("mr/x", i);
             	me->set("mr/y", j);
             	return 1;
             	}
         }

}
