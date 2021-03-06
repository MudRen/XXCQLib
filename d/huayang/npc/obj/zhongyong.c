// laozi16.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name( WHT"中庸"NOR, ({ "book", "shu" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long","子程子曰，「不偏之谓中；不易之谓庸。」中者，天下之正道。庸者，天下之定理
。此篇乃孔门传授心法，子思恐其久而差也，故笔之於书，以授孟子。其书始言一
理；中散为万事；末复合为一理。放之，则弥六合；卷之，则退藏於密。其味无穷
。皆实学也。善读者，玩索而有得焉，则终身用之，有不能尽者矣。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"confu",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jingli_cost":  15, 	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	50,	// the maximum level you can learn
		]) );
	}
}