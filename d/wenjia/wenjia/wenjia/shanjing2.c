// Room: shanjing2.c
// Created by Zeus 1999.4.8
// Modified by Zeus 1999.7.12
// 
// 

inherit ROOM;
void create ()
{
        set ("short", "山间小径");
        set ("long", @LONG
这条小径两边都是陡峭的山壁，小径非常倾斜，一直向南面延伸，通
往一片树林。这里一不小心就会摔跤。向东南方走就会回到那条平坦的小
径。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");
        set("valid_startroom", 1);

        set("exits", ([
                "southeast" : __DIR__"shanjing1",
                "northdown" : __DIR__"shulin1",
        ]));

        setup();
        replace_program(ROOM);
}