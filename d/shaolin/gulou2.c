// Room: /d/shaolin/gulou2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "��¥����");
	set("long", @LONG
ÿ��¥���϶������˽�ʵ��ľ¥�壬�˽��ε�ǽ�����������ȴ�
���Ӵ��׿���ǽ��Ҳ�Ǽ�Ϊ��ʵ���������������������Կ���Χ�����ܵ�
С԰�Լ����ߵ����֣����Ʈ��������Ҷ�����㡣
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"up" : __DIR__"gulou3",
		"down" : __DIR__"gulou1",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
