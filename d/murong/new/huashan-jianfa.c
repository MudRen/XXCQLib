// huashan-jianfa.c 华山剑法

inherit SKILL;

mapping *action = ({
([	"action" : "$N一招「白云出岫」，手中$w点向$n的$l",
	"lian"  :"$N使出一招「白云出岫」把手中$w向上削去......",
    "post_action":  (: call_other, WEAPON_D, "bash_weapon" :),
	"damage" : 20,
	"damage_type" : "刺伤"
]),
([	"action" : "$N使出「有凤来仪」，$w闪烁不定，刺向$n的$l",
	"lian"  :"$N使出「有凤来仪」，$w闪烁不定，刺向前方......",
    "post_action":  (: call_other, WEAPON_D, "bash_weapon" :),
	"damage" : 25,
	"damage_type" : "刺伤"
]),
([	"action" : "$N一招「天绅倒悬」，$w自上而下划出一个大弧，向$n劈砍下去",
    "lian"  :"$N反手一招「天绅倒悬」，$w自上而下划出一个大弧......",
    "post_action":  (: call_other, WEAPON_D, "bash_weapon" :),
	"damage" : 30,
	"damage_type" : "刺伤"
]),
([	"action" : "$N向前跨上一步，手中$w使出「白虹贯日」直刺$n的$l",
	"lian"  :"$N向前跨上一步，手中$w使出「白虹贯日」......",
    "post_action":  (: call_other, WEAPON_D, "bash_weapon" :),
	"damage" : 35,
	"damage_type" : "刺伤"
]),
([      "action" : "$N手中的$w一晃，使出「苍松迎客」直刺$n的$l",
		"lian"  :"$N手中的$w一晃，使出「苍松迎客」......",
        "post_action":  (: call_other, WEAPON_D, "bash_weapon" :),
        "damage" : 50,
        "damage_type" : "刺伤"
]),
});



int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
		
if ((int)me->query_skill("zixia-shengong", 1) < 20)
		return notify_fail("你的华山内功火候太浅。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("jingli") < 20)
		return notify_fail("你的精力不够。\n");
	me->add("jingli",-20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huashan-jianfa/" + action;
}
