// Room: /city/chouduanhang.c
// YZC 1998/12/04 

inherit ROOM;

void create()
{
        set("short", "龙吟堂");
        set("long", @LONG
这是一间宽敞的大堂，堂内布置得颇为肃穆，除“龙吟堂”的匾额是
红匾以外，大部分的装饰均以黑白为主。堂内两侧站有两列弟子，人人一
身白衣短打，显得很是干练。一个与众不同的黑衣年轻人站在堂的中央，
不停的踱来踱去。西面是龙组成员的休息室。
LONG
        );

        set("valid_startroom", 1);
        set("exits", ([
                "south" : __DIR__"northyuan",
        ]));

        set("objects", ([
                "/kungfu/class/huanhua/zhang" : 1,
        ]));

        setup();
        replace_program(ROOM);
}

