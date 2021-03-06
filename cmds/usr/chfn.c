// chfn.c

inherit F_CLEAN_UP;
//还应该有网页地址，ICQ等！
void create() { seteuid(getuid()); }

int main(object me)
{
	object link;
	if( environment(me)->query_regroom() )
		return notify_fail("你现在正处在注册室里，这里不允许修改个人资料！\n");
	if( objectp(link = me->query_temp("link_ob")) ) 
	{
		write("\n为了确保你不会丢失你的密码，请务必如实输入以下信息：\n"+
			"您的出生日期[举例：1976年6月5日] ：");
		input_to("get_birthday", link);
		return 1;
    }
    return 0;
}
void get_birthday(string bir,object link)
{
	object body;
	int year,month,day;
	if(sscanf(bir,"%d年%d月%d日",year,month,day)!=3)
	{
		if(!objectp(body=link->query_temp("body_ob")))
			return;//不正常连线
		write("\n错误的格式！\n重新输入[举例：1976年6月5日] ：");
		input_to("get_birthday", link );
		return;
	}
	link->set("chfn/year",year);
	link->set("chfn/month",month);
	link->set("chfn/day",day);
	//显示设置信息
	if(!objectp(body=link->query_temp("body_ob")))
		return;//不正常连线！
	//显示下一个的提示信息！
	write("\n请设置你的密码提示问题：\n");
	input_to("get_question", link );
}

void get_question(string ques,object link)
{
	object body;
	if(ques!="")
		link->set("chfn/question",ques);
	else
	{
		if(!objectp(body=link->query_temp("body_ob")))
			return;//不正常连线
		write("\n请设置你的密码提示问题：\n");
		input_to("get_question", link );
		return;
	}
	if(!objectp(body=link->query_temp("body_ob")))
		return;//不正常连线
	write("\n请设置你的密码提示问题的答案：\n");
	input_to("get_answer", link );
	return;
}

void get_answer(string ans,object link)
{
	object body;
	if(ans!="")
		link->set("chfn/answer",ans);
	else
	{
		if(!objectp(body=link->query_temp("body_ob")))
			return;//不正常连线
		write("\n请设置你的密码提示问题的答案：\n");
		input_to("get_question", link );
		return;
	}
	if(!objectp(body=link->query_temp("body_ob")))
		return;//不正常连线
	write("\n你的 Email 地址 [" + link->query("email") + "]: ");
	input_to("get_email",link);
	return;
}

void get_email(string new_email,object link)
{
	object body;
	if( new_email != "" )
		link->set("email", new_email);
	write("您的自我介绍: (finger时显示)\n");
	if(!objectp(body=link->query_temp("body_ob")))
		return;//不正常连线！
	body->edit((: call_other, __FILE__, "get_profile", link :));
}

void get_profile(object link, string str)
{
	object body;
	link->set("profile", str);
	write("您的签名格式: (post时用)\n");
	if(!objectp(body=link->query_temp("body_ob")))
		return;//不正常连线！
	body->edit((: call_other, __FILE__, "get_signature", link :));
}

void get_signature(object link, string str)
{
	mapping tmp;
	if( strlen(str) > 400 )
		write("签名格式太长！请重新设定。\n");
	else
		link->set("signature", str);
	link->save();
	//这里应该显示一下全部的数据
	tmp=link->query("chfn");
	write("你的个人资料如下：\n"+
	"出生日期："+tmp["year"]+"年"+tmp["month"]+"月"+tmp["day"]+"日\n"+
	"电子邮件地址："+link->query("email")+"\n"+
	"密码提示问题："+tmp["question"]+"\n"+
	"密码提示问题答案："+tmp["answer"]+"\n"+
	"个人介绍："+link->query("profile")+"\n"+
	"签名档："+link->query("signature")+"\n");
}

int help()
{
write(@HELP
指令格式 : chfn

用途 : 用来修改 email address , 编辑自我介绍(finger 时看到)
       及签名(post 时用)。
HELP
     );
     return 1;
}
