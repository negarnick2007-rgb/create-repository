#include <iostream>
#include <string>
#include "MenuItem.h"
#include "DrinkItem.h"

using std::string;
using std::cout;
using std::endl;

DrinkItem::DrinkItem()= default;

void DrinkItem::displayDetails() const
{
	cout << "Kind of item: Drink" << endl;
	cout << "The item ID: " << getID() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Price: " << getPrice() << " dollars" << endl;
	cout << "Volume: " << volume << " ml" << endl;
	cout << "Preparation Time In Minuts: " << getPrepTime() << endl;
	cout << "Description: " << getDescription() << endl << endl;
}

void DrinkItem::setVolume(double volume)
{
	this->volume= volume;
}

double DrinkItem::getVolume() const
{
	return volume;
}

void DrinkItem::readItem()
{
	string name, descrip, status;
	int id, prep;
	double price, volume;
	
	cin >> id;
	setID(id);
	
	cin.ignore();
	getline(cin, name);
	setName(name);
	
	getline(cin, descrip);
	setDescription(descrip);
	
	cin >> price;
	setPrice(price);
	
	cin >> prep;
	setPrepTime(prep);
	
	cin >> volume;
	setVolume(volume);
	
	cin.ignore();
	getline(cin, status);
	
	if(status == "Yes" || status == "yes"){
		setAvailable(true);
	}else{
		setAvailable(false);
	}
}