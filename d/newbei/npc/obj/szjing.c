// /d/taohua/teibagua.c
// adx 3:55 99-2-6
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(WHT"三字经"NOR, ({ "book" }));
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", WHT"这是一本小孩读的书，你可以读"HIW+
			"（du book）"NOR+WHT"来增加读书写字。\n"NOR);
		set("value", 100);
		set("material", "silk");
		set("skill", ([
			"name":	"literate",
			"exp_required":	0,
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	20
		]) );
	}
}
