// Room: /city/qianzhuang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
        set("short", "钱庄");
        set("long", @LONG
这是一家老字号的钱庄，老板是京城著名的商人高鸡血高老板，因为
高老板雄厚的实力和他那不为人知的后台，没人会怀疑钱庄的信誉，所以
这里的生意总是很好。
LONG
        );
        set("valid_startroom", 1);
        set("no_fight", 1);

        set("exits", ([
                "east" : __DIR__"heibujie7",
        ]));

        set("objects", ([
                __DIR__"npc/gao" : 1
        ]));

        setup();
        replace_program(ROOM);
}


