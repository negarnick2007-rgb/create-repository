#include <iostream>
#include <string>
#include "MenuItem.h"
#include "DrinkItem.h"
#include <limits>

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
	
	while(!(cin >> id)){
		cerr << "Please enter numeric ID: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	setID(id);
	
	cin.ignore();
	getline(cin, name);
	setName(name);
	
	getline(cin, descrip);
	setDescription(descrip);
	
	while(!(cin >> price)){
		cerr << "Please enter numeric price: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	setPrice(price);
	
	while(!(cin >> prep)){
		cerr << "Please enter numeric preparation time in minute: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	setPrepTime(prep);
	
	while(!(cin >> volume)){
		cerr << "Please enter numeric volume: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	setVolume(volume);
	
	cin.ignore();
	getline(cin, status);
	
	if(status == "Yes" || status == "yes"){
		setAvailable(true);
	}else{
		setAvailable(false);
	}
}