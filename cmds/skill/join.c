// join.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob, old_app;
	mapping party;

	if (me->is_busy())
		return notify_fail("你现在正忙着其他事情。\n");

	if( !arg ) 
		return notify_fail("指令格式：join | jiaru [cancel]|<对象>\n");

	if( arg=="cancel" ) {
		old_app = me->query_temp("pending/party");
		if( !objectp(old_app) )
			return notify_fail("你现在并没有希望任何人为你引荐的意思。\n");
		write("你改变主意不想加入" + old_app->name() + "所属的帮派了。\n");
		me->delete_temp("pending/party");
		return 1;
	}

	if( !(ob = present(arg, environment(me)))
	||	!ob->is_character() )
		return notify_fail("你希望帮你引荐的人在这里吗？？\n");

	if( !living(ob) ) 
		return notify_fail("你还是先把" + ob->name() + "弄醒了在谈加入帮派的事吧。\n");

	if( ob==me ) 
		return notify_fail("你自己组织门派了？\n");

	if( userp(ob))
		return notify_fail("真对不起，在这个世界里不能拜玩家为师。\n");

	if( me->is_join_of(ob)) {
		return notify_fail("你已经加入这个帮派了。\n");
	}

	if( !mapp( ob->query("party") ) )
		return notify_fail(ob->name() + "不属于任何帮派，自然也没法引荐你加入。\n");

	if( (object)ob->query_temp("pending/party") == me )
	{
		if( (string)me->query("party/party_name") != (string)ob->query("party/party_name") )
		{
			message_vision(
				"$N决定背叛以前的帮派，改投入$n所属的帮派！！\n\n"
				"$N肃立在$n身边，朗声道：“本人愿为" + (string)ob->query("party/party_name")
				+ "誓死效力！\n\n",me, ob);
		}
		else
			message_vision(
				"$N决定加入$n所属的门派。\n\n"
				"$N肃立在$n身边，朗声道：“本人愿为" + (string)ob->query("party/party_name")
				+ "誓死效力！\n\n",me, ob);
		ob->recruit_party(me,ob->query("rank"));
		ob->delete_temp("pending/party");

		party = me->query("party");
		printf(HIY"恭喜您成为%s的%s。\n"NOR, 
			me->query("party/party_name"),
			me->query("party/rank"));
		return 1;
	
	} else {
		old_app = me->query_temp("pending/party");
		if( ob==old_app )
			return notify_fail("你想加入" + ob->name() + "所属的门派，但是对方还没有答应。\n");
		else if( objectp(old_app) ) {
			write("你改变主意不想加入" + old_app->name() + "的门派了。\n");
		}

		message_vision("$N向$n一拱手道：“您可否为在下引荐加入贵帮？”\n", me, ob);
		me->set_temp("pending/party", ob );
		ob->attempt_join(me);
		return 1;
	}
}


int help(object me)
{
        write(@HELP
指令格式 : apprentice|bai [cancel]|<对象>
 
这个指令能让你拜某人为师，如果对方也答应要收你为徒的话，就会立即行
拜师之礼，否则要等到对方用 recruit 指令收你为弟子才能正式拜师。

请注意你已经有了师父，又背叛师门投入别人门下，新师傅将不会教你他的
绝活（１０Ｋ以下不记为叛师）。

如果对你的师父使用这个指令，会变成向师父请安。

目前本MUD不能拜玩家为师。
 
请参考相关指令 expell、recruit
HELP
        );
        return 1;
}
