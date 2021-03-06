// tangltt

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

int do_pull();
void close(object room);

void create()
{
	set_name("唐老太太", ({ "tangltt", "tang", "tai"}));
//	set("nickname", "小师妹");
	set("long", 
"唐方身材娇小，长的极为清秀，又带几分英气，清劲多于柔弱。\n"
"她是唐门长房宗主唐尧舜之女，后又得唐老太太亲授衣钵，在唐门地位颇高。\n");
	set("gender", "女性");
	set("age", 89);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 18);
	set("int", 25);
	set("con", 24);
	set("dex", 28);

	set("max_qi", 5000);
	set("max_jingli", 2000);
	set("max_douzhi", 1000);
	set("douzhi", 1000);
	set("neili", 6000);
	set("max_neili", 6000);
	set("jiali", 50);
	set("combat_exp", 2000000);
	set("score", 10000);

	set_skill("force", 300);
//	set_skill("zixia-shengong", 30);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("sword", 300);
	set_skill("blade", 300);
	set_skill("strike", 300);
/*	set_skill("hunyuan-zhang", 50);
	set_skill("huashan-jianfa", 50);
	set_skill("huashan-shenfa", 50);
	set_skill("fanliangyi-dao", 30);

	map_skill("force", "zixia-shengong");
	map_skill("blade", "fanliangyi-dao");
	map_skill("dodge", "huashan-shenfa");
	map_skill("parry", "huashan-jianfa");
	map_skill("sword", "huashan-jianfa");
	map_skill("strike", "hunyuan-zhang");

	prepare_skill("strike", "hunyuan-zhang");
	prepare_skill("cuff", "poyu-quan");
*/
	create_family("四川唐门", 2, "掌门");
	set("inquiry", (["唐老爷子" : (:do_pull:),]));
	setup();

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

void attempt_apprentice(object ob)
{
	if ( (string)ob->query ("family/family_name") != "四川唐门" || (int)ob->query ("combat_exp") < 600000 )
	{
        	command("say 你还是先拜尧舜为师，学些唐门的基本工夫吧！\n");
                return;
        }

    command("say 好吧，从今天起你就是我的关门弟子了。\n");
    command("recruit " + ob->query("id"));
}

int do_pull()
{
	object me, room;
	me = this_player();
	room = environment(this_object());
	message_vision(YEL"\n唐老太太一转身在床头扳动了一下。\n只听“滋滋”几声轻响床脚的地面移开了一个洞口。\n"NOR, me);
	room->set("exits/down", "/d/tangmen/didao1");
	remove_call_out("close");
	call_out("close", 3, environment(this_object()));
	return 1;
}

void close(object room)
{
	message("vision",HIR"身后传来一声轻响，想是暗门又被关上了。\n"NOR, this_player());
	room->delete("exits/down");
}