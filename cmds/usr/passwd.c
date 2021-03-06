// passwd.c

inherit F_CLEAN_UP;

string temp;
int help();

int main(object me, string arg)
{
	object ob;
	//在注册室里应该不允许做修改密码的动作！
	if( environment(me)->query_regroom() )
		return notify_fail("你现在正处在注册室里，这里不允许修改密码！\n");
	if( me != this_player(1) ) return 0;
	if(arg&&arg!="-1"&&arg!="-2")
		return help();
	if(!arg||arg=="-1")
		temp="-1";
	if(arg&&arg=="-2")
		temp="-2";
	ob = me->query_temp("link_ob");
	if( !ob ) return 0;
	while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");

	write("为了安全起见，请先输入您原来的密码：");
	input_to("get_old_pass", 1, ob);
	return 1;
}

void get_old_pass(string pass, object ob)
{
	string old_pass;

	write("\n");
	old_pass = (temp=="-1")?ob->query("password"):ob->query("temp_password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("密码错误！\n");
		return;
	}
	write("请输入新的密码：");
	input_to("get_new_pass", 1, ob );
}

void get_new_pass(string pass, object ob)
{
	write("\n请再输入一次新的密码：");
	input_to("confirm_new_pass", 1, ob, crypt(pass,0));
}

void confirm_new_pass(string pass, object ob, string new_pass)
{
	write("\n");
	if( crypt(pass, new_pass)!=new_pass ) {
		write("对不起，您输入的密码并不相同，继续使用原来的密码。\n");
		return;
	}
	seteuid(getuid());
	if(temp=="-1")
	{
		if( !ob->set("password", new_pass) ) 
		{
			write("密码变更失败！\n");
			return;
		}
	}
	else
	{
		if( !ob->set("temp_password", new_pass) ) 
		{
			write("备用密码变更失败！\n");
			return;
		}
	}	
	ob->save();
	(temp=="-1")?write("密码变更成功!\n"):write("备用密码变更成功!\n");
}

int help()
{
	write(@HELP
指令格式 : passwd -[1|2]
这个指令可以修改你的人物密码。
带参数1或不带表示修改当前的正式密码，带参数2表示要修改最初注册用户的备用密码。
使用备用密码登录注册后可以重新获取正式密码，所以请你一定要保密备用密码。
HELP
    );
    return 1;
}
 
