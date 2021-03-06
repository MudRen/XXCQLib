// state.c

#include <ansi.h>

inherit F_CLEAN_UP;
int help();
int main(object me, string arg)
{
	if(!arg) return help();
	if( strlen(arg) > 24 )
		return notify_fail("你的状态要那么长才能描述清楚吗？\n");
	if(arg=="cancel")
	{
		me->delete_temp("state");
		write("状态已被清除。\n");
		return 1;
	}
	me->set_temp("state", arg);
	write("设置状态为：<"+arg+">\n");
	return 1;
}
int help()
{
	write(@HELP
指令格式 : state <状态名字> | cancel
	设置自己的状态：
	比如 state 找BUG中,那么别人look you的时候在名字后就会显示"<找BUG中>"。
	参数cancel取消状态显示。
HELP
	);
	return 1;
}
