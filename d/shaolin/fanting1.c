// Room: /d/shaolin/fanting1.c
// Date: YZC 96/01/19

inherit ROOM;
int do_serve(string arg);

string* names = ({
	__DIR__"obj/mizhi-tianou",
	__DIR__"obj/jiaxin-biji",
	__DIR__"obj/basi-shanyao",
	__DIR__"obj/furong-huagu",
});

void create()
{
	set("short", "斋厅");
	set("long", @LONG
这里便是少林全寺寺僧用斋的地方。斋厅极大，足可容纳上千人同时
进膳。从东到西一排排摆满了长长的餐桌和长凳，几位小和尚正来回忙碌
着布置素斋。桌上摆了几盆豆腐，花生，青菜以及素鸭等美味素食。北面
是个厨房。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"south" : __DIR__"fanting",
		"north" : __DIR__"chufang",
	]));
	set("objects",([
        	__DIR__"obj/qinghulu" : 1,
		names[random(sizeof(names))]: 1,
		names[random(sizeof(names))]: 1,		
	]));
	setup();
}

void init()
{
        add_action("do_serve", "yell");
}

int do_serve(string arg)
{
 object obj;

 if(!arg || arg !="有人吗")
    return notify_fail("你嚷什么,嚷!\n");
 obj = new(names[random(sizeof(names))]);

 if (!present("huagu tang",environment(this_player())))
   {
    obj->move(__DIR__"fanting1");
    return notify_fail("有个僧人从里面钻出来,说道:哟,吃的没了!等等啊!\n");
   }
    else return notify_fail("已经有了再yell也没有用!\n");
}
