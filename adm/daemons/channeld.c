// channeld.c
// 97-10-18 add intermud channel and emote capability
// By ken@XAJH & fuyo@XAJH
// 99-11-4 优化代码，增加同MUD分站间通讯功能。
// By JackyBoy@CCTX&SNOW
#include <ansi.h>
#include <mudlib.h>
#include <net/dns.h>
#include <net/macros.h>

inherit F_DBASE;
nosave string *lock_chn=({});
string remove_addresses(string, int );

mapping channels = ([
	"sys":  ([  "msg_speak": HIR "【系统】%s：%s\n" NOR,
		"msg_color": NOR+HIR,
		"wiz_only": 1,
	]),
    "snow": ([  "msg_speak": NOR+HIW+"【小雪初晴】%s：%s\n" NOR,
		"msg_emote": NOR+HIW+"【小雪初晴】%s" NOR,
		"intermud": GCHANNEL,
		"intermud_emote": 1,
		"channel": "snow",
		"msg_color": NOR+HIW,
		"filter": 1,
		"omit_address": 0,
	]),
    "adm":  ([  "msg_speak": HIW "【管理员】%s: %s\n" NOR,
		"msg_emote": NOR+HIW+"【管理员】%s" NOR,
		"msg_color": NOR+HIW,
		"admin_only": 1,
	]),
	"new": ([  "msg_speak": HIG+"【新手】"HIW"%s：%s\n" NOR,
		"msg_emote": HIG+"【新手】"+HIW+"%s" NOR,
		"msg_color": NOR+HIW,
		"newbie":1,
	]),
    "wiz":  ([  "msg_speak": NOR+HIY+"【巫师】"+HIY+"%s：%s\n" NOR,
		"msg_emote": NOR+HIY+"【巫师】"+HIY+"%s" NOR,
		"msg_color": NOR+HIY,
		"intermud": GCHANNEL,
		"intermud_emote": 1,
		"wiz_only": 1,
		"channel": "wiz",
		"omit_address": 0,
		"filter":1,
	]),
	//"wiz"频道没必要设置为imud频道的
	"gwiz": ([  "msg_speak": NOR+HIC+"【网际巫师】"+HIY+"%s：%s\n" NOR,
		"msg_emote": NOR+HIC+"【网际巫师】"+HIY+"%s" NOR,
		"wiz_only": 1,
		"intermud": GCHANNEL,
		"intermud_emote": 1,
		"channel": "gwiz",
		"msg_color": NOR+HIY,
		"filter": 1,
		"omit_address": 0,
	]),
    "es":   ([  "msg_speak": NOR+BOLD+"【网际闲聊】"+NOR+BOLD+"%s：%s\n" NOR,
		"msg_emote": NOR+BOLD+"【网际闲聊】"+NOR+BOLD+"%s" NOR,
		"msg_color": NOR+BOLD,
		"intermud": GCHANNEL,
		"intermud_emote": 1,
		"channel": "es",
		"filter": (: $1["ENCODING"] == MUDLIB_ENCODING :),
		"omit_address": 0,
	]),
	"gbwiz":([
		"msg_speak": BOLD "【大陆巫师】%s：%s\n" NOR,
		"msg_emote": BOLD "【大陆巫师】%s" NOR,
		"msg_color": BOLD,
		"intermud": GCHANNEL,
		"intermud_emote": 1,
		"channel": "gbwiz",
		"omit_address": 0,
		"filter": (: $1["ENCODING"] == MUDLIB_ENCODING :),
	]),
	"debug":([  "msg_speak": HIW "【调试】%s：%s\n" NOR,
		"msg_emote": HIY "【调试】%s" NOR,
		"msg_color":HIW,
		"wiz_only": 1,
	]),
	"chat": ([  "msg_speak": HIY+"【论道江湖】"+HIC+"%s：%s\n" NOR,
		"msg_emote": HIY+"【论道江湖】"+HIC+"%s" NOR,
		"msg_color": NOR+HIY,
	]),
	"rumor": ([  "msg_speak": HIR "【谣言】"+HIM"%s：%s\n" NOR,
		"msg_emote": HIR "【谣言】"+HIM"%s" NOR,
		"msg_color": NOR+HIR,
		"anonymous": "某人",
	]),
	"party":([  "msg_speak": HIY "【%s】"+HIG"%s: %s\n" NOR,
		"msg_emote": HIY "【%s】"+HIG"%s" NOR,
		"msg_color": NOR+HIY,
		"newbie":1,
	]),
]);

void create()
{
    // This is required to pass intermud access check.
    seteuid(getuid());
    set("channel_id", "频道精灵");
}

int do_lock(string chn)
{
	if(!stringp(chn))
		return 0;
	if(arrayp(lock_chn)&&sizeof(lock_chn)>0)
	{
		lock_chn = lock_chn - ({chn});
	}
	lock_chn=lock_chn+({chn});
	return 1;
}

int do_unlock(string chn)
{
	if(!stringp(chn)||!arrayp(lock_chn))
		return 0;
	if(lock_chn == ({chn}))
		lock_chn=({});
	else
		lock_chn=lock_chn - ({chn});
	return 1;
}

varargs int do_channel(object me, string verb, string arg, int emote,int remote)
{
    object *ob;
    string *tuned_ch, who;
    string arg_bk,self_emote;
    int i;
	string *banword=({"妓女","他妈","她妈","我操","我日","你妈","祖宗","fuck","强奸",
    	"卖淫","鸡巴","神经","精神病",
    });
    self_emote=arg;

    // Check if this is a channel emote.
    if( sizeof(verb) > 2 )
    {
		if( verb[sizeof(verb)-1] == '*' )
		{
			emote = 1;
			verb = verb[0..<2];
		}
	}
	// Check if this is a channel messsage.
	if( !mapp(channels) || undefinedp(channels[verb]) ) return 0;
	// 检查这个频道是否被关闭了。
	if( member_array(verb,lock_chn)!=-1)
	{
		write("对不起，这个频道目前被巫师封闭了！\n");
		return 1;
	}
	for(i=0;i<sizeof(banword);i++)
	{
		if( (verb != "sys") &&arg&&
			(sscanf(lower_case(arg),"%*s"+banword[i]+"%*s")||sscanf(arg,"%*s"+banword[i]+"%*s")) )
		{
			//封闭其所有频道
			do_channel( this_object(), "sys", me->name(1)+"("+me->query("id")+")使用了禁止使用的词汇！");
			if(userp(me))
			{
				me->set("chblk_channel/all",time()+3000);
				tell_object(me,NOR+"由于你使用了禁止使用的词语"+HIR+banword[i]+NOR+"，你的所有聊天频道被关闭了！\n");
			}
			return 1;
		}
	}

	// check if this channel support emote message.
	if( emote && undefinedp(channels[verb]["msg_emote"])  )
	{
		write("对不起，这个频道不支持 emote 。\n");
        return 1;
    }
	//now we can be sure it's indeed a channel message:
	if (!stringp(arg) || arg == "" || arg == " ")
		arg = "...";
	else
		arg_bk = arg;
	if(remote) arg_bk = arg;
    // check if one can write to channels
    // only block rumor or chat...
	if ( userp(me) && !wizardp(me))
	{
		if (userp(me) && me->ban_say()) return 0;//如果被关闭了say则直接返回
		if(time()-(int)me->query("chblk_channel/all")<3600)
			return notify_fail("你所有的聊天频道都被关闭了！\n");
		if(time()-(int)me->query("chblk_channel/"+verb)<3600)
			return notify_fail(HIW"你的"HIR+verb+HIW"被关闭了！\n");
	}
	if( userp(me) )
	{
		if( channels[verb]["wiz_only"] && !wizardp(me))
			return 0;
		if( channels[verb]["admin_only"] && wiz_level(me)<wiz_level("(admin)"))
			return 0;
		//暂时屏蔽新手频道的限制功能！如果出现flood太严重后再起用！
		if(channels[verb]["newbie"]!=1&&me->query("age")<15&&!wizardp(me))
			return notify_fail("你的年纪太小了，只能用新手频道说话。\n");
		if( !wizardp(me))
			if( arg==(string)me->query_temp("last_channel_msg") )
				return notify_fail("用交谈频道说话请不要重复相同的讯息。\n");

	//防止重复使用交谈频道发出同样信息！
	if( userp(me) && !wizardp(me))
	{
		me->set_temp("last_channel_msg", arg);
		me->add_temp("channel_msg_cnt", 1);
	if (me->query_temp("channel_msg_cnt")>5)
		if (time()-me->query_temp("chat_time")<3)
		{
		me->set("chblk_channel/"+verb,time());
                do_channel( this_object(), "rumor", sprintf("山猫拿出一张狗皮膏药，在小火炉上细细地煨热以后，“啪”地捂住了%s的嘴巴。\n", me->name(1) ));
                return 1;
		} else {
                me->set_temp("chat_time",time());
                me->delete_temp("channel_msg_cnt");
		}
	}

		// If we speaks something in this channel, then must tune it in.
		tuned_ch = me->query("channels");
		if( !pointerp(tuned_ch) )
			me->set("channels", ({ verb }) );
		else if( member_array(verb, tuned_ch)==-1 )
			me->set("channels", tuned_ch + ({ verb }) );
	}
	// Support of channel emote
	if( emote  && me->is_character() && !remote)
	{
		string vb, emote_arg, id, mud;
        if( sscanf(arg, "%s %s", vb, emote_arg)!= 2 )
		{
			vb = arg;
			emote_arg = "";
		}
		if( channels[verb]["intermud_emote"]
			&& sscanf(emote_arg, "%s@%s", id, mud)==2 )
		{
				REMOTE_Q->send_remote_q(mud, verb, me->query("id"), id, vb);
				write("网路讯息已送出，请稍候。\n");
				return 1;
		}
		if( channels[verb]["intermud_emote"] )
			arg = EMOTE_D->do_emote(me, vb, emote_arg, 3);
		else if( verb == "rumor" && random(10)<8 )
			arg = EMOTE_D->do_emote(me, vb, emote_arg, 2, channels[verb]["anonymous"]);
		else
			arg = EMOTE_D->do_emote(me, vb, emote_arg, 1);
        if (!arg && emote)
		{
			// we should only allow chinese emote.
			if( (int)vb[0] < 160 ) return 0;
				arg = sprintf("%s(%s@%s)%s\n",me->name(),me->query("id"),Mud_name(),arg_bk);
			if( verb == "rumor" )
			{
				if( userp(me) )
					arg = sprintf("%s%s\n",channels[verb]["anonymous"],vb);
			}
		}
		if( !arg )
		{
			if( channels[verb]["anonymous"] )
				arg = channels[verb]["anonymous"]+vb+" "+emote_arg+"\n";
			else if( channels[verb]["intermud_emote"] )
				arg = sprintf("%s(%s@%s)%s %s\n", me->name(1),
					capitalize(me->query("id")), INTERMUD_MUD_NAME, vb, emote_arg);
			else
				arg = me->name()+vb+" "+emote_arg+"\n";
		}
	}
	// Make the identity of speaker.
	if( channels[verb]["anonymous"] )
	{
		who = channels[verb]["anonymous"];
		if (userp(me))
			if (random(10)>8)
				who=me->name(1) + "(" + capitalize(me->query("id")) + ")";
			else
				do_channel( this_object(), "sys", sprintf("%s躲了起来造谣。", me->name(1)));
	}
	else
	if(me && (userp(me) || !stringp(who = me->query("channel_id")) ))
	{
		if (me->name()!=me->name(1) && emote)
			do_channel( this_object(), "sys", sprintf(HIW"%s(%s)"+WHT+"扮%s!", me->name(1),me->query("id"),me->name()));
		who = me->name(1) + "(" + me->query("id") + ")";
	}
	// Ok, now send the message to those people listening us.
	if (verb=="party")
	{
		if (!me->query("family/family_name"))
			return notify_fail(HIY"你还没有加入任何门派！\n"NOR);
		ob=filter_array( users(), "family_listener", this_object(), me->query("family/family_name") );
	}
	else
		ob = filter_array( users(), "filter_listener", this_object(), channels[verb] );
	if( !arg || arg == "" || arg == " " ) arg = "...";
	if( emote )
	{
		string localmsg;
		string ecol=channels[verb]["msg_color"];
		if(remote)
		{
			arg=arg_bk;
		}
		if (!stringp(arg)) return 0;
		localmsg = arg;
		if ( channels[verb]["msg_emote"] )
			localmsg = remove_addresses(arg, 0); // 98-1-22 14:30
		if( channels[verb]["omit_address"] )
			localmsg = remove_addresses(arg, 1);
		else
		if( channels[verb]["intermud_emote"] )
			localmsg = remove_addresses(arg, 0);
		if(!stringp(localmsg)) return 0;
		if (verb=="party")
			message( "channel:" + verb,sprintf( channels[verb]["msg_emote"],me->query("family/family_name"), replace_string(localmsg,NOR,ecol) ), ob );
		else
			message( "channel:" + verb,  sprintf( channels[verb]["msg_emote"],replace_string(localmsg,NOR,ecol)), ob );
	}
	else
	if (verb=="party")
		message( "channel:" + verb,sprintf( channels[verb]["msg_speak"],me->query("family/family_name"),who,arg ), ob );
	else
		message( "channel:" + verb, sprintf( channels[verb]["msg_speak"], who, arg ), ob );
	if( arrayp(channels[verb]["extra_listener"]) )
	{
		channels[verb]["extra_listener"] -= ({ 0 });
		if( sizeof(channels[verb]["extra_listener"]) )
			channels[verb]["extra_listener"]->relay_channel(me, verb, arg);
	}
	if( !undefinedp(channels[verb]["intermud"]) && me->is_character())
	{
		channels[verb]["intermud"]->send_msg(
			channels[verb]["channel"], me->query("id"), me->name(1), arg, emote,
			channels[verb]["filter"] );
	}
    return 1;
}

int filter_listener(object ppl, mapping ch)
{
	// Don't bother those in the login limbo.
	if( !environment(ppl) ) return 0;
	if( ch["admin_only"])
		if( userp(ppl) )
			if( wiz_level(ppl) < wiz_level("(admin)") )
				return 0;
	if( ch["wiz_only"] )
		if( userp(ppl) )
			return wizardp(ppl);
	if( ch["es_only"] )
	{
		if( wiz_level(ppl) > 0 ) return 1;
		if( ppl->query("age") > 23 ) return 1;
		return 0;
	}
	return 1;
}

void register_relay_channel(string channel)
{
	object ob;
	ob = previous_object();
	if( undefinedp(channels[channel]) || !ob) return;
	if( arrayp(channels[channel]["extra_listener"]) )
	{
		if( member_array(ob, channels[channel]["extra_listener"]) >=0 ) return;
		channels[channel]["extra_listener"] += ({ ob });
	}
	else
		channels[channel]["extra_listener"] = ({ ob });
}

string remove_addresses(string msg, int all)
{
	int i;
	mixed tmp;
	string pattern;
	if(!stringp(msg)) return msg;
	if( all )
		pattern = "[(][A-Za-z]+@[a-zA-Z]+[0-9]+[.]?[)]";
	else
		pattern = "[(][A-Za-z]+@"+Mud_name()+"[)]";
	tmp = reg_assoc(msg, ({pattern}), ({1}));
	if(!arrayp(tmp)) return msg;
	msg = "";
	for(i=0; i< sizeof(tmp[0]); i++)
		if( tmp[1][i] == 0 ) msg += tmp[0][i];
	return msg;
}

int family_listener(object ppl, string str)
{
	// Don't bother those in the login limbo.
	if( !environment(ppl)) return 0;
	if(wizardp(ppl) || ppl->query("family/family_name")==str ) return 1;
	else return 0;
}
