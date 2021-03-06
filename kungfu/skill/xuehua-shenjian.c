// xuehua-shenjian.c 雪花神剑
// by god

#include <ansi.h>
inherit SKILL;

mapping *action = ({
        ([      "name":         "柳暗花明",
                "action":       "$N使出雪花剑法中的"+HIR"「柳暗花明」"NOR+"$N已仿佛与天地在一起。",
                "dodge":        50,
                "parry" :       100,
                "force":        170,
        "damage" :  100,
                "damage_type":  "刺伤"
        ]),
        ([      "name":         "仙云密布",
             "action":       "$N使出雪花剑法中的"+HIW"「仙云密布」"NOR+"，$N立时乘机而入",
                "dodge":        100,
                "parry" :       200,
                "force" :       200,
        "damage":   150,
                "damage_type":  "刺伤"
        ]),
        ([      "name":         "来去若梦",
                "action":       "$N举剑过头，剑意若有若无，$w剑尖遥指$n。使出雪花剑法中的"+HIR"「来去若梦」"NOR,
                "dodge":        100,
                "parry" :       200,
                "force":        170,
        "damage" :  200,
                "damage_type":  "刺伤"
        ]),
        ([      "name":         "龙听梵音",
                "action":       "$N使出雪花剑法中的"+HIY"「龙听梵音」"NOR+"，以声音、吸引住$n，使$n坠入了沉睡之中",
                "dodge":        100,
                "parry" :       200,
                "force" :       200,
        "damage":   250,
                "damage_type":  "刺伤"
        ]),
        ([      "name":         "日月同辉",
                "action":       "$N使出雪花剑法中的"+HIC"「日月同辉」"NOR+"，不慌不忙，$N横手一提，又拿住剑柄，剑光一盎，又罩向$n",
                "dodge":        100,
                "parry" :       200,
                "force" :       300,
                "damage":       250,
                "damage_type":  "刺伤"
        ]),
        ([      "name":         "雪花点点",
                "action":       "$N只觉真似天河一般壮丽的气势，使出雪花剑法中的"+MAG"「雪花点点」"NOR+"，攻向$n",
                "dodge":        100,
                "parry" :       200,
                "force" :       350,
                "damage":       300,
                "damage_type":  "刺伤"
        ]),
        ([      "name":         "雪花太山",
                "action":       "$n感觉到剑势,铺天盖地的涌压而来，正是雪花剑法中的「雪花太山」",
                "dodge":        100,
                "parry" :       200,
                "force" :       400,
                "damage":       350,
                "damage_type":  "刺伤"
        ]),
        ([      "name":         "天河飞遁",
                "action":       "$n刚要刺出，忽然发现自己身形、衣袂、飘飘欲仙，反被$N一剑刺中了"+CYN"「天河飞遁」"NOR,
                "dodge":        100,
                "parry" :       200,
                "force" :       400,
                "damage":       400,
                "damage_type":  "刺伤"
        ]),
});
int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
    mapping myfam;
    myfam = (mapping)me->query("family");
    if ((int)me->query("max_neili") < 200)
        return notify_fail("你的内力不够。\n");
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
    level   = (int) me->query_skill("xuehua-shenjian",1);
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
    if ((int)me->query("qi") < 40)
        return notify_fail("你的体力不够练雪花剑法。\n");
    me->receive_damage("qi", 20);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"xuehua-shenjian/" + action;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        string msg;
        
        if( damage_bonus < 100 ) return 0;
        if (!(me->query("xuehuafore"))) return 0;
        if( random(damage_bonus/2) > victim->query_str() ) {        
        if (me->query("xuehuafore")==1) {
        victim->receive_wound("qi",damage_bonus/2 );
        msg= HIW "$n被雪花神剑的剑气所伤。\n" NOR;
        }
        return msg;
        }
}

