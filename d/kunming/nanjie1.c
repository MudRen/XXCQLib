// Room:/d/kunming/nanjie1.c
// JackyBoy@CuteRabbits Studio for CCTX 1999/4/17

inherit ROOM;

void create()
{
	set("short", "南大街");
	set("long", @LONG
往北是昆明的城中广场，西边的昆明客栈占尽了地理之便，来自五湖四海
的旅客游人都喜欢到店里打尖或者小歇一会，往南是一条商业街，昆明本地人
以及不少外地来的客商都集中在这里开店铺，由于最近官府免税三年，生意很
是红火。东边是一个为江湖人士开办的当铺，你可以跟官府投标买下它来经营
的。
LONG
	);
	set("exits", ([
		"west" : __DIR__"kedian",
		"north": __DIR__"guangchang",
		"east" : __DIR__"dangpu",
	]));
	set("outdoors","kunming");
	setup();
	replace_program(ROOM);
}
