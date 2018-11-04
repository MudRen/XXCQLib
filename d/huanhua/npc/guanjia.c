// shang.c Τ��

inherit NPC;
//inherit F_DEALER
#include <ansi.h>

int ask_job();
int ask_join();

void create()
{
	set_name("������", ({ "jia xiansheng", "jia" }));
	set("title", "佻��������۹ܼ�");
	set("gender", "����");
	set("long", "����佻����ҵ����۹ܼң����ҵļҶ�Ѿ�߶������ܡ�\n");
	set("age", 35);

	set("int", 30);
	
	set("qi", 500);
	set("max_qi", 500);
	set("jing", 300);
	set("max_jing", 300);
	set("shen_type", 1);

	set("combat_exp", 5000);
	set("attitude", "heroism");

	set_skill("dodge", 20);
	set_skill("parry", 20);
	set_skill("literate", 100);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage", 20);

        set("inquiry", ([
                "job" : (: ask_job :),
        ]) );

	setup();
	add_money("gold", 1);
	carry_object("/clone/misc/cloth")->wear();
}

int ask_job()
{
	object me, ob;
	mapping myfam;
	me = this_player();

	myfam = me->query("family");

	if ( !myfam || myfam["family_name"] != "佻�����" )
	{
		command("say "+RANK_D->query_respect(me)+"������佻��ĵ��ӣ������������ͷ����أ�");
		return 1;
	}
        else if (me->query("combat_exp")<30000)
        {
                command("shake");
                command("say ����������,���ǰ�����ĳ�ʦ,��һЩ����ɡ�");
                return 1;
        }

	else if ((int)me->query("combat_exp")>60000)
	{
		command("shake " + me->query("id"));
		command("say "+RANK_D->query_respect(me)+"�����书��ǿ��������ЩӦ�������������Ļ̫�ðɣ�");
		return 1;
	}

	else if ((me->query_temp("jobcloth")=="1") || (me->query_temp("jobcloth")=="2"))
	{
		command("hmm");
		command("say �й�������Ҫ������һ�������ֵļһ");
		return 1;
	}

	else if (me->query_temp("jobcloth")=="3")
	{
		command("sigh");
		command("say �·����˾����˰�,���ﻹ��һ��,��ȥϴϴ�ɡ�");
		me->set_temp("jobcloth", "1");
		ob = new("/d/huanhua/npc/obj/jobcloth1");
		ob->move(me);
		return 1;
	}

	me->set_temp("jobcloth", "1");
	ob = new("/d/huanhua/npc/obj/jobcloth1");
	ob->move(me);
	command("say ��Ը����������˸ɻ�����̫���ˡ�");
	command("say ������һЩ���·�������ȥϪ��ϴϴ�ɣ�лл�ˡ�");
	return 1;
}

int accept_object(object who, object ob)
{
    object me;
	mapping myfam;
// int i;
	me = this_player();
	myfam = me->query("family");

	if ((string)ob->query("name") == "�ɾ��·�") 
	{
		if ( !myfam || myfam["family_name"] != "佻�����" )
		{
			command("say ���ǵģ���֪������˭���ġ�");
			command("thank "+who->query("id"));
			return 1;
		}
		else if ((string)who->query_temp("jobcloth") != "2")
		{
			command("hmm");
			command("say �㲻Ը��ɾͲ�Ҫ�ɣ��ñ���ϴ�õ��·���������ֺα��أ���");
			return 1;
		}
		else
		{
			command("say ��л����л�������ˣ���ȥ��Ϣ��Ϣ�ɡ�");
			message_vision("�ܼҽ��˽�ϴ�õ��·�������Ժ���\n", who);
			who->add("potential", 30+random(30));
			who->add("combat_exp", 50+random(30));
			who->add("succeed", 1);
			who->delete_temp("jobcloth");
			return 1;
		}
	}
	else if ((string)ob->query("name") == "���·�") 
	{
		if ( !myfam || myfam["family_name"] != "佻�����" )
		{
			command("say ���ǵģ���֪������˭���ġ�");
			command("thank "+who->query("id"));
			return 1;
		}
		else if ((string)who->query_temp("jobcloth") != "3")
		{
			command("say ���ǵģ���֪������˭���ġ�");
			command("thank "+who->query("id"));
			return 1;
		}
		else
		{
			command("say �������������ϴ�·���ϴ���ã�");
			who->delete_temp("jobcloth");
			return 1;
		}
	}
	else
	{
		command("say ����������ʲô?");
		return 0;
	}
	
}