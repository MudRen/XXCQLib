//andao2.c		四川唐门—地道

inherit ROOM;

void create()
{
	set("short","地道");
	set("long", @LONG
这里,四周漆黑一团,你好象什么都看不见似的
走在里面,你不觉想到这似乎在每个角落都藏着无限杀机,太恐怖了
四周毫无声息，好象掉下一根针都可能听到。
LONG);
	set("exits",([
		"north" : __DIR__"andao1",
		"west" : __DIR__"huayuan",
	]));
	setup();
	replace_program(ROOM);
}