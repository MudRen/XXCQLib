// Room: /d/shaolin/gulou3.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "鼓楼三层");
	set("long", @LONG
塔身往上似乎越来越窄，楼梯也渐为挤仄。扶手上不少朽坏处续接了
新木，漆色也是新旧不同。从窗孔往外望，往北可以看到竹林中的藏经楼
和方丈楼露出飞檐一角，往西则是后殿的屋顶，屋脊上塑了个大大的漆黄
“佛”字。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"up" : __DIR__"gulou4",
		"down" : __DIR__"gulou2",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

