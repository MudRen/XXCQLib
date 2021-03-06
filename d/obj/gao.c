#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIR "胖" HIC "胖" HIG "蛋" HIB "糕" NOR,
                ({"cake","dan gao","gao"}));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", @LONG
     一块特大的蛋糕，上面盖着香香厚厚的奶油，是胖胖为了庆贺自己生日发给大家的。
     大家同喜同喜，呵呵！
LONG);
                set("unit", "块");
                set("value", 100000);
        }
}
string chinese_time(int type,string get_time)
{
        string e_time, week, month, year;
        string c_week, c_year, c_month, c_time;
        int day, hour, minute, second;
        string *month_name = ({"Jan","Feb","Mar","Apr","May","Jun","Jul",
		"Aug","Sep","Oct","Nov","Dec"});
        string *week_name = ({"Mon","Tue","Wed","Thu","Fri","Sat","Sun"});

        if ( stringp(get_time) )
                e_time = get_time;
        else e_time = ctime(time());

        // e_time must is ctime(time string) like "Sun May  3 00:52:12 1998"
        sscanf(e_time,"%s %s %d %d:%d:%d %s", week, month, day, hour, minute, second, year);

        c_week  = chinese_number(member_array(week, week_name) + 1);
        c_month = chinese_number(member_array(month, month_name) + 1);

        c_year  = sprintf("%s%s%s%s",
                         chinese_number(year[0]-48),
                         chinese_number(year[1]-48),
                         chinese_number(year[2]-48),
                         chinese_number(year[3]-48));

        c_year = c_year + "年";
        c_month  = c_month + "月";
        c_week = " 星期"+c_week;

        c_time = chinese_number(day) + "日";
        c_time += chinese_number(hour) + "点";
        c_time += chinese_number(minute) + "分";
        // maybe not need srcond to show
        // c_time += chinese_number(second) + "秒";

        if (type) {
                switch( type ) {
                        case 1: return c_year+c_month+c_time+c_week;
                        case 2: return c_year+c_month+c_time;
                        case 3: return c_month+c_time+c_week;
                        case 4: return c_month+c_time;
                        case 5: return year+"年"+(member_array(month, month_name) + 1)+
				"月"+day+"日"+hour+"点"+minute+"分";
                        case 6: return (member_array(month, month_name) + 1)+
				"月"+day+"日"+hour+"点"+minute+"分";
                        default: return c_year+c_month+c_time+c_week;
                        }
                }
        return c_year+c_month+c_time+c_week;
}
void init()
{
	add_action("do_eat","eat");
	add_action("do_eat","chi");
}

int do_eat(string arg)
{
	string rtime,skill;
	mapping skl;
	int max;
	object me=this_player();
	if(!arg)
		return notify_fail("你要吃什么？\n");
	rtime=chinese_time(1,(string)localtime(time()));
	message_vision("$N拿起一块"+name(1)+"就要吃。\n",this_player());
	if(strsrch(rtime,"六月五日")!=-1)
	{
		//可以吃礼物。
		max = me->query("max_jingli");
		me->set("eff_jingli",max);
		me->set("jingli",max);
		max = me->query("max_jing");
		me->set("eff_jing",max);
		me->set("jing",max);
		max = me->query("max_neili");
		me->set("eff_neili",max);
		me->set("neili",max);
		max = me->query("max_qi");
		me->set("eff_qi",max);
		me->set("qi",max);
		max = me->query("max_shen");
		me->set("eff_shen",max);
		me->set("shen",max);
		max = me->max_food_capacity();
		me->set("food",max);
		max = me->max_water_capacity();
		me->set("water",max);
		me->clear_condition();
		if(!this_player()->query("bir19990605"))
		{
			me->set("bir19990605",1);
			me->add("combat_exp",me->query("combat_exp")/20);
			me->add("potential",5000);
			me->add("max_neili",me->query("max_neili")/20);
			me->add("max_jingli",me->query("max_jingli")/20);
			me->add("str",me->query("str")/10);
			me->add("int",me->query("int")/10);
			me->add("per",me->query("per")/10);
			me->add("con",me->query("con")/10);
			me->add("dex",me->query("dex")/10);
			skl=me->query_skills();
			if(mapp(skl))
				foreach(skill in keys(skl))
					me->set_skill(skill,(int)(me->query_skill(skill,1)*21/20));
		}
		message_vision("$N几口就把"+name(1)+"给吃完了，直觉得浑身的骨骼经络都轻松了很多。\n",me);
		destruct(this_object());
	}
	else
	{
		write("哎呀！蛋糕过期了，不能吃了！\n");
		message_vision("$N呀地尖叫一声，扔了一块过期的蛋糕下来。\n",this_player());
		set("name",HIR"过期的蛋糕"NOR);
		set("value",10);
		move(environment(this_player()));
	}
	return 1;
}