// jingang.c
// by mulan

#include <ansi.h>
//inherit SKILL;
inherit FORCE;

string *parry_msg = ({
    "$n脸部神态依然，居然发出了一种隐约的淡金色的光辉,将全身罩住\n",
    "$n潜运金刚不坏神功,疯狂舍身的攻击，免却了后顾之忧。\n",
    "$n口中念念有词,对方的兵器只能伤及皮肉，不能毁其筋骨。\n",
    "$n猛吸一口真气,将全身穴道用真气封住,犹如铜墙铁壁一般。\n",
  });


int valid_enable(string usage) { return usage == "force" || usage=="parry"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("banruo-changong", 1) < 100)
       return notify_fail("你的般若禅功火候不够，无法学金刚不坏功。\n");
    if ((int)me->query("max_neili") < 1000)
       return notify_fail("你的内力太弱，无法学到神奇的少林绝学。\n");
    return 1;
}

int practice_skill(object me)
{
   return notify_fail("金刚不坏神功乃少林一绝，不能随意练习。\n");
}

string query_parry_msg(object weapon,object me,object victim)
{
   return parry_msg[random(sizeof(parry_msg))];
}
 
mixed hit_ob(object me, object victim, int damage_bonus,int factor)
{
   int damage;

   damage = 100 + random((int)me->query_skill("force",1)/2);

   if( !me->query_temp("weapon") && me->query("jiali")
   	&&
      random(me->query_skill("force",1)) > victim->query_skill("force",1)/2 )
   {
      
      victim->receive_damage( "qi", damage * 2 );
      victim->receive_wound( "qi", damage );
      victim->set("neili",victim->query("neili")/2);
      me->add("neili",damage);
      return "$n被$N的神奇的金刚不坏神功震伤了元气!\n";
   }
}
