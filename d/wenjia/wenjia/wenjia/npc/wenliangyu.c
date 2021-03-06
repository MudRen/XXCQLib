// NPC: wenliangyu.c 温亮玉
// Created by Zeus 1999.4.7
// Modified by Zeus 1999.7.10
// 
// 大字号的老大。

inherit NPC;
inherit F_DEALER;

#include <ansi.h>

void init();
void greeting(object);
void recover_ob();
int give_task(string);
int ask_praise();
int ask_duzun();

void create()
{
        set_name("温亮玉", ({ "wen liangyu" , "wen"}) );
        set("gender", "男性" );
        set("age", 38);
        set("per", 20);
        set("long",
                "这位文质彬彬的中年人一团和气,他就是老字号里专管藏毒的大字号的负责人。\n");
        set("attitude", "friendly");

        set("qi", 2000);
        set("max_qi", 2000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("lphandbook_count", 1);

        set("combat_exp", 2500000);

        set_skill("lphand", 180);    //施毒手法
        set_skill("force", 180);     //基本内功
        set_skill("dodge", 180);     //基本轻功
        set_skill("parry", 180);     //基本招架
        set_skill("duzun", 200);     //惟毒独尊
        set_skill("zhixin", 180);    //温故知新
        set_skill("qianli", 180);    //毒行千里
        set_skill("poisonk", 180);   //毒药知识
        set_skill("duzi-du", 200);   //毒字毒
        set_skill("shengdu", 200);   //声毒
        set_skill("bupangguan", 200);//袖手不旁观
        set_skill("literate", 160);  //读书写字

        map_skill("force", "zhixin");
        map_skill("dodge", "qianli");
        map_skill("lphand", "duzun");
        map_skill("parry", "duzun");

        prepare_skill("lphand", "duzun");

        create_family("老字号温家", 3, "弟子");

        set("inquiry", ([
                "奖赏" : (: ask_praise :),
                "duzun" : (: ask_duzun :),
                "惟我毒尊" : (: ask_duzun :),
        ]) );

        setup();

        add_money("gold", 10);

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "lphand.weiwo" :),
                (: recover_ob :)
        }) );

        carry_object("/d/wenjia/obj/chouduan")->wear();
}

void init()
{
        object ob;

        add_action("give_task", "task");

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                 remove_call_out("greeting");
                 call_out("greeting", 1, ob);
        }
        
        if (is_fighting()){
                 remove_call_out("arrest");
                 call_out("arrest",1,ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        if (ob->query("wentask/reg") && !(ob->query_temp("taskda/given"))) {
                 say("温亮玉开口说道：“这位" + RANK_D->query_respect(ob)
                 + "你想干大字号的任务吧，想我要任务吧(task)。”\n");
        }
        else {
                 say("温亮玉说道：“温家弟子的绝技是惟我毒尊(duzun)，学了这个武功称霸武林是没有问题的。”\n");
        }
}

void recover_ob()
{
        command("yun recover");
        return;
}

int give_task(string arg)
{
        object me,givesilver;
        int givepot,giveexp,i,tasktime;

        me=this_player();

        message_vision("$N很有礼貌的向温亮玉询问大字号任务的事!\n",me);

        if ( arg || arg == "ok" ) { //如果玩家输入task ok，那么表示玩家完成任务。
                if( me->query_temp("taskda/done") ) {
                        command("pat " + me->query("id"));
                        message_vision("温亮玉对$N说：“既然你已经完成任务，就给你奖赏吧!”\n",me);
                        if ( me->query("wentask/dafirst")) {
                                message_vision(HIY"温亮玉挺高兴的对$N说：“第一次做任务就有这样的成绩，要给你特别奖赏!”\n"NOR,me);
                                me->add("potential", 40+random(100));
                                me->add("combat_exp", 100+random(100));
                                givesilver=new("/clone/money/gold");
                                givesilver->move(me);
                                me->set("wentask/dafirst",0);
                        }
                        givepot=15+random(10);
                        giveexp=85+random(10);
                        me->add("wentask/done",1);
                        tasktime=me->query("wentask/done");
                        me->add("potential", givepot);
                        me->add("combat_exp", giveexp);
                        message_vision(HIY"温亮玉奖赏了$N"+chinese_number(givepot)+"点潜能和"+chinese_number(giveexp)+"点经验。\n"NOR,me);
                        for (i=1;i<2+random(4);i++) {
                        givesilver=new("/clone/money/silver");
                        givesilver->move(me);}
                        message_vision(HIC"$N已经为温家做了"+chinese_number(tasktime)+"次任务。\n"NOR,me);
                        message_vision(HIC"温亮玉给了$N几两银子。\n"NOR,me);
                        me->delete_temp("taskda/done");
                        me->delete_temp("taskda/given");
                        me->delete_temp("taskda/p_given");
                        return 1;
                }
                else if ( !(me->query_temp("taskda/given")) ) {
                        command("angry " + me->query("id"));
                        message_vision("温亮玉对$N说：“你没有领任务，怎么来邀功了!”\n",me);
                        return 1;
                }
                else if ( me->query_temp("taskda/given") ) {
                        command("angry " + me->query("id"));
                        message_vision("温亮玉对$N说：“你领了任务不赶快去做，站在这里干什么!”\n",me);
                        return 1;
                }
        }        

        if ( !(me->query("wentask/reg"))) {
                if (!(string)me->query("family") || (string)me->query("family/family_name") != "老字号温家") {
                        message_vision("温亮玉很客气地对$N说：“你不是我们温家的人，如何敢劳您的大架?”\n",me);
                return 1;
                } {
                message_vision("温亮玉对$N说：“你先到温古那里登记，在来我这里领任务!”\n",me);
                return 1;}                
        }
                
        if ( me->query_temp("taskda/given") ) {
                command("angry " + me->query("id"));
                message_vision("温亮玉对$N说：“你不是已经领了任务了吗?不赶快去做，站在这里干什么!”\n",me);
                return 1;
        }

        me->set_temp("taskda/given",1);
        message_vision("温亮玉对$N说：“既然你想为本门出力，那么就到温哭那里领一个毒药，送到温笑那里吧!”\n",me);

        return 1;
}

int ask_praise()
{
       int worktime;
       object me,ob;

       me=this_player();

       worktime=me->query("wentask/done");

       if (worktime>400 ){
               message_vision("温亮玉对$N说：“不错!既然你已如此尽力的为温家出力，奖赏是应该的!”\n",me);
               if ( query("lphandbook_count") < 1 ){
                           message_vision("温亮玉又对$N说道：“但是你来晚了，秘籍已经不在这里了。”\n",me);
                           return 1;
               }
               add("lphandbook_count", -1);
               ob=new("/d/wenjia/treasure/lphandbook");
               ob->move(me);
               message_vision("温亮玉对$N说：“这本施毒手法的秘籍篇就给你了，你好好的学吧!”\n",me);
               return 1;
       }
       message_vision("温亮玉对$N说：“你还未努力的温家出力，在去做任务吧!”\n",me);
       return 1;
}

int ask_duzun()
{
       object me;

       me=this_player();
       message_vision("温亮玉对$N说：“我可不能教你惟我毒尊，想学就要去拜温故衣为师。”\n",me);
       return 1;
}