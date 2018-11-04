// huangshanjie3.c

#include <room.h>

inherit ROOM;

void create()
{	
	set("short", "黄衫街");
	set("long", @LONG
路东的华清池是有百年历史的老字号了，上到达官贵人、下至贩夫走
卒，只要有钱，都喜欢到这里舒舒服服的泡上一个澡，洗掉一身的疲惫。
路西则是一个大染坊，这里染的布全国驰名。
LONG);	
	set("valid_startroom",1);

	set("exits", ([
//		"north" : __DIR__"huangshanjie2",
		"north" : __DIR__"jiebei4",
		"south" : __DIR__"huangshanjie4",
		"west" : __DIR__"heiyiranfang",
		"east" : __DIR__"zaotang",
	]));

//	set("objects", ([
//		"/clone/weapon/changjian" : 4]));

	set("outdoors", "bianliang");
	set("area", "汴梁");

	setup();

	replace_program(ROOM);
}