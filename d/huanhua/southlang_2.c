// Room: /city/chouduanhang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
������Ⱥͱ�����ȶ��Ǵӽ���֮�������ڴ�û���ɹ��ģ��ȶ����
����֮���Ĺ���Ҳ�Ѿ��߲��ˣ�����������������˺�����Ƥ��ͼѻ����
�����������棬�Ѿ����Կ����仨���ĺ����ˡ�
LONG
	);

	set("valid_startroom", 1);

	set("exits", ([
		"east" : __DIR__"southlang",
		"west" : __DIR__"hupan_s",
	]));

        set("objects", ([
	]));

	setup();
	replace_program(ROOM);
}