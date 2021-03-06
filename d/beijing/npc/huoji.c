// huoji. 药铺伙计

inherit F_DEALER;

void create()
{
	set_name("回春堂伙计", ({ "yaopu huoji", "huoji" }));
	set("str", 20);
	set("gender", "男性");
	set("age", 18);
	set("long", "他是上太师的学徒，平时就在店里当伙计。\n");
	set("combat_exp", 250);
	set("attitude", "friendly");
	set("vendor_goods", ({
		__DIR__"obj/jinchuang",
	}));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
