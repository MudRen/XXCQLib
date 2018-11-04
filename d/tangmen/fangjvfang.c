//fangjvfang.c		四川唐门—防具房

inherit ROOM;

void create()
{
	set("short", "防具房");
	set("long", @LONG
这里是蜀中唐门的防具房，房间很大，靠墙摆放着几个木架，上
面挂着一些防护用具，可以用来防止在练习中伤到自己。其中最具特
色的，莫过于那套唐门独有的鹿皮手套。
LONG
	);
	set("exits", ([
		"north" : __DIR__"nzlange2",
	]));
	set("objects", ([
		"/clone/weapon/changjian" : 4]));

	set("no_fight", 1);
	set("area", "蜀中");	
	setup();
	replace_program(ROOM);
}