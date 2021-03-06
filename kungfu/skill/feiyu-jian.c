// feiyu-jian.c 飞鱼剑法
// Created by Atlus 1999.7.23.
//


inherit SKILL;

mapping *action = ({
([	"action" : "$N使一招［青山隐隐］，手中$w狂风骤雨般地向$n的$l连攻数剑",
//	"parry_action" : "",
	"damage" : 20,
	"parry"  : 0,
	"force"  : 30,
	"lvl"  : 0,
	"dodge"  : -5,
	"skill_name" : "青山隐隐",
	"damage_type" : "刺伤"
]),
([	"action" : "$N手一抖，一招［秋尽木凋］手中的$w幻成一片剑花，象秋风中的落叶一样散向$n的$l。",
//	"parry_action" : "",
	"damage" : 30,
	"parry"  : -5,
	"force"  : 30,
	"lvl"  : 15,
	"dodge"  : -5,
	"skill_name" : "秋尽木凋",
	"damage_type" : "刺伤"
]),
([	"action" : "$N身影晃动，剑锋发出一阵金光，一招［断桥明月］，手中的$w，从中路突然砍至$n的$l",
//	"parry_action" : "",
	"damage" : 50,
	"parry"  : 10,
	"force"  : 60,
	"lvl"  : 25,
	"dodge"  : 0,
	"skill_name" : "断桥明月",
	"damage_type" : "砍伤"
]),
([	"action" : "$N舞动$w，身形一转，一招［玉人吹箫］挟著闪闪剑光直直刺向$n的$l",
//	"parry_action" : "",
	"damage" : 50,
	"parry"  : -20,
	"force"  : 30,
	"lvl"  : 35,
	"dodge"  : -20,
	"skill_name" : "玉人吹箫",
	"damage_type" : "刺伤"
]),
([	"action" : "$N手中$w迅速抽出，瞬息三闪，蒙起三朵剑花，向$n刺去，正是一招［梦笔生花］",
//	"parry_action" : "",
	"damage" : 65,
	"parry"  : -15,
	"force"  : 50,
	"lvl"  : 50,
	"dodge"  : -15,
	"skill_name" : "梦笔生花",
        "damage_type" : "刺伤"
]),
([	"action" : "$N身行跃起，手中$w快速突刺，一招「飞鱼出海」，凌空刺向$n的$l",
//	"parry_action" : "",
	"damage" : 70,
	"parry"  : 0,
	"force"  : 70,
	"lvl"  : 60,
	"dodge"  : 0,
	"skill_name" : "飞鱼出海",
	"damage_type" : "刺伤"
]),
([	"action" : "$N身形拔地而起，手中$w一振，剑气徐徐涌出，一招「烟云漂渺」罩向$n的$l",
//	"parry_action" : "",
	"damage" : 85,
	"parry"  : 0,
	"force"  : 90,
	"lvl"  : 70,
	"dodge"  : -10,
	"skill_name" : "烟云漂渺",
	"damage_type" : "刺伤"
]),
([	"action" : "$N手中$w先是划出一片剑光，突然一招[浑水摸鱼]，直向$n的$l连刺数剑",
//	"parry_action" : "",
	"damage" : 120,
	"parry"  : -20,
	"force"  : 120,
	"lvl"  : 85,
	"dodge"  : -10,
	"skill_name" : "浑水摸鱼",
	"damage_type" : "刺伤"
]),
([	"action" : "$N突然抬头望天，似乎完全不管$n的攻势，手中$w却连环刺出，每剑都直指$n的破绽，真是[杞人忧天]",
//	"parry_action" : "",
	"damage" : 180,
	"parry"  : -20,
	"force"  : 140,
	"lvl"  : 120,
	"dodge"  : -15,
	"skill_name" : "杞人忧天",
	"damage_type" : "刺伤"
]),

});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

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
	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("你的基本内功太低了。\n");
	return 1;
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("没有剑怎么练习飞鱼剑法？\n");
	
	if ((int)me->query("jingli") < 50)
		return notify_fail("你精神状态太差了，还是歇一会再练吧。。\n");
	me->add("jingli",-25);
	return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
		level   = (int) me->query_skill("feiyu-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
	return __DIR__"feiyu-jian/" + action;
}
