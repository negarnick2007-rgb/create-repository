#include <iostream>
#include <string>
#include "FoodItem.h"
#include "MenuItem.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

FoodItem::FoodItem()= default;

void FoodItem::displayDetails() const
{
	cout << "Kind of item: Food" << endl;
	cout << "The item ID: " << getID() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Price: " << getPrice() << " dollars" << endl;
	cout << "Preparation Time In Minuts: " << getPrepTime() << endl;
	cout << "Description: " << getDescription() << endl << endl;
}

void FoodItem::readItem()
{
	string name, descrip, status;
	int id, prep;
	double price;
	
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
	
	cin.ignore();
	getline(cin, status);
	
	if(status == "Yes" || status == "yes"){
		setAvailable(true);
	}else{
		setAvailable(false);
	}
}