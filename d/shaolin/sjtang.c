// Room: /d/shaolin/qfdian.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "诵经堂");
	set("long", @LONG
这是就是诵经堂。大堂内很是素洁，佛堂的正中挂有黄锦黑字的“空
既是色，色既是空”和“苦海无边，回头是岸”两幅大字。堂内摆有二十
余个黄埔团，供僧人在此跪坐诵经(songjing)。少林寺高僧木蝶大师在此
讲经。
LONG );
	set("valid_startroom", 1);

	set("exits", ([
		"southdown" : __DIR__"wuchang",
	]));

	set("objects",([
		"/kungfu/class/shaolin/mudie" : 1,
	]));

	setup();
}

void init()
{
	add_action("do_songjing", "songjing");
}

int do_songjing()
{
	object me, *inv;
	int i;
	mapping skill, myfam;

	me = this_player();
	myfam = (mapping)me->query("family");
	inv = all_inventory(me);

	if (myfam["family_name"] != "少林派")
		return notify_fail("你不是少林弟子，不能在这里诵经。\n");

	for(i=sizeof(inv)-1; i>=0; i--)
	if (inv[i]->query("id") == "jing")
	{
		skill = (mapping)inv[i]->query("skill");
		if (skill["name"] == "buddha"
		&& skill["max_skill"] == 80
		&& skill["min_skill"] == 41)
		{
			if (me->query_skill("buddha",1) < 80)
				return notify_fail("你的禅宗心法等级不够，没资格在这里诵经。\n");
			if (me->query_skill("buddha",1) > 150)
				return notify_fail("你对禅宗心法已经有了相当深的领悟，在这里诵经已经得不到提高了。\n");
			if (me->query("jingli") < (70 - me->query("bac")))
				return notify_fail("你已经无法集中精力诵经了，还是歇歇吧。\n");
			if (!objectp(present("mudie dashi", environment(me))))
				return notify_fail("木蝶大师不在，没有人能指导你诵经。\n");

			tell_object(me, "你排除杂念、净心清神，在木蝶大师的指导下开始诵经。\n");
			tell_object(me, "你对禅宗心法的理解有了进一步的加深。\n");
			me->add("jingli", me->query("bac") - 70);
			me->improve_skill("buddha", me->query("bac"));

			return 1;
		}

		return notify_fail("这本经书不能用来在这里诵经。\n");
	}

	return notify_fail("没有经书怎么诵经，你不是开玩笑吧。\n");
}