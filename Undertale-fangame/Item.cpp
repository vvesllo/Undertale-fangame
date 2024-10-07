#include "Item.h"

Item::Item()
{
	info.title = "base-title";
	info.description = "base-description";
}

void Item::use(TEntityInfo& info)
{
}

TItemInfo Item::getInfo()
{
	return info;
}

std::string Item::getResultText()
{
	return result_text;
}
