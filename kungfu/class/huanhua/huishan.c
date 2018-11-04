// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void heal_ob();
void recover_ob();
int ask_jian();

void create()
{
        set_name("���ɺ", ({"sun huishan", "sun", "huishan"}));
        set("gender", "Ů��");
        set("title", "佻�����"HIM"���ŷ���"NOR);
        set("age", 54);
        set("long", 
"���ǡ�ʮ�ֻ۽���������������ͥ�Ķ���Ů����Ҳ��佻������������ŷ��ˡ�\n"
"����������Ʒ����һ����佻����ɽ������������������һ�ݹ��͡�\n");
        set("attitude", "peaceful");
        set("str", 15);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("bac", 25);

        set("qi", 2900);
        set("max_qi", 2900);
        set("jingli", 2100);
        set("max_jingli", 2100);
        set("neili", 2400);
        set("max_neili", 2400);
        set("jiali", 25);
        
        set("combat_exp", 1200000);
        set("shen", 10000);
        
        set_skill("force", 170);
        set_skill("jiuqu-xinfa", 170); 
        set_skill("strike", 180);
        set_skill("dodge", 180); 
        set_skill("huanhua-shenfa", 180); 
        set_skill("sword", 210); 
        set_skill("parry", 180); 
        set_skill("literate", 150); 
        set_skill("confu", 150); 
        
        map_skill("force", "jiuqu-xinfa");
        map_skill("dodge", "huanhua-shenfa");

        create_family("ʮ�ֽ���", 3, "����");
        set("inquiry", ([
                "����¥" : "�����ҵķ��!",
                "佻����" : (:ask_jian:),
        ]) );

        setup();

        carry_object("/d/huanhua/npc/obj/changqun")->wear();
        carry_object("/clone/weapon/changjian");

        set("chat_chance", 3);
        set("chat_msg", ({
                (: heal_ob :),
                "�����˵��ĵ������ţ���ˮ����Һþ��ˣ���ôҲû�и����أ�\n",
                "�����˲�����շת�����Ϸ��˲�Ҫ���²źã�����Ȩ����Ĺ���Խ��Խ������ô����أ���\n",
        }));

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: recover_ob :)
        }) );
}

void heal_ob()
{
        command("yun heal");
        command("yun heal");
        command("yun heal");
        command("yun recover");
        command("unwield jian");
        return;
}

void recover_ob()
{
        command("yun recover");
        command("wield jian");
        return;
}

void attempt_apprentice(object ob)
{
        command("say �ҵ��书����̫���ˣ������ˣ�����̸��ͽ�أ�");
        command("blush");
        return;
}
int ask_jian()
{
      object ob;
      object me = this_player();
      mapping fam;
      fam = me->query("family");
      if ( fam["family_name"] != "佻�����")
      return 0;
      if(me->query("combat_exp")< 100000) {
      command("say ��ľ��黹����,��佻����Ҳû��ʲô����!\n");
      return 1;
    }
      if(present("shen jian",me))
      {  
        command("say �㲻���Ѿ�������?\n");
          return 1;
      }
      ob = new("/d/huanhua/npc/obj/shenjian");
      ob->move(me);
      command("ok");
      command("say �м�: ����ʱ����ʹ��!\n");
      return 1;
}
