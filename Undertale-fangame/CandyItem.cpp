#include "CandyItem.h"

#include <iostream>

CandyItem::CandyItem()
{
	info.title = "candy";
	info.description = "yummy\nHeals 40HP";
}

void CandyItem::use(TEntityInfo& info)
{
	info.hp += 20;
	result_text = "You eat candy\n";
	if (info.hp > info.max_hp)
	{
		result_text += "HP maxed out";
		info.hp = info.max_hp;
		return;
	}
	result_text += "HP +40";
}
