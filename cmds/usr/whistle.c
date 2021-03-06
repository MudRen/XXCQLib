// 召唤宠物的命令
// By 山猫Adx @ snow 99-12-12

#include <ansi.h>
inherit F_CLEAN_UP;
#define DEATH_PERIOD 1200

int main(object me, string arg)
{
	object pet;
	object *ob;
	int i;
	string id, name, file;

	if(me->is_busy()) return notify_fail("你正忙着呢！哪有空吹口哨！\n");
	
	message_vision (CYN"$N轻轻地吹了声口哨：哔．．．哔．．．\n"NOR, me);

	if(environment(me)->query("nopet")
		||me->query("pet/money")!="ok")
		return 1;

	file = me->query("pet/path");
	ob = children("/adm/npc/pet/pet");

	for(i=0; i<sizeof(ob); i++)
		if(ob[i]->query("possessed") == me)
			pet = ob[i];
	if(!pet && file_size(file) > 0 )
	{
		seteuid(getuid());
		pet = new("/adm/npc/pet/pet");
		pet->set("owner",me->query("id"));
		pet->restore();
		id = pet->query("id");
		name = pet->query("name");
		pet->set("id",id);
		pet->set_name(name,({id}));
		pet->set("possessed",me);
		pet->setup();
	}
	if(pet && environment(pet) != environment(me)
//	&& time() - (int)pet->query("deathstamp") > 1200
	&& !pet->is_fighting())
	{
		pet->move(environment(me));
		pet->reset_action();
		pet->set_leader(me);
		me->set("pet/lead",1);
		pet->add("xing",1);
		message_vision("$N不知从哪里窜了出来，跑到$n面前。\n",pet,me);	
		if(me->is_fighting())
		{
			object *enemy;
			enemy = me->query_enemy();
			i = sizeof(enemy);
		while(i--) {
			if( enemy[i] && living(enemy[i]) ) {
				pet->kill_ob(enemy[i]);
				pet->add("killer",10);
                        if( userp(enemy[i]) )
				enemy[i]->fight_ob(pet);
                        else
				enemy[i]->kill_ob(pet);
				}
			}
		me->remove_all_killer();
		}
	}
	else if (pet) {
		pet->save();
        	message_vision("$N一闪就不见了。\n",pet);
		destruct(pet);
	}
	return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : whistle

召唤你的宠物！
HELP
        );
        return 1;
}
