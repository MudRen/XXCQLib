// Item xiangshi.c
// Created by Zeus 1999.4.3
// Modified by Zeus 1999.6.9
// 
// 

#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void init()
{
        add_action("do_fang", "diu");
}

int do_fang(string);

void create()
{
        set_name("相识蜂雨中", ({"xiangshi"}));

        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("long", "这是一个小小的棉花，一点也看不出这是武林人士闻之色变的温家至宝“相识蜂雨中”。\n");
                set("value", 10000000);
        }
        setup();
}

int do_fang(string arg)
{
        object me, obj;
        int my_exp,obj_exp,beishu;

        me = this_player();

        if( !arg )
                return notify_fail("你想杀谁？\n");

        if( !objectp(obj = present(arg, environment(me)) ) )
                return notify_fail("这里没有这个人。\n");
 
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("看清楚一点，那并不是活物。\n");

        if( obj == me )
                return notify_fail("用suicide 指令会比较快。\n");

        my_exp = me->query("combat_exp");
        obj_exp = obj->query("combat_exp");
        beishu = my_exp / obj_exp;

        if (wizardp(me)) {
                message_vision("$N的经验是"+my_exp+"\n",me);
                message_vision("$N的经验是"+obj_exp+"\n",obj);
                message_vision("$N的经验除以$n的经验是"+beishu+"\n",me,obj);
        }


//      message_vision(HIY "\n    $N说道“我知道，我明白--我们今天才刚刚相识，却早已久闻\n"+
//              "大名，只无缘拜识。江湖风波恶，也风险多，我们这下不打不相识\n"+
//              "，可谓是‘相识风雨中’了......”\n"NOR, me);

//      message_vision(HIY "\n    “可惜知道和明白，也没有用，我们不得不动手--我们岂止相\n"+
//              "识风雨中，还相识在‘蜂雨’中哪！”\n"NOR, me);

        message_vision(HIY "    突然，从$N小小的袖口里，打出一物。\n"+
                "    那物迅速暴胀。\n"+
                "    说也难以置信，原先，那物只像一块棉花。\n"+
                "    小小的，软软的，松松的，灰灰的、自$N的宽衣袖里“漂”\n"+
                "了出来。\n"+
                "    也“飘”了出来。\n"+
                "    但它迅速起变化。迅疾肿大。\n"+
                "    膨胀。\n"+
                "    一下子，已长得像一朵云。\n"+
                "    乌云。\n"+
                "    一朵很大很大得乌云，飞向$n。\n"NOR,me,obj); 

//我的经验是敌人的10倍时，敌人即死。
        if (  my_exp / obj_exp  >= 10 )  
        {
                obj->die();
                tell_object(me, GRN "你觉得眼前的景物不在再有异样，身上的也不再疼痛。\n"+CYN+"你中的「声毒」已经发作完了。\n" NOR );
                tell_object(obj,HIB "你忽然觉得全身皮肤像给蜜蜂刺一样痛，并且突然呼吸困难!\n" NOR );
                destruct(this_object());
                return 1;     
        }

//我的经验是敌人的3到10倍时，敌人中一定的毒。
//        if ( (((int)me->query("combat_exp") / (int)obj->query("combat_exp")) >= 3) &&
//            (((int)me->query("combat_exp") / (int)obj->query("combat_exp")) <= 10) )  
//        {
//                obj->receive_damage("qi", (me->query("max_qi")/30));
//                obj->receive_wound("qi",  (me->query("max_qi")/30));
//                obj->apply_condition("xiangshi_poison", 100 - me->query("con") - me->query_skill("force") +1+ me->query_condition("xiangshi_poison"));
//                message_vision(HIB "$P忽然觉得全身皮肤像给蜜蜂刺一样痛，并且突然呼吸困难!\n" NOR,me,obj);
//                destruct(this_object());
//                return 1;     
//        }

//敌人的经验是我的10到3倍时，敌人化解。
//        if ( (( (int)obj->query("combat_exp") / (int)me->query("combat_exp")) <= 10)&&
//            (((int)obj->query("combat_exp") / (int)me->query("combat_exp")) >= 3) )  
//        {
//                destruct(this_object());
//                return 1;     
//        }

//敌人的经验是我的10以上时，敌人反攻。
//        if ( ( (int)obj->query("combat_exp") / (int)me->query("combat_exp")) >= 10)  
//        {
//                me->die();
//                destruct(this_object());
//                return 1;     
//        }
          destruct(this_object());
          return 1;

}
