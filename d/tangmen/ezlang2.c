//ezlang2.c		�Ĵ����š�����

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
���������Ƹ󶫲�����ȡ�����һ��С�������������ж���ʫ��
�ϱߵ�С��ȴ�ž�������Ҳû��һ���˳��룬��˵�������ŵĽ��أ�
û�����ŵ�����˭Ҳ����˽�Խ��룬����Ʈ�����󷹲���ζ������ʳ
ָ�󶯡�
LONG);
	set("exits", ([
			"north" : __DIR__"eselfroom2",
//			"south" : __DIR__"mishi",
			"west" : __DIR__"ezlang1",
			"east" : __DIR__"ezlang3",
	]));
	set("area", "����");
	setup();
	replace_program(ROOM);
}