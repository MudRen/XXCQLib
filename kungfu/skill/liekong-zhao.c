// liekong-zhao.c 裂空爪
// 平均damage:120 平均force:90 平均dodge:5 平均parry:-5
// 裂空爪的特点在于威力较大，招架较难，躲避较易，等级高时有特殊效果
// By Load

inherit SKILL;

mapping *action = ({
([      "action" : "$N目露凶光，脚步不动，右臂疾伸，陡然竟似长了尺许，一式「锁喉」，右手成爪直探$n的喉咙",
        "damage" : 60,
        "parry"  : -5,
        "force"  : 50,
        "lvl"  : 0,
        "limb"  : "喉咙",
        "dodge"  : 10,
        "skill_name" : "锁喉",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N踏上一步，一式「穿胸」，右手仿佛是一把利刃，直插$n的左胸，左手横胸，防范一切反击",
        "damage" : 70,
        "parry"  : 5,
        "force"  : 60,
        "lvl"  : 12,
        "limb"  : "左胸",
        "dodge"  : -5,
        "skill_name" : "穿胸",
        "damage_type" : "刺伤"
]),
([      "action" : "$N突然欺近$n身旁，一式「断腕」，左手成爪向$n的左腕刁了下去，右手紧跟着一掌拍出",
        "damage" : 90,
        "parry"  : -5,
        "force"  : 70,
        "lvl"  : 24,
        "limb"  : "左腕",
        "dodge"  : 10,
        "skill_name" : "断腕",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N上手就是一招「折臂」，左爪横扫逼得$n抬臂来挡，右臂曲成肘飞砸而下",
        "damage" : 100,
        "parry"  : -15,
        "force"  : 80,
        "lvl"  : 36,
        "limb"  : "左臂",
        "dodge"  : 0,
        "skill_name" : "折臂",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N闷哼一声，双手成爪贯足真力，一式「碎骨」，一前一后，朝$n的$l攻了出去",
        "damage" : 120,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 48,
        "dodge"  : 10,
        "skill_name" : "碎骨",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N飞身而起，一式「摧心」，双爪带起阴风，携撕心裂肺之势抓向$n的$l",
        "damage" : 140,
        "parry"  : 5,
        "force"  : 110,
        "lvl"  : 60,
        "dodge"  : 5,
        "skill_name" : "摧心",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N仰天大笑三声，一式「撕天」，双爪一错，疾伸而出，似乎要撕裂所有敢于阻挡的东西",
        "damage" : 180,
        "parry"  : -5,
        "force"  : 120,
        "lvl"  : 75,
        "dodge"  : 5,
        "skill_name" : "撕天",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形一长，如丈八天神，双臂一展，遮天蔽日，双爪带着刺耳尖啸「裂空」而下，$n立时变了脸色",
        "damage" : 200,
        "parry"  : -20,
        "force"  : 130,
        "lvl"  : 90,
        "dodge"  : 5,
        "skill_name" : "裂空",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return (usage == "claw") || (usage == "parry"); }

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
        if ((int)me->query_skill("xuantian-xinfa", 1) < 25)
                return notify_fail("你的玄天心法火候不够。\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("练习裂空爪不能持有武器\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练裂空爪。\n");
        if ((int)me->query("jingli") < 40)
                return notify_fail("你精神过于疲劳，无法练习裂空爪。\n");
        me->add("neili", -10);
        me->add("jingli",-25);
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
                level   = (int) me->query_skill("liekong-zhao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
        return __DIR__"liekong-zhao/" + action;
}

