// xt.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIW"小厅"NOR);
	set("long",@long
你走进这间小小的厅室, 看到里面放着一张紫檀木茶几和几张湘妃竹椅
子，紫檀木的茶几上摆放着茶壶和几只白玉杯，专供客人饮用。你忍不住想
坐在竹椅上，让疲惫的身心得到充分的休息。
long);
         set("exits",([
             "north" : __DIR__"cf",
             "west" : __DIR__"xj1",
]));
	set("objects",([
	__DIR__"npc/abi" : 1,
	__DIR__"obj/xiangcha" : 2,
]));
         setup();                     
         replace_program(ROOM);
}
