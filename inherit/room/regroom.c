/* 注册器 v0.1 JackyBoy@CuteRabbit Studio 1999/7/12

注册器的房间版，不再使用自身代码发送邮件，而是采用/adm/daemons/emaild.c这个守护程序来
*/
#include <mudlib.h>

#ifdef SERVER_NAME
#else
#define SERVER_NAME "202.101.189.4"
#endif

#ifdef SERVER_PORT
#else
#define SERVER_PORT "5555"
#endif

inherit ROOM;

void init()
{
	add_action("do_register","register");
	add_action("do_register","zhuce");
}

int query_regroom()
{
	return 1;
}

string make_password()
{
	string id;
	int i;
	string *source=({"a","b","c","d","e","f","g","h","i",
		"j","k","l","m","n","o","p","q","r","s","t","u","v",
		"w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L",
		"M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
		"0","1","2","3","4","5","6","7","8","9"});
	id="";
	for(i=random(3)+6;i>0;i--)
	{
		id=id+source[random(sizeof(source))];
	}
	return id;
}

int do_register(string dest)
{
	//当玩家是忘记口令是不能再允许register来设置email了，当然如果未注册过就可以设置email
	object me,linkob;
	string pass,id_num,msg;
	int i;
	me=this_player(1);
	linkob=me->query_temp("link_ob");
	if(me->query("registered"))
	{
		//这时应该进行取回密码操作！不允许设置email地址！
		dest=linkob->query("email");
	}
	if( !dest||!sscanf(dest,"%*s@%*s.%*s") )
		return notify_fail("电子邮件地址错误："+dest+"。\n");
	//设置玩家的注册信息
	pass=make_password();//生成随机密码
	if(!linkob->set("password", crypt(pass,0) ))
		write("password seting is fail!\n");
	linkob->set("email",lower_case(dest));
	me->set("email",lower_case(dest));
	//增加注册玩家数，一个玩家只计算一次发信！
	if(me->query("send_reg_email")!=1)
	{
		id_num=read_file(IDUSER,1);
		i=atoi(id_num); 
		i++;
		write("\n你是第"+i+"个注册的朋友！");
		id_num=sprintf("%d",i);
		write_file(IDUSER,id_num,1);//要设置正确的写权限！
		//在inherit目录内能不能写这个文件呢？？？
	}
	me->set("startroom","/d/bianliang/guangming");
	me->set("send_reg_email",1);
	me->save();
	linkob->save();
	//发出注册信件
	write("\n发送到"+dest+"的邮件已经加入发送队列！\n如果你不能收到此信，请重新注册！\n");
	msg="\n"+"(注意：本信件如果你同时收到多封，请以最后一封为准！)\n\n"+
		me->name(1)+"("+me->query("id")+")，你好！欢迎光临【"+CHINESE_MUD_NAME+"】！\n\n"+
		"为了能完成你在本游戏中的注册手续，请使用下面提供的密码登录游戏完成注册。\n\n你的注册密码是："+
		pass+"\n游戏地址为："+SERVER_NAME+"\n端口为："+SERVER_PORT+"\n\n"+
		"为了帐号不被他人窃用，请在登录后立即使用passwd命令修改你的密码：\n"+
		"    passwd的参数有两个，使用passwd或者passwd -1表示修改你的正式密码！\n"+
		"    使用passwd -2则修改你的备用密码，也就是最初登录时使用的密码。\n"+
		"    备用密码丢失并不会导致你丢失你的角色(只要你原来设置的email地址是正确的)。\n"+
		"    但是却可以重新设置你的密码使你不断收到注册信件！\n"+
		"如果你已经注册过并丢失密码，请用最初申请帐号时的备用密码进入！然后重新用\n"+
		"register或者zhuce命令把密码发回你的信箱。\n"+
		"而你所输入的个人资料信息将用于帮助你在忘记所有密码的时候自动重新设置口令！\n"+
		"在游戏进行总你可以随时使用chfn命令修改个人资料信息！\n"+
		"在游戏进行中请使用help命令获取详细帮助，或者访问本游戏主页！\n";
	//还应该增加一些基本的游戏信息，以及基本的帮助信息！
	EMAIL_D->add_email("小雪初晴",dest,"注册信件!",msg);//未判断是否使用指定的smtp
	return 1;
}
