#pragma once

#include "Item.h"

class DirtyMossItem : public Item
{
public:
	DirtyMossItem();

	void use(
		TEntityInfo& info
	) override;
};

