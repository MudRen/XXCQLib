// tangmen-biaofa	唐门镖法

inherit SKILL;

//int valid_enable(string usage) { return usage=="finger"; }

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("tangmen-biaofa", 1);

	if ( me->query("gender") == "无性" && lvl > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的唐门镖法。\n");
	return 1;
}

int practice_skill(object me)
{
    return notify_fail("唐门镖法只能用学的，或是从运用(exert)中增加熟练度。\n");
}

string exert_function_file(string func)
{
    return __DIR__"tangmen-biaofa/" + func;
}