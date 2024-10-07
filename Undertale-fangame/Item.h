#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.h"

class Item
{
protected:
	TItemInfo info;
	std::string result_text;

public:
	Item();
	virtual void use(
		TEntityInfo& info
	);
	virtual std::string getResultText();
	TItemInfo getInfo();
};

