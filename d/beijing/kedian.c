// Room: /city/kedian.c
// LOAD 

inherit ROOM;

void create()
{
	set("short", "大光明栈");
	set("long", @LONG
	这是北京城四家客店中价格最低廉的一家，一些没钱的学子和赴京告状的
穷人多选择这里落脚，但由于这里便宜，所以设施也简陋，不但没有饭食供应，而
且也只有大通铺可以住，如果您是有钱人，不妨到其他客店看一看。从这里向西是
一家附属在客店的新开的驿站。墙上还挂着一个牌子(paizi)。
LONG
	);

	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);

	set("item_desc", ([
		"paizi" : "客房通铺，每夜十两白银。\n",
	]));

	set("objects", ([
		__DIR__"npc/xiaoer" : 1,
	]));

	set("exits", ([
		"north" : __DIR__"shalan-w2",
		"west" : __DIR__"bjyizhan",
		"enter" : __DIR__"kefang",
		"up" : "/d/wizard/guest_room",
	]));

	setup();
	
	"/clone/board/kedian_b"->foo();
}

int valid_leave(object me, string dir)
{

	if ( !me->query_temp("rent_paid") && dir == "enter" )
	return notify_fail("店小二一下挡在里屋门前，白眼一翻：怎麽着，想白住啊！\n");

	if ( me->query_temp("rent_paid") && dir == "north" )
	return notify_fail("店小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！
旁人还以为小店伺候不周呢！\n");

	return ::valid_leave(me, dir);
}
