// guandao

#include <room.h>

inherit ROOM;

void create()
{       
        set("short", "官道");
        set("long", @LONG
 这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向龙
门,往西则直达汴梁城。
LONG);  
//      set("valid_startroom",1);
//      set("no_steal", "1");
//      set("no_fight", "1");
//      set("sleep_room",1);
        set("exits", ([
                "west" : __DIR__"guandao3",
                "east" : __DIR__"yellw",
        ]));
//      set("objects", ([
//              "/clone/weapon/changjian" : 4]));
        set("area", "汴梁");
        setup();
        replace_program(ROOM);
}

