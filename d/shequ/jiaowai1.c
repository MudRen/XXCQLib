//by andylau

#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "凤翔大道");
    set("long", @LONG
这是小雪社区的主街道，两边树立着无数白玉石碑（read bei），石碑上
刻着的都是一些曾经在江湖上叱姹风云的巫师，他们有的去世了，有的已
经隐居，有的还在闲云野鹤，过着浪迹天涯的生活。但是他们的名字会永
远留在这里，永远铭刻在一代又一代人的心中。落英缤纷，蜂歌蝶舞，朝
露夕光，沁人心脾。真是好时光。偶有几对小男女结伴踏青，莺声丽影，
嬉闹动人。
LONG );

    set("exits", ([
        "south" : __DIR__"jiaowai2",
        "west"  : __DIR__"course",
        "north" : "/d/bianliang/guangming",
        "east"  : __DIR__"bite",
    ]));

    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
    setup();
    create_door("east", "垂花小门", "west", DOOR_CLOSED);
    create_door("west", "垂花小门", "east", DOOR_CLOSED);
}
int valid_leave(object me, string dir)
{
    me = this_player();
    if ((me->query("id")!="course" && me->query("id")!="qixia") && dir == "west")
    {
       return notify_fail(RED"那是人家的私宅，别去讨嫌了！\n"NOR);
    }
    if ((me->query("id")!="bite" && me->query("id")!="princess") && dir == "east")
    {
       return notify_fail(RED"那是人家的私宅，别去讨嫌了！\n"NOR);
    }
    return ::valid_leave(me, dir);
}
void init()
{
	add_action("do_bian", "bian");
	add_action("do_look","read");
	add_action("do_upadm", "upadm");
	add_action("do_uplock", "uplock");
	add_action("do_upboot", "upboot");
}
int do_look(string arg)
{
	object me = this_player();
if (arg == "bei" || arg == "石碑" )
{
	me->start_more( read_file("/doc/help/famous.txt"));
//	me->cat("/doc/help/famous.txt");
	return 1;
}
	else
	write("你要读什么？\n");
	return 1;
}
