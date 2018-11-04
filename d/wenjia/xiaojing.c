// Room: xiaojing.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.4.3
// Modified Long
// 

inherit ROOM;
void create ()
{
        set ("short", "小径");
        set ("long", @LONG
走出练武场，来到了一条小径。离开了那个充满了叫喊声和汗
臭味的地方，来到这个四周种满树木的地方，你顿时觉得精神为之
一震，似乎刚刚练武的疲劳都没有了。前面北方有一个精致的小舍，
那是饭堂。南面是西练武场。
LONG);
        set("area","岭南");
        set("outdoors", "wenjia");

        set("exits", ([
                "south" : __DIR__"xilianwuchang",
                "north" : __DIR__"fantang",
        ]));
        replace_program(ROOM);
        setup();
}