// by xiha@hslj2  05/11/1999  
// last modified by xiha@workgroup on Aug 26,1999
#include <ansi.h>
inherit F_CLEAN_UP;
//string replace_color(string,int);
//此函数被移动到/adm/simul_efun/message.c里作为sim_efun使用！
//如果第二个函数为0表示清除颜色控制！否则为将$HIW$等字符串替换为颜色控制代码

int main(object me, string arg)
{
	int i, flag = 0;
	object ob;
	string mission, wname, wmin, file;
	string *wmission;
	if( me!=this_player(1) ) return 0;
	if( !arg || sscanf(arg, "%s %s", arg, mission)!=2 )
		return notify_fail("指令格式：setmission <使用者> (目前任务)\n");
	//其实这里只要判断一下是否在巫师列表里就OK了
	if( !objectp(ob = present(arg, environment(me))) || !userp(ob) )
		return notify_fail("你只能改变当前使用者的任务。\n");
	mission = replace_color( mission, 1);
	file=read_file("/adm/etc/wizmission");
	if(file)
		wmission = explode(file, "\n");
	else
		wmission = ({});
	for(i=0; i<sizeof(wmission); i++)
	{
		if( wmission[i][0]=='#' || sscanf(wmission[i], "%s %s", wname, wmin)!=2 ) continue;
		if( wname==ob->query("id") )
		{
			wmission[i] = sprintf("%s %s\n", wname, mission);
			flag = 1;
			break;
		}
	}
	for( file = "", i=0; i<sizeof(wmission); i++) file += wmission[i] + "\n";
	if(!flag)
		write_file("/adm/etc/wizmission", ob->query("id") + " " + mission + "\n", 0);
	else
		write_file("/adm/etc/wizmission", file, 1);
	message_vision("$N将$n的工作任务改为 " + mission + " 。\n", me, ob);
	return 1;
}
        
int help(object me)
{
        write(@HELP
指令格式 : setmission <某人> (目前任务)
用来改变巫师当前工作任务的说明，配套 wizlist 使用。
HELP
        );
        return 1;
}

