// Room: xuetang.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.4.3
// Modified Study
// 

inherit ROOM;

void create ()
{
        set ("short", "学堂");
        set ("long", @LONG
未走入学堂就听到了隐隐约约的读书声，走进来之后读书声
变的很大。这种清脆的童声是非常好听的。这里坐着的大部分都
是小孩，有一些是大人，他们就象鹤立鸡群一样，真是“少小不
努力，老大图伤悲”。墙壁上贴的是学规(xuegui)。
LONG);
        set("area","岭南");
	set("valid_startroom", 1);
        set("exits", ([
                "west" : __DIR__"donglianwuchang",
                "south" : __DIR__"cangshufang",
        ]));

        set("item_desc", ([
             "xuegui" : "日讲经书三起，日看纲目数页。"  
                        "\n通晓时务物理，参读古文诗赋。" 
                        "\n读书必须过笔，会课按时蚤完。"
                        "\n夜读仍戒晏起，疑误定要力争。\n"
        ]));

        set("objects", ([
//      __DIR__"npc/wenkongzi": 1,
               __DIR__"npc/wenxiaoming": 1,
               __DIR__"npc/wenxiaofang": 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        me->set_temp("mark/孔", 0);
        return 1;
}
