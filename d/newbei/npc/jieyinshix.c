// jieyinshi.c 接客童子
// CLEANSWORD 1996/2/2

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("接客童子", ({ "tong zi", "tong" }));
        set("long", "这是一为专门接待新玩家的童子\n");
        set("gender", "男性");
        set("age", 18);

        set("shen_type", 1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
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
/*
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
                say("童子说道：这位"+ RANK_D->query_respect(ob)
                                + ",欢迎光临。\n"+
                "一通向江南。\n"+
                "二通向中原。\n"+
                "三通向京城。\n"+
                "四通向西域。\n"+
                "五通向云南。\n"+
                "六通向成都。\n"+
                "请您选择你要去的地方\n");
                
}
*/
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
                say("童子说道：这位"+ RANK_D->query_respect(ob)
                                + ",欢迎光临。\n"+
                "    请您往南走，您将进入"+WHT"小雪初晴神雪山\n"NOR+
                "    您可以先查看一下即时地图"+HIC"（map here）\n"NOR+
                "    您可以再看神雪山的说明"+HIC"（help wuguan）\n"NOR);
}