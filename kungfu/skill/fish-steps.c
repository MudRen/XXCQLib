
// SKILL:fish-steps.c
// Created by Atlus 1999.7.23

inherit SKILL;

string *dodge_msg = ({
        "但是$n身形飘忽，一招「穿云而出」腾空而起，十分轻易的避开这一击。\n",
        "$n身随意转，一招「鱼游四海」，全身化作无数虚影掠出一丈之外。\n",
        "$n气聚丹田，一招「脱袍让位」，身形急缩，躲开$N那致命一击。\n",
        "$n身形晃动，一招「翻江搅海」，侧身一扭，掠出七尺之外。\n",
        "可是$n使一招「如鱼得水」，身子轻轻飘了开去，早已绕到$N身後！\n",
        "$n早已使出一式[如影随形]，步法飘忽不定，$N的攻击失去了准头，反被$n欺身上前！ \n",
        "$n突然一沉，身子在空中成横一字形，像一片柳叶飞到水平的弧度，闪开了$N的一击！ \n",
});

int valid_enable(string usage)
{
        return (usage=="dodge");
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 30 )
                return notify_fail("你的体力太低了，先休息一会儿吧。\n");
        me->receive_damage("qi", 30);
        return 1;
}
int effective_level() { return 15;}

int learn_bonus()
{
        return 0;
}
int practice_bonus()
{
        return 0;
}
int black_white_ness()
{
        return 20;
} 
string perform_action_file(string action)
{
	return __DIR__"feiyu-steps/" + action;
}

