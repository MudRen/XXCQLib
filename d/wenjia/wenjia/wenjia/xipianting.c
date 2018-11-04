// Room: xipianting.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.6.10
// 
// 


inherit ROOM;
void create ()
{
        set ("short", "西偏厅");
        set ("long", @LONG
这里的摆设与前厅的差不多，只是物品的档次显然低多了没有前厅中
的肃杀气氛。这是接待次级宾客的地方。东南方的门是通往前厅的而东北
方的门自然是通往议事厅的。
LONG);
        set("area","岭南");
        set("valid_startroom", 1);

        set("exits", ([
                "northeast" : __DIR__"yishiting",
                "southeast" : __DIR__"qianting",
        ]));

        setup();
        replace_program(ROOM);
}
