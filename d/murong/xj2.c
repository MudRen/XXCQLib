// xj2.c

#include <ansi.h>
inherit ROOM;

void create()
{
         set("short",GRN"小径"NOR);
         set("long",@long
一条曲曲折折用鹅卵石铺成的小径, 路两旁绿柳成阴, 一处处山石花木
点缀在其中。你走在石地上，啪嗒啪嗒的发出清脆的响声。
long);
         set("ourdoors","姑苏慕容");
         set("exits",([
             "north" : __DIR__"sq1",
             "east" : __DIR__"houyuan",
]));
	setup();
	replace_program(ROOM);
}
