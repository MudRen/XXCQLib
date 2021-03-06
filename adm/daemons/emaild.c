//电子邮件守护程序v0.1版本   编写：JackyBoy@CuteRabbit Studio 1999/7/11

/*
可以扩展的功能，向MUD内的玩家直接发信转化到向该玩家的真实email发信！
可以在同系列的MUD间相互发电子邮件！
一些属性说明：
email属性：
	用来保存待发邮件，是一个mapping类型的属性，里面用真实时间来标志接受的一封信
	该信是用一个mapping来表达的：
		rctp_to 对方的邮件地址
		mail_from 发信者的邮件地址
		subject 信件的主题
		msg 信件的内容
		smtp 设置发此信件的SMTP服务器，可省略

*/

//检查是否有待发邮件的间隔时间，以秒为单位
#define CK_DELAY 60*1

#include <ansi.h>
#include <net/dns.h>
#include <net/telnet.h>
#include <net/socket.h>
#include <net/socket_errors.h>
#include <socket_err.h>
#include <mudlib.h>

inherit F_SAVE;
inherit F_DBASE;
//建立连接使用的socket号和发送标志
nosave int my_socket,status=0,scount=0;
//缺省的发送邮件服务器地址
nosave mapping d_smtp=([
	"ip":"202.96.104.8",
	"port":"25",
	"name":"pub.cnnb.net",
	]);
//正式使用的发送邮件服务器地址
nosave mapping smtp;
//邮件的收件人，发件人，主题和信息！
nosave string rcpt_to,mail_from,subject,msg,en;

int write_message(string);

string query_save_file()
{
	return __DIR__"emaild.o";
}

void setup()
{
	restore();
	//设置初始值

	//调用email检查函数
	call_out("check_email",1,this_object());
}

void create()
{
	set("channel_id", "电子邮件精灵");
	setup();
}

void chat(string arg,string opt)
{
	CHANNEL_D->do_channel(this_object(),opt,arg);
	return;
}

int add_email(string m_from,string r_to,string title,string msg,mixed smtp)
{
	string tmp_en;
	mapping tmp_em;

	tmp_em=([]);
	//应该检查地址和信息的合法性！
	tmp_en=CHINESE_D->chinese_time(5,ctime(time()));
	if(query("email/"+tmp_en))
	{
		//如果遇到有相同的项目了，则延迟60秒再尝试
		call_out("add_email",60+random(5),m_from,r_to,title,msg,smtp);
		return 1;
	}
	tmp_em["mail_from"]=m_from;
	tmp_em["rcpt_to"]=r_to;
	tmp_em["subject"]=title;
	tmp_em["msg"]=msg;
	if(mapp(smtp))
		tmp_em["smtp"]=smtp;
	set("email/"+tmp_en,tmp_em);
	save();
	return 1;
}

int delete_email(string tmp_en,int opt)
{
	mapping tmp_em;
	chat("删除邮件操作："+tmp_en+"\n","debug");
	if(!tmp_en)
		return 0;
	if(opt)
	{
		if(!tmp_em=query("email/"+tmp_en))
			log_file("emaild.log","欲删除不存在的邮件："+tmp_en+"\n");
		else
			log_file("emaild.log","删除邮件：\n"+
				"Mail From: "+tmp_em["mail_from"]+"\n"+
				"RCPT To:   "+tmp_em["rcpt_to"]+"\n"+
				"Subject:   "+tmp_em["subject"]+"\n"+
				"Smtp Server:"+smtp["name"]+"("+smtp["ip"]+")"+" Port:"+smtp["port"]+"\n"+
				"MSG:\n"+tmp_em["msg"]+"\n");
	}
	delete("email/"+tmp_en);
	return 1;
}

int close_socket()
{
	if( query("connected") )
	{
		if( socket_close(my_socket) )
		{
			chat("关闭socket，恢复断线状态。\n","debug");
			delete("connected");
		}
		else
			chat("关闭socket失败。\n","debug");
	}
	else
		chat("还没有连接。\n","debug");
	if(!delete_email(en,0))
		chat("删除邮件出错!\n","sys");
	en=0;//stringp对这个值会如何判断呢？
	status=0;//发完信，对这些值重新初始化
	my_socket=0;
	chat("重新设置en为："+en+"\n","debug");
	save();
	return 1;
}

int do_telnet(string arg)
{
	int err;
	if( query("connected") )
		socket_close(my_socket);
	my_socket = socket_create( STREAM, "in_read_callback","in_close_callback" );
	if ( my_socket < 0 )
	{
		chat("创建socket失败。\n","debug");
		return 1;
	}
	err = socket_connect( my_socket, arg , "read_callback","write_callback" );
	if( err==EESUCCESS )
	{
		chat("已经连接" + arg + "\n","debug");
		set("connected",1);
	}
	else
	{
		chat("无法连接" + arg + "\n","debug");
		close_socket();
	}
	return 1;
}


void read_callback(int ,mixed message)
{
    chat( BOLD + "远端返回：" + NOR + message ,"debug");
    switch(status)
    {
    	case 0:
    		if(sscanf(message,"220%*s"))
    		{
    			status++;
    			write_message("HELO " +smtp["name"] );
    			return;
    		}
    		break;
    	case 1:
    		if(sscanf(message,"250%*s"))
    		{
    			status++;
    			write_message("MAIL FROM:<"+mail_from+">");
    			return ;
    		}
			break;
    	case 2:
    		if(sscanf(message,"250%*s"))
    		{
    			status++;
    			write_message("RCPT TO:<"+rcpt_to+">");
    			return ;
    		}
    		break;
    	case 3:
    		if(sscanf(message,"250%*s"))
    		{
    			status++;
    			write_message("DATA");
    			return;
    		}
    		break;
    	case 4:
    		if(sscanf(message,"354%*s"))
    		{
    			status++;
    			if(sscanf(msg,"%*s\r\n.\r\n%*s"))
    			{
    				chat("正在发送的邮件包含非法数据，可能会无法发送。\n","sys");
    				log_file("emaild","\n试图发送数据：\n"+
    					smtp["name"]+"("+smtp["ip"]+")"+smtp["port"]+"\n"+msg+"\n");
    			}
    			write_message(msg+"\n.\n");
    			return;
    		}
    		break;
    	case 5:
    		if(sscanf(message,"451%*s"))
    			chat("Smtp Server接收数据出错！请另选服务器。\n","sys");
    		else
    			chat("信件已经正确发送了!\n","debug");
    		break;
    }
    if(status!=5||!sscanf(message,"250%*s"))
    	chat("发送出错","sys");
    status=0;
	write_message("QUIT");
	close_socket();
	return ;
}

void write_callback(int fd)
{
	int res;
	if(query("connect"))return ;
	res = socket_write( fd,"");
	if (res == EESUCCESS || res == EECALLBACK)
		set("connected",1);
}

int write_message(string arg)
{
	if( !arg ) arg="";
	socket_write(my_socket,arg+"\n");
	return 1;
}
void send_email()
{
	mapping email;
	string ATTACH;

	if(!stringp(en))
		return;
	if(!email=query("email/"+en))
	{
		close_socket();
		chat("发送邮件丢失，发送记录号为："+en+"\n","sys");
		log_file("emaild.log","发送邮件丢失，发送记录号为："+en+"\n");
		return;
	}
	ATTACH="\n\n" +
		"小雪连线地址：202.101.189.4 5555\n"+
		"              10.104.4.4 5555\n"+
		"              10.163.179.201 5555\n"+
		"小雪初晴总站主页 ：http://www.snowmud.com\n" +
		"胖胖的别墅MUD：http://mud.yn.cninfo.net/jackyboy\n" +
		"               http://www.lhmz.yn.cninfo.net/jackyboy\n\n" +
		"                                    " +
		"小雪初晴巫师公会\n本邮件由【"+CHINESE_MUD_NAME+"】电子邮件系统发送!\n"+
		"信件提交时间："+en+"\n"+
		"信件发出时间："+CHINESE_D->chinese_time(0,(string)localtime(time()));

	rcpt_to=email["rcpt_to"];
	subject=email["subject"];
	mail_from=email["mail_from"];
	msg=email["msg"];
	msg="FROM:"+CHINESE_MUD_NAME+"<jackyboy@126.com>\n"+
		"TO:"+rcpt_to+"\n"+
		"SUBJECT:"+subject+"【"+CHINESE_MUD_NAME+"】\n"+
		"MIME-Version:1.0\n"+
		"DATE:"+time()+"\n"+
		"X-MAILER:LPMUD电子邮件精灵v0.1\n"+"\n"+msg+ATTACH;
	//设置邮件服务器地址！
	smtp=(mapp(email["smtp"]))?email["smtp"]:d_smtp;
	//准备开始telnet发邮件
	if(!my_socket&&do_telnet(smtp["ip"]+" "+smtp["port"])==0)
	{
		chat("重复创建连接或者无法连接邮件服务器：\n"+
			smtp["name"]+"("+smtp["ip"]+")"+" 端口"+smtp["port"]+"\n","sys");
		close_socket();
		return;
	}
	else
		chat("系统依然处于连接状态！\n","debug");//应该设置连接次数和超时控制
	return ;
}


void check_email()
{
	string *earray;
	if(en!=""&&stringp(en))
	{
		//应该记录失败次数，如果60秒内没有发信成功就去除！
		if(++scount>20)
			close_socket();//此时造成信件丢失！
		else
		{
			chat("正在发信("+en+")，等候...\n","sys");
			call_out("check_email",6,this_object());
		}
		return;
	}
	scount=0;//发送未成功次数
	if(!query("email"))//如果没有邮件或者正在发信，隔CK_DELAY秒后再检查
	{
		chat("无电子邮件!\n","sys");
		call_out("check_email",CK_DELAY,this_object());
		return;
	}
	earray=keys(query("email"));
	if(sizeof(earray)<1)
	{
		call_out("check_email",CK_DELAY,this_object());
		return;
	}
	en=earray[0];//使用en作为发送邮件标志，但是这里不一定要0的，否则总是先发最后进入的信！
	chat("开始发电子邮件:"+en+"\n","debug");
	status=0;
	send_email();
	call_out("check_email",10,this_object());
	//一般才发了信的话应该马上检查一编！
}
