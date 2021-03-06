// tanglyz

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("唐老爷子", ({ "tanglyz", "tang", "yezi"}));
//	set("nickname", "小师妹");
	set("long", 
"唐方身材娇小，长的极为清秀，又带几分英气，清劲多于柔弱。\n"
"她是唐门长房宗主唐尧舜之女，后又得唐老太太亲授衣钵，在唐门地位颇高。\n");
	set("gender", "男性");
	set("age", 91);
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
	set("combat_exp", 2500000);
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
	
	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

void attempt_apprentice(object ob)
{
	if ( (string)ob->query ("family/family_name") == "四川唐门" && (int)ob->query ("combat_exp") > 1000000 )
	{
		message_vision("唐老爷子微微一笑，对$N说道:“想拜师的话去找老太太吧，我已经不收徒弟了！”",ob);
		message_vision("唐老爷子微微一顿，又道:“不过，既然你已经找到我这里了，我就指点你几招吧！”",ob);
/*
	此段用来添加唐老爷子的所指点的功夫�!!!!

*/
	}
	else
		if ( (string)ob->query ("family/family_name") != "四川唐门" )
		{
			message_vision("\n唐老爷子微微一笑，对$N说道:“你不知我唐门乃是世家，不收外姓弟子嘛！”\n",ob);
			message_vision("唐老爷子微微一顿，又道:“不过，既然你已经找到我这里了，就喝杯茶再走吧！”\n",ob);
			tell_object(ob, "唐老爷子见你有些犹豫，说道:“这茶可是极其珍贵，喝了可以固本培元，对习武之人可是大大的有益啊！”\n\n");
			write(YEL"你要喝吗？请输入选择（y)/n ："NOR);
			input_to("accept_cha", 1, ob, 1);
		}
		else
			tell_object(ob, "唐老爷子惋惜的对你说:“可惜你的功夫还不到家，不能使用我的绝技！你以后再来吧！”\n");
	return;
}

void accept_cha(string want, object ob, int forever)
{
	if ( want == "" || want == "y" || want == "Y" )
	{
		message_vision("唐老爷子微一抬手，便有一家丁给$N奉上了一杯香茶！\n",ob);
		tell_object(ob, "只见茶水发出淡淡的绿色，正冒着热气，几片不知名的叶片漂在杯中，闻起来清香扑鼻。\n");
		message_vision("$N将茶杯端起，美美的喝了一口。\n", ob);
		call_out("dead", 120, ob);
	}
	else
	{
		message_vision("\n唐老爷子勃然大怒，对$N喝道:“让你好死你不要，非要我动手吗！我这里是不能被外人知道的！”\n",ob);
		this_object()->kill_ob(ob);
		ob->fight_ob(this_object());
	}
}

int dead(object ob)
{
	tell_object(ob,HIR"你腹中突然如刀绞一般疼痛，原来茶中竟是剧毒......\n你眼前一黑，一头栽倒在地上......"NOR);
	tell_room( environment(ob), HIR + ob->query("name") + "突然一头栽倒在地上！"NOR, ob);
	ob->die();
	tell_room( environment(this_object()), "唐老爷子长叹一声:“唉！外人怎么会闯进来了呢！”");
}