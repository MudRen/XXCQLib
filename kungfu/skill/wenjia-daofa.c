// 温家刀法
// bye jfeng 江枫
inherit SKILL;
mapping *action = ({
([  "action":"\n$N使一式[清风细吹」，手中$w幻成一条白光刺向$n的$l",
    "force" : 140,
    "lvl" : 20,
    "skill_name" : "清风细吹",
    "damage_type":  "割伤"
]),
([  "action":"$N纵身轻轻跃起，一式「明月高挂」，刀光如水，一泻千里，洒向$n全身",
    "force" : 240,
    "lvl" : 80,
    "skill_name" : "明月高挂",
    "damage_type":  "割伤"
]),
([  "action":"\n$N一式[月上梢头」,手中$w遥摇指向$n的$l",
    "force" : 300,
    "lvl" : 120,
    "skill_name" : "月上梢头",
    "damage_type":  "割伤"
]),
([  "action":"\n$N手中$w斜指苍天,一式「春风无意」，对准$n的$l斜斜击出",
    "force" : 400,
    "lvl" : 180,
    "skill_name" : "春风无意",
    "damage_type":  "割伤"
]),
([  "action":"$N手中$w中宫直进，一式「柔情似水」，无声无息地对准$n的$l砍出一刀",
    "force" : 420,
    "lvl" : 230,
    "skill_name" : "柔情似水",
    "damage_type":  "割伤"
]),
([  "action":"\n$N呼的一声拔地而起，一式「日月同辉」，$w幻出万道光影，将$n团团围住",
    "force" : 500,
    "lvl" : 280,
    "skill_name" : "日月同辉",
    "damage_type":  "砍伤"
]),
([  "action" : "$N募的使一招「秋山红叶」，一片刀光洒向$n全身",
    "force" : 700,
    "lvl" : 380,
    "skill_name" : "秋山红叶",
    "damage_type":  "砍伤"
]),
});
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int practice_level(){   return 60;  }
int valid_learn(object me)
{
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "blade")
        return notify_fail("你使用的武器不对。\n");
    if ((int)me->query("max_neili") < 200)
        return notify_fail("你的内力不够。\n");
    if ((int)me->query_skill("zhixin", 1) < 50)
        return notify_fail("你的温故知新火候太浅。\n");
    if ((int)me->query_skill("force", 1) < 50)
        return notify_fail("你的基本内功火候太浅。\n");
    if (me->query_skill("blade", 1) <=me->query_skill("wenjia-daofa", 1))
        return notify_fail("你的基础不够，无法领会更高深的技巧。\n");
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
    mapping a_action;
    int i, level;
    level   = (int) me->query_skill("wenjia-daofa",1);
    for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]){
                        a_action=action[NewRandom(i, 20, level/5)];
                       break;
                 }
    a_action["dodge"]  = 0-level/2;
    a_action["parry"]  = 0-level/3;
    a_action["attack"]  = level/2;
    a_action["damage"] = level/2;
    return a_action;
}
int practice_skill(object me)
{
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "blade")
        return notify_fail("你使用的武器不对。\n");
    if ((int)me->query("qi") < 50)
        return notify_fail("你的体力不够练温家刀法。\n");
    me->receive_damage("qi", 30);
    return 1;
}
string perform_action_file(string action)
{
    return __DIR__"wenjia-daofa/" + action;
}
