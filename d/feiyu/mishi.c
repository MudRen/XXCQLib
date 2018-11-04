// Room: mishi.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create()
{
        set("short", "密室");
        set("long", @LONG
没有八仙桌，没有虎皮凳，没有锦帐流苏，也没有任何华贵的阵设，
糜奢的珍玩，眩目的珠宝。这屋子的简朴，正如蓝天白云，若搽脂粉，反
而污了颜色。
LONG);
        set("area","飞鱼");
        set("valid_startroom", 1);

        set("exits", ([
                "southdown" : __DIR__"cailiaofang",
        ]));

        setup();
        replace_program(ROOM);
}
