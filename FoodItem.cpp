#include <iostream>
#include <string>
#include "FoodItem.h"
#include "MenuItem.h"
#include <limits>

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
	
	cin.ignore();
	getline(cin, status);
	
	if(status == "Yes" || status == "yes"){
		setAvailable(true);
	}else{
		setAvailable(false);
	}
}