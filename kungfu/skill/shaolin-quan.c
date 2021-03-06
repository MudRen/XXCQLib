// shaolin-quan.c 少林神拳
// 少林神拳是江湖上最普通的功夫之一,但功力深厚也自有妙处
// load 5/14/99
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([	"action" : "$N马步稳扎，一式「黑虎掏心」，左拳带虎虎风声直冲$n的$l而去",
	"damage" : 20,
	"parry"  : -10,
	"force"  : 90,
	"lvl"  : 0,
	"dodge"  : 10,
	"skill_name" : "黑虎掏心",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N轻轻跃上一小步，一式「落地分金」，双手握拳从半空猛地砸了下来",
	"damage" : 30,
	"parry"  : -5,
	"force"  : 120,
	"lvl"  : 10,
	"dodge"  : 0,
	"skill_name" : "落地分金",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N眼无视、耳无闻，一式「六丁开山」，双拳同时击出，直奔$n的$l而去",
	"damage" : 40,
	"parry"  : -15,
	"force"  : 100,
	"lvl"  : 20,
	"dodge"  : 5,
	"skill_name" : "六丁开山",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N踏上几步，一式「单龙出海」，左拳划一条斜线自左下到右上狠命击出",
	"damage" : 50,
	"parry"  : 0,
	"force"  : 110,
	"lvl"  : 30,
	"dodge"  : 0,
	"skill_name" : "单龙出海",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N吐气开声，一式「龙战于野」，双拳一前一后带起破空之声，击向$n的$l",
	"damage" : 60,
	"parry"  : -10,
	"force"  : 130,
	"lvl"  : 38,
	"dodge"  : -5,
	"skill_name" : "龙战于野",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N连续上步欺近$n，一式「双风灌耳」，双拳一左一右打向$n的两侧太阳穴",
	"damage" : 80,
	"parry"  : -20,
	"force"  : 130,
	"lvl"  : 46,
	"dodge"  : 5,
	"skill_name" : "双风灌耳",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N目露凶光，一式「饿虎扑食」，似下山猛虎，挥舞双拳扑向$n",
	"damage" : 100,
	"parry"  : -10,
	"force"  : 150,
	"lvl"  : 54,
	"dodge"  : 0,
	"skill_name" : "饿虎扑食",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N完全不顾自身，高高跃起，一式「猛龙过江」，双拳带风合身扑向$n",
	"damage" : 120,
	"parry"  : -15,
	"force"  : 170,
	"lvl"  : 60,
	"dodge"  : 10,
	"skill_name" : "猛龙过江",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }      

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
       return notify_fail("练少林神拳拳必须空手。\n");
    if ((int)me->query_skill("banruo-changong", 1) < 10 && (int)me->query_skill("wuxiang-shengong", 1) < 10)
       return notify_fail("你的内功火候不够，无法学少林神拳。\n");
    if ((int)me->query("max_neili") < 50)
       return notify_fail("你的内力太弱，无法练少林神拳。\n");
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
    level   = (int) me->query_skill("shaolin-quan",1);
    for(i = sizeof(action); i > 0; i--)
   if(level > action[i-1]["lvl"])
      return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 30)
       return notify_fail("你的体力太低了。\n");
    if ((int)me->query("neili") < 20)
       return notify_fail("你的内力不够练少林神拳。\n");
    me->receive_damage("qi", 25);
    me->add("neili", -5);
    return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if( me->query_skill("shaolin-quan",1) > 80 
	&& me->query_temp("leiting")
	&& random(me->query("str"))>random(victim->query("str"))
	&& me->query("neili")>50)
	{
		victim->receive_wound("qi", 50 + (me->query_skill("shaolin-quan",1)) / 2 );
		me->add("neili",-50);
		return HIR "$N拳风过处，只听到「喀啦」一声轻响，竟似$n身上发出的骨碎的声音！\n" NOR;
	}
	else if ( me->query_skill("shaolin-quan",1) > 160
	&& random(me->query("str")*me->query("combat_exp"))>random(victim->query("str")*victim->query("combat_exp"))
	&& random(me->query_skill("shaolin-quan",1))>130
	&& me->query("neili")>50)
	{
		victim->add("douzhi",-( 1 + random(me->query_skill("shaolin-quan",1)/10)));
		me->add("neili",-50);
		return HIW "$n被$N气势所逼，看起来斗志有些下降了。\n" NOR;
	}
}