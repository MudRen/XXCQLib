// chahua.c 
#include <ansi.h>      
#include <armor.h>
inherit HEAD;          
string* titles = ({
	HIR"抓破美人脸"NOR,
	HIY"十八学士"NOR,
	HIM"八仙过海"NOR,
	HIW"落第秀才"NOR,
});
void create()
{
	set_name(titles[random(sizeof(titles))], ({ "flower" }));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
                set("unit", "朵");
                set("value", 0);
                set("material", "plant");
                set("long", "这是一朵"+titles[random(sizeof(titles))]+"。\n");
                set("wear_msg", "");
                set("unequip_msg", "$N摘下胸前的$n。\n");
                set("armor_prop/armor", 0);
        }
           
        setup();
}	

int wear()
{
	object me = environment();
	int ret;

	message_vision("$N拿出一朵" + this_object()->query("name") + "，戴在头上。", me);
	if (ret=::wear()) {
		if (me->query("gender") == "男性")
			message_vision("好一个风流少年郎！\n", me);
		else if (me->query("gender") == "女性")
			message_vision("好一个美丽俏佳娃！\n", me);
		else
			message_vision("好一个不三不四的家伙！\n", me);
	}
	return ret;
}