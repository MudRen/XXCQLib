// Room: shanlu3.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山路");
        set ("long", @LONG
脚下虽然是塌实的青石路，可是由于常年的雾水弥漫，青石路反而觉
得有点滑，这里已经是半山腰了，不禁有些寒意，从这里再向北攀上去就
是著名的“人止关”了。你抬头向南看去，发现一座山势怪异的山峰。
LONG);
        set("area","飞鱼");
        set("outdoors", "feiyu");

        set("exits", ([
                "northup" : __DIR__"renzhiguan",
                "southup" : __DIR__"luoshenling",
        ]));
        setup();
        replace_program(ROOM);
}
