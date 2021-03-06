// recruit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	mapping party;
	ob = present(arg, environment(me));

	if (userp(me)) return notify_fail("这个世界暂时不许玩家为玩家引荐。\n");

	if((ob->query("party")) && ((string)me->query("party/party_name") != (string)ob->query("party/party_name") ))
	{
		message_vision(
			"$N决定背叛以前的帮派，改投入$n所属的帮派！！\n\n"
			"$N肃立在$n身边，朗声道：“本人愿为" + (string)ob->query("party/party_name")
			+ "誓死效力！\n\n",ob, me);
		me->set("score", 0);
		if (me->query("combat_exp") > 10000)
			me->add("betrayer", 1);
	} else
		message_vision(
			"$N决定加入$n所属的门派。\n\n"
			"$N肃立在$n身边，朗声道：“本人愿为" + (string)me->query("party/party_name")
			+ "誓死效力！\n\n",ob, me);
	me->recruit_party(ob,me->query("rank"));
	ob->delete_temp("pending/party");

	party = ob->query("party");
	tell_object(ob,HIY"恭喜您成为"+ob->query("party/party_name")+"的"+ob->query("party/rank")+"。\n"NOR); 

		return 1;
	
}


int help(object me)
{
        write(@HELP
指令格式 : recruit|shou [cancel]|<对象>
 
这个指令能让你收某人为弟子, 如果对方也答应要拜你为师的话.
 
See Also:	apprentice
HELP
        );
        return 1;
}
