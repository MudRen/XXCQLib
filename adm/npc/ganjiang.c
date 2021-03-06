// ganjiang.c  干将
// Written by Doing Lu  1998/11/2

// 干将负责炼道具的场景，但是不接受玩家的物品，玩家如果炼制道具应该和莫邪打交道。
// 如果 player 在莫邪那里将一切手续办妥，莫邪将道具粗坯交给干将

// 干将接收到莫邪传来的道具，则对他进行锻炼，锻炼完以后，设置 object 的名字为 noname，
// 设置道具的铸造者，铸造者的ID，不设置道具的有效点数 point，因为在莫邪那里已经设置了。
// 并且等候 player 输入关于道具的信息，如果超时，就清除三人的标志，并解除 object
// 如果用户 finish ，这询问 player 是否决定，是则生成道具文件，并在 player 那里纪录道具
// 否则继续修改。
// 其中，在设置道具信息时，采用 set_item() 函数进行设置，如果发现错误，中止锻炼过程

inherit NPC;

#include <ansi.h>
#include "itemmaker.h"

// 如果字符串被设置成这个值，表示输入的字符串具有非法的格式
#define	ILLEGAL_STR	"."
// 在convert时看看要不要去掉彩色
#define	NOCOLOR		1
#define COLORABLE	0

int	ask_me();				// 显示定做信息
int	show_order();				// 显示规则信息
int	start_work(object me, object ob);	// 由莫邪做外部调用
int	prepare_make(object me, object ob);	// 开始打造
object	set_item(string arg1, string arg2);	// 设置打造 object 的各个属性
int	confirm_make(string arg, object ob);	// player 输入完毕后确认

void	clear_data();				// 清除 ganjiang, moye, player 的临时变量并去除粗坯对象

// 转化字符串，主要是针对颜色进行处理
string	converts(string arg, int max_len, int nocolor);

void create()
{
	set_name("干将", ({ "ganjiang", "gan jiang", "gan" }));
	set("long", "他长得粗壮有力，脸庞似如刀削，透出一股英气。他是古往今来有名的铸剑大师。\n" );

	set("nickname", HIR "剑师" NOR);
	set("gender", "男性");
	set("attitude", "friendly");

	set("age", 1535);
	set("shen_type", 0);

	set("str", 1000);

	set("inquiry", ([
		"炼制" : (: ask_me :),
		"铸剑" : (: ask_me :),
		"打造" : (: ask_me :),
		"铸造" : (: ask_me :),
		"制造" : (: ask_me :),
		"打制" : (: ask_me :),
		"定制" : (: ask_me :),
		"定做" : (: ask_me :),
		"定造" : (: ask_me :),
		"兵器" : (: ask_me :),
		"道具" : (: ask_me :),
		"装备" : (: ask_me :),
		"武器" : (: ask_me :),
		"刀剑" : (: ask_me :),
		"装甲" : (: ask_me :),

		"原料" : "炼剑就得有原料，一分钱，一分货，好原料就能出好东西。\n",
		"配料" : "配料有很多，自己去找吧。\n",
		"定金" : "定金很少，就五两黄金，要交定金请交给莫邪。\n",
		"价格" : "你把原料和配料给莫邪看看(show)，她能给你估摸出一个价钱。",

		"规则" : (: show_order :),
		"方法" : (: show_order :),
		"order": (: show_order :),
		
	]));

	seteuid("doing");

        setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_name", "name");
	add_action("do_name", "命名");
	add_action("do_desc", "desc");
	add_action("do_desc", "描述");
	add_action("do_loadmsg", "loadmsg");
	add_action("do_loadmsg", "装备");
	add_action("do_loadmsg", "装备信息");
	add_action("do_backmsg", "backmsg");
	add_action("do_backmsg", "收起");
	add_action("do_backmsg", "收起信息");
	add_action("do_finish", "finish");
	add_action("do_finish", "完成");

	add_action("do_help", "help!");
	add_action("do_help", "帮助");
}

// 发出提示信息
int ask_me()
{
	message_vision("干将对$N说道：这些事请问莫邪，我只管炼剑。\n", this_player());
	return 1;
}

int accept_object(object me, object ob)
{
	if (me->query("name") == "莫邪")
	{
		if (interactive(me))
		{
			command ("kick " + me->query("id"));
			message_vision("干将嘿嘿的奸笑了两声，对$N说道：你以为取了我妻子的名字就能蒙蔽我？我还没瞎呢！\n", me);
			return 1;
		}
		start_work(present(me->query_temp("item/交付人ID"), environment()), ob);
	}
	if (ob->query("item_origin"))
	{
		message_vision("干将对$N说：你别给我这东西，把这个先交给莫邪，在她那里付了钱再说。\n", me);
		return 0;
	} else
	{		
		message_vision("干将冷冷的对$N说道：你给我这些东西干什么？我炼剑，不用这些东西。\n", me);
		return 0;
	}
}

int start_work(object me, object ob)
{
	remove_call_out("prepare_make");
	call_out("prepare_make", 1, me, ob);
	return 1;
}

int prepare_make(object me, object ob)
{
	message_vision(HIC "\n干将说道：好，开炉锻炼！\n\n" NOR, this_object());
	message_vision(HIC "干将接过莫邪手中的" + ob->query("name") +
		       HIC "，随手把它抛入炉内，霎时间，那" + ob->query("name") +
		       HIC "已被火炉中的熊熊烈焰吞没。\n" +
		       "干将凝视着炉火，喃喃说道：天地之精华为其血脉，日月之光辉是其灵气......\n\n" NOR , this_object());
	remove_call_out("work_step_1");
	call_out("work_step_1", 5, me, ob);
	return 1;
}

int work_step_1(object me, object ob)
{
	message_vision(HIG "炉火渐渐的转成了绿色，火苗不断跳跃，你觉得屋内十分燥热，可是干将莫邪若无其事。\n\n" NOR, this_object());
	if (objectp(present(me, environment())))
	{
		me->set_temp("item/help", 1);
		message_vision(HIW "干将对$N说道：如果你想炼得更好，需要注入自己的精气血脉，如是你有此意，请助(help!)我一臂之力！\n\n", me);
	}
	remove_call_out("work_step_2");
	call_out("work_step_2", 8, me, ob);
	return 1;
}

int work_step_2(object me, object ob)
{
	message_vision(HIR "炉火淡淡的暗了下来，呈现出一片红色......\n\n" NOR, this_object());
	remove_call_out("work_step_3");
	me->delete_temp("item/help");
	call_out("work_step_3", 3, me, ob);
	return 1;
}

int work_step_3(object me, object ob)
{
	message_vision(HIW "干将左手持蛟龙剪，一扬手已经取出了" + ob->query("name") +
		       HIW "，右手持金刚锤聚精会神地用力锤打，\n渐渐的，" + ob->query("name") +
		       HIW "在干将手下的成了" + ob->query("ctype") +
		       HIW "的形状。\n\n" NOR, this_object());
	remove_call_out("work_step_4");
	call_out("work_step_4", 5, me, ob);
	return 1;
}

int work_step_4(object me, object ob)
{
	message_vision(HIC "干将锤打完毕，大喝一声，将" + ob->query("ctype") +
		       HIC "抛入水池，只听丝丝作响，从水池腾起一股雾气，弥漫四周。\n\n" NOR, this_object());
	remove_call_out("work_step_5");
	call_out("work_step_5", 3, me, ob);
	return 1;
}

int work_step_5(object me, object ob)
{
	message_vision(HIW "干将缓缓的从水池抽出了炼好的" + ob->query("ctype") +
		       HIW "看了看，满意地说，很好，很好。\n\n" NOR, this_object());
	remove_call_out("work_step_6");
	call_out("work_step_6", 2, me, ob);
}

int work_step_6(object me, object ob)
{
	object moye;
	int improve;
	if (!objectp(moye = present("moye", environment())))
	{
		message_vision(HIW "干将看了看四周，说道：咦，莫邪呢？算了算了，不做了，去吧！\n"
			       "干将把炼好的道具抛进火炉，就此不见。\n\n" NOR, this_object());
		if (objectp(me)) me->delete_temp("item");
		if (objectp(ob)) destruct(ob);
		this_object()->delete_temp("item");
		return 1;
	}
	if (!objectp(me) || !objectp(present(me, environment())))
	{
		message_vision(HIW "干将叹了口气，说道：客人为何这就去了！？罢了罢了，不做了，去吧！\n"
			       "干将把炼好的道具抛进火炉，就此不见。\n\n" NOR , this_object());
		if (objectp(me)) me->delete_temp("item");
		if (objectp(ob)) destruct(ob);
		this_object()->delete_temp("item");
		moye->delete_temp("item");
		return 1;
	}
	moye->set_temp("item/正在等候", 1);
	moye->delete_temp("item/正在炼制");
	me->set_temp("item/输入信息", 1);
	me->delete_temp("item/准备接受");
	message_vision("干将对$N说道：\n"
		       "一" + ob->query("unit") + "好" + ob->query("ctype") + NOR "不能没有名字，你给它起个名字吧！\n", me);
	// 私有信息
	tell_object(me,"名字需要你来定，其它信息系统有缺省的描述，当然也可以你自己为它添一些描述，。\n"
		       "当然了，最好不用让别人误会的词语字句噢。具体的方法如下。\n"
		       "    命名(name):    name 中文名字 英文代号。  (必须有)\n"
		       "    描述(desc):    desc 武器的描述文字。     (可  选)\n"
		       "    装备(loadmsg): loadmsg 装备时的描述。    (可  选)\n"
		       "    收起(backmsg): backmsg 收起时的描述。    (可  选)\n"
		       "描述时分行请用\\n，除了英文代号以外所有的文字都可以用颜色，使用颜色的方法可以参照nick 。\n"
		       "如果你觉得可以了，就请告诉我(finish)，要是没看清楚，可以再问问我 < 规则 >\n\n" NOR);
	// 清除道具的名字，ID，和其它属性，并且设置道具的价值和制造者
	this_object()->set_temp("item/道具名", ob->query("id"));
	ob->set("long", "");
	ob->set("wield_msg", "");
	ob->set("wear_msg", "");
	ob->set("unwield_msg", "");
	ob->set("remove_msg", "");
	ob->set("owner", me->query("name"));
	ob->set("ownerid", me->query("id"));
	// 提升等级
	improve = 0;
	if (me->query_temp("item/cost"))
	{
		improve = me->query_temp("item/cost");
		me->delete_temp("item/cost");
	}
	improve = (improve / 20 + 70);
	improve = improve * ob->query("point") / 100;
	improve = improve / 10 * 10;
	ob->set("point", improve);

	// 设置等待时间，最多3次
	this_object()->set_temp("item/等待", 3);

	// 如果超时，提醒输入
	remove_call_out("waiting");
	call_out("waiting", 240, me, ob, moye);
	return 1;
}

// 以内力哺育炉火，提高道具等级
// 要求：精 >= 180  气 >= 300  内力有效等级 >= 50  内力 >= 800 最大内力 >= 100
// 结果：每耗费 200 点内力，可以提高 10%，初始时为 70%，最大为 120%
int do_help()
{
	object me;
	int    cost;
	me = this_player();
	if (! me->query_temp("item/准备接受"))
	{
		message_vision("干将对$N冷笑一声：关你什么事，少添乱！\n", me);
		return 1;
	}
	if (! me->query_temp("item/help") || me->query_temp("item/help") != 1)
	{
		tell_object(me, "现在不是你帮忙的时候！\n", me);
		return 1;
	}
	if (me->query("jingli") < 180)
	{
		message_vision(HIR "$N长啸一声，双手搭上炉边，正待以内力哺育炉火，突然眼前一黑...\n" NOR, me);
		tell_object(me, "你感到精力衰竭。\n");
        me->set("jingli", 10);
		return 1;
	}
     me->receive_damage("jingli", 180);
	if (me->query("qi") < 300)
	{
		message_vision(HIR "$N长啸一声，双手搭上炉边，正待以内力哺育炉火，突然眼前一黑...\n" NOR, me);
		tell_object(me, "你感到心虚气短。\n");
		me->set("qi", 10);
		return 1;
	}
	me->receive_damage("qi", 300);
	cost = me->query_skill("force");
	if (me->query("neili") < 800 || me->query("max_neili")<100 || cost < 50)
	{
		message_vision(HIR "$N长啸一声，双手搭上炉边，正待以内力哺育炉火，突然眼前一黑...\n" NOR, me);
		tell_object(me, "你感到内力枯竭。\n");
		me->set("neili", 10);
		return 1;
	}
	message_vision(HIC "$N长啸一声，双手搭上炉边，刹那间，炉火沸腾，一道白光，直冲霄汗。\n\n" NOR, me);
	cost = cost * 2 + random(cost * 2);
	if (cost > me->query("max_neili")) cost = me->query("max_neili") - 10;
	if (cost > 1000) cost = 1000;
	if (cost > me->query("neili")) cost = me->query("neili");
	me->set_temp("item/help", 0);
	me->set_temp("item/cost", cost);
	me->add("max_neili", -cost);
	me->add("neili", -cost);
	return 1;
}

int show_order()
{
	object me;
	me = this_object();
	if (! me->query_temp("item/输入信息"))
	{
		message_vision("干将冷冷的坐在那里，理都不理$N。\n", me);
		return 1;
	}
	// 私有信息
	tell_object(me,"名字需要你来定，其它信息系统有缺省的描述，当然也可以你自己为它添一些描述，。\n"
		       "当然了，最好不用让别人误会的词语字句噢。具体的方法如下。\n"
		       "    命名(name):    name 中文名字 英文代号。  (必须有)\n"
		       "    描述(desc):    desc 武器的描述文字。     (可  选)\n"
		       "    装备(loadmsg): loadmsg 装备时的描述。    (可  选)\n"
		       "    收起(backmsg): backmsg 收起时的描述。    (可  选)\n"
		       "描述时分行请用\\n，除了英文代号以外所有的文字都可以用颜色，使用颜色的方法可以参照nick 。\n"
		       "如果你觉得可以了，就请告诉我(finish)，要是没看清楚，可以再问问我 < 规则 >\n\n" NOR);
	return 1;
}

int waiting(object me, object ob, object moye)
{
	if (! objectp(me))
	{
		message_vision("干将叹了口气说道：怎么这走了，算了算了，去吧！\n", this_object());
		if (objectp(moye)) moye->delete_temp("item");
		this_object()->delete_temp("item");
		destruct(ob);
		return 1;
	}
	if (! objectp(present(me, environment())))
	{
		message_vision("干将疑惑地说道：人怎么跑掉了？算了，再等他一会吧。\n", this_object());
	} else
	{
		message_vision("干将催$N道：快点，快点，别磨蹭。\n", me);
	}
	if (this_object()->add_temp("item/等待", -1) <= 0)
	{
		// 等待超时
		if (objectp(moye)) moye->delete_temp("item");
		if (objectp(ob)) destruct(ob);
		me->delete_temp("item");
		this_object()->delete_temp("item");
		if (! objectp(present(me, environment())))
		{
			message_vision("干将皱了皱眉头说道：这人怎么这么磨蹭，算了，不要就不要吧！\n", this_object());
			return 1;
		}
		message_vision("干将皱了皱眉头对$N说道：你这人怎么这么磨蹭，不要就算了，恕不退款！\n", this_object());
		return 1;
	}
	call_out("waiting", 240, me, ob, moye);
}

void clear_data()
{
	object ob;
	object moye;
	if (objectp(moye = present("莫邪", environment())))
	{
		moye->delete_temp("item");
	}
	if (objectp(ob = present(this_object()->query_temp("item/道具名"), this_object())))
	{
		destruct(ob);
	}
	this_player()->delete_temp("item");
	this_object()->delete_temp("item");
	remove_call_out("waiting");
}

object set_item(string arg1, string arg2)
{
	object ob;
	object moye;
	if (! objectp(ob = present(this_object()->query_temp("item/道具名"), this_object())))
	{
		// 数据不对，可能是由于BUG造成，也可能是因为干将被update过
		write("系统故障：数据不一致，你无法继续进行炼制道具......\n");
		clear_data();
		// 返回失败，停止进行
		return 0;
	}
	// 设置信息
	ob->set(arg1, arg2);
	return ob;
}

int do_name(string arg)
{
	object me;
	string sname, sid;

	me = this_player();
	if (! me->query_temp("item/输入信息")) return 0;
	if (! arg || sscanf(arg, "%s %s", sname, sid) != 2)
	{
		write("格式不对！应该是：命名 中文名字 英文ID\n例如：命名 长剑 sword\n");
		return 1;
	}

	// ILLEGAL_STR = "." 表示非法的输入
	if ((sname = converts(sname, 12, COLORABLE)) == ILLEGAL_STR) return 1;
	if (( sid = converts(sid, 6, NOCOLOR)) == ILLEGAL_STR) return 1;
	if (! objectp(set_item("item/name", sname))) return 1;
	if (! objectp(set_item("item/id", sid))) return 1;
	write("名字：" + sname + "    代号：" + sid + "\n");
	return 1;
}

int do_desc(string arg)
{
	object ob;
	object me;

	me = this_player();
	if (! me->query_temp("item/输入信息")) return 0;
	if (! arg)
	{
		write("格式不对！应该是：desc 描述的文字。\n例如：一把锋利的$n\\n它在阳光下闪闪发光 -- 其中\\n表示换行，$n代表道具。\n");
		return 1;
	}
	if ((arg = converts(arg, 100, COLORABLE)) == ILLEGAL_STR) return 1;
	if (! objectp(ob = set_item("long", arg))) return 1;
	arg = replace_string(arg, "$n", ob->query("item/name"));
	ob->set("long", arg);
	arg = replace_string(arg, "\\n", "\n");
	write("当你观察它的时候将会出现下列描述：\n" + arg + "\n");
	return 1;
}

int do_loadmsg(string arg)
{
	object ob;
	object me;

	me = this_player();
	if (! me->query_temp("item/输入信息")) return 0;
	if (! arg)
	{
		write("格式不对！应该是：loadmsg 描述的文字。\n例如：$N伸手一抖，抽出一把锋利长剑。 -- 其中$N表示你自己，$n代表道具。\n");
		return 1;
	}
	if ((arg = converts(arg, 100, COLORABLE)) == ILLEGAL_STR) return 1;
	// 不区分武器还是装备，在生成文件时自动选择一条信息
	if (! objectp(ob = set_item("wield_msg", arg))) return 1;
	if (! objectp(ob = set_item("wear_msg", arg))) return 1;
	arg = replace_string(arg, "\\n", "\n");
	arg = replace_string(arg, "$N", me->query("name"));
	arg = replace_string(arg, "$n", ob->query("item/name"));
	write("当你装备它的时候将会出现下列描述：\n" + arg + "\n");
	return 1;
}

int do_backmsg(string arg)
{
	object ob;
	object me;

	me = this_player();
	if (! me->query_temp("item/输入信息")) return 0;
	if (! arg)
	{
		write("格式不对！应该是：backmsg 描述的文字。\n例如：$N随手一挥，$n已入鞘内。 -- 其中$N表示你自己，$n代表道具。\n");
		return 1;
	}
	if ((arg = converts(arg, 100, COLORABLE)) == ILLEGAL_STR) return 1;
	// 不区分武器还是装备，在生成文件时自动选择一条信息
	if (! objectp(ob = set_item("unwield_msg", arg))) return 1;
	if (! objectp(ob = set_item("remove_msg", arg))) return 1;
	arg = replace_string(arg, "\\n", "\n");
	arg = replace_string(arg, "$N", me->query("name"));
	arg = replace_string(arg, "$n", ob->query("item/name"));
	write("当你收回它的时候将会出现下列描述：\n" + arg + "\n");
	return 1;
}

// 转换字符串中的颜色标志
string converts(string arg, int max_len, int no_color)
{
	// 去除字符串中的空格，引号，避免被别人利用做破坏
	arg = replace_string(arg, " ", ""); 
	arg = replace_string(arg, "\"", "'");

	if (no_color)
	{
		arg = replace_string(arg, "$BLK$", "");
		arg = replace_string(arg, "$RED$", "");
		arg = replace_string(arg, "$GRN$", "");
		arg = replace_string(arg, "$YEL$", "");
		arg = replace_string(arg, "$BLU$", "");
		arg = replace_string(arg, "$MAG$", "");
		arg = replace_string(arg, "$CYN$", "");
		arg = replace_string(arg, "$WHT$", "");
		arg = replace_string(arg, "$HIR$", "");
		arg = replace_string(arg, "$HIG$", "");
		arg = replace_string(arg, "$HIY$", "");
		arg = replace_string(arg, "$HIB$", "");
		arg = replace_string(arg, "$HIM$", "");
		arg = replace_string(arg, "$HIC$", "");
		arg = replace_string(arg, "$HIW$", "");
		arg = replace_string(arg, "$NOR$", "");
	} else
	{
		arg = replace_string(arg, "$BLK$", BLK);
		arg = replace_string(arg, "$RED$", RED);
		arg = replace_string(arg, "$GRN$", GRN);
		arg = replace_string(arg, "$YEL$", YEL);
		arg = replace_string(arg, "$BLU$", BLU);
		arg = replace_string(arg, "$MAG$", MAG);
		arg = replace_string(arg, "$CYN$", CYN);
		arg = replace_string(arg, "$WHT$", WHT);
		arg = replace_string(arg, "$HIR$", HIR);
		arg = replace_string(arg, "$HIG$", HIG);
		arg = replace_string(arg, "$HIY$", HIY);
		arg = replace_string(arg, "$HIB$", HIB);
		arg = replace_string(arg, "$HIM$", HIM);
		arg = replace_string(arg, "$HIC$", HIC);
		arg = replace_string(arg, "$HIW$", HIW);
		arg = replace_string(arg, "$NOR$", NOR);
		arg = arg + NOR;
	}
	if (strlen(arg) > max_len + 12)
	{
		write("对不起，这个字符串太长了，请不要输入超过" + chinese_number(max_len) +
		      "个字符长的字符串。\n");
		// 表示非法的输入
		return ILLEGAL_STR;
	}
	return arg;
}

int do_finish()
{
	object me;
	object ob;
	object moye;
	string msg;

	me = this_player();
	if (! me->query_temp("item/输入信息")) return 0;

	if (! objectp(ob = present(this_object()->query_temp("item/道具名"), this_object())))
	{
		// 数据不对，可能是由于BUG造成，也可能是因为干将被update过
		write("系统故障：数据不一致，你无法完成炼制道具！\n");
		me->delete_temp("item");
		this_object()->delete_temp("item");
		if (objectp(moye = present("莫邪", environment())))
		{
			moye->delete_temp("item");
		}
		// 返回失败，停止进行
		return 0;
	}
	
	if (! ob->query("item/name"))
	{
		message_vision("干将瞪了$N一眼，说道：你怎么能不给他起个名字？你要是不想要了就算了！\n", me);
		return 1;
	}

	// 显示 player 输入的信息
	msg = sprintf("干将对$N说：你的道具描述如下，请看看有没有错。\n");
	message_vision(msg, me);
	// 私有信息
	msg = sprintf("道具名字：%s   道具英文代号：%s\n",
		      ob->query("item/name"), ob->query("item/id"));
	if (ob->query("long") != "")
		msg += sprintf("外观描述如下：\n%s\n", ob->query("long"));
	else
		msg += "采用缺省的外观描述。\n";

	if (ob->query("wield_msg") != "")
		msg += sprintf("装备时描述如下：\n%s\n", ob->query("wield_msg"));
	else
		msg += "装备时采用缺省的描述。\n";

	if (ob->query("unwield_msg") != "")
		msg += sprintf("收回时描述如下：\n%s\n", ob->query("unwield_msg"));
	else
		msg += "收回时采用缺省的描述。\n";
		msg += "如果没有问题，就可以继续进行了(y/n):";
	msg = replace_string(msg, "$N", me->query("name"));
	msg = replace_string(msg, "$n", ob->query("item/name"));

	tell_object(me, msg);

	// 判定 player 是否决定生成道具
	input_to("confirm_make", ob);

	return 1;
}

int confirm_make(string arg, object ob)
{
	object me;
	object moye;
	string item_filename;

	me = this_player();

	if (arg == "y" || arg == "Y")
	{
		message_vision("干将对$N说道：好，马上就好！\n", this_player());
		if ((item_filename = create_file(ob)) != "")
		{
			destruct(ob);
			ob = new(item_filename);
			ob->move(me);
			message_vision("干将把" + ob->query("name") + "交给了$N。\n", me);
		}

		if (objectp(moye = present("moye", environment())))
		{
			moye->delete_temp("item");
		}
		me->delete_temp("item");
		this_object()->delete_temp("item");
		remove_call_out("waiting");
		return 1;
	}
	return 1;
}
