#define CK_DELAY 10*1
#define TIME_OUT 30*1
#define DEBUG

#include <ansi.h>
#include <net/dns.h>
#include <net/telnet.h>
#include <net/socket.h>
#include <net/socket_errors.h>
#include <socket_err.h>
#include <mudlib.h>

inherit F_DBASE;
//建立连接使用的socket号和发送标志
nosave int my_socket;
//问题在于如何判断断线？！

nosave int session_id=0;
nosave mapping cur_session=([]);// object sob,string cmd
nosave int cur_sid=0;
nosave int timeout_running=0;
nosave string server_ip="127.0.0.1";
nosave string server_port="8848";

nosave string password="pass";
object requst_ob;

int write_message(string);
int do_connect(string arg);
void chat(string arg,string opt);

nosave int add_lock=0;

nosave int doing=0;
nosave int connected=0;
nosave int logined=0;
nosave int do_session_flag=0;
nosave int waiting=0;//等待口令验证

nosave string buff="";
int del_session(string sid)
{
	chat("准备删除sid为:"+sid+" 的任务","debug");
	delete("session/"+sid);
}
mapping session() //id,cur_sesson  看来必须使用DBASE，因为涉及到多重mapping
{
	return query("session");
}


//对当前的也要锁

int make_sid()
{
	return session_id++;
}

void process(mixed msg)
{
	string sid,*msgarr;
	mapping tmps=([]);

	if(!stringp(msg))
	{
		chat("收到非字符串返回值","sys");
		return;
	}
	//msg可能是一个多行字符串哟！应该分行处理
	msgarr=explode(msg,"\n");
	for(int i=0;i<sizeof(msgarr);i++)
	{
		msg=msgarr[i];
		msg=replace_string(msg,"\r","");
		chat("处理:"+msg,"sys");
		if(sscanf(msg,"%s`%s",sid,msg)==2)
		{
			tmps=query("session/"+sid);
			if(sizeof(keys(tmps))<=0)
				chat("系统错误，接收到发给不存在的任务ID的命令","sys");
			//发送回来的是命令
			if (msg=="pass ok")//switch?
			{
				//设置登录成功
				chat("登录成功","debug");//未显示？！
				logined=1;
			}
			else if (msg=="session end")
			{
				chat(sprintf("收到任务完成命令，发送回送消息到指定物件：%O",query("session/"+sid+"/object")),"debug");
				//命令结束，发送数据到用户
				query("session/"+sid+"/object")->incoming(sid,buff);
				buff="";//重置缓冲区
				//是否主动中断连接？
				del_session(sid);
				do_session_flag=0;//结束一次任务
			}
			else
			{

				chat("sizeof(msg)"+sizeof(msg)+" 未知命令["+msg+"]\n","sys");
			}
		}
		else
		{
			//发送回来的是字符数据，其实信息数据也应该有命令来控制，避免发错。
			buff=buff+msg;
		}
	}
}


//最最关键和复杂的状态管理程序和功能，只要完全实现 session由状态决定下一步的动作，那么do_session将被允许多次调用
//每个动作完成后都应该有个变量拒绝再次进行该动作
void do_session()
{
	string cmd1;
	string sid1;
	mapping tmp=session();
#ifdef DEBUG
	chat("do_session()被调用","debug");
#endif

	do_session_flag=1;//可以这样处理，进入时设置1，退出后设置0，而 cur_sid里才是要处理的任务

	sid1=(string)cur_sid;//返回cur_sid   这个函数会死掉！
	chat("准备处理"+sid1,"new");
	//判断cur_sid是否已经结束
	if(!mapp(query("session/"+sid1)))
	{
		do_session_flag=0;
		chat("任务已经完成，结束任务处理进程"+sid1+"!","debug");
		return;
	}

	cmd1=tmp[sid1+"/cmd"];
	//应该呼叫一个TimeOut函数
	if(connected)//如果已经建立连接
	{
		chat("已经连接","debug");
		if(logined)//如果还通过了口令验证的话
		{
			//送出请求命令，和返回的sid
			//设置状态为 waiting=1; 此时可以不再调用自身
			waiting=1;
			write_message(sid1+"`"+cmd1);
		}
		else//未通过认证且未进行认证操作则发口令
		{
			//发送认证命令，现在假设网络很好，发出去的信息可以很快返回
			if(!waiting)
			{
				write_message(sid1+"`"+password);
			}
			//已经发送了口令则不再发送（但是如此次发送丢失呢？）
		}
	}
	else
	{
		//开始创建连接
		chat("建立连接中","debug");
		if(do_connect(server_ip+ " " + server_port))
		{
			connected=1;
			buff="";//将收到的信息缓冲清空
			call_out("do_session",1);//马上继续处理
			return;
		}
		else
		{
			chat("错误！无法建立连接。","sys");
		}
	}
	call_out("do_session",CK_DELAY);
}


void check_pool()
{
	int tmp_sid,i;
	string *arr1;
	arr1=keys(session());
#ifdef DEBUG
	chat("检查进程启动，sizeof(session):"+sizeof(arr1)+" do_session_flag="+do_session_flag,"debug");
#endif
	if(sizeof(arr1)>0&&do_session_flag==0)
	{
		//开始连接机器完成任务
		//在这里应该选择启动哪个任务(keys(session)里最小的那个？)
		sscanf(arr1[0],"%d",cur_sid);
		for(i=0;i<sizeof(arr1);i++)
		{
			sscanf(arr1[i],"%d",tmp_sid);
			if(cur_sid > tmp_sid) cur_sid=tmp_sid;
		}
		chat("check_pool启动任务处理进程，处理"+cur_sid,"debug");
		if(do_session_flag==0)	do_session();//是否要启动一个TimeOut进程呢？
		//不禁止再次调用会导致进程越来越多（宁愿在do_session里对进程本身进行控制)
	}
	else
	{
		chat("无需执行条件:"+(sizeof(arr1)>0)+" " + (do_session_flag==0),"debug");
	}
	call_out("check_pool",CK_DELAY+5);//这个时间限制可能太长了，但是太短又容易造成CPU负担重
	//一般才发了信的话应该马上检查一编！
}

int add_session(string cmd,object caller)
{
	string str1;
	mapping tmp=([]);
	int sid=make_sid();
	if(add_lock) return 0;//被锁住，拒绝执行
	add_lock=1;
	str1=sprintf("%d",sid);
	tmp["object"]=caller;
	tmp["cmd"]=cmd;
	set("session/"+str1,tmp);
	add_lock=0;
	return 1;
}
varargs string show_session(string sid)
{
	string *arr,tmp;
	int i;
	if(!stringp(sid))
	{
		mapping tmps=session();
		arr=keys(tmps);
		i=sizeof(arr);
		tmp="\n";
		if(i>0)
		{
			for(i=0;i<sizeof(arr);i++)
			{
				tmps=query("session/"+arr[i]);
				tmp=tmp+"sid:"+arr[i]+" cmd:"+tmps["cmd"]+ " object:"+sprintf("%O",tmps["object"])+"\n";
			}
		}
		else
			tmp="没有任务\n";
	}
	else
	{
		//单独显示指定的任务

	}
	return tmp;
}




//每当开始建立连接后就调用最大限制时间内的断开调用，避免一个连接长时间吊死掉
int close_socket()
{
	if( connected )
	{
		if( socket_close(my_socket) )
		{
			chat("关闭socket，恢复断线状态。\n","debug");
			connected=0;
		}
		else
			chat("关闭socket失败。\n","debug");
	}
	else
		chat("还没有连接。\n","debug");
	my_socket=0;
	return 1;
}

int do_connect(string arg)
{
	int err;
	if( connected )
		socket_close(my_socket);
	my_socket = socket_create( STREAM, "in_read_callback","in_close_callback" );
	if ( my_socket < 0 )
	{
		chat("创建socket失败。\n","debug");
		return 0;
	}
	err = socket_connect( my_socket, arg , "read_callback","write_callback" );
	if( err==EESUCCESS )
	{
		chat("已经连接" + arg + "\n","debug");
		connected=1;
	}
	else
	{
		chat("无法连接" + arg + "。错误代码："+err+"\n","debug");
		close_socket();
		return 0;
	}
	return 1;
}

//应该有个统一的分发函数，将收到的信息分发出去，当然也要包括因为超时无法处理的情况
void read_callback(int s,mixed message)
{
#ifdef DEBUG
    chat( BOLD + "远端返回：" + NOR + message ,"debug");
#endif
	process (message);
	return ;
}

void write_callback(int fd)
{
	int res;
	res = socket_write( fd,"");
	if (res == EESUCCESS || res == EECALLBACK)
		connected=1;
	else
		chat("写入错误代码:"+res,"sys");
}

int write_message(string arg)
{
	if( !arg ) arg="";
	socket_write(my_socket,arg+"\n");
	return 1;
}

void setup()
{
	set("session",([]));
	//调用email检查函数
	chat(query("channel_id")+"启动完毕" ,"sys");
	call_out("check_pool",1);
}

void create()
{
	set("channel_id", "网络连接精灵");
	setup();
}

void chat(string arg,string opt)
{
	CHANNEL_D->do_channel(this_object(),opt,arg);
	return;
}

void start_timeout()
{
	if(timeout_running!=0)
	{
		chat("超时控制已经运行，退出！","sys");
		return;
	}
	chat("超时控制启动！","chat");
	call_out("timeout",1);
}

void timeout()
{
	//根据剩余时间变量决定是否还继续延迟，否则立即中断连接，恢复初始状态。
	if(sizeof(keys(query("session")))>0)
		chat("还有任务，如果此时do_session_flag为1，则超时(应该完成任务就中断)","sys");
	else
		chat("任务已经顺利完成","sys");
}
