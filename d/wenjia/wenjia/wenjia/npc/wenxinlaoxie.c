// NPC: wenxinlaoxie.c
// Created by Zeus 1999.4.7
// Modified by Zeus 1999.7.30
// 
// 

inherit NPC;

string* medsources = ({
        "chihuohe",
        "mushugen",
        "fanmubie",
        "chiaisu", 
        "duanchangcao", 
        "hedinghong", 
        "kongquedan", 
});

string* chinesemedsources = ({
        "赤火蝎",
        "木薯根",
        "番木鳖",
        "赤矮栗",
        "断肠草",
        "鹤顶红",
        "孔雀胆",
});

#include <ansi.h>

void init();
void greeting(object);
void recover_ob();
int give_task();

void create()
{
        set_name("温心老契", ({ "wenxin laoxie" , "wen"}) );
        set("gender", "男性" );
        set("age", 55);
        set("per", 5);
        set("long",
                "这个人的长相十分奇怪,他的头就象一只凤梨,但他却是老字号\n"+
                "中的分号之一小字号的老大,得罪他,你准没好果子吃。\n");
        set("attitude", "friendly");

        set("qi", 2000);
        set("max_qi", 2000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 200);

        set("combat_exp", 2500000);

        set_skill("lphand", 180);    //施毒手法
        set_skill("force", 180);     //基本内功
        set_skill("dodge", 180);     //基本轻功
        set_skill("parry", 180);     //基本招架
        set_skill("duzun", 180);     //惟毒独尊
        set_skill("zhixin", 180);    //温故知新
        set_skill("qianli", 180);    //毒行千里
        set_skill("literate", 160);  //读书写字

        map_skill("force", "zhixin");
        map_skill("dodge", "qianli");
        map_skill("lphand", "duzun");
        map_skill("parry", "duzun");

        prepare_skill("lphand", "duzun");
  
        create_family("老字号温家", 3, "弟子");

        set("inquiry", ([
                "采药" : (: give_task :),
                "任务" : (: give_task :),
                "job" : (: give_task :),
        ]) );

        setup();

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "lphand.weiwo" :),
		(: recover_ob :)
        }) );

        add_money("gold", 10);

        carry_object("/d/wenjia/obj/chouduan")->wear();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                 remove_call_out("greeting");
                 call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        if (ob->query("wentask/reg") && !(ob->query_temp("taskxiao/given")) ) {
                 say("温心老契开口说道：“这位" + RANK_D->query_respect(ob)
                 + "你想干大字号的任务吧，想我要任务吧。”\n");
        }
        else {
                 say("温心老契说道：“温家弟子的绝技是惟我毒尊(duzun)，学了这个武功称霸武林是没有问题的。”\n");
        }
}

void recover_ob()
{
        command("yun recover");
        return;
}

int give_task()
{
        object me,givesilver;
        int givepot,giveexp,i,tasktime;

        me=this_player();

        if ( me->query_temp("taskxiao/given") )
		{
                command("angry " + me->query("id"));
                message_vision("温心老契对$N说：“你领了任务不赶快去做，站在这里干什么!”\n",me);
                return 1;
        }        

        if ( !me->query("wentask/reg") )
        {
                if (!(string)me->query("family") || (string)me->query("family/family_name") != "老字号温家") 
				{
                        message_vision("温心老契很客气地对$N说：“你不是我们温家的人，如何敢劳您的大架?”\n",me);
                        return 1;
                } else
         	    {
                        message_vision("温心老契对$N说：“你先到温古那里登记，在来我这里领任务!”\n",me);
                        return 1;
				}                
		}
                
        if ( me->query_temp("taskxiao/given") )
		{
                command("angry " + me->query("id"));
                message_vision("温心老契对$N说：“你不是已经领了任务了吗?不赶快去做，站在这里干什么!”\n",me);
                return 1;
        }

        me->set_temp("taskxiao/given",1);
        message_vision("温心老契对$N说：“既然你想为本门出力，那么就去温文那里要一张药方，按照药方(yaofang)去采原材料吧!”\n",me);

        return 1;
}

int accept_object(object who, object ob)
{
        object *inv,givesilver;
        int amount,i,givepot,giveexp,tasktime,med1,med2,med3;

		if ( ob->query("name") != "药篓" )
                 return notify_fail("温心老契说：“你给我这个干什么?”\n");

		if (!who->query_temp("taskxiao/yaofanggiven"))
        {
                message_vision("温心老契对$N说道：“你去把药方还给温文再来?”\n",who);
                return 1;
        }

		if (!who->query_temp("taskxiao/yaochugiven"))
        {
                message_vision("温心老契对$N说道：“你去把药锄还给温文再来?”\n",who);
                return 1;
        }

        if ( !(who->query_temp("taskxiao/given")) )
		{
                command("angry " + who->query("id"));
                message_vision("温心老契对$N说：“你没有领任务，怎么来邀功了!”\n",who);
                return 1;
        }

        inv = all_inventory(ob);
        med1=who->query_temp("taskxiao/med1");
        med2=who->query_temp("taskxiao/med2");
        med3=who->query_temp("taskxiao/med3");
		if( !sizeof(inv) )
                 return notify_fail("那里面没有任何东西。\n");

        for(i=0; i<sizeof(inv); i++)
		{
				if( inv[i]->query("name") == chinesemedsources[med1] ) amount++;
                if( inv[i]->query("name") == chinesemedsources[med2] ) amount++;
                if( inv[i]->query("name") == chinesemedsources[med3] ) amount++;
        }

        if (amount < 3 ){
                message_vision("温心老契的脸色变得更难看了，对$N说道：“你身为温家弟子，不为温家出力还这样偷懒?再去采药！\n”",who);
				ob->move(who);
				return 1;
		}

		message_vision("温心老契的脸色变得似乎有些好看，对$N说道：“你为温家出力是应该得到奖赏的！”\n",who);
        givepot=150+random(100);
        giveexp=250+random(200);
        who->add("wentask/done",1);
        tasktime=who->query("wentask/done");
        who->add("potential", givepot);
        who->add("combat_exp", giveexp);
        message_vision(HIY"温心老契奖赏了$N"+chinese_number(givepot)+"点潜能和"+chinese_number(giveexp)+"点经验。\n"NOR,who);
        for (i=1;i<2+random(10);i++) {
        givesilver=new("/clone/money/silver");
        givesilver->move(who);}
        message_vision(HIC"$N已经为温家做了"+chinese_number(tasktime)+"次任务。\n"NOR,who);
        message_vision(HIC"温心老契给了$N几两银子。\n"NOR,who);
        who->delete_temp("taskxiao");
        return 1;
}


//腐尸肉
//桃花瘴
//碧蚕蛊
//十三点
//没解药
//自创
//赤火蝎
//木薯根
//番木鳖
//赤矮栗
