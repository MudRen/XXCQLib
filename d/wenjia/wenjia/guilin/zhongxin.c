// Room: zhongxin.c
// Created by Zeus 1999.6.4
// Modified by Zeus 1999.6.4
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "镇中心");
        set ("long", @LONG
这里是桂林镇的中心。这里是壮族的聚集地，所以到处都可以看见穿
着壮族服饰的人走来走去。东边的那座独立的山峰是“独秀峰”，肚子饿
了可以到西边的小吃店去，那里可是“桂林第一厨”开的店。想去外浣花
的人要走西南边的路，而向北延伸的是街道。
LONG);
        set("area","桂林");
        set("outdoors", "guilin");
	set("valid_startroom", 1);

        set("objects", ([
                __DIR__"npc/zzman" : 1,
                __DIR__"npc/zzboy" : 1,
        ]));

        set("exits", ([
                "southeast" : __DIR__"huaqiao",
                "north" : __DIR__"jiedao",
                "west" : __DIR__"xiaochi",
                "east" : __DIR__"duxiu",
                "southwest" : __DIR__"working",
        ]));
        setup();
        replace_program(ROOM);
}

