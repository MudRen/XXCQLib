// guanri-jianfa.c 观日剑法

inherit SKILL;

mapping *action = ({
([      "name":   "日出中天",
        "action" : "$N身前飓地一亮，一招「日出中天」如旭日股的亮烈芒团又飞起，直扑$n！",
        "dodge" : 20,
        "damage" : 180,
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([      "name":   "乌云遮日",
        "action" : "$N猝吃惊下，一招「乌云遮日」手上长剑时亮时暗，亮如旭日，暗如夕照，一亮一暗间，依然是杀着无穷，势不可当的“观日剑法”。",
        "dodge" : 20,
        "damage" : 160,
        "lvl" : 10,
        "damage_type" : "刺伤"
]),
([      "name":   "九日升空",
        "action" : "$N的剑势越来越威猛，越来越盛，正是观日剑法「九日升空」刺向$n 。",
        "dodge" : 15,
        "damage" : 150,
        "lvl" : 20,
        "damage_type" : "刺伤"
]),
([      "name":   "星日比耀",
        "action" : "$N连舞七八道剑花，叮叮叮，碰开三点星光，长身而起，一招「星日比耀」直取$n的$l",
        "dodge" : 15,
        "damage" : 200,
        "lvl" : 30,
        "damage_type" : "刺伤"
]),
([      "name":   "日落西山",
        "action" : "$N的身形立时飞退，剑锋一直激射，$N一直飞退，虽不及往侧闪避，但飞出十余尺后，便落了下来，使出一招「日落西山」，剑势极妙，刺向$n的$l",
        "dodge" : 25,
        "damage" : 180,
        "lvl" : 40,
        "damage_type" : "刺伤"
]),
([      "name":   "剑如旭日",
        "action" : "$N左手一震，右手却忽然多出一柄剑来，[剑如旭日]，一下子令人眼睛都睁不开来。",
        "dodge" : 25,
        "damage" : 220,
        "lvl" : 50,
        "damage_type" : "刺伤"
]),
([      "name":   "日驰云间",
        "action" : "$N手中的$w，忽然一敛，随后光芒又炽，后又一敛，然后又烈，如此一暗一明，正是「日驰云间」",
        "dodge" : 15,
        "lvl" : 60,
        "damage" : 200,
        "damage_type" : "刺伤"
]),
([      "name":   "日漫金光",
        "action" : "$N吸了一口气，一招「日漫金光」那淬厉外射的剑芒，竟全敛入剑身里去，那里剑犹如旭日一般，发出暗红之金虹，剑尖对准$n 。",
        "dodge" : 35,
        "damage" : 250,
        "lvl" : 80,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage){return (usage== "sword") || (usage== "parry");}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 300)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法火候太浅。\n");
        return 1;
}
mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("guanri-jian",1);
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
        if ((int)me->query("qi") < 150)
                return notify_fail("你的体力不够练观日剑法。\n");
        me->receive_damage("qi", 50);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"guanri-jian/" + action;
}

