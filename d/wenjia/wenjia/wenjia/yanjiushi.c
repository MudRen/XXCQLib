// Room: yanjiushi.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "研究室");
        set ("long", @LONG
这里是活字号的研究室，当温家弟子在江湖上遇到了什么新的毒药，
就必须带回这里研究解毒方法。活字号的第一把手就在这里工作。向东
走是会客室，西边是资料室，南面就是藏毒的仓库。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("objects", ([
                __DIR__"npc/wennuansan" : 1,
        ]));

        set("exits", ([
                "east" : __DIR__"huikeshi1",
                "west" : __DIR__"ziliaoshi1",
                "south" : __DIR__"cangku",
        ]));

        setup();
        replace_program(ROOM);
}
