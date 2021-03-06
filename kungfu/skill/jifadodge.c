// 特殊轻功.c

inherit SKILL;

string *dodge_msg = ({
        "但是$n身形飘忽，轻轻一纵，早已避开。\n",
        "$n身随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
        "可是$n侧身一让，$N这一招扑了个空。\n",
        "却见$n足不点地，往旁窜开数尺，躲了开去。\n",
	"$n不退反进，向前踏出一步，逼得$N中途撤招。\n",
	"$n左跨一步，右跨一步，一时间身影似乎变成了三个，把$N晃得眼花缭乱。\n",
	"$n身体后仰，一个「铁板桥」，闪开了$N这一招。\n",
	"$n脚步一错，一旋身闪到了$N的背后。\n",
        "$n身形微晃，有惊无险地避开了$N这一招。\n"
});

int valid_enable(string usage) 
{ 
	return (usage == "dodge") || (usage == "move"); 
}

int valid_learn(object me) { return notify_fail("这是在战斗中经验积累的结果，无招无式，怎么学？\n"); }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
