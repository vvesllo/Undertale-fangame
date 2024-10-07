#pragma once

#include "Item.h"

class CandyItem : public Item
{
public:
	CandyItem();

	void use(
		TEntityInfo& info
	) override;
};

