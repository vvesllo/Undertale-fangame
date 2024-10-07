#include "DirtyMossItem.h"

DirtyMossItem::DirtyMossItem()
{
	info.title = "Dirty Moss";
	info.description = 
		"Impeccable.\n"
		"Perfect.\n"
		"Beautiful.\n"
		"Incredible.\n"
		"Heals 999HP";
}

void DirtyMossItem::use(TEntityInfo& info)
{
	info.hp += 999;
	result_text = "You eat MOSS\n"
				  "Perfect.\n";
	if (info.hp > info.max_hp)
	{
		result_text += "HP maxed out";
		info.hp = info.max_hp;
		return;
	}
	result_text += "HP +999";
}
