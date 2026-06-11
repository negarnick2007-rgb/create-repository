#include <iostream>
#include <string>
#include "Address.h"
#include <limits>

using namespace std;

Address::Address() : city(""), street(""), placeNumber(0)
{}

void Address::printAddress() const
{
	cout << "Address of restaurant: " << endl;
	cout << city << ", " << street << ", " << placeNumber << endl;
}

istream& operator >> (istream& input, Address& add)
{
	input >> add.city >> add.street;
	while(!(input >> add.placeNumber)){
		cerr << "Please enter a numeric place number: ";
		input.clear();
		input.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return input; 
}

string Address::getCity() const
{
	return city;
}

string Address::getStreet() const
{
	return street;
}

void Address::setCity(string city)
{
	this->city= city;
}

void Address::setStreet(string street)
{
	this->street= street;
}

int Address::getPlaceNumber() const
{
	return placeNumber;
}

void Address::setPlaceNumber(int num)
{
	placeNumber= num;
}