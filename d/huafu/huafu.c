// menfang.c  门房
// mlf设计，lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","花府大门");
	set("long",@LONG
"\n                          "HBBLU+HIR"花府\n\n"NOR
    这里是发党总部花府的大门，大门两侧耸立着两头青石狮子。大门上
方有一块横匾，上书“花府”两个大字，匾的左右垂下两个大红灯笼。大
门敞开着，由于发梦二党的子弟大多是京城的市井之徒，所以这里也就特
别热闹。
LONG
	);
	set("outdoors","huafu");
	set("valid_startroom",1);
	set("exits",([
		"north" : __DIR__"huayuan",
	]));
	set("objects",([
		__DIR__"npc/qi" : 1,
	]));
//	set("no_clean_up",0);
	setup();
	replace_program(ROOM);
}


		
	
	
