inherit ROOM;

void create()
{
      set("short","山路");
      set("long",@LONG
你走在登山的路径上，路的左右各有一条大铁链，象两条长蛇向山上山
下蜿蜒爬去。铁链都被植物缠绕，往上望去，云雾笼罩，不知这条路通向何
方。快点爬吧！
LONG);
            set("valid_startroom",1);
      set("exits",([ /* sizeof() == 1 */
          "westup"  : __DIR__"shanlu4",
          "southdown"  : __DIR__"shanlu2",
      ]));
      set("outdoors", "龙门");
//    set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}

