//compete.c
//create by Netplay@cctxII
//关于比武系统的一些函数定义

#include <ansi.h>
#include <dbase.h>

mapping fight;

void fight_winner(object loser)
{
        object winner=this_object();
		int i=winner->query_tops();
        string arg;
        COMPETE_D->fighter_place(winner,loser);

        arg=winner->name(1)+"比武战胜"+loser->name(1)+"!";
        if(i>winner->query_tops())
		arg+="恭喜"+winner->name(1)+"荣登英雄排行榜第"+winner->query_tops()+
		"名!";
        message("channel:chat",HIC"【江湖传闻】"+arg+"\n" NOR, users());

}

/*varargs int query_fight_result(string type)
{
	if( mapp(fight) )
	return fight[type];
}

void add_fight_result(string type)
{
	if( !mapp(fight) ) fight = ([ type: 1 ]);
	else fight[type] = fight[type]+1;
}

void add_jifen(int i)
{
	if( !mapp(fight) ) fight =(["jifen": i]);
	else fight["jifen"]+=i;
}*/

int query_tops()
{
	return COMPETE_D->query_place(this_object());
}