//zoulang1��c              

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������Ȩ�����Ժ�����ȡ����������Ŵ�Ƭ�����֣�������죬��Ӱ
��涣���ʵ������⣬���в��ٱ���ϡ�е������м����У��������ϣ���
������������ 
LONG);
	set("valid_startroom",1);
	set("outdoors","����");
	set("exits", ([
                        "west" : __DIR__"huozoulang",
                        "south" : __DIR__"xiaozoulang1",
	]));
        set("objects",([
          __DIR__"npc/qi" : 1,
      ]));
        replace_program(ROOM);
	setup();
}