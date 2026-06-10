#include <iostream>
#include <string>
#include "MenuItem.h"

using namespace std;

MenuItem::MenuItem()= default;
	
MenuItem::~MenuItem()= default;

string MenuItem::getKind() const
{
	return kind;
}

int MenuItem::getID() const
{
	return id;
}

string MenuItem::getName() const
{
	return name;
}

string MenuItem::getDescription() const
{
	return description;
}

double MenuItem::getPrice() const
{
	return price;
}

int MenuItem::getPrepTime() const
{
	return preparationTime;
}

bool MenuItem::getAvailable() const
{
	return available;
}

void MenuItem::setKind(string kind)
{
	this->kind= kind;
}

void MenuItem::setID(int id)
{
	this->id= id;
}

void MenuItem::setName(string newName)
{
	name= newName;
}

void MenuItem::setPrice(double newPrice)
{
	price= newPrice;
}

void MenuItem::setDescription(string newDescription)
{
	description= newDescription;
}

void MenuItem::setAvailable(bool available)
{
	this->available= available;
}

void MenuItem::setPrepTime(int minuts)
{
	preparationTime= minuts;
}

istream& operator >> (istream& input, MenuItem& item)
{
	item.readItem();
	return input;
}