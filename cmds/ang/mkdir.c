// mkdir.c

inherit F_CLEAN_UP;

int help();

int main(object me, string arg)
{
	string dir;

	if(!arg) return help();

	dir = resolve_path(me->query("cwd"), arg);

	seteuid(geteuid(me));
	if( mkdir(dir) )
		write("Ok.\n");
	else
		write("你没有在这里建子目录的权利。\n");
	return 1;	
}

int help()
{
	write(@HELP
指令格式 : mkdir <子目录名>

建立一个子目录。
HELP
	);
	return 1;
}
