//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "飞花桥畔");
        set ("long", @LONG
你已经到了成都郊区锦江浣花溪畔，你的西面是方圆五里之内过浣花
溪的唯一一座桥“飞花桥”，如果你是来找浣花萧家的，过了桥上台阶就
到了。向东南是一条土路，通向华阳小镇，附近的人们常去那里买东西。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"westup" : "/d/huanhua/feihuaqiao",
		"south" : __DIR__"fhroad1",
		"southeast" : __DIR__"tulu",
       ]));

        set("outdoors", "huayang");
        setup();
}