//liangongfang��c          

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�շ�");
	set("long", @LONG
LONG);
        set("valid_startroom",1);
	set("exits", ([
                        "north" : __DIR__"biandian",
	]));
        set("area", "Ȩ����");
        set("objects",([
          __DIR__"npc/guan" : 1,
      ]));
	setup();
	replace_program(ROOM);
}
