// huoji. 药铺伙计

inherit NPC;
#include <ansi.h>

void create()
{
    set_name("李老太太", ({ "laotai", "lao", "taitai", "li"}));
	set("str", 20);
	set("gender", "女性");
	set("age", 65);
	set("long", "一个满脸皱纹的老奶奶，看样子连地都下不了了。\n");
	set("max_qi",300);
	set("eff_qi",300);
	set("qi",300);
	set("combat_exp", 1000);
	set("attitude", "friendly");

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

#include "/d/quanli/npc/die_quest.c"
