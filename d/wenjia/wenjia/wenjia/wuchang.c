// Room: wuchang.c
// Created by Zeus 1999.4.16
// Modified by Zeus 1999.6.10
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "武场");
        set ("long", @LONG
这里死字号的武场。这里是死字号的弟子们练习施毒技巧的地方，这
里到处弥漫着死亡的气息。死字号经常拿活人来练习的原因，这里附近都
是坟场。望过去前面有一个烧尸房。向北走是练功房。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

        set("exits", ([
                "north" : __DIR__"liangongfang",
        ]));

        setup();
        replace_program(ROOM);
}
