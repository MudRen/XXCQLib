// Room: /d/wizard/wizard_room.c

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", HIW "通道" NOR);
	set("long", @LONG
这是一个通往全国各地的魔法通道，你可以通过他到各地的主要地方。
LONG );

	set("exits", ([
	"km" : "/d/kunming/kedian",
	"wel" : "/d/welcome/wel1",
           "yw" : "/d/yaowang/yaowanggu",
        "bingqi" : "/d/item/jianchang",
        "luban" : "/d/room/xiaoyuan",
	"east" : __DIR__"wizard_room",
	"down" : __DIR__"guest_room",
 	]));

	set("no_clean_up", 0); 
	setup();
	replace_program(ROOM);
}
