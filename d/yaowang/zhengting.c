// Room: 汴梁药局
// By 山猫adx @ 宁波小雪 17:00 99-10-26

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "正厅");
	set("long", @LONG
这里是回春堂的正厅，宽敞的房间内放着几张桌椅，每天都有药王谷
的医师在这里坐堂，为人看病疗伤。
LONG );
	set("area", "汴梁东");
	set("areb", "回春堂");
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"tingyuan",
	]));

	set("objects", ([
		__DIR__"npc/yishi" : 1,
	]));
	setup();
}

void init()
{
	add_action("do_zhiliao", "zhiliao"); //疗伤
}

int do_zhiliao(string arg)
{
	object me, ob;
	int i, obj;
	me=this_player();
	i=( 100 - (int)me->query_skill("healing",1) );

	if(me->query("party/party_name")!=HIB"药王谷"NOR
         || me->query("party/level")<5 ) {
		return notify_fail("你不能在这里给人疗伤！\n");
	}

	if( !arg )
		return notify_fail("指令格式：zhiliao <ID> \n");

	if(!objectp(ob = present(arg, environment(me))))
		return notify_fail("这里没有这个人！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail("他正忙着呢！\n");

        if( me==ob )
                return notify_fail("你不需要在这里给自己疗伤！\n");

	obj=( ob->query("max_qi")-ob->query("eff_qi") );

	if(!ob->query_temp("heal")) {
	message_vision ("$N得先交诊金"+MONEY_D->price_str(obj*10)+"给唐讹化。\n", ob);
		return 1;
	}

	if( i<5 ) i=5;
	if( i>80 ) i=80;
	if(me->query("jingli")<=i)
		return notify_fail("你太累了，先休息一下吧！\n");

	message_vision ("$N为$n把了把脉，拿出一根银针在$n穴位上扎了几下。\n", me, ob);
	message_vision(WHT"$N吐出一口淤血，脸色看起来好多了。\n"NOR, ob);

	ob->delete_temp("heal");
         ob->set("eff_qi", ob->query("max_qi"));
         ob->set("qi", ob->query("max_qi"));
	me->improve_skill("healing", ((int)me->query_skill("healing",1)/4));
	me->add("jingli", -i);
	me->start_busy(3);
	ob->start_busy(3);

	return 1;
}
