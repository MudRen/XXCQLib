// Room: shanlu1.c
// Created by Zeus 1999.6.5
// Modified by Zeus 1999.6.5
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
一条人由人踩出来的山路，从这里上去就是温家的总堂了。不时看见
温家的弟子从这里经过，他们的神情紧张。当他们走过你身边的时候你会
觉得有一股奇异的气味。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("objects", ([
                __DIR__"npc/wenjiadizi" : 1,
        ]));

        set("exits", ([
                "northdown" : __DIR__"shandi",
                "eastup" : __DIR__"shanlu2",
        ]));
        setup();
        replace_program(ROOM);
}
