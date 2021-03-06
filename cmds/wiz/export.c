#define MASTER "/adm/obj/master"
inherit F_CLEAN_UP;
#define SPLIT "\n.\n"
#define EM_HEAD "\n.\nbegin:\n.\n"
int main(object me,string file)
{
	string *all_keys,key,str,item;
	mapping emote;
	if(!file||file=="")
		return notify_fail("用法：export 文件名\n");
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
