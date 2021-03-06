#include <ansi.h>

inherit SR_DEALER;

/*
典当物品保存在pawn_object里，里面第一层是用户的ID，ID下面是典当物品的文件，
再下面才是该物品的一些信息！
*/

//每个人原则上可以典当的最多物品种类数
//实际最多可以典当则由玩家的"max_pawn"属性来设置
#define MAX_PAWN 100

//原则上当铺可以最多允许多少人来开帐号
//实际最多则由"max_account"属性控制
//为了不至于浪费资源，应该在定期检查里调用一个函数来检查是否有过期了的帐号或者货物！
#define MAX_ACCOUNT 300

//定义典当物品过期时间，超过此时间就要被归入经营者的存款里
//自定义是2592000秒，也就是一个月！(100000000内都不会溢出的！)
#define PAWN_TIME 60*60*24*30

void init()
{
	::init();
	add_action("do_pawn","pawn");
	add_action("do_redeem","redeem");
	add_action("do_redeemp","redeemp");
}

void checking(object ob)
{
	chat("sys","测试函数被调用。\n");
	//这样的书写是可行的！
	//可以在这里书写检查当铺里的货物是否超期
	::checking(ob);
}

int do_redeemp(string target)
{
	object me,dest;
	me=this_player();
	if(!target||target=="")
		return notify_fail("你要赎什么人？\n");
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	if(!objectp(dest=find_player(target)))
		return notify_fail("玩家("+target+")目前不在线上！\n");
	if( !dest->query("tag/selled"))
		return notify_fail(dest->name(1)+"现在正玩得欢呢！\n");
	switch (MONEY_D->player_pay(me, dest->query("per") * 700))
	{
	case 0:
		return notify_fail("穷光蛋，一边呆着去！\n");
	case 2:
		return notify_fail("您的零钱不够了，银票又没人找得开。\n");
	default:
		message_vision("$N赎回了一"+dest->query("unit")+dest->query("name")+"。\n", me);
		dest->move(this_object());
		dest->set("startroom",base_name(this_object()));
		dest->set("tag/selled",0);
		message("vision",
			HIY "只听见嗖的一声，一个遍体鳞伤的家伙从天花板上掉了下来！\n" NOR,
			environment(dest), dest);
		tell_object(dest, "你被" + me->query("name") + "赎了出来。\n");
	}
	return 1;
}

int do_redeem(string arg)
{
	object ob,me;
	mapping sob,fob;
	int number,num,sno;
	string file,str,tmp,prop,fn,dfn;
		
	me=this_player(1);
	//如果物品赎取光了就表示取消帐户！
	if(member_array(me->query("id"),keys(query("pawn_object")))==-1)
		return notify_fail("你没有在这里开户！怎么赎取东西呢？！\n");
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	sob=query("pawn_object/"+me->query("id"));
	//此时表示有典当了的物品存在
	if(!arg)//无参数则显示典当物品情况！
	{
		str="你在本当铺典当的物品有：\n";
		foreach(file in keys(sob))
		{
			ob=new(replace_string(file,"\\","/"));
			if(!objectp(ob))
				continue;//应该删除该属性！
			prop="pawn_object/"+me->query("id")+"/"+file;
			number=query(prop+"/number");
			if(ob->query_amount()!=0)
				ob->set_amount(number);
			ob->set_name(query(prop+"/name"),query(prop+"/id"));
			if(!(tmp=ob->query("base_unit")))
				tmp=ob->query("unit");
			str+=chinese_number(number)+tmp+ob->name(1)+"("+
				implode(ob->parse_command_id_list(),",")+") 单价：";
			if(ob->query("base_value"))
				str+=MONEY_D->price_str(ob->query("base_value"));
			else
				str+=MONEY_D->price_str(ob->query("value"));
			str+=" 最后典当："+CHINESE_D->chinese_time(5,(string)ctime(query(prop+"/time")))+"\n";
		}
		this_player()->start_more(str);
		return 1;
	}
	//赎取物品的代码段
	if(sscanf(arg,"%d %s",num,arg)!=2)
		num=1;
	if(sscanf(arg,"%s %d",arg,sno)!=2)
		sno=1;
	dfn="无此物";
	foreach(fn in keys(sob))
	{
		fob=sob[fn];
		if(member_array(arg,fob["id"])!=-1)
			sno--;
		if(sno==0)
		{
			dfn=fn;
			break;
		}
	}
	if(dfn=="无此物"||sno!=0)
		return notify_fail("你要赎的东西好象没有典当过呀！\n");
	ob=new(replace_string(dfn,"\\","/"));
	fob=sob[fn];
	if(num>fob["number"])
		num=fob["number"];
	get_money(ob,num,dfn,"赎回");//这里最后一个参数必须是"赎回"或者"买"
	return 1;
}

int do_pawn(string arg)
{
	//对于no_give的物品
	object me,ob,nob,tmpob;
	object *obs,*tobs;
	int number,num,tmp;
	string str,prop;
	int value,i;
	if (!arg)
		return notify_fail("你要典当什么？\n");
	me=this_player(1);
	if(query_temp("busy"))
	{
		me->receive_damage("qi",10);//避免刷屏幕
		return notify_fail("对不起，现在忙着呢，请稍后！\n");
	}
	remove_call_out("enough_rest");
	call_out("enough_rest",1);
	set_temp("busy",1);
	if (sscanf(arg,"%d %s",num,arg)!=2)
		num=1;
	if (!(ob = present(arg, me)))
		return notify_fail("你要典当什么？\n");
	if (ob->query("money_id"))
		return notify_fail("你想典当「钱」？？\n");
	if (stringp(ob->query("no_drop"))||ob->query("no_pawn")||ob->query("nopawn")||
		ob->query("nopawn")||ob->query("no_pawn")||ob->query("item_origin"))
		return notify_fail("这样东西不能典当。\n");
	if (ob->query("food_supply"))
		return notify_fail("剩菜剩饭留给您自己用吧。\n");
	if (ob->query("shaolin"))
		return notify_fail("小的只有一个脑袋，可不敢买少林庙产。\n");
	if (userp(ob))
	{
		/*临时禁止在这里卖玩家，要修改为只可以向人贩子卖玩家！*/
		return notify_fail("这里是做正当生意的，不能拐卖人口！快滚出去，不然我叫官兵了！\n");
		num=1;//因为人只可能有一个，所以加个语句避免恶意输入！
		CHANNEL_D->do_channel(ob, "rumor",
			sprintf("%s被某人拐卖了。", ob->name(1)));
	}
	else
	if((ob->query("enpawn")==0))
		return notify_fail("这个东西我们不经营的，不能典当，你还是干脆卖了算了！\n");

	//此处检查num数是否合法！
	if((tmp=ob->query_amount())!=0)//如果是set_amount类物品则直接查询amount
	{
		if(tmp<num)
			num=tmp;
	}
	else//否则按ID和名字进行统计！先获取所有物品然后排除其他只剩同类再统计！
	{
		obs=all_inventory(me);
		tmp=sizeof(obs);//拐卖人口时这里有错！
		tobs=({});
		for(i=0;i<tmp;i++)
		{
			if( !( obs[i]->name(1)!=ob->name(1) || !obs[i]->id(ob->query("id")) ) )
				tobs=tobs+({ obs[i] });//将同类物复制到tobs里
		}
		obs=tobs;//将obs设为tobs
		tmp=sizeof(obs);
		if(tmp<num)
			num=tmp;
	}
	//如果是amount物品应该分离出来！
	if(ob->query_amount()!=0)
	{
		if(!objectp(nob=new(base_name(ob))))
			write("复制新物品错误！"+(string)(ob->query_amount()-num)+"\n");
		nob->set_amount(ob->query_amount()-num);//设置玩家身上的物品（减少！）
		//nob->move(this_player());可能是这里如果move到ob的话就有两个同类OBJECT了！
		ob->set_amount(num);
	}
	value = ob->query("value");
	if(!value)
		value=ob->query("base_value");
	if(value<1)
		value=1;
	value*=num;
	number=num;	
	if (value < 30)
	{
		ob->set_amount(nob->query_amount()+num);
		write(ob->query("name") + "一文不值！\n");
	}
	else 
	{
		if ( userp(ob))
		{
			//典当进来的不花经营者的钱，但是典当出的时候也只允许经营者提成
			pay_money(me,value,1,"典当");
			ob->move("/d/sroom/storage");
			ob->set("startroom","/d/sroom/storage");
			ob->set("tag/selled",1);
		}
		else
		if (value < 50)//value小于50的物品只能销毁！
		{
			pay_money(ob,value,num,"典当");
			if(pointerp(obs))//如果为真说明是非amount物品，应该按num清除！
			{
				for(i=num;i>0;i--)
				{
					tmpob=obs[0];
					obs=obs - ({ tmpob });
					if(objectp(tmpob))
						destruct(tmpob);
				}
			}
			else//如果不存在说明前面已经摧毁了，否则就应该是amount物品
			{
				destruct(ob);
				nob->move(me);
			}
		}
		else
		{
			//这里是处理真正的存放收购进来的物品的代码
			//如何记录购买进来的物品呢？
			//物品文件名，时间，数量，name，id
			//str保存基本文件名
			str=base_name(ob);
			str=replace_string(str,"/","\\");		//注意："\\"即"\"!
			//因为如果是可以amount计数的，那么query_amount肯定不等于0
			//而不可以amount的query_amount肯定等于0
			//所以直接query_amount就可以判断是否可以用amount计数
			//所以如果number==0那么说明不是amount物品，它的数量一定是1
			prop="pawn_object/"+me->query("id")+"/"+str;//设置存储该物品的属性名
			
			//检查该用户在本当铺的存储数达到了上限？
			i=me->query("max_pawn");
			if(i>MAX_PAWN)
				i=MAX_PAWN;
			if(i<0)
				i=1;
			
			//如果查询到了，说明原来就已经存在该帐号了
			if( member_array(me->query("id"),keys(query("pawn_object"))) !=-1)
			{
				if(sizeof( query( "pawn_object/"+me->query("id") ) )>i)
					return notify_fail("对不起，你的帐号已经典当很多物品了，不能再多了。\n");
			}
			else
			{
				//这一段检查是否可以开户
				
				if(me->query("pawn_room")>0)
					return notify_fail("你不能再在当铺开户头了。\n");
				me->add("pawn_room",1);
				//如果将这个属性设置为负数，则变成允许在多个当铺开户
				//默认就是只能在一个当铺开户
				i=query("max_account");
				if(i>MAX_ACCOUNT)
					i=MAX_ACCOUNT;
				if(i<0)
					i=1;
				if(sizeof(query("pawn_object"))+1 >i)
				{
					me->add("pawn_room",-1);//还原可开户数
					return notify_fail("对不起，这个当铺已经有"+(string)(i+1)+"个人开了户头了，你只有等"+
						"当铺扩容后再典当了。\n");
				}
			}

			set(prop+"/time",time());
			set(prop+"/name",ob->name(1));//可以当的应该都存在这个函数
			set(prop+"/id",ob->parse_command_id_list());//这是一个string *类型！
			set(prop+"/number",number+query(prop+"/number"));//是否应该对这个物品
			pay_money(ob,value,num,"典当");
			//这里是要增加种类的处理，这里负责增加，buy命令里负责清除
			if(pointerp(obs))//如果为真说明是非amount物品，应该按num清除！
			{
				for(i=num;i>0;i--)
				{
					tmpob=obs[0];
					obs=obs - ({ tmpob });
					if(objectp(tmpob))
						destruct(tmpob);
				}
			}
			else//如果不存在说明前面已经摧毁了，否则就应该是amount物品
			{
				destruct(ob);
				nob->move(me);
			}
		}
	}
	return 1;
}