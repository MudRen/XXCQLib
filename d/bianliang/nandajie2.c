//changan city

inherit ROOM;

void create ()
{
        set ("short", "南大街");
        set ("long", @LONG
走到这里，你闻到了一股浓烈的中药味，原来你的西面就是京城唯一
的药铺——回春堂，而东面则是一家杂货铺，里面冷冷清清，似乎生意不
是很好。南面传来阵阵马嘶，似乎有家驿站，而北面就是京城广场了。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
        "west" : "/d/yaowang/huichun",
		"east" : __DIR__"zahuopu",
		"north" : __DIR__"guangchang",
		"south" : __DIR__"nandajie1",
        ]));

	set("area", "汴梁");

        set("outdoors", "bianliang");
        setup();
}
