
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$N一招“血河倒泻”，纵身跃起手中$w轻挥，斩向$n后颈",
    "force" : 200,
    "damage" : 100,
    "dodge"  : 10,
    "lvl"   : 0,
    "skill_name" : "血河倒泻",
    "damage_type" : "割伤"
]),
([  "action" : "$N手中$w连画三个弧形，大叫“血河神剑”，向$n的右臂齐肩斩落。",
    "force" : 300,
    "damage" : 200,
    "dodge" : 35,
    "force" : 20,
    "lvl"   : 50,
    "skill_name" : "血河神剑",
    "damage_type" : "割伤"
]),
([  "action" : "$N轻吁一声，刷刷刷刷四剑，向$n胸，腹，腰，肩四处连刺，好一招“血雾纷飞”！",
    "force" : 400,
    "damage" : 300,
    "dodge" : 25,
    "force" : 25,
    "lvl"   : 100,
    "skill_name" : "血雾纷飞",
    "damage_type" : "刺伤"
]),
([  "action" : "$N仰天一声清啸“血踪万里”，斜行向前，$w横削直击，迅捷无比，击向$n的$l",
    "force" : 500,
    "damage" : 400,
    "dodge" : 80,
    "force" : 200,
    "lvl"   : 150,
    "skill_name" : "血踪万里",
    "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
    mapping myfam;
    myfam = (mapping)me->query("family");
    if ((int)me->query("max_neili") < 300)
        return notify_fail("你的内力不够。\n");
/*
    if ((int)me->query("yiqiguan-riyue") < 1)
        return notify_fail("你的一气贯日月火候太浅,还没达到“从心所欲”的境界。\n");
*/
    if ((int)me->query_skill("sword", 1) < 50)
        return notify_fail("你的剑法火候太浅。\n");
    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
    if(level >= action[i]["lvl"])
        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("xuehe-jian",1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
        return notify_fail("你使用的武器不对。\n");
    if ((int)me->query("qi") < 50)
        return notify_fail("你的体力不够练血河剑法。\n");
    me->receive_damage("qi", 30);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"xuehe-jian/" + action;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        string msg;
        
        if( damage_bonus < 100 ) return 0;
        if (!(me->query("yiqiguan-riyue"))) return 0;
        if( random(damage_bonus/2) > victim->query_str() ) {        
        if (me->query("yiqiguan-riyue")==1) {
        victim->receive_wound("qi", (damage_bonus - 100) / 2 );
        msg= WHT "$n一个不防，被剑气中夹杂的“从心所欲”内劲所伤。\n" NOR;
        }
        if (me->query("yiqiguan-riyue")==2) {
        victim->receive_wound("qi",damage_bonus/2 );
        msg= CYN "$n一个不防，被剑气中夹杂的“登峰造极”内劲所伤。\n" NOR;
        }
        return msg;
        }
}

