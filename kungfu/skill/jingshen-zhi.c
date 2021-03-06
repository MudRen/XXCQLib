//jingshen-zhi.c -惊神指
//惊神指共24指,以24节气命名,特殊攻击待定
//惊神指攻击力较高,但出招较慢,且修炼较难,受悟性影响较大

inherit SKILL;

mapping *action = ({
([	"action" : "$N右手背后，左手平胸，小指轻点，一指「立春」带蒙蒙暖意激射向$n的$l",
	"force" : 30,
        "dodge" : -5,
	"lvl" : 0,
	"damage": 10,
	"skill_name" : "立春",
	"damage_type" : "刺伤"
]),
([	"action" : "$N身形加快，右手中指虚点几下，突然食指一挺，一式「雨水」射向$n",
	"force" : 60,
        "dodge" : -5,
	"lvl" : 9,
	"damage": 20,
	"skill_name" : "雨水",
        "damage_type" : "刺伤"
]),
([	"action" : "$N突然越至半空，一式「惊蛰」，居高临下，双手拇指两道指气沛然而出",
	"force" : 90,
        "dodge" : 5,
	"lvl" : 18,
	"damage": 30,
	"skill_name" : "惊蛰",
        "damage_type" : "刺伤"
]),
([	"action" : "$N侧身微转，悄然出指，一式「春分」自左手无名指疾射而出",
	"force" : 120,
        "dodge" : 5,
	"damage": 40,
	"lvl" : 27,
	"skill_name" : "春分",
        "damage_type" : "刺伤"
]),
([	"action" : "$N肃然正目，一指略带悲凉、哀惋的「清明」已自右手中指射向$n的$l",
	"force" : 150,
        "dodge" : 15,
	"damage": 50,
	"lvl" : 36,
	"skill_name" : "清明",
        "damage_type" : "刺伤"
]),
([	"action" : "$N双手轻和，无名指紧并，一指「谷雨」和两指之气向$n当面射去",
	"force" : 180,
        "dodge" : 20,
	"damage": 60,
	"lvl" : 45,
	"skill_name" : "谷雨",
        "damage_type" : "刺伤"
]),
([	"action" : "$N形如急电，突然欺近$n，一指「立夏」似一支火焰缓缓按了下去",
	"force" : 210,
        "dodge" : 25,
	"damage": 70,
	"lvl" : 54,
	"skill_name" : "立夏",
        "damage_type" : "刺伤"
]),
([	"action" : "$N一式「小满」，左手五指乱弹，一束束锐利无俦的指气，向$n的$l射去",
	"force" : 240,
        "dodge" : 30,
	"damage": 80,
	"lvl" : 63,
	"skill_name" : "小满",
        "damage_type" : "刺伤"
]),
([	"action" : "$N迈步疾走，刹那间已然绕到了$n的身后，以指气化剑气，一指「芒种」从后面刺向了$n",
	"force" : 280,
        "dodge" : 35,
	"damage": 90,
	"lvl" : 72,
	"skill_name" : "芒种",
        "damage_type" : "刺伤"
]),
([	"action" : "$N舒臂展指，一指炙热无比的「夏至」自左手拇指而出，穿向$n的$l",
	"force" : 320,
        "dodge" : 50,
	"damage": 100,
	"lvl" : 81,
	"skill_name" : "夏至",
        "damage_type" : "刺伤"
]),
([	"action" : "$N突然向前抢攻，$n正忙于招架，$N身形一顿，一式「小暑」顷刻已打到面前",
	"force" : 360,
        "dodge" : 35,
	"damage": 110,
	"lvl" : 90,
	"skill_name" : "小暑",
        "damage_type" : "刺伤"
]),
([	"action" : "$N左手拇指一连三指，指指相叠，化一缕带些许太阳光芒的「大暑」射向$n",
	"force" : 400,
        "dodge" : 35,
	"damage": 120,
	"lvl" : 99,
	"skill_name" : "大暑",
        "damage_type" : "刺伤"
]),
([	"action" : "$N右手小指一指「立秋」，一缕指风飘然掠向$n的$l，$n几乎毫无察觉",
	"force" : 440,
        "dodge" : 35,
	"damage": 130,
	"lvl" : 108,
	"skill_name" : "立秋",
        "damage_type" : "刺伤"
]),
([	"action" : "$N左手小指发一缕似有似无、诡异无比的「处暑」，$n看起来似乎有些不知所措",
	"force" : 480,
        "dodge" : 35,
	"damage": 140,
	"lvl" : 117,
	"skill_name" : "处暑",
        "damage_type" : "刺伤"
]),
([	"action" : "$N轻歌曼行，飘然而起，一指轻巧的「白露」凌空而下，叫人无从躲起",
	"force" : 520,
        "dodge" : 35,
	"damage": 150,
	"lvl" : 126,
	"skill_name" : "白露",
        "damage_type" : "刺伤"
]),
([	"action" : "$N以指代剑，中路直刺，一式「秋分」，全无花样，简单实用",
	"force" : 560,
        "dodge" : 35,
	"damage": 160,
	"lvl" : 135,
	"skill_name" : "秋分",
        "damage_type" : "刺伤"
]),
([	"action" : "$N一指「寒露」，乎左乎右，乎上乎下，几乎封住了$n的所有退路",
	"force" : 610,
        "dodge" : 35,
	"damage": 170,
	"lvl" : 144,
	"skill_name" : "寒露",
        "damage_type" : "刺伤"
]),
([	"action" : "$N天马行空，十指空点，「霜降」一式水银泻地般的攻向$n的$l",
	"force" : 660,
        "dodge" : 35,
	"damage": 180,
	"lvl" : 153,
	"skill_name" : "霜降",
        "damage_type" : "刺伤"
]),
([	"action" : "$N左手无名指轻点，右手无名指追加一指，两指力一和，一指迅疾的「立冬」点向$n",
	"force" : 710,
        "dodge" : 35,
	"damage": 190,
	"lvl" : 162,
	"skill_name" : "立冬",
        "damage_type" : "刺伤"
]),
([	"action" : "$N指风带阵阵寒意，但见一式“小雪”，左手五指点五道冻气罩向$n的要害",
	"force" : 760,
        "dodge" : 35,
	"damage": 200,
	"lvl" : 171,
	"skill_name" : "小雪",
        "damage_type" : "刺伤"
]),
([	"action" : "$N左右手连点十余指，一式「大雪」恰似满天飞雪扑向$n",
	"force" : 810,
        "dodge" : 35,
	"damage": 230,
	"lvl" : 180,
	"skill_name" : "大雪",
        "damage_type" : "刺伤"
]),
([	"action" : "$N脚步虚晃，指气带起一股寒风，一指「冬至」变穿相$n的$l",
	"force" : 860,
        "dodge" : 35,
	"damage": 260,
	"lvl" : 185,
	"skill_name" : "冬至",
        "damage_type" : "刺伤"
]),
([	"action" : "$N身形微展，飘开三丈，左手食指并右手食指同点，一式「小寒」攻了出去",
	"force" : 910,
        "dodge" : 35,
	"damage": 290,
	"lvl" : 190,
	"skill_name" : "小寒",
        "damage_type" : "刺伤"
]),
([	"action" : "$N眼中精光暴涨，十指乱弹，一式「大寒」带无匹的寒意罩向$n周身",
	"force" : 960,
        "dodge" : 35,
	"damage": 320,
	"lvl" : 195,
	"skill_name" : "大寒",
        "damage_type" : "刺伤"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_combine(string combo) { return combo=="yingzhao-gong"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练惊神指必须空手。\n");
	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("jingshen-zhi", 1)/2)
		return notify_fail("你的基本指法火候不够，无法继续学惊神指。\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练惊神指。\n");
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
		level   = (int) me->query_skill("jingshen-zhi",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 30)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练惊神指。\n");
	me->receive_damage("qi", 30);
	me->add("neili", -10);
	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"jingshen-zhi/" + action;
}

