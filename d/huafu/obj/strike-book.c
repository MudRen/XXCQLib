// sword_book.c

inherit ITEM;

void create()
{
    set_name("基本掌法--（提高篇)", ({ "strike book", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
"封面上写著「基本掌法 -- 卷二（提高）」\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
            "name":     "strike",   // name of the skill
			"exp_required":	10000,		// minimum combat experience required
							// to learn this skill.
			"jingli_cost":	20,		// jing cost every time study this
			"difficulty":	22,		// the base int to learn this skill
							// modify is jing_cost's (difficulty - int)*5%
            "min_skill":    30,
			"max_skill":	100		
		]) );
	}
}
