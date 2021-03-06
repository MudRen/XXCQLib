// who.c

// From congw@cctx && netplay@cctx 98/09/06

// Modify by JackyBoy @ cctx 99/1/1 增加无参数时显示发呆者
// 并且可以显示哪个巫师是在发呆！

#include <net/dns.h>
#include <ansi.h>
#include <net/daemons.h>
#include <net/macros.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mixed main(object me, string arg, int remote)
{
        string str, name,id,*option;
        object *list,*l_list;
        int i, j, ppl_cnt;
        int opt_long, opt_id, opt_wiz,opt_all,wiz_cnt;
        mapping mud_list;
        mixed *muds;

        if( arg ) 
        {
                option = explode(arg, " ");
                i = sizeof(option);
                while( i-- )
                        switch(option[i]) 
                        {
                                case "-l": opt_long = 1;        break;
                                case "-w": opt_wiz = 1;         break;
                                case "-all": opt_all = 1;       break;
                                default:
                                        if( option[i][0]=='@' ) 
                                        {
                                                RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],me, opt_long);
                                                write("网路讯息已送出，请稍候。\n");
                                                return 1;
                                        }
                                        return notify_fail("指令格式：who [-l|-w|-all]\n");
                        }
        }
        if (opt_all)
        {
                if( !find_object(DNS_MASTER) )
                return notify_fail("网路精灵并没有被载入。\n");
        //      Obtain mapping containing mud data
        mud_list = (mapping)DNS_MASTER->query_muds();
                muds = keys( mud_list ) - ({ "DEFAULT" });
                if(!mud_list)
                return notify_fail( CHINESE_MUD_NAME + "目前并没有跟网路上其他 Mud 取得联系。\n");
                for (i=0;i<sizeof(muds);i++)
                {
                        if( mud_list[muds[i]]["VERSION"] != MUDLIB_VERSION )
                                continue;
                        if (mud_list[muds[i]]["MUDLIB"]==MUDLIB_NAME)
                                RWHO_Q->send_rwho_q(mud_list[muds[i]]["NAME"],me,opt_long);
                                //write(mud_list[muds[i]]["NAME"]);
                }
        //      return 1;
        }

        if( opt_long ) 
        {
                if( (int)me->query("jing") < 30 )
                        return notify_fail("你的精神太差了，没有办法得知其他玩家的详细资料。\n");
                me->receive_damage("jing", 30);
        }
        str = "★ "+CHINESE_MUD_NAME+" ★" + "\n";
        str += "——————————————————————————————————\n";
        //list = users();修改为排序过的，如果人太多可以修改为不排序
        list = sort_array(users(), "sort_user", this_object());
        if( opt_long || opt_wiz ) 
        {       
                l_list = sort_array(users(), "sort_family", this_object());
                j = sizeof(l_list);
                while( j-- ) 
                {
                        // Skip those users in login limbo.
                        if( !environment(l_list[j]) ) continue;
                        if( !me->visible(l_list[j]) ) continue;
                        if( wizardp(l_list[j]) ) continue;
                        if( opt_wiz && !wizardp(l_list[j]) ) continue;
                        str = sprintf("%s%12s %s",
                                str,
                                RANK_D->query_rank(l_list[j]),
                                l_list[j]->short(1)
                                );
                        if( query_idle( l_list[j] ) > 120 ) 
                                str += HIM "<发呆"+chinese_number((query_idle(l_list[j])-60)/60)+"分钟>\n" NOR;
                        else str+="\n";
                }
                //      list = sort_array(users(), "sort_user", this_object());
                j = sizeof(list);
                while( j-- ) 
                {
                        // Skip those users in login limbo.
                        if( !environment(list[j]) ) continue;
                        if( !me->visible(list[j]) ) continue;
                        if( !wizardp(list[j]) ) continue;
                        if( opt_wiz && !wizardp(list[j]) ) continue;
                        str = sprintf("%s%12s %s",
                                str,
                                RANK_D->query_rank(list[j]),
                                list[j]->short(1)
                                );
                        if( query_idle( l_list[j] ) > 120 ) 
                                str += HIM "<发呆"+chinese_number((query_idle(l_list[j])-60)/60)+"分钟>\n" NOR;
                        else str+="\n";
                        wiz_cnt++;
                }
        } 
        else 
        {
                ppl_cnt = 0;
                j = sizeof(list);
                while( j-- ) 
                {
                        // Skip those users in login limbo.
                        if( !environment(list[j]) ) continue;
                        if( me && !me->visible(list[j]) ) continue;
                        if( wizardp(list[j]) ) continue;
                        if(list[j]->query("gender") == "女性")  
                                name=list[j]->name(1)+"("+HIR+capitalize(list[j]->query("id"))+NOR+")";
                        else
                                name=list[j]->name(1)+"("+YEL+capitalize(list[j]->query("id"))+NOR+")";
                        if( query_idle( list[j] ) > 120 ) 
                                str+=HIM"@"NOR;
                        str = sprintf("%s%-25s%s", str, name,
                                (ppl_cnt%3==2? "\n": (strlen(list[j]->name(1)+list[j]->query("id"))>13?"\t":"\t\t"))
                                );
                        ppl_cnt++;        
                }
                //      if ( ppl_cnt % 3 ) str += "\n";
                //      ppl_cnt = 0;
                j = sizeof(list);
                while(j--) 
                {
                        if( !environment(list[j]) ) continue;
                        if( me && !me->visible(list[j]) ) continue;
                        if( !wizardp(list[j]) ) continue;
                        name=list[j]->name(1)+"("+HIY+capitalize(list[j]->query("id"))+NOR+")";
                        if( query_idle( list[j] ) > 120 ) 
                                str+=HIM"@"NOR;
                        str = sprintf("%s%-25s%s", str, name,
                                (ppl_cnt%3==2? "\n": (strlen(list[j]->name(1)+list[j]->query("id"))>13?"\t":"\t\t"))
                                );
                        ppl_cnt++;        
                }
                if ( ppl_cnt % 3 ) str += "\n";
        }
        str += "——————————————————————————————————\n";
        if (opt_wiz)
                str = sprintf("%s共有 %d 位巫师连线中，系统负担：%s\n", str, wiz_cnt,
                        query_load_average() + "\n");
        else    
                str = sprintf("%s共有 %d 位使用者连线中，系统负担：%s\n", str, sizeof(list),
                        query_load_average() + "\n");
        if( remote ) return str;
        me->start_more(str);
        return 1;
}

int sort_user(object ob1, object ob2)
{
        if( wizardp(ob1) && !wizardp(ob2) ) return -1;
        if( wizardp(ob2) && !wizardp(ob1) ) return 1;
        if( wizardp(ob1) && wizardp(ob2) )
                return (int)SECURITY_D->get_wiz_level(ob2) 
                        - (int)SECURITY_D->get_wiz_level(ob1);
        if( ob1->query("id") && !ob2->query("id") )
                return -1;
        if( ob2->query("id") && !ob1->query("id") )
                return 1;
        if( !ob1->query("id") && !ob2->query("id") )
                return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
        return strcmp(ob2->query("id"), ob1->query("id"));
}

int sort_family(object ob1, object ob2)
{
        string name1, name2;
        if( wiz_level(ob1) != wiz_level(ob2) )
                return wiz_level(ob2) - wiz_level(ob1);
        name1 = ob1->query("family/family_name");
        name2 = ob2->query("family/family_name");
        if (intp(name1)) name1 = "";
        if (intp(name2)) name2 = "";
        if (name1 > name2) return -1;
        if (name1 < name2) return 1;
        return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
}

int help(object me)
{
write(@HELP
指令格式 : who [-l|-i|-w]
这个指令可以列出所有在线上的玩家及其等级。带@者为发呆者。
-l 选项列出较详细的讯息。
-w 只列出线上所有的巫师。
-all 列出所有系列站点的在线玩家。

相关指令： finger
HELP
    );
    return 1;
}
