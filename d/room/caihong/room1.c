// room1.c 彩虹居房例之房间1
// Written by Doing Lu 1998/12/30

// 在生成房屋时：
// /**/开头的语句将被去掉
// //**开头的语句将被使用。

#include <room.h>
/**/inherit ROOM;
//**inherit PRIVATE_ROOM;

void create()
{
	set("short", "大厅");
	set("long", @LONG
	这里是鲁班大师精心搭建的彩虹居的正厅，透过窗户隐隐约约可以看到
院子的全貌。厅内整齐的摆着几张椅子，还有一张红木桌子，上面摆着一幅琢磨
精细的棋。也许客人们来了以后就在这里谈天说地，间歇里还可以厮杀几局。左
右两边通向两间屋子。
LONG
	);

	set("no_fight", 1);

/**/	set("default_long", "这是大厅，透过窗户可以隐隐约约的看到院子的全貌。厅内整齐的摆着几张椅子，" +
/**/			    "还有一张红木桌子。主人常在这里和客人们谈论江湖恩仇，感慨人间世情，间歇" +
/**/			    "和友人小酌，共聚良宵。左边是主人的房间，右边是一个小间。");

	set("key", "ROOM_KEY");
	set("owner", "ROOM_OWNER");

	set("exits", ([
		"south" : __DIR__"xiaoyuan",
		"west"  : __DIR__"room2",
		"east"  : __DIR__"room3",
	]));

	create_door("south", "厅门", "north", DOOR_CLOSED);
	create_door("west",  "室门", "east",  DOOR_CLOSED);

	setup();
}
