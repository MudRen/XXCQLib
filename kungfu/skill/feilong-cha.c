     // feilong-cha.c -飞龙叉法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
  ([      "action" : "$N握紧手中$w一招「夜叉探海」点向$n的$l",
        "force" : 50,
        "dodge" : 40,
          "damage" : 60,
        "lvl"    : 0,
         "skill_name" : "夜叉探海", 
           "damage_type" : "刺伤"
]),
  ([      "action" : "$N向前跨上一步，手中$w使出「画龙点睛」刺向$n的喉部",
        "force" : 90,
        "dodge" : 80,
      "damage" : 50,
        "lvl"    : 20,
         "skill_name" : "画龙点睛",
           "damage_type" : "刺伤"
]),
      ([      "action" : "只见$N抡起手中的$w，使出「神龙出水」万点金光洒向$n",
        "force" : 90,
        "dodge" : 70,
            "damage" : 90,
        "lvl"    : 40,
       "skill_name" : "神龙出水",
           "damage_type" : "刺伤"
]),
  ([      "action" : "$N使出「混沌初开」，手中$w如刮起狂风一般闪烁不定,刺向$n",
        "force" : 200,
        "dodge" : 80,
         "damage" : 105,
        "lvl"    : 80,
          "skill_name" : "混沌初开",
          "damage_type" : "刺伤"
]),
         ([      "action" : "$N随手使出叉法之奥义「潜龙飞天」，反手一$w刺向$n",
        "force" : 300,
        "dodge" : 90,
                 "damage" : 110,
        "lvl"    : 100,
        "skill_name" : "「潜龙飞天」",
          "damage_type" : "刺伤"
]),
             ([      "action" : "$N吸了一口真气使出叉法之绝招「龙腾四海」手中的$w如发怒的金龙刺向 $n。 \n",
        "force" : 400,
        "dodge" : 100,
        "damage" : 350,
        "lvl"    : 150,
          "skill_name" : "HIY「龙腾四海」"NOR,
             "damage_type" : "刺伤"
]),
});


           int valid_enable(string usage) { return (usage == "fork") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 100)
                  return notify_fail("你对调理气息的火候不够，无法学「飞龙叉法」。\n");
        if ((int)me->query("max_neili") < 300)
               return notify_fail("你的内力太弱，无法练「飞龙叉法」。\n");
        if ((int)me->query("shen") < 10000)
        	return notify_fail("用破山刀法时要满腔正气，否则会反受其害。\n");
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
     level   = (int) me->query_skill("feilong-cha",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/4)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "fork")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 50)
               return notify_fail("你的体力不够练「飞龙叉法」。\n");
        if ((int)me->query("neili") < 50)
                 return notify_fail("你的内力不够练「飞龙叉法」。\n");
        me->receive_damage("qi", 15);
        return 1;
}
string perform_action_file(string action)
{
              return __DIR__"feilong-cha/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if( damage_bonus < 100 ) return 0;
    if(me->query("douzhi")<1)
      return 0;

        if( random(damage_bonus/2) > victim->query_str() ) {
               if ( (( (int)victim->query("shen") - (int)me->query("shen") ) > 50000) && ( (int)me->query("shen") < 0 )  )
			{
				me->add("douzhi",-30);
				message_vision("$N骇然发现手中的兵器竟然受到对方正气的吸引而不听使唤了。$N斗志下降了！\n",me);              
				return 1;
			}
                victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                  return RED "只见$n一个不留神，被$N的$w刺的血肉模糊！\n"NOR;
        }
}


