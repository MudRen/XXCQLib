// youyu-quan.c 游鱼拳
// modified by Atlus 1999.7.23
//

inherit SKILL;

mapping *action = ({
([  "action" : "$N步履一沉，左拳轻微拉开，右拳马上使出「鱼目混珠」击向$n的$l",

        "damage" : 15,
        "parry"  : 5,
        "force"  : 20,
        "lvl"  : 0,
        "dodge"  : 5,
        "skill_name" : "鱼目混珠",
        "damage_type" : "瘀伤"
]),
([  "action" : "$N左拳连环击出，$n急忙招架，不想$N左拳竟是虚招，右拳一招[鱼龙混杂]打向$n的$l",
        
        "damage" : 25,
        "parry"  : 5,
        "force"  : 25,
        "lvl"  : 15,
        "dodge"  : 5,
        "skill_name" : "鱼龙混杂",
        "damage_type" : "瘀伤"
]),
([      "action": "$N使出一招「苦海无涯」，右拳虚幌一下，反身左拳穿出击向$n的$l",
        "damage" : 35,
        "parry"  : 0,
        "force"  : 35,
        "lvl"  : 30,
        "dodge"  : 0,
        "skill_name" : "苦海无涯",
        "damage_type" : "瘀伤"
]),

([  "action" : 
"$N双拳一错，使出「余波未了」，对准$n的$l连续击出三拳",
        "damage" : 50,
        "parry"  : -5,
        "force"  : 45,
        "lvl"  : 45,
        "dodge"  : 0,
        "skill_name" : "余波未了",
        "damage_type" : "瘀伤"
]),

([  "action" : 
"$N使出一招[鱼游釜中]，左拳阴，右拳阳，以弧行之势向$n打去",
        "damage" : 65,
        "parry"  : -5,
        "force"  : 65,
        "lvl"  : 60,
        "dodge"  : -5,
        "skill_name" : "鱼游釜中",
        "damage_type" : "瘀伤"
]),

([      "action":               
"$N身形一纵，使出一招「鱼由天降」，双拳自上而下，砸向$n的$l",
        "damage" : 85,
        "parry"  : -10,
        "force"  : 75,
        "lvl"  : 75,
        "dodge"  : -10,
        "skill_name" : "鱼由天降",
        "damage_type" : "瘀伤"
]),
        
([      "action":
"$N使出一记[余音绕梁]，突然挥出一拳，马上欺身上前，再打出一拳，紧接着纵身而起，又是一拳，三拳竟是一起击向$n的$l",
        "damage" : 120,
        "parry"  : -10,
        "force"  : 90,
        "lvl"  : 100,
        "dodge"  : -10,
        "skill_name" : "余音绕梁",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return (usage == "cuff") || (usage == "parry"); }

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("cuff", 1) < 20)
		return notify_fail("你的基本拳法太低了。\n");
	return 1;
}

int practice_skill(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))

       return notify_fail("练游鱼拳法时必须空手。\n");


	if ((int)me->query("jingli") < 50)
		return notify_fail("你精神状态太差了，还是歇一会再练吧。。\n");
	me->add("jingli",-25);
	return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
		level   = (int) me->query_skill("youyu-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
	return __DIR__"youyu-quan/" + action;
}


