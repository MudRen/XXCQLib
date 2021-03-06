// Room: xilianwuchang.c
// Created by Zeus 1999.3.26
// Modified by Zeus 1999.4.3
// Modified Long and Checked Bugs
// 
inherit ROOM;

void init();
int do_yue(string);

void create ()
{
        set ("short", "西练武场");
        set ("long", @LONG
这是一个宽敞的练武广场，广场周围放着一些兵器架，兵器
架上面有着各式兵器。东边是西走廊，北面有一个林间小径吧。
你面前有一个沙池，你是否可以(yue)过去。
LONG);
        set("area","岭南");
	set("valid_startroom", 1);
        set("outdoors", "wenjia");

        set("objects", ([
                __DIR__"npc/wenjiadizi" : 2,
        ]));

        set("exits", ([
                "east" : __DIR__"xizoulang",
                "north" : __DIR__"xiaojing",
        ]));
        setup();

}

void init()
{
        add_action("do_yue", "yue");
}

int do_yue(string arg)
{
        object me;
        int jingli_cost;
        int qi_cost;

        me = this_player();

        if ( !arg || ( arg != "shachi" ) )
                return notify_fail("你想干什么？\n");

        jingli_cost = (-1) * random(20);
        qi_cost = (-1) * random(20);

        me->add("jingli", jingli_cost);
        me->add("qi", qi_cost);

        message_vision("$N提一口气，将身子一提，双脚离开地面。\n", me);

        if ( (int)me->query_skill("dodge", 1) < 10 )  
        {
                message_vision("结果“啪”地一声$N在沙池对面摔倒了。\n", me);
        } else if ( (int)me->query_skill("dodge", 1) < 20 )
        {
                message_vision("$N摇摇晃晃地跳到沙池对面，差点摔倒！\n", me);
        } else 
        {
                message_vision("$N提一口气，潇洒地落在沙池对面！\n", me);
        }
 
        if ( (int)me->query_skill("dodge", 1) < 30)
        {
                me->improve_skill("dodge", me->query("int"));
                me->set_temp("jumped",1);
        }
        if ( !me->query_temp("jumped") )
        { 
                write("你觉得非常轻易的就跳过了沙池，对自己没什么作用吧！\n");
        }
        return 1;
}