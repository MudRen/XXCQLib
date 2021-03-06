// Room: dongwuchang.c
// Created by Atlus 1999.7.21
// Modified by Atlus 1999.7.21
// 

inherit ROOM;

void init();
int do_da(string);
int do_ci(string);

void create ()
{
        set ("short", "东练武场");
        set ("long", @LONG
这是一个宽敞的东练武场，周围放着一些沙包和木人，左边有一个木
人摇摇晃晃的挂在木架上，你可以拿把剑去刺(ci)它。右边有个大沙包，
你很想用力一拳打(da)过去。两旁兵器架上面有着各式兵器。至于北面是
一个小房子，那是个兵器房。再向东走就是东院了。向南的是一条小路，
一直通向溪边。
LONG);
        set("area","飞鱼");
        set("valid_startroom", 1);
       
        set("objects", ([
                __DIR__"npc/feiyudizi" : 1,
        ]));

        set("exits", ([
                "west" : __DIR__"qianting",
                "east" : __DIR__"eroad",
                "north" : __DIR__"bingqifang",
                "south" : __DIR__"xiaojing1",
        ]));

        setup();
}

void init()
{
        add_action("do_da", "da");
        add_action("do_ci", "ci");
}

int do_da(string arg)
{
        object me;
        int jingli_cost;
        int qi_cost;

        me = this_player();

        if ( !arg || ( arg != "shabao" ) )
                return notify_fail("你想干什么？\n");

        jingli_cost = (-1) * random(15);
        qi_cost = (-1) * random(15);

        me->add("jingli", jingli_cost);
        me->add("qi", qi_cost);

        if ( me->query("jingli") <= (- jingli_cost) || me->query("qi") <= (-qi_cost) )
                return notify_fail("你太疲劳了，没有精力去练功了。\n");

        message_vision("$N摆好架势，一拳向沙包打去。\n", me);

        if ( me->query_skill("parry", 1) < 5 )  
        {
                message_vision("$N根本不会格斗，打得手都麻了。\n", me);
   		
        } else if ( me->query_skill("parry", 1) < 20 )
        {
                message_vision("$N把沙包打得晃来晃去。\n", me);
        } else 
        {
                message_vision("嘣的一声，沙包被$N打得飞了起来。\n", me);
        }
 
        if ( me->query_skill("parry", 1) < 30)
        {
                me->improve_skill("parry", me->query("int"));
                me->set_temp("hitted",1);
        }
        if ( me->query_skill("parry",1) >= 30 )
        { 
                write("你一下就把沙包打穿了，打沙包对你没什么作用了！\n");
        }
        return 1;
}

int do_ci(string arg)
{
        object me;
        int jingli_cost;
        int qi_cost;

        me = this_player();

        if ( !arg || ( arg != "muren" ) )
                return notify_fail("你想干什么？\n");

        jingli_cost = (-1) * random(15);
        qi_cost = (-1) * random(15);

        me->add("jingli", jingli_cost);
        me->add("qi", qi_cost);

        if ( me->query("jingli") <= (- jingli_cost) || me->query("qi") <= (-qi_cost) )
                return notify_fail("你太疲劳了，没有精力去练功了。\n");

        message_vision("$N捏个剑诀，一剑向木人刺去。\n", me);

        if ( me->query_skill("sword", 1) < 5 )  
        {
                message_vision("$N根本不会剑法，剑和木人只是轻碰了一下。\n", me);
   		
        } else if ( me->query_skill("sword", 1) < 20 )
        {
                message_vision("$N看准木人的移动，一剑刺在木人的要穴上。\n", me);
        } else 
        {
                message_vision("$N随手一剑，已经刺中木人的要害了。\n", me);
        }
 
        if ( me->query_skill("sword", 1) < 30)
        {
                me->improve_skill("sword", me->query("int"));
                me->set_temp("hitted",1);
        }
        if ( me->query_skill("sword",1)>= 30 )
        { 
                write("你一下就把木人刺倒了，看来刺木人对你没什么作用了！\n");
        }
        return 1;
}
