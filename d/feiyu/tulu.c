// Room: tulu.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.10.9
// 

inherit ROOM;

void create ()
{
        set ("short", "土路");
        set ("long", @LONG
这是一条普通的土路，黄黄的土路一直延伸到杂草之中，看不清去路
。路上不时滚着一些枯草团。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"northup" : __DIR__"huangdi",
		"east" : __DIR__"mudi",
       ]));

        set("outdoors", "feiyu");
        setup();
        replace_program(ROOM); 
}

