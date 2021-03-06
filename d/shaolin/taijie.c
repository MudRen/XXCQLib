// Room: /d/shaolin/taijie.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "台阶");
	set("long", @LONG
穿过山门殿，面前三道平行的青石台阶通向前方的一个高台。台阶上
精工镂刻着麒麟，玄龟，松鹤等瑞兽，形态逼真动人。高台正中方着个二
人高的青铜大香炉，前面摆着个香台，几位香客正在虔诚谟拜。再往前就
是天王殿。
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"south" : __DIR__"smdian",
		"northup" : __DIR__"twdian",
	]));
	set("outdoors", "shaolin");
	set("objects",([
		__DIR__"npc/tiejian" : 1,
	]));

	setup();
	replace_program(ROOM);
}