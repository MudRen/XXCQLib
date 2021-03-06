// 宠物使用的武功
// By 山猫Adx @ snow 99-12-12

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N扑上来张嘴往$n的$l狠狠地一咬",
	"dodge": 30,
	"damage_type": "瘀伤"
]),
([      "action": "$N用头往$n的$l用力一撞",
	"dodge": 10,
	"damage_type": "瘀伤"
]),
([      "action": "$N用后腿往$n的$l用力一蹬",
	"dodge": -20,
	"damage_type": "瘀伤"
]),
([      "action": "$N用爪子往$n的$l一抓",
	"dodge": 10,
	"damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }   

mapping query_action()
{
	if ( random(5)==3 ) {
		return ([
		"action": HIR"$N突然，全身毛立了起来，发狂般的抓向$n"NOR,
		"damage_type": "抓伤"]);
	}
	return action[random(sizeof(action))];
}
