// /clone/board/lpc_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("进度及修改情况记录本", ({ "board" }) );
	set("location", "/d/wizard/lpcroom");
	set("board_id", "lpc_b");
	set("long", "请各位巫师把你做了的工作在这里公布出来。\n"+
		"加强巫师之间工作的一致性！\n" );
	setup();
	set("capacity",100);
	replace_program(BULLETIN_BOARD);
}

