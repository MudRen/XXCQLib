// reply.c

#include <ansi.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string target, mud;
	object obj;

	if( !arg || arg=="" )
		return notify_fail("你要回答什么？\n");

	if( !stringp(target = me->query_temp("ask_you")) )
		return notify_fail("刚才没有人向你询问。\n");

        if (me->ban_say())
                return 0;

	obj = find_player(target);
	if( !obj )
		return notify_fail("刚才向你询问的人现在无法听见你，或者已经离开游戏了。\n");

        if( environment(obj) != environment(me) )
                return notify_fail("刚才向你询问的人现在不再这里了。\n");

	message_vision("$N回答$n：“" + arg + "”\n" NOR, me, obj);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：reply <讯息>

你可以用这个指令和刚才用 tell 和你说话的使用者说话。

see also : tell
HELP
	);
	return 1;
}
