// edemote.c

inherit F_CLEAN_UP;

int in_use;
#define MASTER "/adm/obj/master"
#define SPLIT "\n.\n"
#define EM_HEAD "\n.\nbegin:\n.\n"

int export_emote(object me,string file)
{
	string *all_keys,key,str,item;
	mapping emote;
	file=MASTER->make_path_absolute(file);
	write("准备输出emote数据到文件"+file+"里。\n");
	if(MASTER->valid_write(file,me,"write_file")==0)
		return notify_fail("你不能写该文件！输出失败！\n");
	if(file_size(file)!=-1)
		return notify_fail("档案已经存在！请先将其删除！\n");//可以多写判断的！
	all_keys=EMOTE_D->query_all_emote();
	str="";
	foreach(key in all_keys)
	{
		emote=EMOTE_D->query_emote(key);
		str+=EM_HEAD+key+SPLIT;
		foreach(item in keys(emote))
			if(item!="updated")
				str+=item+":"+emote[item]+SPLIT;
	}
	if(write_file(file,str,1)==0)
		return notify_fail("写文件"+file+"出错！请仔细检查出错记录！\n");
	write("输出成功！>>"+file+"\n");
	return 1;
}

int main(object me, string arg)
{
	mapping emote;

	if( !arg ) return notify_fail("你要编辑什么 emote？\n");
		if(wiz_level(me)<wiz_level("(immortal)")&&!me->query("edemote"))
		return notify_fail("你无权修改emote动词！\n");

	if( sscanf(arg, "-d %s", arg) ) {
		write("删除 emote：" + arg + "\n");
		EMOTE_D->delete_emote(arg);
		return 1;
	}

	if( sscanf(arg, "-p %s", arg) ) {
		emote = EMOTE_D->query_emote(arg);
		printf("上次修改：%s\n", emote["updated"]);
		printf("—————————————\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
			emote["myself"], emote["others"], emote["myself_self"],
			emote["others_self"], emote["myself_target"], emote["target"],
			emote["others_target"] );
		return 1;
	}

	if( sscanf(arg,"-ex %s",arg)==1 )
		return export_emote(this_player(1),arg);
	emote = EMOTE_D->query_emote(arg);
	emote = (["updated":geteuid(me)]);

	write("编辑 emote：" + arg + "\n");
	write("讯息可以有好几行，用 . 表示结束。\n");
	write("讯息中可使用的参数有以下几种：\n");
	write("  $N  自己的名字。\n");
	write("  $n  使用对象的名字。\n");
	write("  $P  自己的人称代名词，如你、你、他、她、它、它。\n");
	write("  $p  使用对象的人称代名词，如你、你、他、她、它、它。\n");
	write("  $S  对自己的称呼。\n");
	write("  $s  对自己的粗鲁称呼。\n");
	write("  $C  对自己的呢称。\n");
	write("  $c  对别人的呢称。\n");
	write("  $R  对别人的尊称。\n");
	write("  $r  对别人的粗鲁称呼。\n");
	write("————————————————————————————————————\n");
	write("不指定对象使用这个 emote 时，你自己看到的讯息：\n->");
	input_to("get_msg_myself", emote, arg);
	return 1;
}


int get_msg_myself(string msg, mapping emote, string pattern)
{
	if (msg==".") {
		if( !undefinedp(emote["myself"]) ) emote["myself"] += "\n";
		write("不指定对象使用这个 emote 时，其他人看到的讯息：\n->");
		input_to("get_msg_others", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["myself"]) )
		emote["myself"] += msg + "\n";
	else emote["myself"] = msg;
	write("->");
	input_to("get_msg_myself", emote, pattern);
	return 1;
}

int get_msg_others(string msg, mapping emote, string pattern)
{
	if (msg==".") {
		if( !undefinedp(emote["others"]) ) emote["others"] += "\n";
		write("对自己使用这个 emote 时，自己看到的讯息：\n->");
		input_to("get_msg_myself_self", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["others"]) )
		emote["others"] += msg + "\n";
	else emote["others"] = msg;
	write("->");
	input_to("get_msg_others", emote, pattern);
	return 1;
}

int get_msg_myself_self(string msg, mapping emote, string pattern)
{
	if (msg==".") {
		if( !undefinedp(emote["myself_self"]) ) emote["myself_self"] += "\n";
		write("对自己使用这个 emote 时，其他人看到的讯息：\n->");
		input_to("get_msg_others_self", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["myself_self"]) )
		emote["myself_self"] += msg + "\n";
	else emote["myself_self"] = msg;
	write("->");
	input_to("get_msg_myself_self", emote, pattern);
	return 1;
}

int get_msg_others_self(string msg, mapping emote, string pattern)
{
	if (msg==".") {
		if( !undefinedp(emote["others_self"]) ) emote["others_self"] += "\n";
		write("对别人使用这个 emote 时，自己看到的讯息：\n->");
		input_to("get_msg_myself_target", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["others_self"]) )
		emote["others_self"] += msg + "\n";
	else emote["others_self"] = msg;
	write("->");
	input_to("get_msg_others_self", emote, pattern);
	return 1;
}

int get_msg_myself_target(string msg, mapping emote, string pattern)
{
	if (msg==".") {
		if( !undefinedp(emote["myself_target"]) ) emote["myself_target"] += "\n";
		write("对别人使用这个 emote 时，使用对象看到的讯息：\n->");
		input_to("get_msg_target", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["myself_target"]) )
		emote["myself_target"] += msg + "\n";
	else emote["myself_target"] = msg;
	write("->");
	input_to("get_msg_myself_target", emote, pattern);
	return 1;
}

int get_msg_target(string msg, mapping emote, string pattern)
{
	if (msg==".") {
		if( !undefinedp(emote["target"]) ) emote["target"] += "\n";
		write("对别人使用这个 emote 时，除你自己和使用对象外，其他人看到的讯息：\n->");
		input_to("get_msg_others_target", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["target"]) )
		emote["target"] += msg + "\n";
	else emote["target"] = msg;
	write("->");
	input_to("get_msg_target", emote, pattern);
	return 1;
}

int get_msg_others_target(string msg, mapping emote, string pattern)
{
	if (msg==".") {
		if( !undefinedp(emote["others_target"]) ) emote["others_target"] += "\n";
		EMOTE_D->set_emote(pattern, emote);
		write("Emote 编辑结束。\n");
		return 1;
	}
	if( !undefinedp(emote["others_target"]) )
		emote["others_target"] += msg + "\n";
	else emote["others_target"] = msg;
	write("->");
	input_to("get_msg_others_target", emote, pattern);
	return 1;
}

int help()
{
write(@HELP
指令格式 : edemote [-d|-p] <emote>
 
这个指令可以修改, 删除 emote 或列出其内容. 加上 -d 参数会删除
指定的 emote, -p 参数则会列出指定 emote 的内容. 列出的顺序与编
辑 emote 时相同.
 
输入 emote 讯息时有三个项目: 没有目标, 指定目标或是对自己. 若
不想有某项讯息, 则直接在空白行输入 '.' 跳过.
 
一个 emote 讯息可以有很多行, 在空白行输入 '.' 结束输入该项 emote.
 
编辑 emote 时可以用以下的符号来表示:
 
$N : 自己的名字.
$n : 目标的名字.
$P : 自己的人称代名词.
$p : 目标的人称代名词.
$S : 对自己的称呼。
$s : 对自己的粗鲁称呼。
$C : 对自己的呢称。
$c : 对别人的呢称。
$R : 对别人的尊称。
$r : 对别人的粗鲁称呼。
HELP
    );
    return 1;
}
