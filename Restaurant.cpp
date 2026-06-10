#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"
#include "Restaurant.h"
#include "Address.h"

using namespace std;

Restaurant::Restaurant() : active(false)
{}

Restaurant::~Restaurant()
{
	for(size_t i=0; i<items.size(); i++){
		delete items[i];
		items[i]= nullptr;
	}
}

int Restaurant::getID() const
{
	return id;
}

string Restaurant::getName() const
{
	return name;
}

string Restaurant::getPhoneNumber() const
{
	return phoneNumber;
}

string Restaurant::getDescription() const
{
	return description;
}

void Restaurant::changeAddress(Address& address)
{
	this->address.setCity(address.getCity());
	this->address.setStreet(address.getStreet());
	this->address.setPlaceNumber(address.getPlaceNumber());
}

bool Restaurant::isActive() const
{
	return active;
}

int Restaurant::getManagerID() const
{
	return managerID;
}

int Restaurant::getItemCount() const
{
	return items.size();
}

const Address& Restaurant::getAddress() const
{
	return address;
}

void Restaurant::setManagerID(int id)
{
	managerID= id;
}

void Restaurant::addMenuItem(MenuItem* item)
{
	if(item == nullptr){
		cerr << "Can not add a null item to the menu" << endl << endl;
		return;
	}
	for(size_t i=0; i<items.size(); i++){
		if(items[i]->getID() == item->getID()){
			cerr << "Item ID is repetitive!" << endl;
			delete item;
			return;
		}
	}
	items.push_back(item);
}

void Restaurant::displayMenu() const
{
	cout << "***** Menu*****" << endl << endl;
	for(size_t i=0; i<items.size(); i++){
		if( (items[i]->getKind() == "Food" || items[i]->getKind() == "food") && items[i]->getAvailable()){
			items[i]->displayDetails();
		}
	}
	for(size_t i=0; i<items.size(); i++){
		if( (items[i]->getKind() == "Drink" || items[i]->getKind() == "drink") && items[i]->getAvailable()){
			items[i]->displayDetails();
		}
	}
	cout << "***************" << endl;
}

void Restaurant::printRestaurantInfo() const
{
	cout << "======== Restaurant Information ========" << endl << endl;
	cout << "The name of restaurant: " << name << endl;
	cout << "Restaurant ID: " << id << endl;
	cout << "Phone Number: " << phoneNumber << endl;
	cout << "Description: " << description << endl;
	address.printAddress();
	cout << endl;
	displayMenu();
	cout << "========================================" << endl << endl;
}

MenuItem* Restaurant::getItemById(int itemID) const
{
	for(size_t i=0; i<items.size(); i++){
		if(items[i]->getID() == itemID){
			return items[i];
		}
	}
	return nullptr;
}

void Restaurant::setActive(bool active)
{
	this->active= active;
}

void Restaurant::setID(int id)
{
	this->id= id;
}

void Restaurant::setName(string name)
{
	this->name= name;
}

void Restaurant::setPhoneNumber(string phn)
{
	phoneNumber= phn;
}

void Restaurant::setDescription(string des)
{
	description= des;
}

void Restaurant::removeItem(int itemId)
{
	for(size_t i=0; i<items.size(); i++){
		if(items[i]->getID() == itemId){
			delete items[i];
			items.erase(items.begin()+i);
			return;
		}
	}
}

istream& operator >> (istream& input, Restaurant& r)
{
	input >> r.id;
	input.ignore();
	getline(input, r.name);
	getline(input, r.phoneNumber);
	getline(input, r.description);
	input >> r.address;
	input.ignore();
	input >> r.managerID;
	return input;
	
}