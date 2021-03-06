// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "听雨楼二层");
	set("long", @LONG
沿楼梯走上来，就到了听雨楼的二层。你环视一下这里，发现二层的
陈设相对一层简单了许多，只有一个雕花圆桌和四把红木圆椅摆在二层中
间，另有一套书案和一个书架沿墙而立，南北两面都有窗户，通过窗户可
以全览整个剑庐。一个锦衣人临窗而立，你一上来，他似乎便已知晓。
LONG
	);

	set("valid_startroom", 1);
	set("exits", ([
		"down" : __DIR__"tingyulou",
	]));

        set("objects", ([
		"/kungfu/class/huanhua/kaiyan" : 1,
	]));

	setup();
	replace_program(ROOM);
}