// qhlist1000.c

inherit SKILL;
#include <ansi.h>;

mapping *quest = ({
        ([	"quest_1":		"华阳杂货铺",
		"quest_2":		"前两天定的东西",
                "quest_3":		"定单",
                "quest_4":		"胡掌柜",
        ]),
        ([	"quest_1":		"汴梁城黑衣染坊",
		"quest_2":		"前两天送染的布",
                "quest_3":		"定单",
                "quest_4":		"冉毅然",
        ]),
        ([	"quest_1":		"汴梁城当铺",
		"quest_2":		"在那里抵押的东西",
                "quest_3":		"抵押单",
                "quest_4":		"刘亚父",
        ]),
        ([	"quest_1":		"汴梁城回春堂",
		"quest_2":		"前两天定的药材",
                "quest_3":		"定单",
                "quest_4":		"上太师",
        ]),
        ([	"quest_1":		"汴梁城杂货铺",
		"quest_2":		"前两天定的东西",
                "quest_3":		"定单",
                "quest_4":		"韦鸭毛",
        ]),
});

mapping query_quest()
{
        return quest[random(sizeof(quest))];
}
