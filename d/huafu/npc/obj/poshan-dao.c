

#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIC"破山刀"NOR, ({ "poshan dao", "dao" }));
          set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                 set("long", "这是一把破旧不堪的钢刀，刀锋还有缺口。\n");
            set("value", 10000);
                set("no_break",1);
                set("material", "steel");
                set("wield_msg", YEL "$N从背后抽出一把很不起眼的刀。\n" NOR);
                set("unwield_msg", YEL "$N小心翼翼的把这把破刀檫拭干净，背在背后。\n" NOR);
        }
         init_blade(70);
        setup();
}

