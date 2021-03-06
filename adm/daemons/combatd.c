// combatd.c
//#pragma optimize all
//Change by Netplay@CctxII (7/99)
//修改do_attack() 取消潜能，改为特殊skill的实战技能提高
//修改skill_power() 将计算公式改为 skill占60% exp占%40

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

//int dpadd;
//由于do_attack里定义不下，只有放这里来了，不知道不同程序对此变量的修改是否会相互影响？
//备注：为了避免出现问题，先用里面的temp作为临时的变量！
inherit F_DBASE;

string *guard_msg = ({
		CYN "$N凝神聚气，紧紧的盯着$n，提防$n出冷招。\n" NOR,
        CYN "$N注视著$n的行动，企图寻找机会出手。\n" NOR,
        CYN "$N正盯著$n的一举一动，随时准备发动攻势。\n" NOR,
        CYN "$N缓缓地移动脚步，想要找出$n的破绽。\n" NOR,
        CYN "$N目不转睛地盯著$n的动作，寻找进攻的最佳时机。\n" NOR,
        CYN "$N慢慢地移动著脚步，伺机出手。\n" NOR,
});

string *catch_hunt_msg = ({
        HIW "$N和$n仇人相见分外眼红，立刻打了起来！\n" NOR,
        HIW "$N对著$n大喝：「可恶，又是你！」\n" NOR,
        HIW "$N和$n一碰面，二话不说就打了起来！\n" NOR,
        HIW "$N一眼瞥见$n，「哼」的一声冲了过来！\n" NOR,
        HIW "$N一见到$n，愣了一愣，大叫：「我宰了你！」\n" NOR,
        HIW "$N喝道：「$n，我们的帐还没算完，看招！」\n" NOR,
        HIW "$N喝道：「$n，看招！」\n" NOR,});

string *winner_msg = ({
        CYN "\n$N哈哈大笑，拱手说道：承让了！\n\n" NOR,
        CYN "\n$N双手一拱，笑著说道：知道我的利害了吧！\n\n" NOR,
        CYN "\n$N胜了这招，笑道：胜败乃兵家常事，不必在意。\n\n" NOR,
        CYN "\n$n向后退了几步，说道：咱们来日方长！\n\n" NOR,
		//CYN "\n$n向后一纵，恨恨地说道：君子报仇，十年不晚！\n\n" NOR,
		CYN "\n$N哈哈大笑，说道：承让了！\n\n" NOR,
        CYN "\n$N双手一拱，笑著说道：承让！\n\n" NOR,
        CYN "\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR,
        CYN "\n$n脸色微变，说道：佩服，佩服！\n\n" NOR,
        CYN "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR,
        CYN "\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
});

void create()
{
        seteuid(getuid());
        set("name", "战斗精灵");
        set("id", "combatd");
}

string damage_msg(int damage, string type)
{
        string str;

        if( damage == 0 ) return "结果没有造成任何伤害。\n";

        switch( type ) {
        case "劈伤":
		if( damage < 10) return "结果只碰到了$p的衣脚。\n";
		else if ( damage < 20) return "结果只是轻轻的碰到$p的皮肉。\n";
		else if ( damage < 40) return "结果「嗤」的一声斩出一到口子。\n";
		else if ( damage < 80) return "结果只听「嚓」的一声，竟斩入$p皮肉两分。\n";
		else if ( damage < 160) return " 结果「嚓」的一声，竟斩到了$p的骨头，鲜血直流。\n";
		else return "结果只听见$n一声惨嚎，$w已在$p$l斩出一道血肉模糊的严重伤口！！\n";
        case "割伤":
                if( damage < 10 ) return "结果只是轻轻地划破$p的皮肉。\n";
                else if( damage < 20 ) return "结果在$p$l划出一道细长的血痕。\n";
                else if( damage < 40 ) return "结果「嗤」地一声划出一道伤口！\n";
                else if( damage < 80 ) return "结果「嗤」地一声划出一道血淋淋的伤口！\n";
                else if( damage < 160 ) return "结果「嗤」地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
                else return "结果只听见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！！\n";
                break;
        case "刺伤":
                if( damage < 10 ) return "结果只是轻轻地刺破$p的皮肉。\n";
                else if( damage < 20 ) return "结果在$p$l刺出一个创口。\n";
                else if( damage < 40 ) return "结果「噗」地一声刺入了$n$l寸许！\n";
                else if( damage < 80 ) return "结果「噗」地一声刺进$n的$l，使$p不由自主地退了几步！\n";
                else if( damage < 160 ) return "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉模糊的血窟窿！\n";
                else return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！！\n";
                break;
        case "瘀伤":
                if( damage < 10 ) return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
                else if( damage < 20 ) return "结果在$p的$l造成一处瘀青。\n";
                else if( damage < 40 ) return "结果一击命中，$n的$l登时肿了一块老高！\n";
                else if( damage < 80 ) return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n";
                else if( damage < 120 ) return "结果「砰」地一声，$n退了两步！\n";
                else if( damage < 160 ) return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n";
                else if( damage < 240 ) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
                else return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！！\n";
                break;
        case "内伤":
                if( damage < 10 ) return "结果只是把$n打得退了半步，毫发无损。\n";
                else if( damage < 20 ) return "结果$n痛哼一声，在$p的$l造成一处瘀伤。\n";
                else if( damage < 40 ) return "结果一击命中，把$n打得痛得弯下腰去！\n";
                else if( damage < 80 ) return "结果$n闷哼了一声，脸上一阵青一阵白，显然受了点内伤！\n";
                else if( damage < 120 ) return "结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n";
                else if( damage < 160 ) return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
                else if( damage < 240 ) return "结果「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n";
                else return "结果只听见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！！\n";
                break;
        default:
                if( !type ) type = "伤害";
                if( damage < 10 ) str =  "结果只是勉强造成一处轻微";
                else if( damage < 20 ) str = "结果造成轻微的";
                else if( damage < 30 ) str = "结果造成一处";
                else if( damage < 50 ) str = "结果造成一处严重";
                else if( damage < 80 ) str = "结果造成颇为严重的";
                else if( damage < 120 ) str = "结果造成相当严重的";
                else if( damage < 170 ) str = "结果造成十分严重的";
                else if( damage < 230 ) str = "结果造成极其严重的";
                else str =  "结果造成非常可怕的严重";
                return str + type + "！\n";
        }
}

string eff_status_msg(int ratio)
{
        if( ratio==100 ) return HIG "看起来气血充盈，并没有受伤。" NOR;
        if( ratio > 95 ) return HIG "似乎受了点轻伤，不过光从外表看不大出来。" NOR;
        if( ratio > 90 ) return HIY "看起来可能受了点轻伤。" NOR;
        if( ratio > 80 ) return HIY "受了几处伤，不过似乎并不碍事。" NOR;
        if( ratio > 60 ) return HIY "受伤不轻，看起来状况并不太好。" NOR;
        if( ratio > 40 ) return HIR "气息粗重，动作开始散乱，看来所受的伤著实不轻。" NOR;
        if( ratio > 30 ) return HIR "已经伤痕累累，正在勉力支撑著不倒下去。" NOR;
        if( ratio > 20 ) return HIR "受了相当重的伤，只怕会有生命危险。" NOR;
        if( ratio > 10 ) return RED "伤重之下已经难以支撑，眼看就要倒在地上。" NOR;
        if( ratio > 5  ) return RED "受伤过重，已经奄奄一息，命在旦夕了。" NOR;
        return RED "受伤过重，已经有如风中残烛，随时都可能断气。" NOR;
}

string status_msg(int ratio)
{
        if( ratio==100 ) return HIG "看起来充满活力，一点也不累。" NOR;
        if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
        if( ratio > 90 ) return HIY "看起来可能有些累了。" NOR;
        if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
        if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
        if( ratio > 40 ) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
        if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑著不倒下去。" NOR;
        if( ratio > 20 ) return HIR "看起来已经力不从心了。" NOR;
        if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
        return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}


varargs void report_status(object ob, int effective)
{
	if( effective ) 
		message_vision( "( $N" + eff_status_msg(
			(int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi") ) 
			+ " )\n", ob);
	else
		message_vision( "( $N" + status_msg(
			(int)ob->query("qi") * 100 / (int)ob->query("max_qi") ) 
			+ " )\n", ob);
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
// 这个函数计算某种绑定的skills的攻击和防御力
varargs int skill_power(object ob, string skill, int usage)
{
	int level, power;

	if( !living(ob) ) return 0;

	level = ob->query_skill(skill);
	

	switch(usage) {
		case SKILL_USAGE_ATTACK:
			level += ob->query_temp("apply/attack");
			break;
		case SKILL_USAGE_DEFENSE:
			level += ob->query_temp("apply/defense");
			if (ob->is_fighting())
				level = level * (100 + ob->query_temp("fight/dodge")) / 100;
			break;
	}

	if( !level ) return (int)ob->query("combat_exp") / 2;

	power = level*level*level/10 * 60/100; //等级所占比重60%

	//exp所占比重40%
	if (usage == SKILL_USAGE_ATTACK)
		return (power + (ob->query("combat_exp")) / 30 * ob->query_str()) * 40/100;
	else
		return (power + (ob->query("combat_exp")) / 30 * ob->query_dex()) * 40/100;
	//return 1; ok?
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
	mapping my, your, prepare, action;
	string limb, *limbs, result;
	string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
	mixed foo;
	int ap, dp, pp;
	int damage, damage_bonus, temp = 0;
	//由于maxvar 的限制temp取代temp和wounded的作用
	//同时也作为dpadd的作用，即斗志对攻防的影响。for snow mud . jackyboy 1999/11/7
	int award_me,award_you;
	award_me=random(me->query_skill("feat"));
	award_me=award_me*30/me->query("int");
	
	award_you=random(victim->query_skill("feat"));
	award_you=award_you*30/victim->query("int");

	if (environment(me)->query("no_fight")||environment(victim)->query("no_fight"))
		return notify_fail("这里禁止战斗的哟！\n");
	my = me->query_entire_dbase();
	your = victim->query_entire_dbase();
	//找出进攻者准备要采用的功夫
	prepare = me->query_skill_prepare();
	
	if (!prepare) prepare = ([]);

	if( objectp(weapon) )	attack_skill = weapon->query("skill_type");
	else if ( sizeof(prepare) == 0)	attack_skill = "unarmed";
	else if ( sizeof(prepare) == 1)	attack_skill = (keys(prepare))[0];
	else if ( sizeof(prepare) == 2)	attack_skill = (keys(prepare))[me->query_temp("action_flag")];

	martial_skill=me->query_skill_mapped(attack_skill);//进攻者所采用的特殊skill

	// (1) Find out what action the offenser will take.
	// 找出进攻者采用什么action
	me->reset_action();
	action = me->query("actions");
	if( !mapp(action) ) {
		me->reset_action();//为什么再次调用？
		action = me->query("actions");//为了避免错误设置actions为action???
		if( !mapp(action) ) {//查找不到可以采用的action则用sys频道显示出来
			CHANNEL_D->do_channel( this_object(), "sys",
				sprintf("COMBAT_D(do_attack) >> %s(%s): bad action = %O",
					me->name(1), me->query("id"), me->query("actions", 1)));
			return 0;
		}
	}

	if (me->query_temp("action_flag") == 0)//此标志为1表示刚刚做了一个action攻击？
		result = "\n" + action["action"] + "！\n";
	else
		result = "\n" + "紧跟着"+action["action"] + "！\n"; 

	//
	// (2) Prepare AP, DP for checking if hit.
	// 
	limbs = victim->query("limbs");
	//查询被攻击者可被攻击哪些部位，在chard.c里有定义，也可以在程序里重新定义
	limb = limbs[random(sizeof(limbs))];//选定一个部位攻击
	//斗志对dp的影响 for snow mud
	temp = my["douzhi"] - 100;
	if (temp < 0) temp = - temp;
	
	ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);//计算攻击力到ap里
	
	if( ap < 1) ap = 1;
	if (userp(me) && intp(action["dodge"]))
		me->set_temp("fight/dodge", action["dodge"]);

	dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);//计算对方的防御力到dp
	//斗志对躲避的影响
	dp = dp * my["eff_douzhi"] / (temp + my["eff_douzhi"]);
	if( dp < 1 ) dp = 1;
	if( victim->is_busy() ) dp /= 3;//如果被攻击者忙，降低三倍防御力

	//
	// (3) Fight!
	//     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
	//     AP and DP are greater than zero, so we always have chance to hit
	//     or be hit.
	//
	if( random(ap + dp) < dp ) { 		// Does the victim dodge this hit?
		//如果ap不高，就很可能执行这段程序，表示攻击失误，被攻击者躲开了
		dodge_skill = victim->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		result += SKILL_D(dodge_skill)->query_dodge_msg(limb);

		if( dp < ap && (!userp(victim) || !userp(me)) 
		&&	random(your["jingli"]*100/your["max_jingli"] + your["int"]) > 50 ) {
			//符合此条件的时候被攻击者轻功熟练程度加一
			your["combat_exp"] += 1;
			victim->improve_skill("dodge", random(your["int"]));
			//如果激发了特殊轻功，该技能提高
			if(dodge_skill != "dodge")
			victim->active_skill(dodge_skill, award_you);
		}

		// This is for NPC only. NPC have chance to get exp when fail to hit.
		if( (ap < dp) && !userp(me) ) {
			//如果攻击者是npc，则此时npc的战斗经验加一，并提高所使用的技能
			if( random(my["int"]) > 15 ) my["combat_exp"] += 1;
			me->improve_skill(attack_skill, random(my["int"]));
			if(martial_skill)
			me->active_skill(martial_skill, award_me);
		
		}
		damage = RESULT_DODGE;
	}
	else //如果不能躲开的话,看是否能招架
	{
		//	(4) Check if the victim can parry this attack.
		//被击中，检查被攻击者是否能够招架此次攻击
		if( victim->query_temp("weapon") ) 
		{
			//如果被攻击者持有兵器
			pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
			if( !weapon ) pp *= 2;//如果攻击者没有持兵器，招架能力增加两倍
		}
		else
		{
			pp=( weapon )? 0 : skill_power(victim, "unarmed", SKILL_USAGE_DEFENSE);
		}
		//斗志对招架的影响
		pp = pp * my["eff_douzhi"] / (temp + my["eff_douzhi"]);
		if( victim->is_busy() ) pp /= 3;//如果被攻击者忙，招架能力削弱3倍
		if( pp < 1 ) pp = 1;

		if( random(ap + pp)< pp ) 
		{
			//如果攻击力差则很可能执行这段程序，即很可能被招架住
			parry_skill = victim->query_skill_mapped("parry");
			if( !parry_skill ) parry_skill = "parry";
			// change to SKILL_D(parry_skill) after added parry msg to those
			// martial arts that can parry.
			result += SKILL_D(parry_skill)->query_parry_msg(weapon);
			//这里是不是应该是parry_skill呢？
			
			if( dp < ap && (!userp(victim) || !userp(me)) 
			&&	random(your["jingli"]*100/your["max_jingli"] + your["int"]) > 50 )
			{
				//如果有一个不是玩家，则被攻击者经验加一，parry提高一点
				your["combat_exp"] += 1;
				victim->improve_skill( "parry", random(your["int"]) );
				if(parry_skill != "parry")
				victim->active_skill(parry_skill, award_you);
		
			}
			damage = RESULT_PARRY;

		} else {

			//
			//	(5) We hit the victim and the victim failed to parry
			//如果被攻击者无法招架就中招了
			damage = me->query_temp("apply/damage");
			damage = (damage + random(damage)) / 2;
			if( action["damage"] )
				damage += action["damage"] * damage / 100;

			damage_bonus = me->query_str();//臂力越大，攻击力越强

			// Let force skill take effect.
			if( my["jiali"] && (my["neili"] > my["jiali"]) ) {
				if( force_skill = me->query_skill_mapped("force") ) 
				{
					//用上了内力的攻击，是不是每个force文件都要有hit_ob函数？不一定！！！
					foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["jiali"]);
					if( stringp(foo) ) result += foo;
					else if( intp(foo) ) damage_bonus += foo;
				}
			}

			if( action["force"] )
				damage_bonus += action["force"] * damage_bonus / 100;

			if( martial_skill ) 
			{
				//调用攻击使用功夫的hit_ob函数，得到字符返回结果或整型的损伤程度
				foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}

			// Let weapon or monster have their special damage.
			if( weapon ) 
			{
				//允许武器有它的特殊攻击信息或攻击力
				foo = weapon->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}
			else 
			{
				//这个可能只有在me是npc的时候才有用！
				foo = me->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}

			if( damage_bonus > 0 )
				damage += (damage_bonus + random(damage_bonus))/2;
			if( damage < 0 ) damage = 0;

			// Let combat exp take effect
			// 如果被攻击者的经验比攻击者高很多，那么伤害减为三分之一
			temp = your["combat_exp"];
			while( random(temp) > my["combat_exp"] ) {
				damage -= damage / 3;
				temp /= 2;
			}
			temp = 0; 	
			//
			//	(6) Inflict the damage.
			//使被攻击者受伤
			
			//斗志对攻击力的影响
			damage = (int)( ( damage * my["douzhi"]) / my["eff_douzhi"] );	
			//斗志的加减
			if (( (damage *100 / your["max_qi"]) >= 1 )
				&& ( (damage *100 / your["max_qi"]) < ((60 - your["bac"]) / 10 )))
				victim->add("douzhi", -1);
			else if (( (damage *100 / your["max_qi"]) >= ((60 - your["bac"]) / 10 ))
				&& ( (damage *100 / your["max_qi"]) < your["bac"] / 2 ))
				victim->add("douzhi", 2);
			else if (( (damage *100 / your["max_qi"]) >= your["bac"] / 2 )
				&& ((damage *100 / your["max_qi"]) < your["bac"] ))
				victim->add("douzhi", -5);
			else if ((damage *100 / your["max_qi"]) >= your["bac"] )
				victim->add("douzhi", -20);
			if (your["douzhi"] < 0) your["douzhi"] = 0;
			if (your["douzhi"] >your["max_douzhi"]) your["douzhi"] = your["max_douzhi"];
			if ( wizardp(me))
				tell_object(me, YEL"\n" + victim->query("name") + "的斗志："+your["douzhi"]+"   你攻击的威力："+damage+"   " + victim->query("name") + "的毅力："+your["bac"]+NOR);
			if ( wizardp(victim))
				tell_object(victim, "\n你的斗志："+your["douzhi"]+"   " + me->query("name") + "攻击的威力："+damage + "   你的毅力："+your["bac"]);

			damage = victim->receive_damage("qi", damage, me );
			if( random(damage) > (int)victim->query_temp("apply/armor")
			&& ( (me->is_killing(victim->query("id"))) 
				&& ((!weapon) && !random(4) || weapon && !random(2) )
			    || ( (!weapon) && !random(7) || weapon && !random(4) ) )  )
			{
				// We are sure that damage is greater than victim's armor here.
				//受伤程度应该比攻击者的apply/armor多
				victim->receive_wound("qi",
					damage - (int)victim->query_temp("apply/armor"), me);
				temp = 1;
			}

			result += damage_msg(damage, action["damage_type"]);
			//计算受伤程度，并得到受伤显示的信息
			//
			//	(7) Give experience
			//经验的奖励部分
			if( !userp(me) || !userp(victim) ) //玩家打玩家没有奖励
			{
				//对于特殊的skill来说，只要击中了对方，就有可能获得提高
				if(martial_skill && random(my["int"]) > 15
					&& your["combat_exp"] > my["combat_exp"]*2/3)
				me->active_skill(martial_skill, award_me);
				
				if( (ap < dp)
				&&	(random(my["jingli"]*100/my["max_jingli"] + my["int"]) > 30) ) {
					my["combat_exp"] += 1;
					me->improve_skill(attack_skill, award_me);
				}
				if( random(your["max_qi"] + your["qi"]) < damage ) {
					your["combat_exp"] += 1;
				}
			}
		}
	} 
	//后面几句取代一些信息中的代号
	result = replace_string( result, "$l", limb );
	if( objectp(weapon) )
		result = replace_string( result, "$w", weapon->name() );
	else if( stringp(action["weapon"]) )
		result = replace_string( result, "$w", action["weapon"] );
	else if( attack_skill == "finger" ) 
		result = replace_string( result, "$w", "手指" );

	message_vision(result, me, victim );

	if( wizardp(me) && (string)me->query("env/combat") )
	{
		//通知巫师此次攻击的伤害程度
		if( damage > 0 )
			CHANNEL_D->do_channel( this_object(), "debug", sprintf("AP：%d，DP：%d，PP：%d，伤害力：%d\n" ,
				ap/100, dp/100, pp/100, damage));
		else
			CHANNEL_D->do_channel( this_object(), "debug", sprintf("AP：%d，DP：%d，PP：%d\n" ,
				ap/100, dp/100, pp/100));
	}

	if( damage > 0 ) 
	{
		report_status(victim, temp);//显示被攻击者的状态
		if( victim->is_busy() ) victim->interrupt_me(me);
		if( (!me->is_killing(your["id"])) && 
		(!victim->is_killing(my["id"])) &&
		victim->query("qi")*2 <= victim->query("max_qi")) 
		{
			//不是kill的时候的处理
			me->remove_enemy(victim);
			victim->remove_enemy(me);
			if(me->query_temp("biwu"))
				me->fight_winner(victim);
			message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);
		}
	}

	if( functionp(action["post_action"]) )
		evaluate( action["post_action"], me, victim, weapon, damage);

	// See if the victim can make a riposte.
	//判断被攻击者是否能反攻
	if( attack_type==TYPE_REGULAR
	&&	damage < 1
	&&	victim->query_temp("guarding") )
	{
		victim->set_temp("guarding", 0);
		if( random(my["dex"]) < 5 )
		{
			message_vision("$N一击不中，露出了破绽！\n", me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
		} else {
			message_vision("$N见$n攻击失误，趁机发动攻击！\n", victim, me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
		}
	}
}

//	fight()
//
//	This is called in the attack() defined in F_ATTACK, which handles fighting
//	in the heart_beat() of all livings. Be sure to optimize it carefully.
//  这个函数调用了一些定义在F_ATTACK(通常是/feature/attack.c)里的一些函数比如fight_ob
void fight(object me, object victim)
{
	
	if( !living(me) ) return;
	//如果me不是生物，不进行fight调用！
	
	// If victim is busy or unconcious, always take the chance to make an attack.
	//如果被fight的对象忙或昏迷，那么总是能发出攻击
	if( victim->is_busy() || !living(victim) ) {
		me->set_temp("guarding", 0);
		if( !victim->is_fighting(me) ) victim->fight_ob(me);
		do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);

		if( me->is_fighting(victim) && victim->is_fighting(me)) 
			if( (!objectp(me->query_temp("weapon")) && sizeof(me->query_skill_prepare()) > 1))
			{
			   me->set_temp("action_flag",1);
			   do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
			   me->set_temp("action_flag",0);
		    }
	// Else, see if we are brave enough to make an aggressive action.
	} 
	else 
	if( random( (int)victim->query_dex() * 3 ) > (int)me->query_str()) 
	{//如果不昏迷且身法*3大于有效臂力则执行下面的程序
		me->set_temp("guarding", 0);
		if( !victim->is_fighting(me) ) victim->fight_ob(me);  
		do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
		if( me->is_fighting(victim) && victim->is_fighting(me)) 
			if( (!objectp(me->query_temp("weapon")) && sizeof(me->query_skill_prepare()) > 1))
			{
			   me->set_temp("action_flag",1);
			   do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
			   me->set_temp("action_flag",0);
			}
	// Else, we just start guarding.
	} else 
	if( !me->query_temp("guarding") ) 
	{
		//开始防守
		me->set_temp("guarding", 1);
		message_vision( guard_msg[random(sizeof(guard_msg))], me, victim);
		return;
	} 
	else 
		return;
}

//	auto_fight()
//
//	This function is to start an automatically fight. Currently this is
//	used in "aggressive", "vendetta", "hatred", "berserk" fight.
//这个函数用于自动进入fight状态！
void auto_fight(object me, object obj, string type)
{
	// Don't let NPC autofight NPC.
	//这句是避免npc自动同npc战斗的！
	if( !userp(me) && !userp(obj) ) return;

	// Because most of the cases that we cannot start a fight cannot be checked
	// before we really call the kill_ob(), so we just make sure we have no 
	// aggressive callout wating here.
	
	if( me->query_temp("looking_for_trouble") ) return;
	me->set_temp("looking_for_trouble", 1);

	// This call_out gives victim a chance to slip trough the fierce guys.
	call_out( "start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
	int shen;

	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	shen = 0 - (int)me->query("shen");
	message_vision("$N用一种异样的眼神扫视著在场的每一个人。\n", me);

	if( !userp(me) || (int)me->query("neili") > (random(shen) + shen)/10 ) return;
	//如果是npc或者内力大于shen的一个随机变化范围除于10，也就是说shen相比较内力而言太底了
	//不能压制住杀气！
	if( shen > (int)me->query("score") //score又是一个什么东西呢？
	&&	!wizardp(obj) ) {
		message_vision("$N对著$n喝道：" + RANK_D->query_self_rude(me)
			+ "看你实在很不顺眼，去死吧。\n", me, obj);
		me->kill_ob(obj);
	} else {
		message_vision("$N对著$n喝道：喂！" + RANK_D->query_rude(obj)
			+ "，" + RANK_D->query_self_rude(me) + "正想找人打架，陪我玩两手吧！\n",
			me, obj);
		me->fight_ob(obj);
	}
}

void start_hatred(object me, object obj)
{
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We found our hatred! Charge!
	message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
	me->kill_ob(obj);
}

void start_vendetta(object me, object obj)
{
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We found our vendetta opponent! Charge!
	me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We got a nice victim! Kill him/her/it!!!
	me->kill_ob(obj);
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
	switch(event) {
		case "dead":
			message_vision("\n$N死了。\n\n", ob);
			break;
		case "unconcious":
			message_vision("\n$N脚下一个不稳，跌在地上一动也不动了。\n\n", ob);
			break;
		case "revive":
			message_vision("\n$N慢慢睁开眼睛，清醒了过来。\n\n", ob);
			break;
	}
}

void winner_reward(object killer, object victim)
{
	killer->defeated_enemy(victim);//没有发现这个函数的定义！
}

void killer_reward(mixed killer, object victim)
{
	int bls;
	string vmark,diemessage="";

	//netplay add
	if(stringp(killer)) diemessage=killer;
	if(objectp(killer)) 

	// Call the mudlib killer apply.
	//???这个函数不会是系统定义的吧？也找不到呀！
	killer->killed_enemy(victim);
	
	if( userp(victim) ) {
		if(objectp(killer)) 
		killer->add("PKS", 1);
		//victim->clear_condition(); 为了实现就地处决，移动到后面了！请参看注释！
		// Give the death penalty to the dying user.
		victim->add("shen", -(int)victim->query("shen") / 10);
		victim->add("combat_exp", -(int)victim->query("combat_exp") / 50);
		victim->delete("vendetta");
		if( victim->query("thief") )
			victim->set("thief", (int)victim->query("thief") / 2);
		if( (int)victim->query("potential") > (int)victim->query("learned_points"))
			victim->add("potential",
				((int)victim->query("learned_points") - (int)victim->query("potential"))/2 );
		victim->skill_death_penalty();
		// Add by jungu             
		if (objectp(killer))  if (userp(killer))
		write_file("/log/static/KILL_PLAYER",sprintf("%s(%s) killed by %s(%s) on %s\n",
		victim->name(1), victim->query("id"),
		killer->name(1),killer->query("id"),ctime(time()) ));
		
		// Look for PKS 
		bls = 10;
		
		if (objectp(killer))
		{
			if ( interactive(killer))
			{ 
				if(victim->query_condition("killer"))
				{
					CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s被%s就地处决了。", victim->name(1), killer->name(1)));
				}
				else
				{
					CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s被%s杀害了。", victim->name(1), killer->name(1)));
					CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s被官府通缉了。", killer->name(1)));
				}
			}
			else {
				if(victim->query_condition("killer"))
					CHANNEL_D->do_channel(this_object(),"rumor",
					sprintf("%s被%s就地处决了！",victim->name(1),killer->name(1)));
				else
					CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s被%s杀死了。", victim->name(1), killer->name(1)));
			}
			if(!victim->query_condition("killer"))
				killer->apply_condition("killer", 500);
		}else 
		if (stringp(killer)){
			CHANNEL_D->do_channel(this_object(), "rumor",
				sprintf("%s%s。", victim->name(1), diemessage));
			return;
		}
		victim->clear_condition();//在实现了处决的判断后清除被杀者的状态！
	} else {
		if (objectp(killer))
		{
		killer->add("MKS", 1);
		bls = 1;		}
	}

	if (objectp(killer) && userp(killer) && killer->query("combat_exp") < victim->query("combat_exp")) 
		killer->add("shen", -(int)victim->query("shen") / 10);
	//vendetta -> 深仇大恨
	if( stringp(vmark = victim->query("vendetta_mark")) )
		killer->add("vendetta/" + vmark, 1);
}
