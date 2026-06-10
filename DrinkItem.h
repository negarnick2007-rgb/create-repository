#ifndef DRINKITEM_H
#define DRINKITEM_H
#include <string>
#include "MenuItem.h"

using std::string;

class DrinkItem : public MenuItem{
	private:
		double volume;
	public:
		DrinkItem();
		virtual void displayDetails() const override;
		virtual void readItem() override;
		
		void setVolume(double volume);
		double getVolume() const;
};

#endif