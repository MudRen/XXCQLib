#include <ansi.h>
#include <mudlib.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *hufa = ({
		" "," "," "," "," "," "," "," ",
		});
	string *liu = ({
		" "," "," "," ",
		});
	string *shenjun = ({
		" "," "," "," "," "," "," "," "," "," ",
		" "," "," "," "," "," "," "," "," ",
		});
	string temp;
    int i = 1;
    int m = 0;
    int n = 0;
    int p = 0;
    int k = 0;
    int l = 0;
    int h = 0;
	
    while(temp = read_file("/d/quanli/npc/QUANLI",i,1))
	{
		if(temp[9..10] == "王")
		{
			hufa[m] = temp;
			m = m + 1;
		}
		else if(temp[7..8] == "柳")
		{
			liu[n] = temp;
			n = n + 1;
		}
		else if(temp[17..20] == "神君")
		{
			shenjun[p] = temp;
			p = p + 1;
		}
	i = i + 1;
	}
if(hufa[0] != " ")
{
    write(HIY"权力帮八大护法名单:\n");
    write("__________________\n");
	while(hufa[k] != " " && k <= sizeof(hufa))
	{
    write(RED"-> "+hufa[k]);
	k = k + 1;
	}
}
if(liu[0] != " ")
{
    write(HIW"\n\n权力帮柳随风手下名单:\n");
    write("__________________________________\n");
	while(liu[h] != " " && h <= sizeof(liu))
	{
    write(RED"-> "+liu[h]);
	h = h + 1;
	}
}
if(shenjun[0] != " ")
{
    write(HIB"\n\n权力帮十九神君名单:\n");
    write("______________________\n");
	while(shenjun[l] != " " && l <= sizeof(shenjun))
	{
    write(RED"-> "+shenjun[l]);
	l = l + 1;
	}
}
	return 1;
}
int help(object me)
{
        write("\n指令格式 : qlist\n"
        "用途 : 列出权力帮新名单。\n"
        );
        return 1;
}
