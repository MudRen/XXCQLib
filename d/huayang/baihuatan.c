//changan city

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
        set ("short", "百花潭");
        set ("long", @LONG
你现在所站的百花潭是华阳风景有名的“四花”之一，潭深不见底，
水四季寒可彻骨，潭四周百花丛生，每年春夏都引来百鸟朝潭。从这里向
东南是华阳小镇，往北则通往浣花溪。
LONG);
	set("valid_startroom", 1);

        set("exits", 
        ([
		"north" : __DIR__"treeroad2",
		"southwest" : __DIR__"tulu2",
       ]));

        set("outdoors", "huayang");
        setup();
}