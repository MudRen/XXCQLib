//changan city

inherit ROOM;

void create ()
{
        set ("short", "南大街");
        set ("long", @LONG
你站的地方已经京城的最南端，南面耸立的就是巍峨的南城门了，由
于这是皇帝出京走的路，所以比京城其他街道更为宽敞。街的西面是京城
有名的“大光明栈”，东面则是一家驿站。从这里直往北则通向黄衫街。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
                "west" : __DIR__"guangming",
		"east" : __DIR__"blyizhan",
		"north" : __DIR__"nandajie2",
		"south" : __DIR__"nanchengmen",
        ]));

	set("area", "汴梁");

        set("outdoors", "bianliang");
        setup();
	replace_program(ROOM);
}
