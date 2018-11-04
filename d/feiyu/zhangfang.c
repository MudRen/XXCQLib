// Room: zhangfang.c
// Created by Atlus 1999.7.23
// Modified by Atlus 1999.7.23
// 

inherit ROOM;

void create ()
{
        set ("short", "帐房");
        set ("long", @LONG
这里是飞鱼塘的帐房。飞鱼塘日常的收入支出在这里都有记录，负责
管帐的是个老先生，据说是个老进士，学识颇为丰富，如果有什么学习上
的问题就来问他。帐房里堆了一柜子的帐本、单据，还有不少贴上封条的
大箱子，想来都是银子吧。从这里向南就是兵器房。
LONG);
        set("area","飞鱼");
        set("valid_startroom", 1);
        
        set("objects", ([
                __DIR__"npc/zhangfangxs" : 1,
        ]));

        
        set("exits", ([
                "south" : __DIR__"bingqifang",
        ]));

        setup();
        replace_program(ROOM);
}

