// houyuan.c

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short",HIW"后院"NOR);
         set ("long",
"穿过一个半月形的拱门, 你来到一座小楼之前。小楼檐下一块匾额, 写\n"
"着："BLINK HIM"云锦楼"NOR"三个墨绿毫字, 楼下前后左右种的都是茶花。但这些茶花都不过\n"
"是三四流货色, 和这精致的楼阁亭榭相比, 未免不衬。\n"
);
         set("outdoors","姑苏慕容");
         set("exits",([
         "west" : __DIR__"xj2",
         "east" : __DIR__"xf",
         "south" : __DIR__"yjl",
]));
	set("objects",([
	__DIR__"npc/puren" : 1,
	]));
         setup();
         replace_program(ROOM);
}
