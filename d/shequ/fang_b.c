// common_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("《碧雪社区》购房板", ({ "board" }) );
        set("location", "/d/shequ/jiaowai1");
        set("board_id", "fang_b");
        set("long",     "这是一个供人留言记事的留言板。\n" );
        setup();
 set("capacity", 90)
;
        replace_program(BULLETIN_BOARD);
}
