//changan city

inherit ROOM;

void create ()
{
        set ("short", "大栅栏街口");
        set ("long", @LONG
这是南城的一个重要的街口，无数的人流在这里往来穿行，从这里向北望去，
已经可以看到正阳门城楼了，而向南则是北京最热闹的天桥了，向东和向西则是大
栅栏的东西两街，许多百姓日常不可缺少的商家都坐落在这条街上。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"west" : __DIR__"shalan-w1",
		"east" : __DIR__"shalan-e1",
        ]));

        set("objects", 
        ([
        ]));


        set("outdoors", "beijing");
        setup();
	replace_program(ROOM);
}