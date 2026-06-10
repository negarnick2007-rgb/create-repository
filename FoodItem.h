#ifndef FOODITEM_H
#define FOODITEM_H
#include "MenuItem.h"
#include <string>

using std::string;

class FoodItem : public MenuItem{
	public:
		FoodItem();
		virtual void displayDetails() const override;
		virtual void readItem() override;
};

#endif