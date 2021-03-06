#define MASTER "/adm/obj/master"
inherit F_CLEAN_UP;
#define SPLIT "\n.\n"
#define EM_HEAD "\n.\nbegin:\n.\n"
int main(object me,string file)
{
	string key,str,str1,item,type,mesg;
	mapping emote;
	if(!file||file=="")
		return notify_fail("用法：import 文件名\n");
	file=MASTER->make_path_absolute(file);
	write("准备从文件"+file+"导入emote数据。\n");
	if(MASTER->valid_read(file,me,"read_file")==0)
		return notify_fail("你不能写该文件！输出失败！\n");
	if(file_size(file)<0)
		return notify_fail("档案不存在！\n");
	str=read_file(file);
	foreach(str1 in explode(str,EM_HEAD))
	{
		emote=([]);
		if(sscanf(str1,"%s"+SPLIT+"%s",key,str1)!=2)
			return notify_fail("关键字emote动词读取出错！\n");
		//if(mapp(EMOTE_D->query_emote(key)))//跳过key这个emote!
		//	continue;
		foreach(item in explode(str1,SPLIT))
		{
			if(sscanf(item,"%s:%s",type,mesg)!=2)
				return notify_fail("动词"+key+"的内容分析错误！\n");
			emote[type]=mesg;
		}
		emote["updated"]=me->id(1);
		EMOTE_D->set_emote(key,emote);
		write("成功增加emote -> "+key+"!\n");
	}
	return 1;
}
