// Room: shulin.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "树林边");
        set ("long", @LONG
在两旁的树林里，茂密的树叶遮挡了阳光，这使你那里的环境显得有
点阴森。一阵风吹过，周围的树叶“沙沙”的作响。使你不禁加快了脚步
。再向南，便是钓鱼台了。
LONG);
        set("area","飞鱼");
        set("valid_startroom", 1);
        set("outdoors", "feiyu");

        set("exits", ([
                "south" : __DIR__"diaoyutai",
                "north" : __DIR__"xiaojing1",
                
        ]));
        setup();
        replace_program(ROOM);
}

